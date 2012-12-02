#
# arch/i386/crt0.S
#
# Does arch-specific initialization and invokes __libc_init
# with the appropriate arguments.
#
# See __static_init.c or __shared_init.c for the expected
# arguments.
#


	.text
	.align 4
	.type _start,@function
	.globl _start
_start:
	call	main
	push	$0
	call	env_delete
	hlt

	.size _start, .-_start
