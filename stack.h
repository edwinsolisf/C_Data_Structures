#ifndef DATA_STACK_H
#define DATA_STACK_H

#include <stdlib.h>

typedef struct
{
    size_t element_size_;
    size_t size_;
    size_t capacity_;
    void* data_;
} stack_t;

stack_t create_stack(size_t capacity, size_t element_size);
void destroy_stack(stack_t* stack);

void resize_stack(stack_t* stack, size_t size);
void reuse_stack(stack_t* stack, size_t capacity, size_t element_size);
void reserve_stack(stack_t* stack, size_t new_capacity);
size_t next_capacity_stack(size_t current_capacity);

void* get_element_stack(const stack_t* stack, size_t index);
void set_element_stack(stack_t* stack, size_t index, const void* data);

void push_back_stack(stack_t* stack, const void* data);
void pop_back_stack(stack_t* stack, void* data);

stack_t create_int_stack(size_t capacity);
int get_int_stack(const stack_t* stack, size_t index);
void set_int_stack(stack_t* stack, size_t index, int value);

void push_back_int_stack(stack_t* stack, int value);
int pop_back_int_stack(stack_t* stack);

#endif /* DATA_STACK_H */