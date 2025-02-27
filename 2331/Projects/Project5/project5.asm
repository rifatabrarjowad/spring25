; Purpose: The implementation of Project 5
%include "asm_io.inc"
; initialized data
segment .data
prompt1 db "Enter a number: ", 0
prompt2 db "Enter a second number: ", 0
x16_msg db "x16 if negative: ", 0
bit8_msg db "Turn on 8th bit if odd: ", 0
zero_msg db "Zero out if even: ", 0
swap_msg db "Swap top & bottom 16 bits: ", 0
invert_msg db "Invert bits 3 - 6: ", 0
opp_msg db "Opposite sign? ", 0

; uninitialized data
segment .bss
num1 resd 1        ; First number entered by user
num2 resd 1        ; Second number entered by user

segment .text
        global  asm_main
asm_main:
        enter   0,0               ; setup routine
        pusha

        ; Prompt user for first number
        mov     eax, prompt1      ; Load address of prompt1
        call    print_string      ; Print prompt

        call    read_int          ; Read integer into EAX
        mov     [num1], eax       ; Store the input in num1
        
        ; 1. Multiply by 16 if the number is negative
        mov     eax, [num1]       ; Load the number into EAX
        test    eax, 0x80000000   ; Test if the number is negative (bit 31 set)
        jz      not_negative      ; Jump if zero (not negative)
        shl     eax, 4            ; Shift left by 4 bits (multiply by 16)
        
not_negative:
        ; Print result
        mov     ebx, eax          ; Save result in EBX
        mov     eax, x16_msg      ; Load message for multiply result
        call    print_string      ; Print message
        mov     eax, ebx          ; Restore result to EAX
        call    print_int         ; Print result
        call    print_nl          ; Print newline
        
        ; 2. Turn on the 8th bit if the number is odd
        mov     eax, [num1]       ; Load the original number into EAX
        test    eax, 1            ; Test if number is odd (bit 0 is 1)
        jz      not_odd           ; Jump if zero (not odd)
        or      eax, 0x80         ; Turn on 8th bit (bit 7)
        
not_odd:
        ; Print result
        mov     ebx, eax          ; Save result in EBX
        mov     eax, bit8_msg     ; Load message for 8th bit result
        call    print_string      ; Print message
        mov     eax, ebx          ; Restore result to EAX
        call    print_int         ; Print result
        call    print_nl          ; Print newline
        
        ; 3. Zero out all bits when even
        mov     eax, [num1]       ; Load the original number into EAX
        test    eax, 1            ; Test if number is odd (bit 0 is 1)
        jnz     is_odd            ; Jump if not zero (is odd)
        xor     eax, eax          ; Zero out the number if even
        
is_odd:
        ; Print result
        mov     ebx, eax          ; Save result in EBX
        mov     eax, zero_msg     ; Load message for zero out result
        call    print_string      ; Print message
        mov     eax, ebx          ; Restore result to EAX
        call    print_int         ; Print result
        call    print_nl          ; Print newline
        
        ; 4. Swap the top 16 bits and the bottom 16 bits
        mov     eax, [num1]       ; Load the original number into EAX
        mov     ebx, eax          ; Copy to EBX
        shr     ebx, 16           ; Shift right to get high 16 bits in low position
        shl     eax, 16           ; Shift left to get low 16 bits in high position
        or      eax, ebx          ; Combine the two parts using OR
        
        ; Print result
        mov     ebx, eax          ; Save result in EBX
        mov     eax, swap_msg     ; Load message for swap result
        call    print_string      ; Print message
        mov     eax, ebx          ; Restore result to EAX
        call    print_int         ; Print result
        call    print_nl          ; Print newline
        
        ; 5. Invert the bits 3-6
        mov     eax, [num1]       ; Load the original number into EAX
        xor     eax, 0x78         ; XOR with 01111000 to invert bits 3-6
        
        ; Print result
        mov     ebx, eax          ; Save result in EBX
        mov     eax, invert_msg   ; Load message for invert result
        call    print_string      ; Print message
        mov     eax, ebx          ; Restore result to EAX
        call    print_int         ; Print result
        call    print_nl          ; Print newline
        
        ; Prompt user for second number
        mov     eax, prompt2      ; Load address of prompt2
        call    print_string      ; Print prompt
        
        call    read_int          ; Read integer into EAX
        mov     [num2], eax       ; Store the second input in num2
        
        ; 6. Determine if 2 numbers have opposite signs
        mov     eax, [num1]       ; Load first number into EAX
        mov     ebx, [num2]       ; Load second number into EBX
        xor     eax, ebx          ; XOR the two numbers (if signs differ, bit 31 will be 1)
        and     eax, 0x80000000   ; Isolate sign bit (bit 31)
        shr     eax, 31           ; Shift right logical to get 0 or 1
        
        ; Print result
        mov     ebx, eax          ; Save result in EBX
        mov     eax, opp_msg      ; Load message for opposite sign result
        call    print_string      ; Print message
        mov     eax, ebx          ; Restore result to EAX
        call    print_int         ; Print result
        call    print_nl          ; Print newline

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret