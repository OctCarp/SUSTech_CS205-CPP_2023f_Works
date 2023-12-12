#include "mmpool.h"
#include <stdio.h>

/* Functions for tests */
/* ==BEGIN== */
void prt_mmpool_details(mmpool_t *pool) {
    if (pool == NULL) return;
    puts("===MEMORY POOL DETAILS===");
    printf("POOL ADDRESS: %p\n", pool);
    printf("POOL SIZE (FOR EACH): %lu\n", MMPOOL_SIZE);
    printf("MAX ALLOCATION SIZE: %lu\n", MMPOOL_MAX_ALLOC);
    printf("MAX FAILED TIMES: %d\n", MMPOOL_MAX_FAILED);
    printf("CURRENT ACTIVE POOL ADDRESS: %p\n", pool->current);
    puts("\nSUB POOL DETAILS:");

    size_t count = 0;
    mmpool_t *cur = pool;
    while (cur != NULL) {
        printf("\t-> Sub pool #%lu, address=%p, free_space=%lu (bytes), failed=%lu\n",
                ++count, cur, (size_t)(cur->data.end - cur->data.last), cur->data.failed);
        cur = cur->data.next;
    }
    printf("SUB POOL COUNT: %lu\n", count);

    puts("\nLARGE BLOCK DETAILS: ");
    count = 0;
    mmpool_large_t *large = pool->large;
    while (large != NULL) {
        printf("\t-> Large block #%lu, address=%p\n", ++count, large);
        large = large->next;
    }
    printf("LARGE BLOCK COUNT: %lu\n", count);
    puts("===MEMORY POOL DETAILS END===\n");
}
/* ==END== */

mmpool_t* mmpool_create() {
    mmpool_t* p = NULL;

    p = (mmpool_t*) malloc(sizeof(mmpool_t) + MMPOOL_SIZE);
    if (p != NULL) {
        p->data.last = (uint8_t*) p + sizeof(mmpool_t);
        p->data.end = p->data.last + MMPOOL_SIZE;
        p->data.next = NULL;
        p->data.failed = 0;

        p->current = p;
        p->large = NULL;
    }

    return p;
}

/* WRITE YOUR CODE HERE */
/* SUBMIT THIS PART */
/* ==BEGIN== */
void *mmpool_alloc(mmpool_t *pool, size_t size) {
    if (!pool || size <= 0) { return NULL; }

    if (size > MMPOOL_MAX_ALLOC) {
        mmpool_large_t *new_large = mmpool_alloc_large(size);
        if (pool->large) {
            mmpool_large_t *last_large = pool->large;
            while (last_large->next) {
                last_large = last_large->next;
            }
            last_large->next = new_large;
        } else {
            pool->large = new_large;
        }
        return new_large->alloc;
    } else {
        void *res_memory;
        
        for (mmpool_t *cur = pool->current;; cur = cur->data.next) {
            if (cur->data.end - cur->data.last < size) {
                ++cur->data.failed;
                if (cur->data.failed > MMPOOL_MAX_FAILED) {
                    pool->current = cur->data.next;
                }
                if (!cur->data.next) {
                    cur->data.next = mmpool_create();
                    if (cur->data.failed > MMPOOL_MAX_FAILED) {
                        pool->current = cur->data.next;
                    }
                    res_memory = cur->data.next->data.last;
                    cur->data.next->data.last += size;

                    return res_memory;
                }

            } else {
                res_memory = cur->data.last;
                cur->data.last += size;

                return res_memory;
            }
        }
    }
}

mmpool_large_t *mmpool_alloc_large(size_t size) {
    if (size <= 0) { return NULL; }

    mmpool_large_t *large_block = (mmpool_large_t *) malloc(sizeof(mmpool_large_t));
    large_block->alloc = malloc(size);
    large_block->next = NULL;
    return large_block;
}

void mmpool_destroy(mmpool_t *pool) {
    if (!pool) { return; }

    mmpool_large_t *current_large = pool->large;
    while (current_large) {
        mmpool_large_t *temp = current_large;
        current_large = current_large->next;
        if (temp->alloc) {
            free(temp->alloc);
        }
        free(temp);
    }

    mmpool_t *current_pool = pool;
    while (current_pool) {
        mmpool_t *temp = current_pool;
        current_pool = current_pool->data.next;
        free(temp);
    }
}

void mmpool_free_large(mmpool_t *pool, void *p) {
    if (!pool || !p) { return; }

    mmpool_large_t *cur = pool->large;
    mmpool_large_t *prev = NULL;

    while (cur) {
        if (cur->alloc == p) {
            if (prev == NULL) {
                pool->large = cur->next;
            } else {
                prev->next = cur->next;
            }
            if (cur->alloc) {
                free(cur->alloc);
            }
            free(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }
}

void mmpool_reset(mmpool_t *pool) {
    if (!pool) { return; }

    pool->current = pool;
    
    for (mmpool_t *cur = pool; cur; cur = cur->data.next) {
        cur->data.last = (uint8_t *) cur + sizeof(mmpool_t);
        cur->data.failed = 0;
    }

    mmpool_large_t *current_large = pool->large;
    while (current_large) {
        mmpool_large_t *temp = current_large;
        current_large = current_large->next;
        if (temp->alloc) {
            free(temp->alloc);
        }
        free(temp);
    }
    pool->large = NULL;
}
