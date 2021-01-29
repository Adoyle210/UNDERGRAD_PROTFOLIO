TITLE Program Two     (ProgramTwo.asm)

; Author: Alexis Doyle
; Last Modified: Jan 24, 2021
; Course number/section: cs 127 001 W21
; Assignment Number:    two             Due Date: sunday, week 3
; Description: This program vailidates user input and display an amount of numbers of the fibonacci series picked by the user

INCLUDE Irvine32.inc
upper = 46	;upper limit
lower = 1	;lower limit
two = 2		;used to check user input
three = 3	;used to check user input

.data
info	BYTE	"Fibonacci Numbers by Alexis Doyle", 0
ask		BYTE	"what is your name?",0
greet	BYTE	"Hello, ",0
direct	BYTE	"Enter the number of Fibonacci terms you want to display.",0
direct2	BYTE	"Provide a number as an integer in the range [1...46].",0
ask2	BYTE	"How many Fibonacci terms do you want?",0
ermsg	BYTE	"Out of range. Enter a number in [1..46]",0
end1	BYTE	"Results Certified by Alexis Doyle",0
end2	BYTE	"Goodbye, ",0
username	BYTE	20 DUP(0)    ;users name
usernum		DWORD	?	;user input for number of terms
four	DWORD 4
temp1	DWORD ?			;previous number
temp2	DWORD ?			;second previous 
temp3	DWORD ?			;current temp number

.code
main PROC
;introduce the program
	mov		edx, OFFSET info
	call	WriteString
	call	crlf

;ask for user's name/get name
	mov		edx, OFFSET ask
	call	WriteString
	mov		edx, OFFSET username
	mov		ecx, 19  
	call	ReadString

;say hello
	mov		edx, OFFSET greet
	call	WriteString
	mov		edx, OFFSET username
	call	WriteString
	call	crlf

;directions/ask for fibonacci terms
	mov		edx, OFFSET direct
	call	WriteString
	call	crlf
	mov		edx, OFFSET direct2
	call	 WriteString
	call	crlf
	mov		edx, OFFSET	ask2
	call	WriteString
	jg		LoopOne

;error Message for inproper input
ErrorMSG:
	call	crlf
	mov		edx, OFFSET ermsg
	call	WriteString

;get and check input with a "loop"
LoopOne:
	call	ReadInt
	mov		usernum, eax
	cmp		usernum, lower	;comparing to the vaule of one
	jb		errormsg		;jumps back if smaller than one
	cmp		usernum, upper	;comparing to the vaule of 46
	ja		ErrorMSG

;checking where to start 
Check:
	cmp		usernum, two
	jb		StartOne
	cmp		usernum, three
	jb		StartTwo
	jg		StartThree

;starts here if user only wants one
StartOne:
	mov		eax, OFFSET lower
	call    WriteDec
	call	crlf
	jg		Ending;

;starts here if user wants two	
StartTwo:
	mov		eax, OFFSET lower
	call    WriteDec
	call	crlf
	mov		eax, OFFSET lower
	call    WriteDec
	call	crlf
	jp		Ending;

;starts here if user wants three or more
StartThree:
	mov		ecx, usernum
	sub		ecx, 3
	mov		eax, 1
	call	WriteDec
	call	crlf
	call	WriteDec
	call	crlf
	mov		temp2, eax 
	mov		eax, 2
	call	WriteDec
	call	crlf
	mov		temp1, eax

;print and calcuates Fibonacci Numbers
LoopTwo:
	add		eax, temp2
	call	WriteDec
	call	crlf      
	mov		temp3, eax
	mov		eax, temp1
	mov		temp2, eax
	mov     eax, temp3
	mov		temp1, eax
	mov     edx, ecx
	cdq
	div		four
	cmp		edx, 0
	jne		Counter
	call	crlf

;loops "loop two" for the fibonacci terms
Counter:
	mov		eax, temp3
	loop	LoopTwo

;closing message
Ending:
	mov		edx, OFFSET end1
	call	WriteString
	call	crlf
	mov		edx, OFFSET end2
	call	WriteString
	mov		edx, OFFSET username
	call	WriteString
	call	crlf

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
