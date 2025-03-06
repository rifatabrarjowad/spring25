# Linux Makefile
# Use with make command

AS := nasm
ASFLAGS := -f elf -F dwarf
CFLAGS := -m32
LDFLAGS := -m32 -no-pie
CC := gcc
CXX := g++
CXXFLAGS := -m32
TARGETS := project6
DEP := project6.o driver.o asm_io.o

.PHONY: all clean

# Build all targets
all: $(TARGETS)

# Rule to build project6
project6: $(DEP)
	$(CC) $(LDFLAGS) -o project6 $(DEP)  # <-- Make sure this line is indented with a TAB

# Assemble asm_io.asm
asm_io.o: asm_io.asm
	$(AS) $(ASFLAGS) -d ELF_TYPE asm_io.asm -o asm_io.o  # <-- TAB indentation

# Assemble project6.asm
project6.o: project6.asm asm_io.inc
	$(AS) $(ASFLAGS) project6.asm -o project6.o  # <-- TAB indentation

# Compile driver.c
driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c -o driver.o  # <-- TAB indentation

# Clean up object files and the executable
clean:
	rm -f project6 *.o  # <-- TAB indentation
