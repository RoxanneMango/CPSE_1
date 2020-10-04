#include "compressed.S"

.cpu cortex-m3
.global	decode
.section .data
text:
	.ascii	"%s\r\n"
.section .text
decode:
	push	{lr}		@ push link register to stack
	ldr r7, =array		@ compressed array from compressed.S
	movs	r1, #1		@ r1 = sizeof(char)
	movs	r0, #100	@ r0 = BUFF_LEN
	bl	calloc			@ r0 = calloc(100, 1) ; yoink that memory
	mov r11, r0			@ ouput
	mov r6, r0			@ output_ptr
	bl calloc			@ r0 = calloc(100, 1) ; yoink all the memory
	mov r10, r0			@ buffer
for:
	ldrb r0, [r7]		@ c = *(input)
	cmp r0, #0			@ c == 0 ?
	beq return			@ goto return
	add r7, #1			@ input++
	cmp r0, #'@'		@ c != '@' ?
	beq Cliff			@ goto Cliff
Larry:				@ if( c!= '@' )
	strb r0, [r6]		@ putchar(c)
	add r6, #1			@ output++							@ r6
	mov r5, #100		@ int i = BUFF_LEN					@ r5
Rita:				@ for(int i = BUFF_LEN: i > 0: --i)
	cmp r5, #0			@ i > 0 ?
	beq Keeg			@ goto Keeg
	mov r4, r10			@ r4 = buffer						@ r4
	add r4, r5			@ r4 = buffer+i
	mov r3, r10			@ r3 = buffer						@ r3
	add r3, r5			@ r3 = buffer+i
	sub r3, #1			@ r3 = buffer+i-1
	ldrb r3, [r3]		@ r3 = *(buffer+i-1)
	strb r3, [r4]		@ *(buffer+i) = *(buffer+i-1)
	sub r5, #1			@ i--
	b Rita
Keeg:				@ end of Rita for loop
	mov r1, r10			@ r1 = buffer
	strb r0, [r1]		@ *(buffer) = c
	b for
Cliff:
	ldrb r2, [r7]		@ int offset = *(input)
	sub r2, #'0'		@ offset - '0'
	add r7, #1			@ input++
	ldrb r1, [r7]		@ int length = input
	sub r1, #'0'		@ length - '0'
	add r7, #1			@ input++
Jane:				@ while( length )
	cmp r1, #0			@ length > 0?
	beq for				@ goto for
	mov r0, r10			@ c = buffer
	add r0, r2			@ c = buffer+offset
	ldrb r0, [r0]		@ c = *(buffer+offset)
	strb r0, [r6]		@ putchar(c)
	add r6, #1			@ output++
	mov r5, #100		@ int i = BUFF_LEN					@ r5
Clara:				@ for( int i = BUFF_LEN: i > 0: i--)
	cmp r5, #0			@ r5 > 0 ?
	beq Niles			@ goto Niles
	mov r4, r10			@ r4 = buffer						@ r4
	add r4, r5			@ r4 = buffer+i
	mov r3, r10			@ r3 = buffer						@ r3
	add r3, r5			@ r3 = buffer+i
	sub r3, #1			@ r3 = buffer+i-1
	ldrb r3, [r3]		@ r3 = *(buffer+i-1)
	strb r3, [r4]		@ *(buffer+i) = *(buffer+i-1)
	sub r5, #1			@ i--
	b Clara
Niles:				@ end of Clara for loop
	mov r4, r10			@ r1 = buffer
	strb r0, [r4]		@ *(buffer) = c
	sub r1, #1			@ length--
	b Jane
return:
	strb r0, [r6]		@ add '\0'
	ldr r0, =text		@ r0 = "%s\r\n"
	mov r1, r11			@ r1 = ouput
	bl printf			@ printf("%s\r\n", ouput)
	mov r0, r11			@ r0 = ouput
	bl free				@ free(output)
	mov r0, r10			@ r0 = buffer
	bl free				@ free(buffer)
	pop	{pc}			@ YEET program counter
