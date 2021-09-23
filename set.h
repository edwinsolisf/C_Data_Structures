#ifndef CX_SET_H
#define CX_SET_H

#include <stdlib.h>

typedef int(*LESS_THAN_FUNC)(const void* left, const void* right);

typedef struct data_ordered_set_st
{
    size_t size_;
    size_t capacity_;
    size_t element_size_;
    void* data_;
    LESS_THAN_FUNC order_func_;
} ordered_set;

ordered_set create_ordered_set(size_t element_size, size_t capacity, LESS_THAN_FUNC order_function);
void destroy_ordered_set(ordered_set* set);

void resize_ordered_set(ordered_set* set, size_t new_capacity);
void reuse_ordered_set(ordered_set* set, size_t element_size, size_t capacity, LESS_THAN_FUNC order_function);
size_t next_capacity_ordered_set(size_t capacity);

const void* get_element_ordered_set(const ordered_set* set, int index);

void remove_element_ordered_set(ordered_set* set, const void* element);
void insert_element_ordered_set(ordered_set* set, const void* element);

void* binary_search(void* array, void* element, size_t element_count, size_t element_size, LESS_THAN_FUNC order_func);

ordered_set create_int_oset(size_t capacity);
void reuse_int_oset(ordered_set* set, size_t capacity);
void insert_int_oset(ordered_set* set, int val);
void remove_int_oset(ordered_set* set, int val);
int get_int_oset(const ordered_set* set, int index);

#endif /* CX_SET_H */