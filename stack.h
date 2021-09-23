#ifndef DATA_STACK_H
#define DATA_STACK_H

#include <stdlib.h>

typedef struct data_stack_st
{
    size_t element_size_;
    size_t size_;
    size_t capacity_;
    void* data_;
} array_stack_t;

struct data_stack_st create_stack(size_t capacity, size_t element_size);
void destroy_stack(struct data_stack_st* stack);

void resize_stack(struct data_stack_st* stack, size_t size);
void reuse_stack(struct data_stack_st* stack, size_t capacity, size_t element_size);
void reserve_stack(struct data_stack_st* stack, size_t new_capacity);
size_t next_capacity_stack(size_t current_capacity);

void* get_element_stack(const struct data_stack_st* stack, size_t index);
void set_element_stack(struct data_stack_st* stack, size_t index, const void* data);

void push_back_stack(struct data_stack_st* stack, const void* data);
void pop_back_stack(struct data_stack_st* stack, void* data);

struct data_stack_st create_int_stack(size_t capacity);
int get_int_stack(const struct data_stack_st* stack, size_t index);
void set_int_stack(struct data_stack_st* stack, size_t index, int value);

void push_back_int_stack(struct data_stack_st* stack, int value);
int pop_back_int_stack(struct data_stack_st* stack);

#endif /* DATA_STACK_H */