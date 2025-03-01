%include "asm_io.inc"

; initialized data
segment .data
    prompt1 db "Enter a number: ", 0
    msg_mult db "x16 if negative: ", 0
    msg_8thbit db "Turn on 8th bit if odd: ", 0
    msg_zero db "Zero out if even: ", 0
    msg_swap db "Swap top & bottom 16 bits: ", 0
    msg_invert db "Invert bits 3 - 6: ", 0
    prompt2 db "Enter a second number: ", 0
    msg_opposite db "Opposite sign? ", 0

; uninitialized data
segment .bss
    num1 resd 1    ; First input number
    num2 resd 1    ; Second input number
    result resd 1  ; Result of operations

segment .text
    global  asm_main
asm_main:
    enter   0,0               ; setup routine
    pusha

    ; Prompt for first number
    mov eax, prompt1
    call print_string
    
    ; Read the first number
    call read_int
    mov [num1], eax

    ; ===== Operation 1: Multiply by 16 if the number is negative =====
    mov eax, [num1]           ; Load the number into eax
    mov ebx, eax              ; Copy the number
    
    ; Create a mask: all 1s if negative, all 0s if positive
    sar ebx, 31               ; If negative: 0xFFFFFFFF, if positive: 0x00000000
    
    ; Create a value to add: original value * 15 if negative, 0 if positive
    mov ecx, [num1]           ; Load original number
    imul ecx, 15              ; Multiply by 15
    and ecx, ebx              ; If negative: keep the value, if positive: make it 0
    
    ; Add the calculated value to the original
    add eax, ecx              ; For negative numbers: x + 15x = 16x
                              ; For positive numbers: x + 0 = x
    
    mov [result], eax         ; Store the result
    
    ; Print result message
    mov eax, msg_mult
    call print_string
    
    ; Print the result
    mov eax, [result]
    call print_int
    call print_nl
    
    ; ===== Operation 2: Turn on the 8th bit if the number is odd =====
    mov eax, [num1]           ; Load the original number
    mov ebx, eax              ; Copy the number
    and ebx, 1                ; Isolate the least significant bit
    
    ; Create a mask: 0x100 if odd, 0x000 if even
    shl ebx, 8                ; Shift the LSB to position 8
    
    ; Set the 8th bit if odd
    or eax, ebx               ; Apply the mask
    
    mov [result], eax         ; Store the result
    
    ; Print result message
    mov eax, msg_8thbit
    call print_string
    
    ; Print the result
    mov eax, [result]
    call print_int
    call print_nl
    
    ; ===== Operation 3: Zero out all bits when even =====
    mov eax, [num1]           ; Load the original number
    mov ebx, eax              ; Copy the number
    and ebx, 1                ; Isolate the least significant bit
    
    ; Create a mask: all 1s if odd, all 0s if even
    neg ebx                   ; If odd (ebx=1): ebx=0xFFFFFFFF, if even (ebx=0): ebx=0
    
    ; Apply the mask
    and eax, ebx              ; If odd: keep all bits, if even: zero out
    
    mov [result], eax         ; Store the result
    
    ; Print result message
    mov eax, msg_zero
    call print_string
    
    ; Print the result
    mov eax, [result]
    call print_int
    call print_nl
    
    ; ===== Operation 4: Swap the top 16 bits and the bottom 16 bits =====
    mov eax, [num1]           ; Load the original number
    ror eax, 16               ; Rotate right by 16 bits (swap halves)
    mov [result], eax         ; Store the result
    
    ; Print result message
    mov eax, msg_swap
    call print_string
    
    ; Print the result
    mov eax, [result]
    call print_int
    call print_nl
    
    ; ===== Operation 5: Invert the bits 3 - 6 =====
    mov eax, [num1]           ; Load the original number
    xor eax, 0x78             ; XOR with 0x78 (01111000 in binary)
    mov [result], eax         ; Store the result
    
    ; Print result message
    mov eax, msg_invert
    call print_string
    
    ; Print the result
    mov eax, [result]
    call print_int
    call print_nl
    
    ; ===== Operation 6: Determine if 2 numbers have opposite signs =====
    ; Prompt for second number
    mov eax, prompt2
    call print_string
    
    ; Read the second number
    call read_int
    mov [num2], eax
    
    ; Check if numbers have opposite signs
    mov eax, [num1]           ; Load first number
    mov ebx, [num2]           ; Load second number
    xor eax, ebx              ; XOR the numbers
    and eax, 0x80000000       ; Isolate the sign bit (bit 31)
    shr eax, 31               ; Shift right to get a 0 or 1 result
    
    mov [result], eax         ; Store the result
    
    ; Print result message
    mov eax, msg_opposite
    call print_string
    
    ; Print the result
    mov eax, [result]
    call print_int
    call print_nl

    popa
    mov eax, 0                ; return back to C
    leave                     
    ret