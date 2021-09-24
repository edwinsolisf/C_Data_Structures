#include "stack.h"

#include <string.h>

static const int BASE_CAPACITY = 8;

array_stack_t create_astack(size_t capacity, size_t element_size)
{
    array_stack_t out;

    out.size_ = 0;
    out.capacity_ = capacity;
    out.element_size_ = element_size;
    out.data_ = malloc(element_size * capacity);

    return out;
}

void destroy_astack(array_stack_t* stack)
{
    stack->size_ = 0;
    stack->capacity_ = 0;
    stack->element_size_ = 0;
    free(stack->data_);
    stack->data_ = NULL;
}

void resize_astack(array_stack_t* stack, size_t size)
{
    if (size > stack->size_)
        reserve_astack(stack, next_capacity_astack(stack->capacity_));
    stack->size_ = size;
}

void reuse_astack(array_stack_t* stack, size_t capacity, size_t element_size)
{
    if (capacity * element_size > stack->capacity_ * stack->element_size_)
    {
        stack->data_ = realloc(stack->data_, capacity * element_size);
    }
    stack->capacity_ = capacity;
    stack->element_size_ = element_size;
    stack->size_ = 0;
}

void reserve_astack(array_stack_t* stack, size_t new_capacity)
{
    if (new_capacity > stack->capacity_)
    {
        stack->data_ = realloc(stack->data_, new_capacity * stack->element_size_);
        stack->capacity_ = new_capacity;
    }
}

size_t next_capacity_astack(size_t current_capacity)
{
    return current_capacity != 0 ? current_capacity * 2 : BASE_CAPACITY;
}

void* get_element_astack(const array_stack_t* stack, size_t index)
{
    return index < stack->size_ ? stack->data_ + (index * stack->element_size_) : NULL;
}

void set_element_astack(array_stack_t* stack, size_t index, const void* data)
{
    memcpy(get_element_astack(stack, index), data, stack->element_size_);
}

void push_astack(array_stack_t* stack, const void* data)
{
    if (stack->size_ == stack->capacity_)
        reserve_astack(stack, next_capacity_astack(stack->capacity_));
    set_element_astack(stack, stack->size_++, data);
}

void pop_astack(array_stack_t* stack, void* data)
{
    if (stack->size_ != 0)
    {
        memcpy(data, get_element_astack(stack, stack->size_ - 1), stack->element_size_);
        --stack->size_;
    }
}

int contains_astack(const array_stack_t* stack, const void* element, EQUALS_FUNC equal_func)
{
    return array_contains(element, stack->data_, stack->size_, stack->element_size_, equal_func);
}

array_stack_t create_int_astack(size_t capacity)
{
    return create_astack(capacity, sizeof(int));
}

int get_int_astack(const array_stack_t* stack, size_t index)
{
    return *(int*)get_element_astack(stack, index);
}

void set_int_astack(array_stack_t* stack, size_t index, int value)
{
    set_element_astack(stack, index, &value);
}

void push_int_astack(array_stack_t* stack, int value)
{
    push_astack(stack, &value);
}

int pop_int_astack(array_stack_t* stack)
{
    int temp;
    pop_astack(stack, &temp);
    return temp;
}