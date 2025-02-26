; Purpose: The implementation of Project 5 - Bit Twiddling

%include "asm_io.inc"

section .data
    prompt_num db "Enter a number: ", 0
    prompt_second_num db "Enter a second number: ", 0
    msg_x16 db "x16 if negative: ", 0
    msg_8th_bit db "Turn on 8th bit if odd: ", 0
    msg_zero_even db "Zero out if even: ", 0
    msg_swap db "Swap top & bottom 16 bits: ", 0
    msg_invert db "Invert bits 3 - 6: ", 0
    msg_opposite db "Opposite sign? ", 0
    newline db 10, 0

section .bss
    num resd 1
    second_num resd 1

section .text
    global asm_main

asm_main:
    enter 0,0               ; setup routine
    pusha

    ; Prompt for first number
    mov eax, prompt_num
    call print_string
    call read_int
    mov [num], eax

    ; Multiply by 16 if negative
    mov eax, msg_x16
    call print_string
    mov eax, [num]
    cmp eax, 0
    jge skip_mult
    shl eax, 4 ; Multiply by 16 using shift left
    mov [num], eax
    skip_mult:
    call print_int
    call print_nl

    ; Turn on 8th bit if odd
    mov eax, msg_8th_bit
    call print_string
    mov eax, [num]
    test eax, 1
    jz skip_set_8th
    or eax, 0x80 ; Set 8th bit while preserving sign
    mov [num], eax
    skip_set_8th:
    call print_int
    call print_nl

    ; Zero out all bits if even
    mov eax, msg_zero_even
    call print_string
    mov eax, [num]
    test eax, 1
    jnz skip_zero
    mov eax, 0 ; Zero out if even
    skip_zero:
    call print_int
    call print_nl

    ; Swap top 16 and bottom 16 bits
    mov eax, msg_swap
    call print_string
    mov eax, [num]
    rol eax, 16 ; Rotate left by 16 bits
    call print_int
    call print_nl

    ; Invert bits 3-6
    mov eax, msg_invert
    call print_string
    mov eax, [num]
    xor eax, 0x78 ; Toggle bits 3-6
    call print_int
    call print_nl

    ; Prompt for second number
    mov eax, prompt_second_num
    call print_string
    call read_int
    mov [second_num], eax

    ; Check if numbers have opposite signs
    mov eax, msg_opposite
    call print_string
    mov eax, [num]
    mov ebx, [second_num]
    xor eax, ebx
    test eax, 0x80000000 ; Check sign bit
    setnz al
    movzx eax, al
    call print_int
    call print_nl

    popa
    mov eax, 0            ; return back to C
    leave
    ret
