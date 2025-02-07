; Purpose: takes notes during class

%include "asm_io.inc"

MEANING_OF_LIFE equ 42

%define YEARS_IN_DECADE 10

; initialized data
segment .data
age dd 31
greeting db "Hello Wrold",0


; uninitialized data
segment .bss


segment .text
        global  asm_main
asm_main:
        enter   0,0               ; setup routine
        pusha
        mov eax, [age]
        mov edx, [greeting]
        dump_regs 1
        ; mov eax, MEANING_OF_LIFE
        ; mov ebx, YEARS_IN_DECADE
        ; dump_regs 1

        ; NO EXPECTED OUTPUT (YET)

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret