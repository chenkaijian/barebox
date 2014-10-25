/*
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>

/* decode S[0-2] to Output Divider (OD) */
static u8 ics307_s_to_od[] = {
	10, 2, 8, 4, 5, 7, 3, 6
};

/* Calculate frequency being generated by ICS307-02 clock chip. */
unsigned long ics307_clk_freq(unsigned int reg)
{
	const unsigned long input_freq = 33333000;
	void __iomem *fpga_base = IOMEM(CFG_PIXIS_BASE);
	unsigned char cw0, cw1, cw2;
	unsigned long vdw, rdw, od, freq;

	cw0 = in_8(fpga_base + reg);
	cw1 = in_8(fpga_base + reg + 1);
	cw2 = in_8(fpga_base + reg + 2);
	vdw = ((cw1 << 1) & 0x1fe) + ((cw2 >> 7) & 1);
	rdw = cw2 & 0x7f;
	od = ics307_s_to_od[cw0 & 0x7];
	/*
	 * CLK1 Freq = Input Frequency * 2 * (VDW + 8) / ((RDW + 2) * OD)
	 *
	 * cw0:  C1 C0 TTL F1 F0 S2 S1 S0
	 * cw1:  V8 V7 V6 V5 V4 V3 V2 V1
	 * cw2:  V0 R6 R5 R4 R3 R2 R1 R0
	 *
	 * R6:R0 = Reference Divider Word (RDW)
	 * V8:V0 = VCO Divider Word (VDW)
	 * S2:S0 = Output Divider Select (OD)
	 * F1:F0 = Function of CLK2 Output
	 * TTL = duty cycle
	 * C1:C0 = internal load capacitance for crystal
	 */
	freq = input_freq * 2 * (vdw + 8) / ((rdw + 2) * od);

	return freq;
}
