/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** examour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** examour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MSR_H_
#define MSR_H_

#include	<stdbool.h>
#include	<stdint.h>

/* TODO: move this file in a arch specific and support subdirectory. */
/* TODO: Add support of returned MSR contents. */


/**
 *  Kernel internal headers for MSR control.
 */


/* Kernel internal data structures */

typedef enum	msr
{
	/* Core 2 duo family */
		
	IA32_P5_MC_ADDR = 0,
	IA32_P5_MC_TYPE = 1,
	IA32_MONITOR_FILTER_SIZE = 6,
	IA32_TIME_STAMP_COUNTER = 16,
	IA32_PLATFORM_ID = 23,
	IA32_APIC_BASE = 27,
	MSR_EBL_CR_POWERON = 42,
	IA32_FEATURE_CONTROL = 58,
	MSR_LASTBRANCH_0_FROM_IP = 64,
	MSR_LASTBRANCH_1_FROM_IP = 65,
	MSR_LASTBRANCH_2_FROM_IP = 66,
	MSR_LASTBRANCH_3_FROM_IP = 67,
	MSR_LASTBRANCH_0_TO_LIP = 96,
	MSR_LASTBRANCH_1_TO_LIP = 97,
	MSR_LASTBRANCH_2_TO_LIP = 98,
	MSR_LASTBRANCH_3_TO_LIP = 99,
	IA32_BIOS_UPDT_TRIG = 121,
	IA32_BIOS_SIGN_ID = 139,
	IA32_PMC0 = 193,
	IA32_PMC1 = 194,
	MSR_FSB_FREQ = 205,
	IA32_MPERF = 231,
	IA32_APERF = 232,
	IA32_MTRRCAP = 254,
	MSR_BBL_CR_CTL3 = 281,
	IA32_SYSENTER_CS = 372,
	IA32_SYSENTER_ESP = 373,
	IA32_SYSENTER_EIP = 374,
	IA32_MGC_CAP = 377,
	IA32_MGC_STATUS = 378,
	IA32_PERFEVTSEL0 = 390,
	IA32_PERFEVTSEL1 = 391,	
	IA32_PERF_STAT = 408,
	MSR_PERF_STAT = 408,
	IA32_PERF_CTL = 409,
	IA32_CLOCK_MODULATION = 410,
	IA32_THERM_INTERRUPT = 411,
	IA32_THERM_STATUS = 412,
	MSR_THERM2_CTL = 413,
	IA32_MISC_ENABLE = 416,
	MSR_LASTBRANCH_TOS = 457,
	IA32_DEBUGCTL = 473,
	MSR_LER_FROM_LIP = 477,
	MSR_LER_TO_LIP = 478,
	ROB_CR_BKUPTMPDR6 = 480,
	MTRR_PHYS_BASE0 = 512,
	MTRR_PHYS_MASK0 = 513,	
	MTRR_PHYS_BASE1 = 514,
	MTRR_PHYS_MASK1 = 515,	
	MTRR_PHYS_BASE2 = 516,
	MTRR_PHYS_MASK2 = 517,	
	MTRR_PHYS_BASE3 = 518,
	MTRR_PHYS_MASK3 = 519,	
	MTRR_PHYS_BASE4 = 520,
	MTRR_PHYS_MASK4 = 521,	
	MTRR_PHYS_BASE5 = 522,
	MTRR_PHYS_MASK5 = 523,	
	MTRR_PHYS_BASE6 = 524,
	MTRR_PHYS_MASK6 = 525,	
	MTRR_PHYS_BASE7 = 526,
	MTRR_PHYS_MASK7 = 527,	
	MTRR_FIX_64K_00000 = 592,
	MTRR_FIX_16K_80000 = 600,
	MTRR_FIX_16K_A0000 = 601,	
	MTRR_FIX_4K_C0000 = 616,
	MTRR_FIX_4K_C8000 = 617,	
	MTRR_FIX_4K_D0000 = 618,	
	MTRR_FIX_4K_D8000 = 619,	
	MTRR_FIX_4K_E0000 = 620,	
	MTRR_FIX_4K_E8000 = 621,	
	MTRR_FIX_4K_F0000 = 622,	
	MTRR_FIX_4K_F8000 = 623,
	IA32_MTRR_DEF_TYPE = 767,
	MSR_PERF_FIXED_CTR0 = 777,
	MSR_PERF_FIXED_CTR1 = 778,
	MSR_PERF_FIXED_CTR2 = 779,
	IA32_PERF_CAPABILITIES = 837,
	MSR_PERF_FIXED_CTR_CTRL = 909,
	MSR_PERF_GLOBAL_STATUS = 910,
	MSR_PERF_GLOBAL_CTRL = 911,
	MSR_PERF_GLOBAL_OVF_CTRL = 912,
	IA32_PEBS_ENABLE = 1009,
	IA32_MC0_CTL = 1024,
	IA32_MC0_STATUS = 1025,
	IA32_MC0_ADDR = 1026,
	IA32_MC1_CTL = 1028,
	IA32_MC1_STATUS = 1029,
	IA32_MC1_ADDR = 1030,
	IA32_MC2_CTL = 1032,
	IA32_MC2_STATUS = 1033,
	IA32_MC2_ADDR = 1034,
	MSR_MC3_CTL = 1040,
	MSR_MC3_STATUS = 1041,
	MSR_MC3_ADDR = 1042,
	MSR_MC3_MISC = 1043,
	MSR_MC4_CTL = 1036,
	MSR_MC4_STATUS = 1037,
	MSR_MC4_ADDR = 1038,
	MSR_MC5_CTL = 1044,
	MSR_MC5_STATUS = 1045,
	MSR_MC5_ADDR = 1046,
	MSR_MC5_MISC = 1047,
	IA32_VMX_BASIC = 1152,
	IA32_VMX_PINBASEDCTLS = 1153,
	IA32_VMX_PROCBASED_CTLS = 1154,
	IA32_VMX_EXIT_CTLS = 1155,
	IA32_VMX_ENTRY_CTLS = 1156,
	IA32_VMX_MISC = 1157,
	IA32_VMX_CR0_FIXED0 = 1158,
	IA32_VMX_CR0_FIXED1 = 1159,
	IA32_VMX_CR4_FIXED0 = 1160,
	IA32_VMX_CR4_FIXED1 = 1161,
	IA32_VMX_VMCS_ENUM = 1162,
	IA32_DS_AREA = 1536,
	IA32_EFER = 0xC0000080,
	IA32_STAR = 0xC0000081,
	IA32_LSTAR = 0xC0000082,
	IA32_FMASK = 0xC0000084,
	IA32_FS_BASE = 0xC0000100,
	IA32_GS_BASE = 0xC0000101,
	IA32_KERNEL_GS_BASE = 0xC0000102,			
	
}				msr_e;

typedef enum	pmc
{
	/* Core 2 duo family */
	/* TODO: fill this table: Intel vol3b Appendix A.2. */
		NONE,
//	MSR_PERF_FIXED_CTR0 = 0x309,
//	MSR_PERF_FIXED_CTR1 = 0x30A,
//	MSR_PERF_FIXED_CTR2 = 0x30B,
	
	
}				pmc_e;



/* Kernel internal methods */

/**
 * Read the current timestamp counter value.
 * @return	The current timestamp counter value.
 */
uint64_t	get_tsc(void);

/**
 * Get the value of an MSR register.
 * @param	msr		The MSR register name.
 * @return			The value of the MSR.
 */
uint64_t	get_msr(msr_e msr);

/**
 * Set the value of an MSR register.
 * @param	msr		The MSR register name.
 * @param	val		The value to set.
 */
void	set_msr(msr_e msr, uint64_t val);

/**
 * Get the value of an Performance monitoring counter register.
 * @param	msr		The PMC register name.
 * @return			The value of the PMC.
 */
uint64_t	get_pmc(pmc_e pmc);

#endif /*MSR_H_*/
