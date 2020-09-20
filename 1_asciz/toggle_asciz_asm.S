	.cpu cortex-m3				@ This assembly is for the ARM cortex-M3 processor
	.global	toggle_asciz_asm	@ Declare the toggle_asciz_asm co-routine
.section .text					@ start of code
toggle_asciz_asm:
	push	{lr}				@ Store context of link register
	cmp r0, #90					@ compare char value of ASCII value of 'Z'
	bgt to_upper_case			@ if char in r0 is bigger than ASCII value of 'Z'
	bl tolower					@ call tolower(char) function from <ctype.h>
	b return					@ goto return
to_upper_case:
	bl toupper					@ call toupper(char) function from <ctype.h>
return:
	pop	{pc}					@ YEET the program counter