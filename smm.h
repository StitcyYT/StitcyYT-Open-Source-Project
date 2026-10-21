/*
 Copyright (c) 2026 StitcyYT Open Source Project.
 author: StitcyYT
 This file is part of the StitcyYT Open Source Project.
 It handles smart memory management and can genuinely help you with memory management in C.
 Used for: Allocating memory, freeing memory, and other memory management operations dynamically
*/

#ifndef SMM_H
#define SMM_H

#define POOL_SIZE 20480
#define STD_MEMORY_PLACE 0x10000000

#ifdef SMM_IMPLEMENTATION

typedef struct Block {
    size_t size;
    bool is_free;
    struct Block *next;
} Block;

static Block* free_list = NULL;
static char mem_pool[POOL_SIZE];

void init_smm() {
    free_list = (Block*)mem_pool;
    free_list->size = POOL_SIZE - sizeof(Block);
    free_list->is_free = true;
    free_list->next = NULL;
}

void* smm_alloc(size_t size) {
    // alignment size setup
    size = (size + 7) & ~7;

    // init if not init
    if (free_list == NULL) {
        init_smm();
    }

    Block* curr = free_list;
    
    // search for whatever block is free and has enough size to allocate the requested size
    while (curr != NULL) {
        if (curr->is_free && curr->size >= size) {
            
            // check if we can split
            // if the block size is good and 8 bytes more than the requested size then we can split it
            if (curr->size >= size + sizeof(Block) + 8) {
                Block* new_block = (Block*)((char*)curr + sizeof(Block) + size);
                new_block->size = curr->size - size - sizeof(Block);
                new_block->is_free = true;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }

            curr->is_free = false;
            
            // return pointer to the memory just after the block header
            return (void*)((char*)curr + sizeof(Block));
        }
        curr = curr->next;
    }

    return NULL; // oom
}

void smm_free(void* ptr) {
    if (ptr == NULL) return;

    // move pointer to block header
    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->is_free = true;

    // merge adjacent free blocks
    Block* curr = free_list;
    while (curr != NULL && curr->next != NULL) {
        if (curr->is_free && curr->next->is_free) {
            curr->size += sizeof(Block) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void* smm_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL) {
        return smm_alloc(new_size);
    }

    if (new_size == 0) {
        smm_free(ptr);
        return NULL;
    }

    // alignment size setup
    new_size = (new_size + 7) & ~7;

    Block* block = (Block*)((char*)ptr - sizeof(Block));

    // if the block is already big enough
    if (block->size >= new_size) {
        if (block->size >= new_size + sizeof(Block) + 8) {
            Block* new_block = (Block*)((char*)block + sizeof(Block) + new_size);
            new_block->size = block->size - new_size - sizeof(Block);
            new_block->is_free = true;
            new_block->next = block->next;

            block->size = new_size;
            block->next = new_block;
        }
        return ptr;
    }

    // try expanding into the next block if it's free
    if (block->next != NULL && block->next->is_free) {
        size_t combined_size = block->size + sizeof(Block) + block->next->size;
        
        if (combined_size >= new_size) {
            block->size = combined_size;
            block->next = block->next->next;

            if (block->size >= new_size + sizeof(Block) + 8) {
                Block* new_block = (Block*)((char*)block + sizeof(Block) + new_size);
                new_block->size = block->size - new_size - sizeof(Block);
                new_block->is_free = true;
                new_block->next = block->next;

                block->size = new_size;
                block->next = new_block;
            }
            return ptr;
        }
    }

    // allocate a brand new block if we can't grow in place
    void* new_ptr = smm_alloc(new_size);
    if (new_ptr == NULL) {
        return NULL; 
    }

    // copy data over byte-by-byte
    char* src = (char*)ptr;
    char* dest = (char*)new_ptr;
    for (size_t i = 0; i < block->size; i++) {
        dest[i] = src[i];
    }

    smm_free(ptr);
    return new_ptr;
}


#endif // SMM_IMPLEMENTATION

#endif // SMM_H