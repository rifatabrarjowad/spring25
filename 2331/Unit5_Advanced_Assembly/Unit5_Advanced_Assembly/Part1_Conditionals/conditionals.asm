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

        mov eax, 4
        mov ebx, 6

        cmp eax, ebx 
        jl if_block
        
        cmp eax,ebx
        jg elif_block


        mov eax, 15
        call print_int
        jmp end_conditional
        ; NO EXPECTED OUTPUT (YET)

if_block:
        mov eax, 5
        call print_int

elif_block:
        mov eax, 10
        call print_int

end_conditional 

        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret


