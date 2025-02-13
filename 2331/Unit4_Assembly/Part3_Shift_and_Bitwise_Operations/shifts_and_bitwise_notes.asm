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
        mov eax, 0FH ;
        shl eax, 4 
        dump_regs 1
        call print_nl

        mov eax, 080000000H
        shr eax, 5
        dump_regs 2
        call print_nl

        mov eax, 0F0000000H
        shl eax, 5
        mov ebx, 0
        setc bl
        dump_regs 3
        call print_nl

        mov eax, 080000000H
        sar eax, 3
        dump_regs 4
        call print_nl
        
        mov eax, 080000000H
        rol eax, 3
        dump_regs 5
        call print_nl


        mov eax, 0FH
        mov ebx, 09H
        and eax, ebx
        dump_regs 6
        call print_nl

        mov eax, 00BH
        mov ebx, 04H
        or eax, ebx 
        dump_regs 7
        call print_nl

        mov eax, 0FH
        mov ebx, 8
        not ebx
        and eax, ebx 
        dump_regs 8
        call print_nl

        xor eax, eax 


        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret