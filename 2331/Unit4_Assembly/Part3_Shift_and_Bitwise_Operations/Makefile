# Linux Makefile
# Use with make command

AS		:= nasm
ASFLAGS := -f elf -F dwarf
CFLAGS	:= -m32
LDFLAGS := -m32
CC		:= gcc
CXX		:= g++
CXXFLAGS := -m32
TARGETS := shifts_and_bitwise_notes template
DEP := driver.o asm_io.o

.PHONY: clean

%.o: %.asm
	$(AS) $(ASFLAGS) $< 

all: $(TARGETS)

loops_notes: $(DEP)
shifts_and_bitwise_notes: $(DEP)
template: $(DEP)

asm_io.o: asm_io.asm
	$(AS) $(ASFLAGS) -d ELF_TYPE asm_io.asm

shifts_and_bitwise_notes.o: asm_io.inc
template.o: asm_io.inc

clean :
	rm -f *.o $(TARGETS)
