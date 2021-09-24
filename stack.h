#ifndef DATA_STACK_H
#define DATA_STACK_H

#include <stdlib.h>

#include "algorithm.h"

typedef struct data_stack_st
{
    size_t element_size_;
    size_t size_;
    size_t capacity_;
    void* data_;
} array_stack_t;

array_stack_t create_astack(size_t capacity, size_t element_size);
void destroy_astack(array_stack_t* stack);

void resize_astack(array_stack_t* stack, size_t size);
void reuse_astack(array_stack_t* stack, size_t capacity, size_t element_size);
void reserve_astack(array_stack_t* stack, size_t new_capacity);
size_t next_capacity_astack(size_t current_capacity);

void* get_element_astack(const array_stack_t* stack, size_t index);
void set_element_astack(array_stack_t* stack, size_t index, const void* data);

void push_astack(array_stack_t* stack, const void* data);
void pop_astack(array_stack_t* stack, void* data);

int contains_astack(const array_stack_t* stack, const void* element, EQUALS_FUNC equal_func);

array_stack_t create_int_astack(size_t capacity);
int get_int_astack(const array_stack_t* stack, size_t index);
void set_int_astack(array_stack_t* stack, size_t index, int value);

void push_int_astack(array_stack_t* stack, int value);
int pop_int_astack(array_stack_t* stack);

#endif /* DATA_STACK_H */