#include <stdio.h> // Include standard input-output library
#include <stdlib.h> // Include standard library for memory allocation and utilities
#include <stdbool.h> // Include boolean type definitions

#define CACHE_SIZE 4 // Number of blocks in the cache
#define BLOCK_SIZE 16 // Size of each block in bytes

// Cache Block Structure
typedef struct { 
    int tag; // Stores the tag part of the address
    bool valid; // Indicates whether the cache block is valid
    int fifo_order; // For FIFO replacement policy
    int lru_counter; // For LRU replacement policy
} CacheBlock;

int lru_counter_global = 0; // Global counter for LRU replacement

// Function prototypes
void direct_mapped_cache(int *addresses, int num_accesses); // Function for direct-mapped cache simulation
void fully_associative_fifo(int *addresses, int num_accesses); // Function for FIFO replacement policy
void fully_associative_lru(int *addresses, int num_accesses); // Function for LRU replacement policy

int main() {
    int num_accesses; // Variable to store the number of memory accesses
    printf("Enter the number of memory accesses: "); // Prompt user for input
    scanf("%d", &num_accesses); // Read the number of accesses

    int *addresses = malloc(num_accesses * sizeof(int)); // Allocate memory for storing addresses
    if (addresses == NULL) { // Check if memory allocation failed
        perror("Memory allocation failed"); // Print error message
        return EXIT_FAILURE; // Exit program with failure status
    }

    printf("Enter memory addresses in hexadecimal format (e.g., 0x0003):\n"); // Prompt user for addresses
    for (int i = 0; i < num_accesses; i++) { // Loop through each access
        printf("Access #%d: ", i + 1); // Print access number
        scanf("%x", &addresses[i]); // Read the address in hexadecimal
    }

    printf("\n--- Direct Mapped Cache ---\n"); // Section header for direct-mapped cache
    direct_mapped_cache(addresses, num_accesses); // Call direct-mapped cache function

    printf("\n--- Fully Associative Cache (FIFO) ---\n"); // Section header for FIFO replacement
    fully_associative_fifo(addresses, num_accesses); // Call FIFO replacement function

    printf("\n--- Fully Associative Cache (LRU) ---\n"); // Section header for LRU replacement
    fully_associative_lru(addresses, num_accesses); // Call LRU replacement function

    free(addresses); // Free allocated memory
    return 0; // Exit program successfully
}

void direct_mapped_cache(int *addresses, int num_accesses) {
    CacheBlock cache[CACHE_SIZE] = {0}; // Initialize cache blocks
    int hits = 0, compulsory_misses = 0, conflict_misses = 0; // Initialize counters

    for (int i = 0; i < num_accesses; i++) { // Loop through each memory access
        int address = addresses[i]; // Get the current address
        int index = (address / BLOCK_SIZE) % CACHE_SIZE; // Compute cache index
        int tag = address / (BLOCK_SIZE * CACHE_SIZE); // Compute cache tag

        if (cache[index].valid && cache[index].tag == tag) { // Check for cache hit
            hits++; // Increment hit counter
        } else { // Cache miss
            if (!cache[index].valid) { // If block is invalid
                compulsory_misses++; // Increment compulsory miss counter
            } else { // Block is valid but tag mismatch
                conflict_misses++; // Increment conflict miss counter
            }
            cache[index].valid = true; // Set block as valid
            cache[index].tag = tag; // Update tag
        }
    }

    printf("Hits: %d\n", hits); // Print number of hits
    printf("Compulsory Misses: %d\n", compulsory_misses); // Print compulsory misses
    printf("Conflict Misses: %d\n", conflict_misses); // Print conflict misses
}

void fully_associative_fifo(int *addresses, int num_accesses) {
    CacheBlock cache[CACHE_SIZE] = {0}; // Initialize cache blocks
    int hits = 0, compulsory_misses = 0, capacity_misses = 0; // Initialize counters
    int fifo_counter = 0; // FIFO replacement order counter

    for (int i = 0; i < num_accesses; i++) { // Loop through each memory access
        int address = addresses[i]; // Get the current address
        int tag = address / BLOCK_SIZE; // Compute cache tag
        bool hit = false; // Initialize hit flag

        for (int j = 0; j < CACHE_SIZE; j++) { // Search for tag in cache
            if (cache[j].valid && cache[j].tag == tag) { // Check for hit
                hits++; // Increment hit counter
                hit = true; // Set hit flag
                break; // Exit loop
            }
        }

        if (!hit) { // If not a hit
            bool replaced = false; // Initialize replacement flag
            for (int j = 0; j < CACHE_SIZE; j++) { // Search for invalid block
                if (!cache[j].valid) { // If block is invalid
                    cache[j].valid = true; // Set block as valid
                    cache[j].tag = tag; // Update tag
                    cache[j].fifo_order = fifo_counter++; // Set FIFO order
                    compulsory_misses++; // Increment compulsory miss counter
                    replaced = true; // Set replacement flag
                    break; // Exit loop
                }
            }

            if (!replaced) { // If no invalid block found
                int oldest = 0; // Initialize oldest block index
                for (int j = 1; j < CACHE_SIZE; j++) { // Find oldest block
                    if (cache[j].fifo_order < cache[oldest].fifo_order) {
                        oldest = j; // Update oldest block index
                    }
                }
                cache[oldest].tag = tag; // Replace oldest block's tag
                cache[oldest].fifo_order = fifo_counter++; // Update FIFO order
                capacity_misses++; // Increment capacity miss counter
            }
        }
    }

    printf("Hits: %d\n", hits); // Print number of hits
    printf("Compulsory Misses: %d\n", compulsory_misses); // Print compulsory misses
    printf("Capacity Misses: %d\n", capacity_misses); // Print capacity misses
}

void fully_associative_lru(int *addresses, int num_accesses) {
    CacheBlock cache[CACHE_SIZE] = {0}; // Initialize cache blocks
    int hits = 0, compulsory_misses = 0, capacity_misses = 0; // Initialize counters

    for (int i = 0; i < num_accesses; i++) { // Loop through each memory access
        int address = addresses[i]; // Get the current address
        int tag = address / BLOCK_SIZE; // Compute cache tag
        bool hit = false; // Initialize hit flag

        for (int j = 0; j < CACHE_SIZE; j++) { // Search for tag in cache
            if (cache[j].valid && cache[j].tag == tag) { // Check for hit
                hits++; // Increment hit counter
                cache[j].lru_counter = ++lru_counter_global; // Update LRU counter
                hit = true; // Set hit flag
                break; // Exit loop
            }
        }

        if (!hit) { // If not a hit
            bool replaced = false; // Initialize replacement flag
            for (int j = 0; j < CACHE_SIZE; j++) { // Search for invalid block
                if (!cache[j].valid) { // If block is invalid
                    cache[j].valid = true; // Set block as valid
                    cache[j].tag = tag; // Update tag
                    cache[j].lru_counter = ++lru_counter_global; // Update LRU counter
                    compulsory_misses++; // Increment compulsory miss counter
                    replaced = true; // Set replacement flag
                    break; // Exit loop
                }
            }

            if (!replaced) { // If no invalid block found
                int lru_index = 0; // Initialize LRU block index
                for (int j = 1; j < CACHE_SIZE; j++) { // Find LRU block
                    if (cache[j].lru_counter < cache[lru_index].lru_counter) {
                        lru_index = j; // Update LRU block index
                    }
                }
                cache[lru_index].tag = tag; // Replace LRU block's tag
                cache[lru_index].lru_counter = ++lru_counter_global; // Update LRU counter
                capacity_misses++; // Increment capacity miss counter
            }
        }
    }

    printf("Hits: %d\n", hits); // Print number of hits
    printf("Compulsory Misses: %d\n", compulsory_misses); // Print compulsory misses
    printf("Capacity Misses: %d\n", capacity_misses); // Print capacity misses
}
