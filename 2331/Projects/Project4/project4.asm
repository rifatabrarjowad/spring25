%include "asm_io.inc"

segment .data
    prompt db "Enter your favorite number: ", 0
    newline db 10, 0
    times10_msg db "Number * 10: ", 0
    times72_msg db "Number * 72: ", 0
    times81_msg db "Number * 81: ", 0

segment .bss
    number resd 1  ; Reserve space for an integer

segment .text
    global asm_main
asm_main:
    enter 0, 0
    pusha

    ; Print prompt
    mov eax, prompt
    call print_string

    ; Read integer input
    call read_int
    mov [number], eax  ; Store input in variable

    ; Print newline
    mov eax, newline
    call print_string

    ; Print starting number
    mov eax, [number]
    call print_int
    call print_nl

    ; Calculate and print number * 10
    mov eax, times10_msg
    call print_string
    mov eax, [number]
    imul eax, 10
    call print_int
    call print_nl

    ; Calculate and print number * 72
    mov eax, times72_msg
    call print_string
    mov eax, [number]
    imul eax, 72
    call print_int
    call print_nl

    ; Calculate and print number * 81
    mov eax, times81_msg
    call print_string
    mov eax, [number]
    imul eax, 81
    call print_int
    call print_nl

    popa
    mov eax, 0  ; Return 0
    leave
    ret
