TITLE Program Three   (ProgramThree.asm)

; Author: Alexis
; Last Modified: Jan 31, 2021
; Course number/section: cs 127 001 W21
; Assignment Number:    Three        Due Date: Sunday, week 4
; Description: prompt the user for there name and greet them, state the directions
;ask for a number between -100 to -1 and validate the user input
;conduct and print calcuations and give the user a closing message

INCLUDE Irvine32.inc


.data
intro		BYTE	"Welcome to the Integer Accumulator By Alexis",0
ask			BYTE	"what is your name?",0
greet		BYTE	 "Hello, ",0
direct		BYTE	"Please enter a numbers in [-100, -1].",0
direct2		BYTE	"Enter a non-negative number when you are finshed to see results.",0
prompt		BYTE	"Enter Number: ",0
erMSG		BYTE	"Invalid Number, please enter numbers in [-100, -1].",0
count1		BYTE	"You entered ",0
count2		BYTE	" valid numbers.",0
sumMSG		BYTE	"The sum of your valid numbers is ",0
avgMSG		BYTE	"The rounded average is ",0
endMSG		BYTE	"You did not enter any negative numbers.",0
endMSG1		BYTE	"Thank you for playing Integer Accumulator!",0
endMSG2		BYTE	"Goodbye, ",0
userName	BYTE	30 Dup(0)			;stores users name
userNum		DWORD	?					;numbers ebtered by user
numCount	DWORD	?					;count of vaild ints entered by the user
counter		DWORD	?					;
sum			DWORD	0					;sum of all the numbers
avg			DWORD   0					;the average of the numbers

;number limit constants
upper = -1
lower = -100

.code
main PROC
Start:
;introduction to the program
	mov		edx, OFFSET intro
	call	WriteString
	call	crlf

;ask/get user's name
	mov		edx, OFFSET ask
	call	WriteString
	mov		edx, OFFSET userName
	mov		ecx, 29
	call	ReadString

;greet user
	mov		edx, OFFSET greet
	call	WriteString
	mov		edx, OFFSET userName
	call	WriteString
	call	crlf

;prints direction
	mov		edx, OFFSET direct
	call	WriteString
	call	crlf
	mov 	edx, OFFSET direct2
	call	WriteString
	call	crlf
	jmp		GetNums


ErrorMSG:
;error Message for inproper input
	mov		eax, numCount				;deletes one from count because invalid int
	sub		eax, 1
	mov		numCount, eax
	mov		edx, OFFSET ermsg			;notifies user of error
	call	WriteString
	call	crlf

GetNums:
;ask for user numbers
	mov		eax, numCount			 ;adds one to count
	add		eax, 1
	mov		numCount, eax
	mov		edx, OFFSET prompt		;asks for number
	call	WriteString
	call	ReadInt					;gets number
	mov		userNum, eax

	;vailidate ints with limits
	cmp		eax, upper
	jg		Adding					;adds to sum
	cmp		eax, lower
	jl		Adding					;adds to sum
	add		eax, sum
	mov		sum, eax
	loop	GetNums					;loops untill out of range


Adding:
	mov		eax, numCount
	sub		eax, 1					; subtracts one because 1 was added to the count for the postive number the ended loop
	jz		closing					;if number of vaild numbers equals zeros ends program
	mov		eax, sum

	;tells user how many vaild numbers they entered
	mov		edx, OFFSET count1
	call	WriteString
	mov		eax, numCount
	sub		eax, 1
	call	WriteDec
	mov		edx, OFFSET count2
	call	WriteString
	call	crlf

	;prints out the sum of all the negative numbers and the sum msg
	mov		edx, OFFSET sumMSG
	call	WriteString
	mov		eax, sum
	call	WriteInt
	call	crlf

	;prints out the average of all the numbers and the avg msg
	mov		edx, OFFSET avgMSG
	call	WriteString
	mov		eax, 0
	mov		eax,sum
	cdq
	mov		ebx, numCount
	sub		ebx, 1
	idiv	ebx
	mov		avg, eax
	call	Writeint
	call	crlf
	jmp		closing2


closing:
;closing message for no vaild numbered entered
	mov		edx, OFFSET endMSg
	call	WriteString
	call	crlf

closing2:
;closing for when valid numbers have been entered
	mov		edx, OFFSET endMSG1
	call	WriteString
	call	crlf
	mov		edx, OFFSET endMSG2
	call    WriteString
	call    crlf
	mov		edx, OFFSET userName
	call    WriteString
	call    crlf

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
