; Purpose: The implementation of Project 5

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

        ; NO EXPECTED OUTPUT (YET)
        ; TODO: Implemement project 4

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret


