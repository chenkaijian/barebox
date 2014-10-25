/*
 * Copyright (C) 2012 Juergen Beisert
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
 */

#ifndef __MACH_IOMUX_S3C64XX_H
# define __MACH_IOMUX_S3C64XX_H

/* 3322222222221111111111
 * 10987654321098765432109876543210
 *                           ^^^^^^_ Bit offset
 *                      ^^^^^_______ Group Number
 *                  ^^^^____________ Function
 *                 ^________________ initial GPIO out value
 *                ^_________________ Pull up/down feature present
 *              ^^__________________ initial pull up/down setting
 */

#define PIN(group,bit) ((group << 6) + bit)
#define FUNC(x) (((x) & 0xf) << 11)
#define GET_FUNC(x) (((x) >> 11) & 0xf)
#define GET_GROUP(x) (((x) >> 6) & 0x1f)
#define GET_BIT(x) ((x) & 0x3f)
#define GET_GPIOVAL(x) (!!((x) & (1 << 15)))
#define GPIO_OUT (1 << 11)
#define GPIO_IN (0 << 11)
#define GPIO_VAL(x) ((!!(x)) << 15)
#define PUD_MASK 0x3
#define PUD (1 << 16)
#define PUD_PRESENT(x) (!!((x) & (1 << 16)))
#define DISABLE_PUD (0 << 17)
#define ENABLE_PU (2 << 17)
#define ENABLE_PD (1 << 17)
#define GET_PUD(x) (((x) >> 17) & PUD_MASK)

/*
 * To have a chance for simple GPIO manipulation routines
 * define the GPIO numbers with a real simple scheme.
 *
 * Keep in mind: The 'GPIO_2_NO' creates a value to be used with the real gpio
 * routines and *not* for the multiplexer routines!
 */
#define GPIO_2_NO(x,y) (PIN(x,y))

/*
 * Group A: GPIO 0...7
 * Used GPIO: 0...7
 * These pins can also act as GPIO outputs
 */
#define GPA0		(PIN(0,0) | PUD)
#define GPA0_GPIO	(GPA0 | FUNC(0))
#define GPA0_RXD0	(GPA0 | FUNC(2))
#define GPA1		(PIN(0,4) | PUD)
#define GPA1_GPIO	(GPA1 | FUNC(0))
#define GPA1_TXD0	(GPA1 | FUNC(2))
#define GPA2		(PIN(0,8) | PUD)
#define GPA2_GPIO	(GPA2 | FUNC(0))
#define GPA2_NCTS0	(GPA2 | FUNC(2))
#define GPA3		(PIN(0,12) | PUD)
#define GPA3_GPIO	(GPA3 | FUNC(0))
#define GPA3_NRTS0	(GPA3 | FUNC(2))
#define GPA4		(PIN(0,16) | PUD)
#define GPA4_GPIO	(GPA4 | FUNC(0))
#define GPA4_RXD1	(GPA4 | FUNC(2))
#define GPA5		(PIN(0,20) | PUD)
#define GPA5_GPIO	(GPA5 | FUNC(0))
#define GPA5_TXD1	(GPA5 | FUNC(2))
#define GPA6		(PIN(0,24) | PUD)
#define GPA6_GPIO	(GPA6 | FUNC(0))
#define GPA6_NCTS1	(GPA6 | FUNC(2))
#define GPA7		(PIN(0,28) | PUD)
#define GPA7_GPIO	(GPA7 | FUNC(0))
#define GPA7_NRTS1	(GPA7 | FUNC(2))

/*
 * Group B: GPIO 0...7
 * Used GPIO: 8...15
 * These pins can also act as GPIO outputs
 */
#define GPB0		(PIN(1,0) | PUD)
#define GPB0_GPIO	(GPB0 | FUNC(0))
#define GPB0_RXD2	(GPB0 | FUNC(2))
#define GPB0_DMAREQ	(GPB0 | FUNC(3))
#define GPB0_IRDA_RXD	(GPB0 | FUNC(4))
#define GPB0_ADDR_CF0	(GPB0 | FUNC(5))
#define GPB1		(PIN(1,4) | PUD)
#define GPB1_GPIO	(GPB1 | FUNC(0))
#define GPB1_TXD2	(GPB1 | FUNC(2))
#define GPB1_DMAREQ	(GPB1 | FUNC(3))
#define GPB1_IRDA_TXD	(GPB1 | FUNC(4))
#define GPB1_ADDR_CF1	(GPB1 | FUNC(5))
#define GPB2		(PIN(1,8) | PUD)
#define GPB2_GPIO	(GPB2 | FUNC(0))
#define GPB2_RXD3	(GPB2 | FUNC(2))
#define GPB2_IRDA_RXD	(GPB2 | FUNC(3))
#define GPB2_DMAREQ	(GPB2 | FUNC(4))
#define GPB2_ADDR_CF2	(GPB2 | FUNC(5))
#define GPB2_IIC1_SCL	(GPB2 | FUNC(6))
#define GPB3		(PIN(1,12) | PUD)
#define GPB3_GPIO	(GPB3 | FUNC(0))
#define GPB3_TXD3	(GPB3 | FUNC(2))
#define GPB3_IRDA_TXD	(GPB3 | FUNC(3))
#define GPB3_DMAREQ	(GPB3 | FUNC(4))
#define GPB3_IIC1_SDA	(GPB3 | FUNC(6))
#define GPB4		(PIN(1,16) | PUD)
#define GPB4_GPIO	(GPB4 | FUNC(0))
#define GPB4_SDBW	(GPB4 | FUNC(2))
#define GPB4_CAM_FLD	(GPB4 | FUNC(3))
#define GPB4_CF_DIR	(GPB4 | FUNC(4))
#define GPB5		(PIN(1,20) | PUD)
#define GPB5_GPIO	(GPB5 | FUNC(0))
#define GPB5_IIC0_SCL	(GPB5 | FUNC(2))
#define GPB6		(PIN(1,24) | PUD)
#define GPB6_GPIO	(GPB6 | FUNC(0))
#define GPB6_IIC0_SDA	(GPB6 | FUNC(2))

#define GPC0		(PIN(2,0) | PUD)
#define GPC0_GPIO	(GPC0 | FUNC(0))
#define GPC0_SPI0_MISO	(GPC0 | FUNC(2))
#define GPC1		(PIN(2,4) | PUD)
#define GPC1_GPIO	(GPC1 | FUNC(0))
#define GPC1_SPI0_CLK	(GPC1 | FUNC(2))
#define GPC2		(PIN(2,8) | PUD)
#define GPC2_GPIO	(GPC2 | FUNC(0))
#define GPC2_SPI0_MOSI	(GPC2 | FUNC(2))
#define GPC3		(PIN(2,12) | PUD)
#define GPC3_GPIO	(GPC3 | FUNC(0))
#define GPC3_SPI0_NCS	(GPC3 | FUNC(2))
#define GPC4		(PIN(2,16) | PUD)
#define GPC4_GPIO	(GPC4 | FUNC(0))
#define GPC4_SPI1_MISO	(GPC4 | FUNC(2))
#define GPC5		(PIN(2,20) | PUD)
#define GPC5_GPIO	(GPC5 | FUNC(0))
#define GPC5_SPI1_CLK	(GPC5 | FUNC(2))
#define GPC6		(PIN(2,24) | PUD)
#define GPC6_GPIO	(GPC6 | FUNC(0))
#define GPC6_SPI1_MOSI	(GPC6 | FUNC(2))
#define GPC7		(PIN(2,28) | PUD)
#define GPC7_GPIO	(GPC7 | FUNC(0))
#define GPC7_SPI1_NCS	(GPC7 | FUNC(2))

#define GPD0		(PIN(3,0) | PUD)
#define GPD0_AC97_BITCLK (GPD0 | FUNC(4))
#define GPD1		(PIN(3,4) | PUD)
#define GPD1_AC97_NRST	(GPD1 | FUNC(4))
#define GPD2		(PIN(3,8) | PUD)
#define GPD2_AC97_SYNC	(GPD2 | FUNC(4))
#define GPD3		(PIN(3,12) | PUD)
#define GPD3_AC97_SDI	(GPD3 | FUNC(4))
#define GPD4		(PIN(3,16) | PUD)
#define GPD4_AC97_SDO	(GPD4 | FUNC(4))

#define GPE0		(PIN(4,0) | PUD)
#define GPE0_GPIO	(GPE0 | FUNC(0))
#define GPE1		(PIN(4,4) | PUD)
#define GPE1_GPIO	(GPE1 | FUNC(0))
#define GPE2		(PIN(4,8) | PUD)
#define GPE2_GPIO	(GPE2 | FUNC(0))
#define GPE3		(PIN(4,12) | PUD)
#define GPE3_GPIO	(GPE3 | FUNC(0))
#define GPE4		(PIN(4,16) | PUD)
#define GPE4_GPIO	(GPE4 | FUNC(0))

#define GPF0		(PIN(5,0) | PUD)
#define GPF0_GPIO	(GPF0 | FUNC(0))
#define GPF1		(PIN(5,2) | PUD)
#define GPF1_GPIO	(GPF1 | FUNC(0))
#define GPF2		(PIN(5,4) | PUD)
#define GPF2_GPIO	(GPF2 | FUNC(0))
#define GPF3		(PIN(5,6) | PUD)
#define GPF3_GPIO	(GPF3 | FUNC(0))
#define GPF4		(PIN(5,8) | PUD)
#define GPF4_GPIO	(GPF4 | FUNC(0))
#define GPF5		(PIN(5,10) | PUD)
#define GPF5_GPIO	(GPF5 | FUNC(0))
#define GPF6		(PIN(5,12) | PUD)
#define GPF6_GPIO	(GPF6 | FUNC(0))
#define GPF7		(PIN(5,14) | PUD)
#define GPF7_GPIO	(GPF7 | FUNC(0))
#define GPF8		(PIN(5,16) | PUD)
#define GPF8_GPIO	(GPF8 | FUNC(0))
#define GPF9		(PIN(5,18) | PUD)
#define GPF9_GPIO	(GPF9 | FUNC(0))
#define GPF10		(PIN(5,20) | PUD)
#define GPF10_GPIO	(GPF10 | FUNC(0))
#define GPF11		(PIN(5,22) | PUD)
#define GPF11_GPIO	(GPF11 | FUNC(0))
#define GPF12		(PIN(5,24) | PUD)
#define GPF12_GPIO	(GPF12 | FUNC(0))
#define GPF13		(PIN(5,26) | PUD)
#define GPF13_GPIO	(GPF13 | FUNC(0))
#define GPF14		(PIN(5,28) | PUD)
#define GPF14_GPIO	(GPF14 | FUNC(0))
#define GPF14_PWM0	(GPF14 | FUNC(2))
#define GPF14_CLKOUT	(GPF14 | FUNC(3))
#define GPF15		(PIN(5,30) | PUD)
#define GPF15_GPIO	(GPF15 | FUNC(0))
#define GPF15_PWM1	(GPF15 | FUNC(2))

#define GPG0		(PIN(6,0) | PUD)
#define GPG0_MMC0_CLK	(GPG0 | FUNC(2))
#define GPG1		(PIN(6,4) | PUD)
#define GPG1_MMC0_CMD	(GPG1 | FUNC(2))
#define GPG2		(PIN(6,8) | PUD)
#define GPG2_MMC0_DAT0	(GPG2 | FUNC(2))
#define GPG3		(PIN(6,12) | PUD)
#define GPG3_MMC0_DAT1	(GPG3 | FUNC(2))
#define GPG4		(PIN(6,16) | PUD)
#define GPG4_MMC0_DAT2	(GPG4 | FUNC(2))
#define GPG5		(PIN(6,20) | PUD)
#define GPG5_MMC0_DAT3	(GPG5 | FUNC(2))
#define GPG6		(PIN(6,24) | PUD)
#define GPG6_MMC0_NCD	(GPG6 | FUNC(2))

#define GPH0		(PIN(7,0) | PUD)
#define GPH0_GPIO	(GPH0 | FUNC(0))
#define GPH1		(PIN(7,4) | PUD)
#define GPH1_GPIO	(GPH1 | FUNC(0))
#define GPH2		(PIN(7,8) | PUD)
#define GPH2_GPIO	(GPH2 | FUNC(0))
#define GPH3		(PIN(7,12) | PUD)
#define GPH3_GPIO	(GPH3 | FUNC(0))
#define GPH4		(PIN(7,16) | PUD)
#define GPH4_GPIO	(GPH4 | FUNC(0))
#define GPH5		(PIN(7,20) | PUD)
#define GPH5_GPIO	(GPH5 | FUNC(0))
#define GPH6		(PIN(7,24) | PUD)
#define GPH6_GPIO	(GPH6 | FUNC(0))
#define GPH7		(PIN(7,28) | PUD)
#define GPH7_GPIO	(GPH7 | FUNC(0))
#define GPH8		(PIN(7,32) | PUD)
#define GPH8_GPIO	(GPH8 | FUNC(0))
#define GPH9		(PIN(7,36) | PUD)
#define GPH9_GPIO	(GPH9 | FUNC(0))

#define GPI0		(PIN(8,0) | PUD)
#define GPI0_GPIO	(GPI0 | FUNC(0))
#define GPI1		(PIN(8,2) | PUD)
#define GPI1_GPIO	(GPI1 | FUNC(0))
#define GPI2		(PIN(8,4) | PUD)
#define GPI2_GPIO	(GPI2 | FUNC(0))
#define GPI3		(PIN(8,6) | PUD)
#define GPI3_GPIO	(GPI3 | FUNC(0))
#define GPI4		(PIN(8,8) | PUD)
#define GPI4_GPIO	(GPI4 | FUNC(0))
#define GPI5		(PIN(8,10) | PUD)
#define GPI5_GPIO	(GPI5 | FUNC(0))
#define GPI6		(PIN(8,12) | PUD)
#define GPI6_GPIO	(GPI6 | FUNC(0))
#define GPI7		(PIN(8,14) | PUD)
#define GPI7_GPIO	(GPI7 | FUNC(0))
#define GPI8		(PIN(8,16) | PUD)
#define GPI8_GPIO	(GPI8 | FUNC(0))
#define GPI9		(PIN(8,18) | PUD)
#define GPI9_GPIO	(GPI9 | FUNC(0))
#define GPI10		(PIN(8,20) | PUD)
#define GPI10_GPIO	(GPI10 | FUNC(0))
#define GPI11		(PIN(8,22) | PUD)
#define GPI11_GPIO	(GPI11 | FUNC(0))
#define GPI12		(PIN(8,24) | PUD)
#define GPI12_GPIO	(GPI12 | FUNC(0))
#define GPI13		(PIN(8,26) | PUD)
#define GPI13_GPIO	(GPI13 | FUNC(0))
#define GPI14		(PIN(8,28) | PUD)
#define GPI14_GPIO	(GPI14 | FUNC(0))
#define GPI15		(PIN(8,30) | PUD)
#define GPI15_GPIO	(GPI15 | FUNC(0))

#define GPJ0		(PIN(9,0) | PUD)
#define GPJ0_GPIO	(GPJ0 | FUNC(0))
#define GPJ1		(PIN(9,2) | PUD)
#define GPJ1_GPIO	(GPJ1 | FUNC(0))
#define GPJ2		(PIN(9,4) | PUD)
#define GPJ2_GPIO	(GPJ2 | FUNC(0))
#define GPJ3		(PIN(9,6) | PUD)
#define GPJ3_GPIO	(GPJ3 | FUNC(0))
#define GPJ4		(PIN(9,8) | PUD)
#define GPJ4_GPIO	(GPJ4 | FUNC(0))
#define GPJ5		(PIN(9,10) | PUD)
#define GPJ5_GPIO	(GPJ5 | FUNC(0))
#define GPJ6		(PIN(9,12) | PUD)
#define GPJ6_GPIO	(GPJ6 | FUNC(0))
#define GPJ7		(PIN(9,14) | PUD)
#define GPJ7_GPIO	(GPJ7 | FUNC(0))
#define GPJ8		(PIN(9,16) | PUD)
#define GPJ8_GPIO	(GPJ8 | FUNC(0))
#define GPJ9		(PIN(9,18) | PUD)
#define GPJ9_GPIO	(GPJ9 | FUNC(0))
#define GPJ10		(PIN(9,20) | PUD)
#define GPJ10_GPIO	(GPJ10 | FUNC(0))
#define GPJ11		(PIN(9,22) | PUD)
#define GPJ11_GPIO	(GPJ11 | FUNC(0))

#define GPK0		(PIN(10,0) | PUD)
#define GPK0_DATA0	(GPK0 | FUNC(2))
#define GPK0_GPIO	(GPK0 | FUNC(0))
#define GPK1		(PIN(10,4) | PUD)
#define GPK1_DATA1	(GPK1 | FUNC(2))
#define GPK1_GPIO	(GPK1 | FUNC(0))
#define GPK2		(PIN(10,8) | PUD)
#define GPK2_DATA2	(GPK2 | FUNC(2))
#define GPK2_GPIO	(GPK2 | FUNC(0))
#define GPK3		(PIN(10,12) | PUD)
#define GPK3_DATA3	(GPK3 | FUNC(2))
#define GPK3_GPIO	(GPK3 | FUNC(0))
#define GPK4		(PIN(10,16) | PUD)
#define GPK4_DATA4	(GPK4 | FUNC(2))
#define GPK4_GPIO	(GPK4 | FUNC(0))
#define GPK5		(PIN(10,20) | PUD)
#define GPK5_DATA5	(GPK5 | FUNC(2))
#define GPK5_GPIO	(GPK5 | FUNC(0))
#define GPK6		(PIN(10,24) | PUD)
#define GPK6_DATA6	(GPK6 | FUNC(2))
#define GPK6_GPIO	(GPK6 | FUNC(0))
#define GPK7		(PIN(10,28) | PUD)
#define GPK7_DATA7	(GPK7 | FUNC(2))
#define GPK7_GPIO	(GPK7 | FUNC(0))
#define GPK8		(PIN(10,32) | PUD)
#define GPK8_DATA8	(GPK8 | FUNC(2))
#define GPK8_GPIO	(GPK8 | FUNC(0))
#define GPK9		(PIN(10,36) | PUD)
#define GPK9_DATA9	(GPK9 | FUNC(2))
#define GPK9_GPIO	(GPK9 | FUNC(0))
#define GPK10		(PIN(10,40) | PUD)
#define GPK10_DATA10	(GPK10 | FUNC(2))
#define GPK10_GPIO	(GPK10 | FUNC(0))
#define GPK11		(PIN(10,44) | PUD)
#define GPK11_DATA11	(GPK11 | FUNC(2))
#define GPK11_GPIO	(GPK11 | FUNC(0))
#define GPK12		(PIN(10,48) | PUD)
#define GPK12_DATA12	(GPK12 | FUNC(2))
#define GPK12_GPIO	(GPK12 | FUNC(0))
#define GPK13		(PIN(10,52) | PUD)
#define GPK13_DATA13	(GPK13 | FUNC(2))
#define GPK13_GPIO	(GPK13 | FUNC(0))
#define GPK14		(PIN(10,56) | PUD)
#define GPK14_DATA14	(GPK14 | FUNC(2))
#define GPK14_GPIO	(GPK14 | FUNC(0))
#define GPK15		(PIN(10,60) | PUD)
#define GPK15_DATA15	(GPK15 | FUNC(2))
#define GPK15_GPIO	(GPK15 | FUNC(0))

#define GPL0		(PIN(11,0) | PUD)
#define GPL0_ADDR0	(GPL0 | FUNC(2))
#define GPL0_GPIO	(GPL0 | FUNC(0))
#define GPL1		(PIN(11,4) | PUD)
#define GPL1_ADDR1	(GPL1 | FUNC(2))
#define GPL1_GPIO	(GPL1 | FUNC(0))
#define GPL2		(PIN(11,8) | PUD)
#define GPL2_ADDR2	(GPL2 | FUNC(2))
#define GPL2_GPIO	(GPL2 | FUNC(0))
#define GPL3		(PIN(11,12) | PUD)
#define GPL3_ADDR3	(GPL3 | FUNC(2))
#define GPL3_GPIO	(GPL3 | FUNC(0))
#define GPL4		(PIN(11,16) | PUD)
#define GPL4_ADDR3	(GPL4 | FUNC(2))
#define GPL4_GPIO	(GPL4 | FUNC(0))
#define GPL5		(PIN(11,20) | PUD)
#define GPL5_ADDR3	(GPL5 | FUNC(2))
#define GPL5_GPIO	(GPL5 | FUNC(0))
#define GPL6		(PIN(11,24) | PUD)
#define GPL6_ADDR3	(GPL6 | FUNC(2))
#define GPL6_GPIO	(GPL6 | FUNC(0))
#define GPL7		(PIN(11,28) | PUD)
#define GPL7_ADDR3	(GPL7 | FUNC(2))
#define GPL7_GPIO	(GPL7 | FUNC(0))
#define GPL8		(PIN(11,32) | PUD)
#define GPL8_ADDR3	(GPL8 | FUNC(2))
#define GPL8_GPIO	(GPL8 | FUNC(0))
#define GPL9		(PIN(11,36) | PUD)
#define GPL9_ADDR3	(GPL9 | FUNC(2))
#define GPL9_GPIO	(GPL9 | FUNC(0))
#define GPL10		(PIN(11,40) | PUD)
#define GPL10_ADDR3	(GPL10 | FUNC(2))
#define GPL10_GPIO	(GPL10 | FUNC(0))
#define GPL11		(PIN(11,44) | PUD)
#define GPL11_ADDR3	(GPL11 | FUNC(2))
#define GPL11_GPIO	(GPL11 | FUNC(0))
#define GPL12		(PIN(11,48) | PUD)
#define GPL12_ADDR3	(GPL12 | FUNC(2))
#define GPL12_GPIO	(GPL12 | FUNC(0))
#define GPL13		(PIN(11,52) | PUD)
#define GPL13_ADDR16	(GPL13 | FUNC(2))
#define GPL13_GPIO	(GPL13 | FUNC(0))
#define GPL14		(PIN(11,65) | PUD)
#define GPL14_ADDR17	(GPL14 | FUNC(2))
#define GPL14_GPIO	(GPL14 | FUNC(0))

#define GPM0		(PIN(12,0) | PUD)
#define GPM0_GPIO	(GPM0 | FUNC(0))
#define GPM1		(PIN(12,4) | PUD)
#define GPM1_GPIO	(GPM1 | FUNC(0))
#define GPM2		(PIN(12,8) | PUD)
#define GPM2_GPIO	(GPM2 | FUNC(0))
#define GPM3		(PIN(12,12) | PUD)
#define GPM3_GPIO	(GPM3 | FUNC(0))
#define GPM4		(PIN(12,16) | PUD)
#define GPM4_GPIO	(GPM4 | FUNC(0))
#define GPM5		(PIN(12,20) | PUD)
#define GPM5_GPIO	(GPM5 | FUNC(0))

#define GPN0		(PIN(13,0) | PUD)
#define GPN0_GPIO	(GPN0 | FUNC(0))
#define GPN1		(PIN(13,0) | PUD)
#define GPN1_GPIO	(GPN1 | FUNC(0))
#define GPN2		(PIN(13,0) | PUD)
#define GPN2_GPIO	(GPN2 | FUNC(0))
#define GPN3		(PIN(13,0) | PUD)
#define GPN3_GPIO	(GPN3 | FUNC(0))
#define GPN4		(PIN(13,0) | PUD)
#define GPN4_GPIO	(GPN4 | FUNC(0))
#define GPN5		(PIN(13,0) | PUD)
#define GPN5_GPIO	(GPN5 | FUNC(0))
#define GPN6		(PIN(13,0) | PUD)
#define GPN6_GPIO	(GPN6 | FUNC(0))
#define GPN7		(PIN(13,0) | PUD)
#define GPN7_GPIO	(GPN7 | FUNC(0))
#define GPN8		(PIN(13,0) | PUD)
#define GPN8_GPIO	(GPN8 | FUNC(0))
#define GPN9		(PIN(13,0) | PUD)
#define GPN9_GPIO	(GPN9 | FUNC(0))
#define GPN10		(PIN(13,20) | PUD)
#define GPN10_GPIO	(GPN10 | FUNC(0))
#define GPN11		(PIN(13,20) | PUD)
#define GPN11_GPIO	(GPN11 | FUNC(0))
#define GPN12		(PIN(13,20) | PUD)
#define GPN12_GPIO	(GPN12 | FUNC(0))
#define GPN13		(PIN(13,20) | PUD)
#define GPN13_GPIO	(GPN13 | FUNC(0))
#define GPN14		(PIN(13,20) | PUD)
#define GPN14_GPIO	(GPN14 | FUNC(0))
#define GPN15		(PIN(13,20) | PUD)
#define GPN15_GPIO	(GPN15 | FUNC(0))

#define GPO0		(PIN(14,0) | PUD)
#define GPO0_GPIO	(GPO0 | FUNC(0))
#define GPO0_NCS2	(GPO0 | FUNC(2))
#define GPO1		(PIN(14,2) | PUD)
#define GPO1_GPIO	(GPO1 | FUNC(0))
#define GPO1_NCS3	(GPO1 | FUNC(2))
#define GPO2		(PIN(14,4) | PUD)
#define GPO2_GPIO	(GPO2 | FUNC(0))
#define GPO2_NCS4	(GPO2 | FUNC(2))
#define GPO3		(PIN(14,6) | PUD)
#define GPO3_GPIO	(GPO3 | FUNC(0))
#define GPO3_NCS5	(GPO3 | FUNC(2))
#define GPO4		(PIN(14,8) | PUD)
#define GPO4_GPIO	(GPO4 | FUNC(0))
#define GPO5		(PIN(14,10) | PUD)
#define GPO5_GPIO	(GPO5 | FUNC(0))
#define GPO6		(PIN(14,12) | PUD)
#define GPO6_GPIO	(GPO6 | FUNC(0))
#define GPO6_ADDR6	(GPO6 | FUNC(2))
#define GPO7		(PIN(14,14) | PUD)
#define GPO7_GPIO	(GPO7 | FUNC(0))
#define GPO7_ADDR7	(GPO7 | FUNC(2))
#define GPO8		(PIN(14,16) | PUD)
#define GPO8_GPIO	(GPO8 | FUNC(0))
#define GPO8_ADDR8	(GPO8 | FUNC(2))
#define GPO9		(PIN(14,18) | PUD)
#define GPO9_GPIO	(GPO9 | FUNC(0))
#define GPO9_ADDR9	(GPO9 | FUNC(2))
#define GPO10		(PIN(14,20) | PUD)
#define GPO10_GPIO	(GPO10 | FUNC(2))
#define GPO10_ADDR10	(GPO10 | FUNC(2))
#define GPO11		(PIN(14,22) | PUD)
#define GPO11_GPIO	(GPO11 | FUNC(0))
#define GPO11_ADDR11	(GPO11 | FUNC(2))
#define GPO12		(PIN(14,24) | PUD)
#define GPO12_GPIO	(GPO12 | FUNC(0))
#define GPO12_ADDR12	(GPO12 | FUNC(2))
#define GPO13		(PIN(14,26) | PUD)
#define GPO13_GPIO	(GPO13 | FUNC(0))
#define GPO13_ADDR13	(GPO13 | FUNC(2))
#define GPO14		(PIN(14,28) | PUD)
#define GPO14_GPIO	(GPO14 | FUNC(0))
#define GPO14_ADDR14	(GPO14 | FUNC(2))
#define GPO15		(PIN(14,30) | PUD)
#define GPO15_GPIO	(GPO15 | FUNC(0))
#define GPO15_ADDR15	(GPO15 | FUNC(2))

#define GPP0		(PIN(15,0) | PUD)
#define GPP0_GPIO	(GPP0 | FUNC(0))
#define GPP1		(PIN(15,2) | PUD)
#define GPP1_GPIO	(GPP1 | FUNC(0))
#define GPP2		(PIN(15,4) | PUD)
#define GPP2_NWAIT	(GPP2 | FUNC(2))
#define GPP3		(PIN(15,6) | PUD)
#define GPP3_FALE	(GPP3 | FUNC(2))
#define GPP4		(PIN(15,8) | PUD)
#define GPP4_FCLE	(GPP4 | FUNC(2))
#define GPP5		(PIN(15,10) | PUD)
#define GPP5_FWE	(GPP5 | FUNC(2))
#define GPP6		(PIN(15,12) | PUD)
#define GPP6_FRE	(GPP6 | FUNC(2))
#define GPP7		(PIN(15,14) | PUD)
#define GPP7_RNB	(GPP7 | FUNC(2))
#define GPP8		(PIN(15,16) | PUD)
#define GPP8_GPIO	(GPP8 | FUNC(0))
#define GPP9		(PIN(15,18) | PUD)
#define GPP9_GPIO	(GPP9 | FUNC(0))
#define GPP10		(PIN(15,20) | PUD)
#define GPP10_GPIO	(GPP10 | FUNC(0))
#define GPP11		(PIN(15,22) | PUD)
#define GPP11_GPIO	(GPP11 | FUNC(0))
#define GPP12		(PIN(15,24) | PUD)
#define GPP12_GPIO	(GPP12 | FUNC(0))
#define GPP13		(PIN(15,26) | PUD)
#define GPP13_GPIO	(GPP13 | FUNC(0))
#define GPP14		(PIN(15,28) | PUD)
#define GPP14_GPIO	(GPP14 | FUNC(0))

#define GPQ0		(PIN(16,0) | PUD)
#define GPQ0_GPIO	(GPQ0 | FUNC(0))
#define GPQ1		(PIN(16,2) | PUD)
#define GPQ1_GPIO	(GPQ1 | FUNC(0))
#define GPQ2		(PIN(16,4) | PUD)
#define GPQ2_GPIO	(GPQ2 | FUNC(0))
#define GPQ3		(PIN(16,8) | PUD)
#define GPQ3_GPIO	(GPQ3 | FUNC(0))
#define GPQ4		(PIN(16,8) | PUD)
#define GPQ4_GPIO	(GPQ4 | FUNC(0))
#define GPQ5		(PIN(16,10) | PUD)
#define GPQ5_GPIO	(GPQ5 | FUNC(0))
#define GPQ6		(PIN(16,12) | PUD)
#define GPQ6_GPIO	(GPQ6 | FUNC(0))
#define GPQ7		(PIN(16,14) | PUD)
#define GPQ7_GPIO	(GPQ7 | FUNC(0))
#define GPQ8		(PIN(16,16) | PUD)
#define GPQ8_GPIO	(GPQ7 | FUNC(0))


#endif /* __MACH_IOMUX_S3C64XX_H */
