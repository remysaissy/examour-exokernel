
.text

.macro ISR_NOERRCODE intnum
.align 8
  .global isr\intnum
  isr\intnum:
    cli                         /* Disable interrupts firstly. */
    pushl $0					/* Push a dummy error code. */
    pushl $\intnum                /* Push the interrupt number. */
    jmp isr_common_stub         /* Go to our common handler code. */
.endm

.macro ISR_ERRCODE intnum
.align 8
.global isr\intnum
  isr\intnum:
    cli                         /* Disable interrupts. */
    pushl $\intnum               /* Push the interrupt number */
    jmp isr_common_stub
.endm

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

/* This is our common ISR stub. It saves the processor state, sets */
/* up for kernel mode segments, calls the C-level fault handler, */
/* and finally restores the stack frame. */
.align 8
isr_common_stub:
    pusha                    /* Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax */

    call isr_handler

    popl	%ebx        	/* reload the original data segment descriptor */

    popa                    /* Pops edi,esi,ebp... */
    addl	$8, %esp		/* Cleans up the pushed error code and pushed ISR number */
    /* sti */
    iret           			/* pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP */


/* Exabus syscalls. */

.align 8
.global isr80_exabus_publish
isr80_exabus_publish:
    cli                         /* Disable interrupts firstly. */
    pushl $0                    /* Push a dummy error code. */
    pushl $80
    jmp isr_common_stub         /* Go to our common handler code. */

.align 8
.global isr81_exabus_unpublish
isr81_exabus_unpublish:
    cli                         /* Disable interrupts firstly. */
    pushl $0                    /* Push a dummy error code. */
    pushl $81
    jmp isr_common_stub         /* Go to our common handler code. */

.align 8
.global isr82_exabus_subscribe
isr82_exabus_subscribe:
    cli                         /* Disable interrupts firstly. */
    pushl $0                    /* Push a dummy error code. */
    pushl $82
    jmp isr_common_stub         /* Go to our common handler code. */

.align 8
.global isr83_exabus_unsubscribe
isr83_exabus_unsubscribe:
    cli                         /* Disable interrupts firstly. */
    pushl $0                    /* Push a dummy error code. */
    pushl $83
    jmp isr_common_stub         /* Go to our common handler code. */

.align 8
.global isr84_exabus_find
isr84_exabus_find:
    cli                         /* Disable interrupts firstly. */
    pushl $0                    /* Push a dummy error code. */
    pushl $84
    jmp isr_common_stub         /* Go to our common handler code. */

.align 8
.global isr85_exabus_raise
isr85_exabus_raise:
    cli                         /* Disable interrupts firstly. */
    pushl $0                    /* Push a dummy error code. */
    pushl $85
    jmp isr_common_stub         /* Go to our common handler code. */

.align 8
.global isr86_exabus_call
isr86_exabus_call:
    cli                         /* Disable interrupts firstly. */
    pushl $0                    /* Push a dummy error code. */
    pushl $86
    jmp isr_common_stub         /* Go to our common handler code. */
