#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Memory allocation and process control functions
#include <stdint.h> // Fixed-width integer types

#define FRAME_COUNT 16 // Number of frames in physical memory
#define OFFSET_BITS 8  // Number of bits used for offset within a page

// Structure for a second-level page table entry
typedef struct SecondLevelPageTable {
    int frame_number; // Stores the frame number where the page is stored
    int valid;        // Indicates if the entry is valid (1) or invalid (0)
} SecondLevelPageTable;

// Structure for a first-level page table entry
typedef struct FirstLevelPageTable {
    SecondLevelPageTable **second_level; // Pointer to second-level page table
    int valid; // Indicates if the first-level entry is valid
} FirstLevelPageTable;

// Global variables
FirstLevelPageTable *page_table; // Pointer to the first-level page table
int *physical_memory; // Simulated physical memory array
int frame_index = 0; // Keeps track of the next available frame

// Function to initialize the page table
void initialize_page_table(int first_level_size) {
    page_table = (FirstLevelPageTable *)malloc(sizeof(FirstLevelPageTable) * first_level_size); // Allocate memory for first-level page table
    for (int i = 0; i < first_level_size; i++) { // Iterate through each entry
        page_table[i].second_level = NULL; // Initialize second-level pointer to NULL
        page_table[i].valid = 0; // Mark entry as invalid
    }
    physical_memory = (int *)malloc(sizeof(int) * FRAME_COUNT); // Allocate memory for physical memory simulation
}

// Function to allocate a new second-level page table
SecondLevelPageTable **allocate_second_level(int second_level_size) {
    SecondLevelPageTable **second_level = (SecondLevelPageTable **)malloc(sizeof(SecondLevelPageTable *) * second_level_size); // Allocate memory for second-level page table
    for (int i = 0; i < second_level_size; i++) { // Initialize each entry
        second_level[i] = NULL; // Set each entry to NULL
    }
    return second_level; // Return the allocated second-level page table
}

// Function to handle memory translation
int translate_address(uint16_t virtual_address, int first_level_bits, int second_level_bits) {
    int first_level_index = (virtual_address >> (OFFSET_BITS + second_level_bits)) & ((1 << first_level_bits) - 1); // Extract first-level index
    int second_level_index = (virtual_address >> OFFSET_BITS) & ((1 << second_level_bits) - 1); // Extract second-level index
    int offset = virtual_address & ((1 << OFFSET_BITS) - 1); // Extract offset within the page

    if (!page_table[first_level_index].valid) { // Check if first-level entry is valid
        page_table[first_level_index].second_level = allocate_second_level(1 << second_level_bits); // Allocate second-level table if needed
        page_table[first_level_index].valid = 1; // Mark first-level entry as valid
    }

    if (!page_table[first_level_index].second_level[second_level_index]) { // Check if second-level entry is valid
        if (frame_index >= FRAME_COUNT) { // Check if frames are exhausted
            printf("Out of frames! Time to evict!\n");
            exit(0); // Exit if no more frames are available
        }
        page_table[first_level_index].second_level[second_level_index] = (SecondLevelPageTable *)malloc(sizeof(SecondLevelPageTable)); // Allocate second-level entry
        page_table[first_level_index].second_level[second_level_index]->frame_number = frame_index++; // Assign next available frame
        page_table[first_level_index].second_level[second_level_index]->valid = 1; // Mark entry as valid
    }
    
    int physical_address = (page_table[first_level_index].second_level[second_level_index]->frame_number << OFFSET_BITS) | offset; // Compute physical address
    return physical_address; // Return physical address
}

// Function to free allocated memory
void free_memory(int first_level_size, int second_level_size) {
    for (int i = 0; i < first_level_size; i++) { // Iterate through first-level entries
        if (page_table[i].valid) { // If first-level entry is valid
            for (int j = 0; j < (1 << second_level_size); j++) { // Iterate through second-level entries
                if (page_table[i].second_level[j]) { // If second-level entry exists
                    free(page_table[i].second_level[j]); // Free second-level entry
                }
            }
            free(page_table[i].second_level); // Free second-level table
        }
    }
    free(page_table); // Free first-level table
    free(physical_memory); // Free physical memory
}

int main() {
    int first_level_bits, second_level_bits, num_accesses; // Variables for user input
    printf("Bits in 1st level: ");
    scanf("%d", &first_level_bits); // Read number of first-level bits
    printf("Bits in 2nd level: ");
    scanf("%d", &second_level_bits); // Read number of second-level bits
    printf("Number of accesses: ");
    scanf("%d", &num_accesses); // Read number of memory accesses

    initialize_page_table(1 << first_level_bits); // Initialize page table with given size
    
    for (int i = 0; i < num_accesses; i++) { // Loop for each memory access
        uint16_t virtual_address; // Variable to store virtual address
        printf("Access #%d: 0x", i + 1);
        scanf("%hx", &virtual_address); // Read virtual address
        int physical_address = translate_address(virtual_address, first_level_bits, second_level_bits); // Translate virtual address
        printf("Physical address: 0x%03X\n", physical_address); // Print resulting physical address
    }
    
    free_memory(1 << first_level_bits, second_level_bits); // Free allocated memory before exit
    return 0; // Return success
}
