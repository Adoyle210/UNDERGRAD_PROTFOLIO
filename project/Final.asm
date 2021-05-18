TITLE Final Project     (final.asm)

; Author: Alexis Doyle
; last Modified: March 
; Course number/section: cs 271 001 W21
; Assignment Number: six                Due Date:  March 17th 
; Description: this code has a decoy mode that calculates the sum 
; of the two operands and will store the result into memory 
; the second mode is encryption and it encrypts and the third 
;  is decryption and it decrypts the code recived from the stack 



INCLUDE Irvine32.INCLUDE

.data
    operand1 WORD 46
    operand2 WORD -20
    dest     DWORD 0

.code
main PROG
; empty main for testing, pls be nice 
    push operand1
    push operand2
    push OFFSET dest
    call compute 
    mov eax, dest
    call writeInt 

main    ENDP

;procedure to run the program and make calls to different modes 
;receives:  the pushed values from the stack 
;returns:	the values from the varring modes 
;pre-condtions: 
;register changes: 
compute PROG
    push ebp
    mov     ebp, esp            ;setting up the stack  
    mov     ebx,[esp + 8]       ;offseting the dest value 

    cmp ebx, -1                 ;comparing to see what mode to run
    jg DecoyMode            
    je EncryptionMode
    jl DecryptionMode
    jmp Done                    ;this is to end compute

    DecoyMode:                   ;this is to call decoy mode
        push WORD ptr [ebp + 14] ;operand1
        push WORD ptr [ebp + 12] ;operand2
        call decoy
        mov   [ebx],eax           ;moving value to be called/printed in main
        jmp Done

    EncryptionMode:
        push [ebp + 16]           ;offset of key
        push [ebp + 12]           ;offset the message
        call encryption
        jmp Done
        
    DecryprionMode:
        push [ebp + 16]           ;offset of key
        push [ebp + 12]           ;offset the message
        call decryption
        jmp Done

    Done:
        ret                         ;return back to main
compute     ENDP

;procedure to run decoy 
;receives: accepts 3 parameters on the stack 
;returns:
;pre-condtions: 
;register changes: 
decoy PROG
    mov     ebp, esp            ;setting up the stack  
    mov     ebx,[esp + 8]       ;dtest value that will save the sum
    mov eax,[esp + 14]          ;operand1 
    mov edi,[ebp + 12]          ;operand2            
    add eax, ebx                ;adding the operands 
    mov [ebx], eax              ;storing value as dtest 
 ret
decoy       ENDP

;procedure to run encryption
;receives: accepts 3 parameters from the stack  
;returns:	an encryption message 
;pre-condtions: 
;register changes: 
encryption PROG

encryption      ENDP

;procedure to run decryption
;receives: accepts 3 parameters from the stack
;returns:	
;pre-condtions: 
;register changes: 
decryption PROG


decryption 

END main