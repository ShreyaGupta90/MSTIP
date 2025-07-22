# Custom Memory Allocator (Malloc/Free)

## Overview

This project implements a custom memory allocator in C. The objective of this internship project is to develop a basic version of `malloc` and `free` using system calls like `sbrk()` (or `mmap()`) to allocate memory from the operating system. The custom allocator will manage memory blocks, a free list, and handle block splitting for efficient memory management.

### Libraries Used
- **stdio.h**: For input and output operations.
- **stdlib.h**: For memory management functions and utilities.
- **unistd.h**: For system calls like `sbrk()`.

## Key Features

1. **Custom `malloc` and `free`**:
   - Implement basic versions of `malloc` and `free` using system calls (`sbrk()` or `mmap()`).
   - The `malloc` function allocates memory from the operating system, while `free` deallocates it and returns the memory block to the free list.

2. **Free List Management**:
   - A simple free list is used to track allocated and free memory blocks.
   - The allocator manages a linked list of free memory blocks, which helps improve allocation and deallocation efficiency.

3. **Block Splitting**:
   - When a large block of memory is found in the free list, and if the requested memory size is smaller than the available block, the allocator will split the block into two parts:
     - One part will be used to fulfill the allocation request.
     - The remaining block will be returned to the free list.

## Functional Requirements

1. **`malloc(size_t size)`**:
   - Allocates a memory block of the requested size.
   - If no suitable free block exists, memory is requested from the operating system using `sbrk()` or `mmap()`.
   - If the block found is larger than necessary, it is split into two blocks: one for the requested size and one for the remaining space.

2. **`free(void *ptr)`**:
   - Deallocates memory previously allocated by `malloc`.
   - Adds the freed block back to the free list.
   - Optionally, merges adjacent free blocks to reduce fragmentation.

3. **Block Splitting**:
   - When a block is larger than required, it is split into two parts:
     - One block is allocated to the user.
     - The other part is returned to the free list for future allocations.

4. **Memory Management with System Calls**:
   - The allocator uses `sbrk()` or `mmap()` to extend the heap and allocate memory directly from the operating system.

## Installation

To compile and run this project:

1. Make sure you have a C compiler installed (e.g., GCC).
2. Download or clone the repository:
   ```bash
   git clone https://github.com/your-repo/custom-memory-allocator.git

## 📩 Contact & Contribution

For contributions, feedback, or collaborations, feel free to reach out:  
- **Author:** Shreya Gupta
- **Email:** shreyagupta119809@gmail.com
- **LinkedIn:** https://www.linkedin.com/in/shreya-gupta-2a6a292ab

