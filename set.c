#include "set.h"

#include <stdio.h>
#include <string.h>

ordered_set create_ordered_set(size_t element_size, size_t capacity, LESS_THAN_FUNC order_function)
{
    ordered_set out;

    out.capacity_ = capacity;
    out.element_size_ = element_size;
    out.size_ = 0;
    out.data_ = malloc(element_size * capacity);
    out.order_func_ = order_function;

    return out;
}

void destroy_ordered_set(ordered_set* set)
{
    set->capacity_ = 0;
    set->size_ = 0;
    set->element_size_ = 0;
    set->order_func_ = NULL;
    free(set->data_);
}

void resize_ordered_set(ordered_set* set, size_t new_capacity)
{
    if (new_capacity > set->capacity_)
    {
        set->data_ = realloc(set->data_, new_capacity * set->element_size_);
        set->capacity_ = new_capacity;
    }
}

void reuse_ordered_set(ordered_set* set, size_t element_size, size_t capacity, LESS_THAN_FUNC order_function)
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

const void* get_element_ordered_set(const ordered_set* set, int index)
{
    if (index < set->size_ && index >= 0)
        return set->data_ + (index * set->element_size_);
    return NULL;
}

void remove_element_ordered_set(ordered_set* set, const void* element)
{
    void* position = binary_search(set->data_, (void*)element, set->size_, set->element_size_, set->order_func_);
    if (!(set->order_func_(position, element) || set->order_func_(element, position))) //*element == *position
    {
        memmove(position, position + set->element_size_, (uintptr_t)(set->data_ + set->size_ * set->element_size_) - (uintptr_t)position);
        --set->size_;
    }
}

void insert_element_ordered_set(ordered_set* set, const void* element)
{
    if (set->size_ == set->capacity_)
        resize_ordered_set(set, next_capacity_ordered_set(set->capacity_));

    if (set->size_ == 0)
        memcpy(set->data_, element, set->element_size_), ++set->size_;
    void* position = binary_search(set->data_, (void*)element, set->size_, set->element_size_, set->order_func_);

    if (set->order_func_(position, element) != set->order_func_(element, position)) //*element != *position
    {
        size_t offset = (uintptr_t)(set->data_ + set->size_ * set->element_size_) - (uintptr_t)position;
        memmove(position + set->element_size_, position, offset);
        memcpy(position, element, set->element_size_);
        ++set->size_;
    }
}

//return address of the element in the array; if not in the array then returns the address were it would be
void* binary_search(void* array, void* element, size_t element_count, size_t element_size, LESS_THAN_FUNC order_func)
{
    // for (int i = 0; i < element_count; ++i)
    //     printf("%d ", ((int*)array)[i]);
    // printf("\n");
    if (element_count == 0)
        return array;

    void* left = array;
    void* right = array + (element_count - 1) * element_size;

    if (!order_func(left, element))
        return left;
    if (order_func(right, element))
        return right + element_size;
    else if (!order_func(element, right))
        return right;

    void* current = left + ((((uintptr_t)right - (uintptr_t)left) / (element_size)) / 2) * element_size;
    //printf("current %d, left: %d, right: %d\n", *(int*)current, *(int*)left, *(int*)right);
    while ((right - left) > element_size)
    {
        if (!(order_func(current, element) || order_func(element, current)))
            return current;
        else if (!order_func(current, element))
            right = current;
        else
            left = current;

        //size_t diff = right > left ? right - left : 0;
        current = left + (((right - left) / (element_size)) / 2) * element_size;

        //printf("current %d, left: %d, right: %d, step: %ld\n", *(int*)current, *(int*)left, *(int*)right, (intptr_t)right - (intptr_t)left);
    }

    return (order_func(current, element) ? current + element_size : current);
    //return !order_func(current, element) ? current + element_size : current;
}

int int_less_than_func(const void* left, const void* right)
{
    return *(const int*)left < *(const int*)right;
}

ordered_set create_int_oset(size_t capacity)
{
    return create_ordered_set(sizeof(int), capacity, int_less_than_func);
}

void reuse_int_oset(ordered_set* set, size_t capacity)
{
    reuse_ordered_set(set, sizeof(int), capacity, int_less_than_func);
}

void insert_int_oset(ordered_set* set, int val)
{
    insert_element_ordered_set(set, &val);
}

void remove_int_oset(ordered_set* set, int val)
{
    remove_element_ordered_set(set, &val);
}

int get_int_oset(const ordered_set* set, int index)
{
    return *(const int*)get_element_ordered_set(set, index);
}