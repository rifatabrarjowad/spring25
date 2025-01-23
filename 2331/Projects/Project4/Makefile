# Linux Makefile
# Use with make command

AS		:= nasm
ASFLAGS := -f elf -F dwarf
CFLAGS	:= -m32
LDFLAGS := -m32
CC		:= gcc
CXX		:= g++
CXXFLAGS := -m32
TARGETS := project4
DEP := driver.o asm_io.o

.PHONY: clean

%.o: %.asm
	$(AS) $(ASFLAGS) $< 

all: $(TARGETS)

project4: $(DEP)

asm_io.o: asm_io.asm
	$(AS) $(ASFLAGS) -d ELF_TYPE asm_io.asm

project4.o: asm_io.inc

clean :
	rm -f *.o $(TARGETS)
