#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FRAME_COUNT 16 // Number of frames in physical memory
#define OFFSET_BITS 8  // Offset bits

// Structure for a second-level page table entry
typedef struct SecondLevelPageTable {
    int frame_number; // Stores the frame number
    int valid;        // Valid bit
} SecondLevelPageTable;

// Structure for first-level page table entry
typedef struct FirstLevelPageTable {
    SecondLevelPageTable **second_level;
    int valid;
} FirstLevelPageTable;

// Global variables
FirstLevelPageTable *page_table;
int *physical_memory;
int frame_index = 0;

// Function to initialize the page table
void initialize_page_table(int first_level_size) {
    page_table = (FirstLevelPageTable *)malloc(sizeof(FirstLevelPageTable) * first_level_size);
    for (int i = 0; i < first_level_size; i++) {
        page_table[i].second_level = NULL;
        page_table[i].valid = 0;
    }
    physical_memory = (int *)malloc(sizeof(int) * FRAME_COUNT);
}

// Function to allocate a new second-level page table
SecondLevelPageTable **allocate_second_level(int second_level_size) {
    SecondLevelPageTable **second_level = (SecondLevelPageTable **)malloc(sizeof(SecondLevelPageTable *) * second_level_size);
    for (int i = 0; i < second_level_size; i++) {
        second_level[i] = NULL;
    }
    return second_level;
}

// Function to handle memory translation
int translate_address(uint16_t virtual_address, int first_level_bits, int second_level_bits) {
    int first_level_index = (virtual_address >> (OFFSET_BITS + second_level_bits)) & ((1 << first_level_bits) - 1);
    int second_level_index = (virtual_address >> OFFSET_BITS) & ((1 << second_level_bits) - 1);
    int offset = virtual_address & ((1 << OFFSET_BITS) - 1);

    if (!page_table[first_level_index].valid) {
        printf("Creating new first-level page table at index %d\n", first_level_index);
        page_table[first_level_index].second_level = allocate_second_level(1 << second_level_bits);
        page_table[first_level_index].valid = 1;
    }

    if (!page_table[first_level_index].second_level[second_level_index]) {
        if (frame_index >= FRAME_COUNT) {
            printf("Out of frames! Time to evict!\n");
            exit(0);
        }
        printf("Page fault at index [%d][%d], allocating frame %d\n", first_level_index, second_level_index, frame_index);
        page_table[first_level_index].second_level[second_level_index] = (SecondLevelPageTable *)malloc(sizeof(SecondLevelPageTable));
        page_table[first_level_index].second_level[second_level_index]->frame_number = frame_index++;
        page_table[first_level_index].second_level[second_level_index]->valid = 1;
    }
    
    int physical_address = (page_table[first_level_index].second_level[second_level_index]->frame_number << OFFSET_BITS) | offset;
    return physical_address;
}

// Function to free allocated memory
void free_memory(int first_level_size, int second_level_size) {
    for (int i = 0; i < first_level_size; i++) {
        if (page_table[i].valid) {
            for (int j = 0; j < (1 << second_level_size); j++) {
                if (page_table[i].second_level[j]) {
                    free(page_table[i].second_level[j]);
                }
            }
            free(page_table[i].second_level);
        }
    }
    free(page_table);
    free(physical_memory);
}

int main() {
    int first_level_bits, second_level_bits, num_accesses;
    printf("Enter bits for first-level page table: ");
    scanf("%d", &first_level_bits);
    printf("Enter bits for second-level page table: ");
    scanf("%d", &second_level_bits);
    printf("Enter number of memory accesses: ");
    scanf("%d", &num_accesses);

    initialize_page_table(1 << first_level_bits);
    
    for (int i = 0; i < num_accesses; i++) {
        uint16_t virtual_address;
        printf("Access #%d: 0x", i + 1);
        scanf("%hx", &virtual_address);
        int physical_address = translate_address(virtual_address, first_level_bits, second_level_bits);
        printf("Physical address: 0x%03X\n", physical_address);
    }
    
    free_memory(1 << first_level_bits, second_level_bits);
    return 0;
}
