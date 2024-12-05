#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sbrk()

// Block structure to store the size of the block and the next block in the free list
typedef struct Block {
    size_t size;         // Size of the block (including header)
    struct Block* next;  // Pointer to the next free block
} Block;

// Head of the free list
static Block* free_list = NULL;

// Custom malloc function using sbrk
void* my_malloc(size_t size) {
    Block* prev = NULL;
    Block* curr = free_list;
    
    // Align the requested size to be a multiple of pointer size (e.g., 8 bytes)
    size = (size + sizeof(void*) - 1) & ~(sizeof(void*) - 1);

    // Search for a free block that can accommodate the requested size
    while (curr != NULL) {
        if (curr->size >= size + sizeof(Block)) {  // Ensure enough space for the block header
            // If the block is larger than needed, split it
            if (curr->size > size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)curr + sizeof(Block) + size);
                new_block->size = curr->size - size - sizeof(Block);
                new_block->next = curr->next;
                curr->next = new_block;
            }

            // Allocate the block
            if (prev) {
                prev->next = curr->next;
            } else {
                free_list = curr->next;
            }

            curr->size = size;  // Set the block size to the requested size
            return (void*)((char*)curr + sizeof(Block));  // Return the memory after the block header
        }

        prev = curr;
        curr = curr->next;
    }

    // If no suitable block is found, request more memory from the system using sbrk
    size_t total_size = size + sizeof(Block);
    Block* new_block = (Block*)sbrk(total_size);
    if (new_block == (void*)-1) {
        return NULL;  // sbrk() failed
    }

    // Initialize the new block
    new_block->size = size;
    new_block->next = NULL;

    return (void*)((char*)new_block + sizeof(Block));  // Return memory after the block header
}

// Custom free function
void my_free(void* ptr) {
    if (ptr == NULL) return;

    Block* block_to_free = (Block*)((char*)ptr - sizeof(Block));  // Get the block header

    // Add the freed block to the free list
    block_to_free->next = free_list;
    free_list = block_to_free;

    // Coalesce adjacent free blocks
    Block* curr = free_list;
    while (curr != NULL && curr->next != NULL) {
        if ((char*)curr + curr->size + sizeof(Block) == (char*)curr->next) {
            // Merge with the next block
            curr->size += curr->next->size + sizeof(Block);
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

// Helper function to print the free list (for debugging)
void print_free_list() {
    Block* curr = free_list;
    printf("Free list:\n");
    while (curr != NULL) {
        printf("Block at %p, size: %zu\n", (void*)curr, curr->size);
        curr = curr->next;
    }
}

int main() {
    // Simulate memory allocations and deallocations
    void* ptr1 = my_malloc(200);
    printf("Allocated 200 bytes at %p\n", ptr1);

    void* ptr2 = my_malloc(100);
    printf("Allocated 100 bytes at %p\n", ptr2);

    print_free_list();

    // Free some memory
    my_free(ptr1);
    printf("Freed 200 bytes at %p\n", ptr1);

    void* ptr3 = my_malloc(50);
    printf("Allocated 50 bytes at %p\n", ptr3);

    print_free_list();

    // Free all memory
    my_free(ptr2);
    my_free(ptr3);
    printf("Freed all memory.\n");

    print_free_list();

    return 0;
}