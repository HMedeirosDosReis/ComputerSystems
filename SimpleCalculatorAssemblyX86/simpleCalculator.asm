;simple calculator 
;Henrique Medeiros Dos Reis
;nov29Version

	section .bss
bufferChoice:	 resb 100	;reserve 2 bytes
bufferNumber: 	 resb   32 
num2: 			 resb   32

	section .data
buffPrint: 		 db     0

	section .text
	global _start

_start:
	
userInput:
	;reset all my registers
	mov 	word [bufferChoice], 0
	mov 	eax, 0
	mov		ebx, 0
	mov		ecx, 0
	mov 	edx, 0
	
	mov 	eax, 3 				;read
	mov 	ebx, 0				;stdin
	mov 	ecx, bufferChoice	;start of storage
	mov 	edx, 100			;number of bytes
	int 	0x80				;return to linux
	

	
	mov		eax, [bufferChoice]
	sub		eax, 0xa00
	; compare and go to the correct section
	cmp 	eax, 's' 
	je		store
	
	cmp 	eax, 'n'
	je		negate
	
	cmp 	eax, '+'
	je		addition
	
	cmp 	eax, '-'
	je		subtraction
	
	cmp 	eax, '*'
	je		multiply
	
	cmp 	eax, '/'
	je		divide
	
	cmp 	eax, 'd'
	je		pDecimal
	
	cmp 	eax, 'b'
	je		pBinary
	
	cmp 	eax, 'q'
	je		quit

store:			; needs user input
	mov 	eax, 3 				; read from stdin
	mov 	ebx, 0
	mov		ecx, bufferNumber
	mov     edx, 32			; no more than 32 char
	int 	0x80
	
	;; we need to convert the string to the number ----- needs to do this for any input
	; reset eax and ecx, also, put the number into ebx
	xor		eax, eax
	mov 	ebx, bufferNumber
	xor		ecx, ecx
	;check if it is negative
	isNeg:
		cmp		ebx, 0x0
		jge		stringtoInt
		
		mov		esi, ebx
		
		mov		BYTE [bufferNumber], '-'
		mov		ebx, esi
		neg		ebx
		
	;lets convert the string to a number value 
	stringtoInt:
		mov		cl, [ebx] 		;take the first byte
		cmp		ecx, '0'		;is it smaller than 0
		jb		doneLooping		; then we are done
		cmp		ecx, '9'		; is it bigger than 9
		ja 		doneLooping		; then we are done
		imul	eax, 10			;multiply the value in eax by 10
		sub		eax, '0'		; subtract the value for the ascii 0
		add		eax, ecx		; add the ecx to eax 
		inc 	ebx				; ebx++
		jmp		stringtoInt		; keep looping
	
	doneLooping:		; when done
	mov		ebx, eax			;put eax into ebx
	mov		[bufferNumber], ebx	; is now the wanted value
	jmp 	_start				; go back to the beggining of the program
	
negate:
	mov 	eax, [bufferNumber] ; put the number into the rax
	neg		eax
	mov 	[bufferNumber], eax	; put in the buffer nubmer
	jmp 	_start				; go back to start
	
addition:		; needs user input
	mov 	eax, 3				; read from stdin
	mov 	ebx, 0
	mov     ecx, num2
	mov     edx, 32
	int 	0x80  				;get num 2 from keybord

	;; we need to convert the string to the number ----- needs to do this for any input
	; reset eax and ecx, also, put the number into ebx
	xor		eax, eax
	mov 	ebx, num2
	xor		ecx, ecx
	;lets convert the string to a number value 
	stringtoIntAdd:
		mov		cl, [ebx] 			;take the first byte
		cmp		ecx, '0'			;is it smaller than 0
		jb		doneLoopingAdd		; then we are done
		cmp		ecx, '9'			; is it bigger than 9
		ja 		doneLoopingAdd		; then we are done
		imul	eax, 10				;multiply the value in eax by 10
		sub		eax, '0'			; subtract the value for the ascii 0
		add		eax, ecx			; add the ecx to eax 
		inc 	ebx					; ebx++
		jmp		stringtoIntAdd		; keep looping
	
	doneLoopingAdd:		; when done
		mov		ebx, eax			;put eax into ebx
		mov		[num2], ebx			; is now the wanted value
	
	
	mov		eax, [bufferNumber]
	mov		ebx, [num2]
	ADD		eax, ebx			; bufferNumber += num2
	
	mov		[bufferNumber], eax
	
	jmp		_start
	
subtraction:			; needs user input
	mov 	eax, 3				; read from stdin
	mov 	ebx, 0
	mov     ecx, num2
	mov     edx, 32
	int 	0x80  				;get num 2 from keybord
	
	;; we need to convert the string to the number ----- needs to do this for any input
	; reset eax and ecx, also, put the number into ebx
	xor		eax, eax
	mov 	ebx, num2
	xor		ecx, ecx
	;lets convert the string to a number value 
	stringtoIntSub:
		mov		cl, [ebx] 			;take the first byte
		cmp		ecx, '0'			;is it smaller than 0
		jb		doneLoopingSub		; then we are done
		cmp		ecx, '9'			; is it bigger than 9
		ja 		doneLoopingSub		; then we are done
		imul	eax, 10				;multiply the value in eax by 10
		sub		eax, '0'			; subtract the value for the ascii 0
		add		eax, ecx			; add the ecx to eax 
		inc 	ebx					; ebx++
		jmp		stringtoIntSub		; keep looping
	
	doneLoopingSub:		; when done
		mov		ebx, eax			;put eax into ebx
		mov		[num2], ebx			; is now the wanted value
	
	mov		eax, [bufferNumber]
	mov		ebx, [num2]
	SUB		eax, ebx ; bufferNumber -= num2
	
	mov 	[bufferNumber], eax
	
	jmp		_start
	
multiply:				;needs user input
	mov 	eax, 3				; read from stdin
	mov 	ebx, 0
	mov     ecx, num2
	mov     edx, 32
	int 	0x80  				;get num 2 from keybord
	
	;; we need to convert the string to the number ----- needs to do this for any input
	; reset eax and ecx, also, put the number into ebx
	xor		eax, eax
	mov 	ebx, num2
	xor		ecx, ecx
	;lets convert the string to a number value 
	stringtoIntMul:
		mov		cl, [ebx] 			;take the first byte
		cmp		ecx, '0'			;is it smaller than 0
		jb		doneLoopingMul		; then we are done
		cmp		ecx, '9'			; is it bigger than 9
		ja 		doneLoopingMul		; then we are done
		imul	eax, 10				;multiply the value in eax by 10
		sub		eax, '0'			; subtract the value for the ascii 0
		add		eax, ecx			; add the ecx to eax 
		inc 	ebx					; ebx++
		jmp		stringtoIntMul		; keep looping
	
	doneLoopingMul:		; when done
		mov		ebx, eax			;put eax into ebx
		mov		[num2], ebx			; is now the wanted value
	
	; multiplication will be eax * operand 
	mov		eax, [bufferNumber] 
	cdq
	mov 	ebx, [num2]
	imul 	ebx
								; since operand is 32 bits
	mov		[bufferNumber], eax
	
	jmp		_start
	
divide:					; needs user input
	mov 	eax, 3				; read from stdin
	mov 	ebx, 0
	mov     ecx, num2
	mov     edx, 32
	int 	0x80  				;get num 2 from keybord
	
	;; we need to convert the string to the number ----- needs to do this for any input
	; reset eax and ecx, also, put the number into ebx
	xor		eax, eax
	mov 	ebx, num2
	xor		ecx, ecx
	;lets convert the string to a number value 
	stringtoIntDiv:
		mov		cl, [ebx] 			;take the first byte
		cmp		ecx, '0'			;is it smaller than 0
		jb		doneLoopingDiv		; then we are done
		cmp		ecx, '9'			; is it bigger than 9
		ja 		doneLoopingDiv		; then we are done
		imul	eax, 10				;multiply the value in eax by 10
		sub		eax, '0'			; subtract the value for the ascii 0
		add		eax, ecx			; add the ecx to eax 
		inc 	ebx					; ebx++
		jmp		stringtoIntDiv		; keep looping
	
	doneLoopingDiv:		; when done
		mov		ebx, eax			;put eax into ebx
		mov		[num2], ebx			; is now the wanted value
	
	; division will be eax / ebx 
	mov		eax, [bufferNumber]
	cdq
	mov 	ebx, [num2]
	idiv	ebx
	
	mov		[bufferNumber], eax ;since the operand is 32 bits
	
	jmp 	_start
	
pDecimal:
	mov		eax, [bufferNumber]
	printDecimal:
		cmp		eax, 0x0
		jge		dumpNumber
		
		mov		esi, eax
		mov		BYTE [buffPrint], '-' ;back up for edx
		mov		eax, 4
		mov		ebx, 1
		mov 	ecx, buffPrint
		mov		edx, 1
		int 	0x80
		
		mov		eax, esi 				;get eax back
		
		neg 	eax						; pring the positive version 
	
	dumpNumber:
		mov		esi, 0x0 				;digit count
	
	extractDigit:
		inc 	esi					; digit count ++
		; base conversion for base 10, divide by 10 and keep remainders until 0
		mov 	ebx, 0xa
		mov		edx, 0x0
		div		ebx					; eax / ebx the remainder is edx
		
		push rdx		;digit to print is on the stacl
		; if number is 0, we are done
		cmp		eax, 0x0
		jne		extractDigit
		
	printDigitFromStack:
		pop		rdx						;pull from stack
		dec		esi						; digit count --
		
		;; now we can print
		add 	dl, '0' 				;transform into ascii character
		mov 	[buffPrint], dl 		; back value is our d low
		mov 	eax, 4
		mov 	ebx, 1
		mov		ecx, buffPrint
		mov		edx, 1
		int		0x80
		;; keep going until remainder is 0
		cmp		esi, 0x0
		jne printDigitFromStack
		
		jmp _start
	
	
pBinary:	;; for binary, the printing principle is the same, but we will divide by 2 instead of 10
	; this is incorrect in the amount of nubmer that this is printing
	mov		eax, [bufferNumber]
	mov		edi, 0
	printBinary:
		cmp		eax, 0x0
		jge		dumpNumberBinary
		
		mov		esi, eax
		mov		BYTE [buffPrint], '-' ;back up for edx
		mov		eax, 4
		mov		ebx, 1
		mov 	ecx, buffPrint
		mov		edx, 1
		int 	0x80
		
		mov		eax, esi 				;get eax back
		
		neg 	eax						; pring the positive version 
	
	dumpNumberBinary:
		mov		esi, 0x0 				;digit count
	
	extractDigitBinary:
		inc 	edi
		inc 	esi					; digit count ++
		; base conversion for base 2, divide by 2 and keep remainders until 0
		mov 	ebx, 0x2
		mov		edx, 0x0
		div		ebx					; eax / ebx the remainder is edx
		
		push rdx		;digit to print is on the stacl
		; if number is 0, we are done
		cmp		edi, 0x20
		jne		extractDigitBinary
		
	printDigitFromStackBinary:
		pop		rdx						;pull from stack
		dec		esi						; digit count --
		
		;; now we can print
		add 	dl, '0' 				;transform into ascii character
		mov 	[buffPrint], dl 		; back value is our d low
		mov 	eax, 4
		mov 	ebx, 1
		mov		ecx, buffPrint
		mov		edx, 1
		int		0x80
		;; keep going until remainder is 0
		cmp		esi, 0x0
		jne printDigitFromStackBinary
		
	jmp _start
dumNumber:
	mov		esi, 0x0	;esi holds digit count
	
quit: ; quit the program 
	mov 	eax, 1
	mov 	ebx, 0
	int 	0x80
	
	
	
	
	
