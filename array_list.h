#ifndef array_list_t_H
#define array_list_t_H

#include <stdlib.h>
#include "algorithm.h"

typedef struct data_array_list_st
{
    size_t capacity_;
    size_t size_;
    size_t element_size_;
    void* data_;
} array_list_t;

array_list_t create_array_list(size_t reserve_capacity, size_t element_size_);
void destroy_array_list(array_list_t* list);
void reuse_array_list(array_list_t* list, size_t capacity, size_t element_size);
void swap_array_list(array_list_t* left, array_list_t* right);

void reserve_array_list(array_list_t* list, size_t new_capacity);
size_t next_array_list_capacity(size_t current_capacity);

void push_front_array_list(array_list_t* list, const void* element);
void push_back_array_list(array_list_t* list, const void* element);
void insert_array_list(array_list_t* list, size_t index, const void* element);

void pop_front_array_list(array_list_t* list, void* element);
void pop_back_array_list(array_list_t* list, void* element);
void remove_array_list(array_list_t* list, size_t index, void* element);

void mem_copy_array_list(array_list_t* list, const void* src, size_t count);

void* get_element_array_list(const array_list_t* list, size_t index);
void set_element_array_list(array_list_t* list, size_t index, const void* value);

void* front_array_list(const array_list_t* list);
void* back_array_list(const array_list_t* list);

int contains_array_list(const array_list_t* list, const void* element, EQUALS_FUNC equal_func);
int contains_sorted_array_list(const array_list_t* list, const void* element, LESS_THAN_FUNC order_func);

array_list_t create_int_alist(size_t capacity);

void push_front_int_alist(array_list_t* list, int value);
void push_back_int_alist(array_list_t* list, int value);
void insert_int_alist(array_list_t* list, size_t index, int value);

int pop_front_int_alist(array_list_t* list);
int pop_back_int_alist(array_list_t* list);
int remove_int_alist(array_list_t* list, size_t index);

int get_int_alist(const array_list_t* list, size_t index);
void set_int_alist(array_list_t* list, size_t index, int value);

int front_int_alist(const array_list_t* list);
int back_int_alist(const array_list_t* list);

#endif /* array_list_t_H */
