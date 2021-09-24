#include "array_list.h"

#include <stdlib.h>
#include <string.h>

array_list_t create_array_list(size_t reserve_size, size_t element_size)
{
    array_list_t out;

    out.capacity_ = reserve_size;
    out.size_ = 0;
    out.element_size_ = element_size;
    out.data_ = malloc(element_size * reserve_size);

    return out;
}

void destroy_array_list(array_list_t* list)
{
    list->size_ = 0;
    list->capacity_ = 0;
    list->element_size_ = 0;
    free(list->data_);
    list->data_ = NULL;
}

void reuse_array_list(array_list_t* list, size_t capacity, size_t element_size)
{
    if (capacity * element_size > list->element_size_ * list->capacity_)
    {
        list->data_ = malloc(capacity * element_size);
        list->capacity_ = capacity;
    }
    else
        list->capacity_ = (list->capacity_ * list->element_size_) / element_size;
    list->element_size_ = element_size;
    list->size_ = 0;
}

void swap_array_list(array_list_t* left, array_list_t* right)
{
    array_list_t temp = {
        .capacity_ = right->capacity_,
        .size_ = right->size_,
        .element_size_ = right->element_size_,
        .data_ = right->data_
    };
    *right = *left;
    *left = temp;
}

void reserve_array_list(array_list_t* list, size_t new_capacity)
{
    if (list->capacity_ < new_capacity)
    {
        list->data_ = realloc(list->data_, new_capacity * list->element_size_);
        list->capacity_ = new_capacity;
    }
}

size_t next_array_list_capacity(size_t current_capacity)
{
    return current_capacity ? current_capacity * 2 : 2;
}

void push_back_array_list(array_list_t* list, const void* element)
{
    if (list->size_ == list->capacity_)
        reserve_array_list(list, next_array_list_capacity(list->capacity_));
    set_element_array_list(list, list->size_++, element);
}

void push_front_array_list(array_list_t* list, const void* element)
{
    if (list->size_ == list->capacity_)
        reserve_array_list(list, next_array_list_capacity(list->capacity_));
    if (list->size_ != 0)
    {
        memmove(list->data_ + list->element_size_, list->data_, list->element_size_ * list->size_);
        set_element_array_list(list, 0, element);
        ++list->size_;
    }
    else
        push_back_array_list(list, element);
}

void insert_array_list(array_list_t* list, size_t index, const void* element)
{
    if (index == 0)
        push_front_array_list(list, element);
    else if (index == list->size_)
        push_back_array_list(list, element);
    else
    {
        if (index < list->size_)
        {
            if (list->size_ == list->capacity_)
                reserve_array_list(list, next_array_list_capacity(list->capacity_));
            memmove(get_element_array_list(list, index + 1), get_element_array_list(list, index), list->element_size_ * (list->size_ - index));
            set_element_array_list(list, index, element);
            ++list->size_;
        }
    }
}

void pop_back_array_list(array_list_t* list, void* element)
{
    if (list->size_ != 0)
    {
        memcpy(element, get_element_array_list(list, list->size_ - 1), list->element_size_);
        --list->size_;
        //memset(get_element_array_list(list, list->size_), list->element_size_, 0);
    }
}

void pop_front_array_list(array_list_t* list, void* element)
{
    if (list->size_ != 0)
    {
        memcpy(element, get_element_array_list(list, 0), list->element_size_);
        memmove(list->data_, list->data_ + list->element_size_, list->element_size_ * --list->size_);
    }
}

void remove_array_list(array_list_t* list, size_t index, void* element)
{
    if (list->size_ != 0)
    {
        if (index == 0)
            pop_front_array_list(list, element);
        else if (index == list->size_ - 1)
            pop_back_array_list(list, element);
        else
        {
            if (index < list->size_ - 1)
            {
                memcpy(element, get_element_array_list(list, index), list->element_size_);
                memmove(get_element_array_list(list, index), get_element_array_list(list, index + 1), list->element_size_ * (--list->size_ - index));
            }
        }
    }
}

void mem_copy_array_list(array_list_t* list, const void* src, size_t count)
{
    if (list->capacity_ < count)
        reserve_array_list(list, next_array_list_capacity(list->capacity_));
    memcpy(list->data_, src, count * list->element_size_);
    if (count > list->size_) list->size_ = count;
}

void* get_element_array_list(const array_list_t* list, size_t index)
{
    return index < list->size_ ? list->data_ + (index * list->element_size_) : NULL;
}

void set_element_array_list(array_list_t* list, size_t index, const void* value)
{
    memcpy(get_element_array_list(list, index), value, list->element_size_);
}

void* front_array_list(const array_list_t* list)
{
    return get_element_array_list(list, 0);
}

void* back_array_list(const array_list_t* list)
{
    return get_element_array_list(list, list->size_ - 1);
}

int contains_array_list(const array_list_t* list, const void* element, EQUALS_FUNC equal_func)
{
    return array_contains(element, list->data_, list->size_, list->element_size_, equal_func);
}

int contains_sorted_array_list(const array_list_t* list, const void* element, LESS_THAN_FUNC order_func)
{
    return sorted_array_contains(element, list->data_, list->size_, list->element_size_, order_func);
}

array_list_t create_int_alist(size_t capacity)
{
    return create_array_list(capacity, sizeof(int));
}

void push_front_int_alist(array_list_t* list, int value)
{
    push_front_array_list(list, &value);
}

void push_back_int_alist(array_list_t* list, int value)
{
    push_back_array_list(list, &value);
}

void insert_int_alist(array_list_t* list, size_t index, int value)
{
    insert_array_list(list, index, &value);
}

int pop_front_int_alist(array_list_t* list)
{
    int temp;
    pop_front_array_list(list, &temp);
    return temp;
}

int pop_back_int_alist(array_list_t* list)
{
    int temp;
    pop_back_array_list(list, &temp);
    return temp;
}

int remove_int_alist(array_list_t* list, size_t index)
{
    int temp;
    remove_array_list(list, index, &temp);
    return temp;
}

int get_int_alist(const array_list_t* list, size_t index)
{
    return *(int*)get_element_array_list(list, index);
}

void set_int_alist(array_list_t* list, size_t index, int value)
{
    set_element_array_list(list, index, &value);
}

int front_int_alist(const array_list_t* list)
{
    return *(int*)front_array_list(list);
}

int back_int_alist(const array_list_t* list)
{
    return *(int*)back_array_list(list);
}