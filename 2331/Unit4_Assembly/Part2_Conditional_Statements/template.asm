; Original Author: Paul Carter
; Updated by: Megan Avery Summer 2023
; 
; Purpose: template file for writing an assembly program

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

        ; NO EXPECTED OUTPUT FOR BASE TEMPLATE CODE

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret


