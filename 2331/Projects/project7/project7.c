#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CACHE_SIZE 4 // Number of blocks in the cache
#define BLOCK_SIZE 16 // Size of each block in bytes

// Structure to represent a cache block
typedef struct {
    int tag;
    bool valid;
    int fifo_order; // For FIFO replacement
    int lru_counter; // For LRU replacement
} CacheBlock;

// Global counter for LRU policy
int lru_counter_global = 0;

// Function prototypes
void direct_mapped_cache(int *addresses, int num_accesses);
void fully_associative_fifo(int *addresses, int num_accesses);
void fully_associative_lru(int *addresses, int num_accesses);

int main() {
    int num_accesses;
    printf("Enter the number of memory accesses: ");
    scanf("%d", &num_accesses);

    int *addresses = malloc(num_accesses * sizeof(int));
    if (addresses == NULL) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    printf("Enter memory addresses in hexadecimal (e.g., 0x0003):\n");
    for (int i = 0; i < num_accesses; i++) {
        printf("Access #%d: ", i + 1);
        scanf("%x", &addresses[i]);
    }

    printf("\n--- Direct Mapped Cache ---\n");
    direct_mapped_cache(addresses, num_accesses);

    printf("\n--- Fully Associative Cache (FIFO) ---\n");
    fully_associative_fifo(addresses, num_accesses);

    printf("\n--- Fully Associative Cache (LRU) ---\n");
    fully_associative_lru(addresses, num_accesses);

    free(addresses);
    return 0;
}

void direct_mapped_cache(int *addresses, int num_accesses) {
    CacheBlock cache[CACHE_SIZE] = {0};
    int hits = 0, compulsory_misses = 0, conflict_misses = 0;

    for (int i = 0; i < num_accesses; i++) {
        int address = addresses[i];
        int index = (address / BLOCK_SIZE) % CACHE_SIZE;
        int tag = address / (BLOCK_SIZE * CACHE_SIZE);

        if (cache[index].valid && cache[index].tag == tag) {
            hits++;
        } else {
            if (!cache[index].valid) {
                compulsory_misses++;
            } else {
                conflict_misses++;
            }
            cache[index].valid = true;
            cache[index].tag = tag;
        }
    }

    printf("Hits: %d\n", hits);
    printf("Compulsory Misses: %d\n", compulsory_misses);
    printf("Conflict Misses: %d\n", conflict_misses);
}

void fully_associative_fifo(int *addresses, int num_accesses) {
    CacheBlock cache[CACHE_SIZE] = {0};
    int hits = 0, compulsory_misses = 0, capacity_misses = 0;
    int fifo_counter = 0;

    for (int i = 0; i < num_accesses; i++) {
        int address = addresses[i];
        int tag = address / BLOCK_SIZE;
        bool hit = false;

        for (int j = 0; j < CACHE_SIZE; j++) {
            if (cache[j].valid && cache[j].tag == tag) {
                hits++;
                hit = true;
                break;
            }
        }

        if (!hit) {
            bool replaced = false;
            for (int j = 0; j < CACHE_SIZE; j++) {
                if (!cache[j].valid) {
                    cache[j].valid = true;
                    cache[j].tag = tag;
                    cache[j].fifo_order = fifo_counter++;
                    compulsory_misses++;
                    replaced = true;
                    break;
                }
            }

            if (!replaced) {
                int oldest = 0;
                for (int j = 1; j < CACHE_SIZE; j++) {
                    if (cache[j].fifo_order < cache[oldest].fifo_order) {
                        oldest = j;
                    }
                }
                cache[oldest].tag = tag;
                cache[oldest].fifo_order = fifo_counter++;
                capacity_misses++;
            }
        }
    }

    printf("Hits: %d\n", hits);
    printf("Compulsory Misses: %d\n", compulsory_misses);
    printf("Capacity Misses: %d\n", capacity_misses);
}

void fully_associative_lru(int *addresses, int num_accesses) {
    CacheBlock cache[CACHE_SIZE] = {0};
    int hits = 0, compulsory_misses = 0, capacity_misses = 0;

    for (int i = 0; i < num_accesses; i++) {
        int address = addresses[i];
        int tag = address / BLOCK_SIZE;
        bool hit = false;

        for (int j = 0; j < CACHE_SIZE; j++) {
            if (cache[j].valid && cache[j].tag == tag) {
                hits++;
                cache[j].lru_counter = ++lru_counter_global;
                hit = true;
                break;
            }
        }

        if (!hit) {
            bool replaced = false;
            for (int j = 0; j < CACHE_SIZE; j++) {
                if (!cache[j].valid) {
                    cache[j].valid = true;
                    cache[j].tag = tag;
                    cache[j].lru_counter = ++lru_counter_global;
                    compulsory_misses++;
                    replaced = true;
                    break;
                }
            }

            if (!replaced) {
                int lru_index = 0;
                for (int j = 1; j < CACHE_SIZE; j++) {
                    if (cache[j].lru_counter < cache[lru_index].lru_counter) {
                        lru_index = j;
                    }
                }
                cache[lru_index].tag = tag;
                cache[lru_index].lru_counter = ++lru_counter_global;
                capacity_misses++;
            }
        }
    }

    printf("Hits: %d\n", hits);
    printf("Compulsory Misses: %d\n", compulsory_misses);
    printf("Capacity Misses: %d\n", capacity_misses);
}
