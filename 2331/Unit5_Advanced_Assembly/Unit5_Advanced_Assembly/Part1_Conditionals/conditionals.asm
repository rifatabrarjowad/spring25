; Purpose: takes notes during class

%include "asm_io.inc"

; initialized data
segment .data
if_promot db "Enter Character :", 0
if_massage db "and... your point is?", 0

if_else_promt dv "Enter a number :", 0
even db "Even", 0
odd db "Odd", 0
happy_face db "😊", 0    ; 😀 A happy face
sad_face db "😢", 0      ; 😞 A sad face
cool_face db "😎", 0     ; 😎 A cool face
angry_face db "😡", 0    ; 😠 An angry face
surprised_face db "😲", 0 ; 😮 A surprised face


and_promt db "Enter a number", 0
amazing db "Amazing!", 0
rocket db "rock!", 0
perfect db "PERFECT", 0
while_promt db "Enter a number"

; uninitialized data
segment .bss


segment .text
        global  asm_main
asm_main:
        enter   0,0               ; setup routine
        pusha


        mov eax, while_promt
        call print_string

        call read_int

while_top:
        mov ebx, eax
        sub ebx, 1
        and eax, ebx
        jnz end_while

        mov eax. perfect
        call print_string
        jmp while_top

end_while:

;         mov ecx, 5 
; for_top:
;         mov eax,ecx
;         call print_int
;         call print_nl
;         loop for_top
        
;         mov eax, rocket
;         call print_string

;         mov eax, and_promt
;         call print_string
;         call read_int
;         cmp eax, -99
;         jg end_if
        
;         cmp eax, -99
;         jl end_if
;         mov eax, amazing
;         call print_string

; end_if:



        ;if else
;         mov eax, if_else_promt
;         call print_string
;         call read_int
;         and eax, 1 
;         cmp eax, 1
;         je else_block
;         mov eax, even
;         jmp end_structure

; else_block:
;         mov eax, odd
; end_structure:
;         call print_string
        
        ; mov eax, if_promot 
        ; call print_string

        ; call read_char

        ; cmp eax, '&'
        ; jne end_if

        ; mov eax, if_massage
        ; call print_string


        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret


