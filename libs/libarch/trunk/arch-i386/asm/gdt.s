
.text

/*
 * gdtr *:  4(%esp)
 * ds:      8(%esp)
 * es:      12(%esp)
 * fs:      16(%esp)
 * gs:      20(%esp)
 * ss:      24(%esp)
 * cs:      28(%esp)
 */
.globl	gdt_flush
gdt_flush:
    movl    4(%esp),    %eax
    lgdt    (%eax)

	movl	8(%esp),	%eax
	movl	%eax,		%ds

	movl	12(%esp),	%eax
	movl	%eax,		%es

	movl	16(%esp),	%eax
	movl	%eax,		%fs

	movl	20(%esp),	%eax
	movl	%eax,		%gs

	movl	24(%esp),	%eax
	movl	%eax,		%ss

    /*
    movl    28(%esp),   %eax
    pushl   %eax
    pushl   $.flush
    ljmp    *8(%esp)
    */


/*    pushl  $flush
    movl    28(%esp),   %eax
    shr     $16,        %eax
    pushl   %eax*/
	/* TODO: use 28(%esp) which contains the requested cs register. */
    ljmp   $0x8, $flush

flush:
    ret
