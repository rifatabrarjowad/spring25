#include <stdio.h>            // Include the standard I/O library for input/output functions
#include <stdlib.h>           // Include the standard library for memory allocation functions

#define PAGE_COUNT 8          // Define a constant for the number of pages in memory

// Define the structure for a node in the page list
typedef struct Node {
    int page;                 // Page number
    int ref_bit;              // Reference bit (used in Second Chance algorithm)
    struct Node* next;        // Pointer to the next node
} Node;

// Function to create a new node with a given page number
Node* create_node(int page) {
    Node* node = (Node*)malloc(sizeof(Node));  // Allocate memory for the new node
    node->page = page;         // Set the page number
    node->ref_bit = 1;         // Initialize the reference bit to 1
    node->next = NULL;         // Set the next pointer to NULL
    return node;               // Return the new node
}

// Function to print the current state of the list
void print_list(Node* head, int access_num, int is_fault) {
    if (access_num == 0) return;               // Do not print for the first (0th) access
    printf("Access #%d%s: ", access_num, is_fault ? "*" : "");  // Print access number with * if page fault
    Node* temp = head;                         // Temporary pointer to traverse the list
    while (temp) {                             // Traverse the list
        printf("%d (%d) -> ", temp->page, temp->ref_bit);  // Print page and ref_bit
        temp = temp->next;                     // Move to the next node
    }
    printf("NULL\n");                          // Print end of list
}

// Function to check if a page exists in the list
int page_in_list(Node* head, int page) {
    Node* temp = head;                         // Start from the head
    while (temp) {                             // Traverse the list
        if (temp->page == page)                // If page is found
            return 1;                          // Return 1 (true)
        temp = temp->next;                     // Move to next node
    }
    return 0;                                  // Return 0 (false) if not found
}

// FIFO algorithm simulation
void simulate_fifo(int accesses[], int n) {
    printf("----------------------------------------------------------------------------\nFIFO: ");  // Print header
    Node *head = NULL, *tail = NULL;           // Initialize head and tail of the list
    for (int i = 1; i <= PAGE_COUNT; i++) {    // Create the initial list of pages
        Node* new_node = create_node(i);       // Create new node
        if (!head)                             // If list is empty
            head = tail = new_node;            // Set head and tail to new node
        else {
            tail->next = new_node;             // Append to end of list
            tail = new_node;                   // Update tail
        }
    }
    Node* temp = head;                         // Temp pointer to print list
    while (temp) {
        printf("%d (%d) -> ", temp->page, temp->ref_bit);  // Print initial list
        temp = temp->next;
    }
    printf("NULL\n");

    for (int i = 0; i < n; i++) {              // Loop over each page access
        int page = accesses[i];                // Current page access
        int is_fault = !page_in_list(head, page);  // Check for page fault

        if (is_fault) {                        // If page fault occurs
            Node* old = head;                  // Remove the first node (FIFO)
            head = head->next;                 // Move head
            free(old);                         // Free old node
            Node* new_node = create_node(page);  // Create new node for accessed page
            tail->next = new_node;             // Add to end of list
            tail = new_node;                   // Update tail
        }
        print_list(head, i + 1, is_fault);     // Print current list state
    }
}

// Second Chance algorithm simulation
void simulate_second_chance(int accesses[], int n) {
    printf("----------------------------------------------------------------------------\nSecond chance: ");  // Print header
    Node *head = NULL, *tail = NULL;           // Initialize head and tail
    for (int i = 1; i <= PAGE_COUNT; i++) {    // Create initial list
        Node* new_node = create_node(i);       // Create new node
        if (!head)
            head = tail = new_node;            // First node
        else {
            tail->next = new_node;             // Add to end
            tail = new_node;
        }
    }
    Node* temp = head;                         // Print initial list
    while (temp) {
        printf("%d (%d) -> ", temp->page, temp->ref_bit);
        temp = temp->next;
    }
    printf("NULL\n");

    for (int i = 0; i < n; i++) {              // For each page access
        int page = accesses[i];                // Get current page
        int is_fault = !page_in_list(head, page);  // Check if page is in list

        if (!is_fault) {                       // If page is found
            Node* temp = head;                 // Traverse to set ref_bit
            while (temp) {
                if (temp->page == page) {
                    temp->ref_bit = 1;         // Set reference bit
                    break;
                }
                temp = temp->next;
            }
        } else {                               // If page fault
            while (1) {                        // Loop to find victim
                if (head->ref_bit == 0) {      // If reference bit is 0
                    Node* to_remove = head;    // Remove node
                    head = head->next;
                    free(to_remove);
                    Node* new_node = create_node(page);  // Create new node
                    tail->next = new_node;     // Append to end
                    tail = new_node;
                    break;
                } else {                       // If reference bit is 1
                    head->ref_bit = 0;         // Set it to 0
                    tail->next = head;         // Move node to end
                    tail = head;
                    head = head->next;         // Advance head
                    tail->next = NULL;         // Null-terminate tail
                }
            }
        }
        print_list(head, i + 1, is_fault);     // Print list state
    }
}

// LRU algorithm simulation
void simulate_lru(int accesses[], int n) {
    printf("----------------------------------------------------------------------------\nLRU: ");  // Print header
    Node *head = NULL;                         // Head of list

    for (int i = 1; i <= 8; i++) {             // Create list 1 → 2 → ... → 8
        Node* new_node = create_node(i);
        if (!head) {
            head = new_node;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = new_node;
        }
    }

    Node* prev = NULL;                         // Reversing the list
    Node* current = head;
    Node* next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;                               // Update head to reversed list

    Node* temp = head;                         // Print initial list
    while (temp) {
        printf("%d (%d) -> ", temp->page, temp->ref_bit);
        temp = temp->next;
    }
    printf("NULL\n");

    for (int i = 0; i < n; i++) {              // For each access
        int page = accesses[i];                // Get page number
        int is_fault = !page_in_list(head, page);  // Check if in memory

        Node *prev = NULL, *curr = head;       // Find page in list
        while (curr && curr->page != page) {
            prev = curr;
            curr = curr->next;
        }

        if (curr) {                            // If found
            if (prev) {
                prev->next = curr->next;       // Remove from current pos
                curr->next = head;             // Move to front
                head = curr;
            }
        } else {                               // If not found
            Node *prev_tail = NULL, *tail = head;
            while (tail->next) {               // Find last node
                prev_tail = tail;
                tail = tail->next;
            }
            if (prev_tail) {
                prev_tail->next = NULL;        // Remove last node
                free(tail);
            }

            Node* new_node = create_node(page);  // Create new node
            new_node->next = head;             // Add to front
            head = new_node;
        }

        print_list(head, i + 1, is_fault);     // Print current state
    }
}

// Main function
int main() {
    int n;                                     // Number of page accesses
    printf("Number of accesses? ");            // Prompt user
    scanf("%d", &n);                           // Read number of accesses

    int accesses[n];                           // Array to hold access sequence
    for (int i = 0; i < n; i++) {              // Read each page number
        printf("Access #%d: ", i + 1);
        scanf("%d", &accesses[i]);
    }

    simulate_fifo(accesses, n);                // Simulate FIFO
    simulate_second_chance(accesses, n);       // Simulate Second Chance
    simulate_lru(accesses, n);                 // Simulate LRU

    return 0;                                  // Exit program
}
