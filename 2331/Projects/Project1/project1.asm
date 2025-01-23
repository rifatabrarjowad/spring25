; Purpose: The test NASM file for Project 1

%include "asm_io.inc"

; initialized data
segment .data

; uninitialized data
segment .bss


segment .text
        global  asm_main
asm_main:
        enter   0,0               ; setup routine
        pusha

        mov eax, 2025
		call print_int

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret


