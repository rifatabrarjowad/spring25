; Purpose: takes notes during class

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

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret


