/**
 * @file
 * @brief NS16550 Driver implementation
 *
 * FileName: drivers/serial/serial_ns16550.c
 *
 * NS16550 support
 * Modified from u-boot drivers/serial.c and drivers/ns16550.c
 * originally from linux source (arch/ppc/boot/ns16550.c)
 * modified to use CFG_ISA_MEM and new defines
 */
/*
 * (C) Copyright 2008
 * Texas Instruments, <www.ti.com>
 * Nishanth Menon <x0nishan@ti.com>
 *
 * (C) Copyright 2000
 * Rob Taylor, Flying Pig Systems. robt@flyingpig.com.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <common.h>
#include <driver.h>
#include <init.h>
#include <errno.h>
#include <malloc.h>
#include <io.h>
#include <linux/clk.h>

#include "serial_ns16550.h"
#include <ns16550.h>

struct ns16550_priv {
	struct console_device cdev;
	struct NS16550_plat plat;
	int access_width;
	struct clk *clk;
	uint32_t fcrval;
};

static inline struct ns16550_priv *to_ns16550_priv(struct console_device *cdev)
{
	return container_of(cdev, struct ns16550_priv, cdev);
}

struct ns16550_drvdata {
	void (*init_port)(struct console_device *cdev);
	const char *linux_console_name;
};

/**
 * @brief read register
 *
 * @param[in] cdev pointer to console device
 * @param[in] offset
 *
 * @return value
 */
static uint32_t ns16550_read(struct console_device *cdev, uint32_t off)
{
	struct ns16550_priv *priv = to_ns16550_priv(cdev);
	struct device_d *dev = cdev->dev;
	struct NS16550_plat *plat = &priv->plat;
	int width = priv->access_width;

	off <<= plat->shift;

	if (plat->reg_read)
		return plat->reg_read((unsigned long)dev->priv, off);

	switch (width) {
	case IORESOURCE_MEM_8BIT:
		return readb(dev->priv + off);
	case IORESOURCE_MEM_16BIT:
		return readw(dev->priv + off);
	case IORESOURCE_MEM_32BIT:
		return readl(dev->priv + off);
	}
	return -1;
}

/**
 * @brief write register
 *
 * @param[in] cdev pointer to console device
 * @param[in] offset
 * @param[in] val
 */
static void ns16550_write(struct console_device *cdev, uint32_t val,
			  uint32_t off)
{
	struct ns16550_priv *priv = to_ns16550_priv(cdev);
	struct device_d *dev = cdev->dev;
	struct NS16550_plat *plat = &priv->plat;
	int width = priv->access_width;

	off <<= plat->shift;

	if (plat->reg_write) {
		plat->reg_write(val, (unsigned long)dev->priv, off);
		return;
	}

	switch (width) {
	case IORESOURCE_MEM_8BIT:
		writeb(val & 0xff, dev->priv + off);
		break;
	case IORESOURCE_MEM_16BIT:
		writew(val & 0xffff, dev->priv + off);
		break;
	case IORESOURCE_MEM_32BIT:
		writel(val, dev->priv + off);
		break;
	}
}

/**
 * @brief Compute the divisor for a baud rate
 *
 * @param[in] cdev pointer to console device
 * @param[in] baudrate baud rate
 *
 * @return divisor to be set
 */
static inline unsigned int ns16550_calc_divisor(struct console_device *cdev,
					 unsigned int baudrate)
{
	struct ns16550_priv *priv = to_ns16550_priv(cdev);
	struct NS16550_plat *plat = &priv->plat;
	unsigned int clk = plat->clock;

	return (clk / MODE_X_DIV / baudrate);

}

/**
 * @brief Set the baudrate for the uart port
 *
 * @param[in] cdev  console device
 * @param[in] baud_rate baud rate to set
 *
 * @return  0-implied to support the baudrate
 */
static int ns16550_setbaudrate(struct console_device *cdev, int baud_rate)
{
	unsigned int baud_divisor = ns16550_calc_divisor(cdev, baud_rate);
	struct ns16550_priv *priv = to_ns16550_priv(cdev);

	ns16550_write(cdev, LCR_BKSE, lcr);
	ns16550_write(cdev, baud_divisor & 0xff, dll);
	ns16550_write(cdev, (baud_divisor >> 8) & 0xff, dlm);
	ns16550_write(cdev, LCRVAL, lcr);
	ns16550_write(cdev, MCRVAL, mcr);
	ns16550_write(cdev, priv->fcrval, fcr);

	return 0;
}

/**
 * @brief Initialize the device
 *
 * @param[in] cdev pointer to console device
 */
static void ns16550_serial_init_port(struct console_device *cdev)
{
	/* initializing the device for the first time */
	ns16550_write(cdev, 0x00, lcr); /* select ier reg */
	ns16550_write(cdev, 0x00, ier);
}

static void ns16450_serial_init_port(struct console_device *cdev)
{
	struct ns16550_priv *priv = to_ns16550_priv(cdev);

	priv->fcrval &= ~FCR_FIFO_EN;

	ns16550_serial_init_port(cdev);
}

#define omap_mdr1		8

static void ns16550_omap_init_port(struct console_device *cdev)
{
	ns16550_serial_init_port(cdev);

	ns16550_write(cdev, 0x07, omap_mdr1);	/* Disable */
	ns16550_write(cdev, 0x00, omap_mdr1);
}

#define JZ_FCR_UME 0x10 /* Uart Module Enable */

static void ns16550_jz_init_port(struct console_device *cdev)
{
	struct ns16550_priv *priv = to_ns16550_priv(cdev);

	priv->fcrval |= JZ_FCR_UME;
	ns16550_serial_init_port(cdev);
}

/*********** Exposed Functions **********************************/

/**
 * @brief Put a character to the serial port
 *
 * @param[in] cdev pointer to console device
 * @param[in] c character to put
 */
static void ns16550_putc(struct console_device *cdev, char c)
{
	/* Loop Doing Nothing */
	while ((ns16550_read(cdev, lsr) & LSR_THRE) == 0) ;
	ns16550_write(cdev, c, thr);
}

/**
 * @brief Retrieve a character from serial port
 *
 * @param[in] cdev pointer to console device
 *
 * @return return the character read
 */
static int ns16550_getc(struct console_device *cdev)
{
	/* Loop Doing Nothing */
	while ((ns16550_read(cdev, lsr) & LSR_DR) == 0) ;
	return ns16550_read(cdev, rbr);
}

/**
 * @brief Test if character is available
 *
 * @param[in] cdev pointer to console device
 *
 * @return  - status based on data availability
 */
static int ns16550_tstc(struct console_device *cdev)
{
	return ((ns16550_read(cdev, lsr) & LSR_DR) != 0);
}

static void ns16550_probe_dt(struct device_d *dev, struct ns16550_priv *priv)
{
	struct device_node *np = dev->device_node;

	if (!IS_ENABLED(CONFIG_OFDEVICE))
		return;

	of_property_read_u32(np, "reg-shift", &priv->plat.shift);
}

static struct ns16550_drvdata ns16450_drvdata = {
	.init_port = ns16450_serial_init_port,
};

static struct ns16550_drvdata ns16550_drvdata = {
	.init_port = ns16550_serial_init_port,
};

static __maybe_unused struct ns16550_drvdata omap_drvdata = {
	.init_port = ns16550_omap_init_port,
	.linux_console_name = "ttyO",
};

static __maybe_unused struct ns16550_drvdata jz_drvdata = {
	.init_port = ns16550_jz_init_port,
};

/**
 * @brief Probe entry point -called on the first match for device
 *
 * @param[in] dev matched device
 *
 * @return EINVAL if platform_data is not populated,
 *	   ENOMEM if calloc failed
 *	   else return result of console_register
 */
static int ns16550_probe(struct device_d *dev)
{
	struct ns16550_priv *priv;
	struct console_device *cdev;
	struct NS16550_plat *plat = (struct NS16550_plat *)dev->platform_data;
	struct ns16550_drvdata *devtype;
	int ret;

	ret = dev_get_drvdata(dev, (unsigned long *)&devtype);
	if (ret)
		devtype = &ns16550_drvdata;

	dev->priv = dev_request_mem_region(dev, 0);

	priv = xzalloc(sizeof(*priv));

	if (plat)
		priv->plat = *plat;
	else
		ns16550_probe_dt(dev, priv);

	if (!plat || !plat->clock) {
		priv->clk = clk_get(dev, NULL);
		if (IS_ERR(priv->clk)) {
			ret = PTR_ERR(priv->clk);
			goto err;
		}
		priv->plat.clock = clk_get_rate(priv->clk);
	}

	if (priv->plat.clock == 0 && IS_ENABLED(CONFIG_OFDEVICE)) {
		struct device_node *np = dev->device_node;

		of_property_read_u32(np, "clock-frequency", &priv->plat.clock);
	}

	if (priv->plat.clock == 0) {
		dev_err(dev, "no valid clockrate\n");
		ret = -EINVAL;
		goto err;
	}

	priv->access_width = dev->resource[0].flags & IORESOURCE_MEM_TYPE_MASK;

	cdev = &priv->cdev;
	cdev->dev = dev;
	cdev->tstc = ns16550_tstc;
	cdev->putc = ns16550_putc;
	cdev->getc = ns16550_getc;
	cdev->setbrg = ns16550_setbaudrate;
	cdev->linux_console_name = devtype->linux_console_name;

	if (plat && (plat->flags & NS16650_FLAG_DISABLE_FIFO))
		priv->fcrval = FCRVAL & ~FCR_FIFO_EN;
	else
		priv->fcrval = FCRVAL;

	devtype->init_port(cdev);

	return console_register(cdev);

err:
	free(priv);

	return ret;
}

static struct of_device_id ns16550_serial_dt_ids[] = {
	{
		.compatible = "ns16450",
		.data = (unsigned long)&ns16450_drvdata,
	}, {
		.compatible = "ns16550a",
		.data = (unsigned long)&ns16550_drvdata,
	}, {
		.compatible = "snps,dw-apb-uart",
		.data = (unsigned long)&ns16550_drvdata,
	},
#if IS_ENABLED(CONFIG_ARCH_OMAP)
	{
		.compatible = "ti,omap2-uart",
		.data = (unsigned long)&omap_drvdata,
	}, {
		.compatible = "ti,omap3-uart",
		.data = (unsigned long)&omap_drvdata,
	}, {
		.compatible = "ti,omap4-uart",
		.data = (unsigned long)&omap_drvdata,
	},
#endif
#if IS_ENABLED(CONFIG_MACH_MIPS_XBURST)
	{
		.compatible = "ingenic,jz4740-uart",
		.data = (unsigned long)&jz_drvdata,
	},
#endif
	{
		/* sentinel */
	},
};

static __maybe_unused struct platform_device_id ns16550_serial_ids[] = {
	{
		.name = "omap-uart",
		.driver_data = (unsigned long)&omap_drvdata,
	}, {
		/* sentinel */
	},
};

/**
 * @brief Driver registration structure
 */
static struct driver_d ns16550_serial_driver = {
	.name = "ns16550_serial",
	.probe = ns16550_probe,
	.of_compatible = DRV_OF_COMPAT(ns16550_serial_dt_ids),
#if IS_ENABLED(CONFIG_ARCH_OMAP)
	.id_table = ns16550_serial_ids,
#endif
};
console_platform_driver(ns16550_serial_driver);
