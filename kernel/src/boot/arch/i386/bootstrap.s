/*
** This file is part of exAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * This file contains the bootstrap entry point and the multiboot header.
 */
 #include		"include/multiboot.h"



/* TODO: The MP boot process. adds APIc informations into exaboot_t. */

/*
	Intel Volume 3A. Section 7.5.4.1

	BSPs

	1. Initializes memory.
2. Loads the microcode update into the processor.
3. Initializes the MTRRs.
4. Enables the caches.
5. Executes the CPUID instruction with a value of 0H in the EAX register, then reads
    the EBX, ECX, and EDX registers to determine if the BSP is “GenuineIntel.”
6. Executes the CPUID instruction with a value of 1H in the EAX register, then saves
    the values in the EAX, ECX, and EDX registers in a system configuration space in
    RAM for use later.
7. Loads start-up code for the AP to execute into a 4-KByte page in the lower 1
    MByte of memory.
8. Switches to protected mode and insures that the APIC address space is mapped
    to the strong uncacheable (UC) memory type.
9. Determine the BSP’s APIC ID from the local APIC ID register (default is 0):
        MOV ESI, APIC_ID; Address of local APIC ID register
        MOV EAX, [ESI];
        AND EAX, 0FF000000H; Zero out all other bits except APIC ID
        MOV BOOT_ID, EAX; Save in memory
    Saves the APIC ID in the ACPI and MP tables and optionally in the system config-
    uration space in RAM.
10. Converts the base address of the 4-KByte page for the AP’s bootup code into 8-bit
    vector. The 8-bit vector defines the address of a 4-KByte page in the real-address
    mode address space (1-MByte space). For example, a vector of 0BDH specifies a
    start-up memory address of 000BD000H.
11. Enables the local APIC by setting bit 8 of the APIC spurious vector register (SVR).
        MOV ESI, SVR; Address of SVR
        MOV EAX, [ESI];
        OR EAX, APIC_ENABLED; Set bit 8 to enable (0 on reset)
        MOV [ESI], EAX;
12. Sets up the LVT error handling entry by establishing an 8-bit vector for the APIC
    error handler.
        MOV ESI, LVT3;
                                                                              Vol. 3 7-27
MULTIPLE-PROCESSOR MANAGEMENT
        MOV EAX, [ESI];
        AND EAX, FFFFFF00H; Clear out previous vector.
        OR EAX, 000000xxH; xx is the 8-bit vector the APIC error handler.
        MOV [ESI], EAX;
13. Initializes the Lock Semaphore variable VACANT to 00H. The APs use this
    semaphore to determine the order in which they execute BIOS AP initialization
    code.
14. Performs the following operation to set up the BSP to detect the presence of APs
    in the system and the number of processors:
    — Sets the value of the COUNT variable to 1.
    — Starts a timer (set for an approximate interval of 100 milliseconds). In the AP
         BIOS initialization code, the AP will increment the COUNT variable to indicate
         its presence. When the timer expires, the BSP checks the value of the COUNT
         variable. If the timer expires and the COUNT variable has not been incre-
         mented, no APs are present or some error has occurred.
15. Broadcasts an INIT-SIPI-SIPI IPI sequence to the APs to wake them up and
    initialize them:
        MOV ESI, ICR_LOW; Load address of ICR low dword into ESI.
        MOV EAX, 000C4500H; Load ICR encoding for broadcast INIT IPI
        ; to all APs into EAX.
        MOV [ESI], EAX; Broadcast INIT IPI to all APs
        ; 10-millisecond delay loop.
        MOV EAX, 000C46XXH; Load ICR encoding for broadcast SIPI IP
        ; to all APs into EAX, where xx is the vector computed in step 10.
        MOV [ESI], EAX; Broadcast SIPI IPI to all APs
        ; 200-microsecond delay loop
        MOV [ESI], EAX; Broadcast second SIPI IPI to all APs
        ; 200-microsecond delay loop
        Step 15:
        MOV EAX, 000C46XXH; Load ICR encoding from broadcast SIPI IP
        ; to all APs into EAX where xx is the vector computed in step 8.
16. Waits for the timer interrupt.
17. Reads and evaluates the COUNT variable and establishes a processor count.
18. If necessary, reconfigures the APIC and continues with the remaining system
    diagnostics as appropriate.

 */

 /*
 	Intel Volume 3A. Section 7.5.4.2

 	APs.

 	When an AP receives the SIPI, it begins executing BIOS AP initialization code at the
vector encoded in the SIPI. The AP initialization code typically performs the following
operations:
1. Waits on the BIOS initialization Lock Semaphore. When control of the semaphore
    is attained, initialization continues.
2. Loads the microcode update into the processor.
3. Initializes the MTRRs (using the same mapping that was used for the BSP).
4. Enables the cache.
5. Executes the CPUID instruction with a value of 0H in the EAX register, then reads
    the EBX, ECX, and EDX registers to determine if the AP is “GenuineIntel.”
6. Executes the CPUID instruction with a value of 1H in the EAX register, then saves
    the values in the EAX, ECX, and EDX registers in a system configuration space in
    RAM for use later.
7. Switches to protected mode and insures that the APIC address space is mapped
    to the strong uncacheable (UC) memory type.
8. Determines the AP’s APIC ID from the local APIC ID register, and adds it to the MP
    and ACPI tables and optionally to the system configuration space in RAM.
9. Initializes and configures the local APIC by setting bit 8 in the SVR register and
    setting up the LVT3 (error LVT) for error handling (as described in steps 9 and 10
    in Section 7.5.4.1, “Typical BSP Initialization Sequence”).
10. Configures the APs SMI execution environment. (Each AP and the BSP must have
    a different SMBASE address.)
11. Increments the COUNT variable by 1.
12. Releases the semaphore.
13. Executes the CLI and HLT instructions.
14. Waits for an INIT IPI.
  */

.text

.globl  _start

_start:

/* The real entry point of the kernel. */
	/* Set up a stack */
	movl	$(stack + 0x4000),		%esp

	/* Reset EFLAGS. */
	pushl	$0
	popf
	finit

	/* Push the magic and the address on the stack, so that they
	will be the parameters of the cmain function */
/* This one is not in the multiboot specification but grub keeps */
/* multiboot_header_t in it. */
/*	pushl	%ecx */
/* Save this parameter in an unused register. */
	movl	%eax,				%edx

/* Push multiboot parameters on the stack. */
	pushl	%ebx
	pushl	%edx

	/* Call the kernel's main function. */
	/* For a fully functional kernel, gdt,idt, tss and kernel stack */
	/* need to be created. */
	call	examain

	/* Should never go here */
loop:
	hlt
	jmp loop


.data

.align  8
.comm   stack, 0x4000
