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

        ;dump_regs 1
        ;call print_nl
        ;dump_regs 2

        ; mov eax, 011111111H
        ; mov ebx, 011111111H
        ; mov ecx, 011111111H
        ; mov edx, 011111111H

        ; mov al, 0AAH
        ; mov bh, 0BBh
        ; mov cx, 0CCCCH
        ; mov dx, 0DDDDDDDDH

        ; mov eax, 011111111H
        ; mov ax, 02222H
        ; mov ah, 033H
        ; mov al, 044H

        ; dump_regs 1
        mov eax,4
        add eax, eax
        add eax, eax
        mpv ebx, eax

        dump_regs 1

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret


