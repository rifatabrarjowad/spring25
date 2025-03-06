%include "asm_io.inc"  ; Include the assembly I/O macros

; Data section
segment .data  ; Define initialized data
msg_welcome db "Game Starting Now!", 10, 0  ; Welcome message string with newline
msg_prompt1 db " R, P, S, L, $: ", 0  ; Prompt string for Player 1 input
msg_prompt2 db "R, P, S, L, $: ", 0  ; Prompt string for Player 2 input
msg_win1 db "Player 1 wins!", 10, 0  ; String for Player 1 win message
msg_win2 db "Player 2 wins!", 10, 0  ; String for Player 2 win message
msg_tied db "It's a tie!", 10, 0  ; String for tie message

; Uninitialized section
segment .bss  ; Define uninitialized data
choice_p1 resb 1  ; Reserve 1 byte for Player 1's choice
choice_p2 resb 1  ; Reserve 1 byte for Player 2's choice

segment .text  ; Define code segment
global asm_main  ; Make asm_main accessible externally

asm_main:
    enter 0,0  ; Setup stack frame
    pusha  ; Push all registers onto the stack

    ; Display welcome message
    mov eax, msg_welcome  ; Load address of welcome message into eax
    call print_string  ; Print welcome message

    ; Prompt Player 1 for input
    mov eax, msg_prompt1  ; Load address of Player 1 prompt message into eax
    call print_string  ; Print Player 1 prompt message
    call read_char  ; Read a single character input from Player 1
    mov [choice_p1], al  ; Store Player 1's choice in memory
    call read_char  ; Read and discard newline character

    ; Prompt Player 2 for input
    mov eax, msg_prompt2  ; Load address of Player 2 prompt message into eax
    call print_string  ; Print Player 2 prompt message
    call read_char  ; Read a single character input from Player 2
    mov [choice_p2], al  ; Store Player 2's choice in memory
    call read_char  ; Read and discard newline character

    ; Load choices into registers
    mov al, [choice_p1]  ; Load Player 1's choice into AL register
    mov bl, [choice_p2]  ; Load Player 2's choice into BL register

    ; Check for tie condition first
    cmp al, bl  ; Compare Player 1's choice with Player 2's choice
    je game_tied  ; If they are the same, jump to tie handling

    ; Determine the winner based on Player 1's choice
    cmp al, 'R'  ; Check if Player 1 chose Rock
    je rock_case  ; Jump to rock_case if true
    cmp al, 'P'  ; Check if Player 1 chose Paper
    je paper_case  ; Jump to paper_case if true
    cmp al, 'S'  ; Check if Player 1 chose Scissors
    je scissors_case  ; Jump to scissors_case if true
    cmp al, 'L'  ; Check if Player 1 chose Lizard
    je lizard_case  ; Jump to lizard_case if true
    cmp al, '$'  ; Check if Player 1 chose Spock
    je spock_case  ; Jump to spock_case if true

    ; If input is invalid, exit immediately
    jmp end_game  ; Jump to end_game if no valid choice is found

rock_case:
    cmp bl, 'S'  ; Check if Player 2 chose Scissors
    je player1_win  ; Rock beats Scissors, Player 1 wins
    cmp bl, 'L'  ; Check if Player 2 chose Lizard
    je player1_win  ; Rock beats Lizard, Player 1 wins
    jmp player2_win  ; Otherwise, Player 2 wins

paper_case:
    cmp bl, 'R'  ; Check if Player 2 chose Rock
    je player1_win  ; Paper beats Rock, Player 1 wins
    cmp bl, '$'  ; Check if Player 2 chose Spock
    je player1_win  ; Paper beats Spock, Player 1 wins
    jmp player2_win  ; Otherwise, Player 2 wins

scissors_case:
    cmp bl, 'P'  ; Check if Player 2 chose Paper
    je player1_win  ; Scissors beats Paper, Player 1 wins
    cmp bl, 'L'  ; Check if Player 2 chose Lizard
    je player1_win  ; Scissors beats Lizard, Player 1 wins
    jmp player2_win  ; Otherwise, Player 2 wins

lizard_case:
    cmp bl, 'P'  ; Check if Player 2 chose Paper
    je player1_win  ; Lizard beats Paper, Player 1 wins
    cmp bl, '$'  ; Check if Player 2 chose Spock
    je player1_win  ; Lizard beats Spock, Player 1 wins
    jmp player2_win  ; Otherwise, Player 2 wins

spock_case:
    cmp bl, 'R'  ; Check if Player 2 chose Rock
    je player1_win  ; Spock beats Rock, Player 1 wins
    cmp bl, 'S'  ; Check if Player 2 chose Scissors
    je player1_win  ; Spock beats Scissors, Player 1 wins
    jmp player2_win  ; Otherwise, Player 2 wins

player1_win:
    mov eax, msg_win1  ; Load Player 1 win message into eax
    call print_string  ; Print Player 1 win message
    jmp end_game  ; Jump to end_game

player2_win:
    mov eax, msg_win2  ; Load Player 2 win message into eax
    call print_string  ; Print Player 2 win message
    jmp end_game  ; Jump to end_game

game_tied:
    mov eax, msg_tied  ; Load tie message into eax
    call print_string  ; Print tie message

end_game:
    popa  ; Restore registers from stack
    mov eax, 0  ; Return 0 (exit code)
    leave  ; Clean up stack frame
    ret  ; Return from function
