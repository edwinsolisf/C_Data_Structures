#ifndef DATA_HEAP_H
#define DATA_HEAP_H

#include "binary_tree.h"

typedef int (*LESS_THAN_FUNC)(void* left, void* right);
typedef int (*GREATER_THAN_FUNC)(void* left, void* right);

typedef struct data_heap_st
{
    binary_tree tree_;
    LESS_THAN_FUNC order_func;
} heap;

heap create_heap(size_t initial_capacity, size_t element_size, LESS_THAN_FUNC less_than_func);
heap copy_heap(const heap* heap_);
void destroy_heap(heap* heap_);
void reuse_heap(heap* heap_, size_t element_size);
void resize_heap(heap* heap_, size_t new_size);
void reserve_heap(heap* heap_, size_t reserve_capacity);

void push_heap(heap* heap_, const void* data);
void pop_last_heap(heap* heap_, void* data);
void pop_root_heap(heap* heap_, void* data);

void* get_element_heap(const heap* heap_, int node);
void set_element_heap(heap* heap_, int node, void* data);

void heapify_down(heap* heap_, int node);
void heapify_up(heap* heap_, int node);

int is_heap(const heap* heap_);

#endif /* DATA_HEAP_H */