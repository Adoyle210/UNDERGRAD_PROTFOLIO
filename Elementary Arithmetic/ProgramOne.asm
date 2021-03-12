TITLE Program One     (ProgramOne.asm)

; Author: Alexis Doyle
; Last Modified: jan 16
; Course number/section: cs 271 001 W21
; Assignment Number:      project 1        Due Date: sunday, week 2
; Description: display name and program title, display user instructions, prompt to enter two numbers, calculate and  display terminating message 

INCLUDE Irvine32.inc

; (insert constant definitions here)

.data
	info	BYTE	"Elementary Arithmetic by Alexis Doyle", 0
	ecmsg	BYTE	"**EC: program verifies second number is less than the first.",0
	direct	BYTE	"Enter in two numbers and I will show you the sum, difference, product, quotient, and remainder.",0
	ermsg	BYTE	"The second number must be less than the first!",0
	goodbye	BYTE	"Impressed? Bye!",0
	numone	BYTE	"First number: ",0
	numtwo	BYTE	"Second number: ",0
	plus	BYTE	" + ",0
	minus	BYTE	" - ",0
	multi	BYTE	" x ",0
	divide	BYTE	" / ",0
	equal	BYTE	" = ",0
	remain	BYTE	" remainder: ",0
	enter1	DWORD	?			;first number entered by user
	enter2	DWORD	?			;second number entered by user
	solu1	DWORD	?			;addition solution
	solu2	DWORD	?			;subtraction solution
	solu3	DWORD	?			;multiplication solution
	solu4	DWORD	?			;division solution
	solu5	DWORD	?			;dividion remainder

.code
main PROC
	; introduce program 
	mov		edx, OFFSET info
	call WriteString
	call crlf

	;print ec message
	mov		edx, OFFSET ecmsg
	call	WriteString
	call	crlf

	;print directions 
	mov		edx, OFFSET direct
	call WriteString
	call crlf

	;first user input 
	mov		edx, OFFSET numone
	call	WriteString
	call	ReadInt
	mov		enter1, eax
	;call	crlf

	;second user input
	mov		edx, OFFSET numtwo
	call	WriteString
	call	ReadInt
	mov		enter2, eax
	;call	crlf

	;EC: COMPARE FOR ERROR
	mov		eax, enter2
	cmp		eax, enter1
	jg		Error
	jle		Solve

Error:
	mov		edx, OFFSET ermsg
	call	WriteString
	call	crlf
	jg		EndProgram
		

Solve:
	;adding sums to get solu1
	mov		eax,enter1
	add		eax,enter2
	mov		solu1,eax

	;print addtion solution 1
	mov		eax, enter1
	call	WriteDec
	mov		edx, OFFSET plus
	call	WriteString
	mov		eax, enter2
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, solu1
	call	WriteDec
	call	Crlf
	
	;subtracing sums to get solu2
	mov		eax,enter1
	sub		eax,enter2
	mov		solu2,eax

	;print subtraction solution 2
	mov		eax, enter1
	call	WriteDec
	mov		edx, OFFSET minus
	call	WriteString
	mov		eax, enter2
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, solu2
	call	WriteDec
	call	Crlf

	;multiplying user values to get solu3
	mov		eax,enter1
	mov		ebx,enter2
	mul		ebx
	mov		solu3,eax
	
	;print solution 3 for multipication
	mov		eax, enter1
	call	WriteDec
	mov		edx, OFFSET multi
	call	WriteString
	mov		eax, enter2
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, solu3
	call	WriteDec
	call	Crlf

	;dividing numbers to get solu4 and the remainder solu5
	mov edx, 0
	mov eax, enter1
	cdq
	mov ebx, enter2
	cdq
	div	ebx
	mov solu4, eax
	mov solu5, edx

	;print solution 4 and 5 for division
	mov		eax, enter1
	call	WriteDec
	mov		edx, OFFSET divide
	call	WriteString
	mov		eax, enter2
	call	WriteDec
	mov		edx, OFFSET equal
	call	WriteString
	mov		eax, solu4
	call	WriteDec
	mov		edx, OFFSET remain
	call	WriteString
	mov		eax, solu5
	call	WriteDec
	call	Crlf

EndProgram:
	;closing message
	mov edx, OFFSET goodbye
	call WriteString
	call crlf

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
	
