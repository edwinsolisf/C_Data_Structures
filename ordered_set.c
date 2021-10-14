#include "ordered_set.h"

#include <string.h>
#include <stdio.h>

ordered_set_t create_ordered_set(size_t element_size, size_t capacity, LESS_THAN_FUNC order_function)
{
    ordered_set_t out;

    out.capacity_ = capacity;
    out.element_size_ = element_size;
    out.size_ = 0;
    out.data_ = malloc(element_size * capacity);
    out.order_func_ = order_function;

    return out;
}

void destroy_ordered_set(ordered_set_t* set)
{
    set->capacity_ = 0;
    set->size_ = 0;
    set->element_size_ = 0;
    set->order_func_ = NULL;
    free(set->data_);
}

void reserve_ordered_set(ordered_set_t* set, size_t new_capacity)
{
    if (new_capacity > set->capacity_)
    {
        set->data_ = realloc(set->data_, new_capacity * set->element_size_);
        set->capacity_ = new_capacity;
    }
}

void reuse_ordered_set(ordered_set_t* set, size_t element_size, size_t capacity, LESS_THAN_FUNC order_function)
{
    if (element_size * capacity > set->capacity_ * set->element_size_)
        set->data_ = realloc(set->data_, element_size * capacity);
    
    set->size_ = 0;
    set->element_size_ = element_size;
    set->capacity_ = capacity;
    set->order_func_ = order_function;
}

size_t next_capacity_ordered_set(size_t capacity)
{
    return capacity ? capacity * 2 : 2;
}

const void* get_element_ordered_set(const ordered_set_t* set, size_t index)
{
    if (index < set->size_ && index >= 0)
        return set->data_ + (index * set->element_size_);
    return NULL;
}

void remove_element_ordered_set(ordered_set_t* set, const void* element)
{
    void* position = (void*)binary_search(element, set->data_, set->size_, set->element_size_, set->order_func_);
    if (!(set->order_func_(position, element) || set->order_func_(element, position)))
    {
        memmove(position, position + set->element_size_, (uintptr_t)(set->data_ + set->size_ * set->element_size_) - (uintptr_t)position);
        --set->size_;
    }
}

void insert_element_ordered_set(ordered_set_t* set, const void* element)
{
    if (set->size_ == set->capacity_)
        reserve_ordered_set(set, next_capacity_ordered_set(set->capacity_));

    if (set->size_ == 0)
        memcpy(set->data_, element, set->element_size_), ++set->size_;
    void* position = (void*)binary_search(element, set->data_, set->size_, set->element_size_, set->order_func_);

    if (set->order_func_(position, element) != set->order_func_(element, position))
    {
        size_t offset = (uintptr_t)(set->data_ + set->size_ * set->element_size_) - (uintptr_t)position;
        memmove(position + set->element_size_, position, offset);
        memcpy(position, element, set->element_size_);
        ++set->size_;
    }
}

int contains_ordered_set(const ordered_set_t* set, const void* element)
{
    return sorted_array_contains(element, set->data_, set->size_, set->element_size_, set->order_func_);
}

int int_less_than_func(const void* left, const void* right)
{
    return *(const int*)left < *(const int*)right;
}

ordered_set_t create_int_oset(size_t capacity)
{
    return create_ordered_set(sizeof(int), capacity, int_less_than_func);
}

void reuse_int_oset(ordered_set_t* set, size_t capacity)
{
    reuse_ordered_set(set, sizeof(int), capacity, int_less_than_func);
}

void insert_int_oset(ordered_set_t* set, int val)
{
    insert_element_ordered_set(set, &val);
}

void remove_int_oset(ordered_set_t* set, int val)
{
    remove_element_ordered_set(set, &val);
}

int get_int_oset(const ordered_set_t* set, int index)
{
    return *(const int*)get_element_ordered_set(set, index);
}

void print_int_oset(const ordered_set_t* set)
{
    printf("set: ----\nsize: %zu\ncapacity: %zu\nelement_size: %zu\n(", set->size_, set->capacity_, set->element_size_);
    for (int i = 0; i < set->size_; ++i)
        printf(" %d,", get_int_oset(set, i));
    printf(" )\n");
}

int contains_int_oset(const ordered_set_t* set, int value)
{
    return contains_ordered_set(set, &value);
}