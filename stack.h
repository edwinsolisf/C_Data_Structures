#ifndef DATA_STACK_H
#define DATA_STACK_H

/**
 * @file stack.h
 * @author Edwin Solis (esolis6@gatech.edu)
 * @brief A type adjustable stack implementation
 * @version 0.1
 * @date 2021-08-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>

#include "algorithm.h"

/**
 * @brief Struct representing an array stack
 * 
 * @var data_ stores the pointer to the buffer of data
 * @var element_size_ stores the size in bytes of the datatype being stored
 * @var size_ stores the number of elements in the stack
 * @var capacity_ stores the maximum number of elements that can be stored
 */
typedef struct data_stack_st
{
    void* data_;
    size_t element_size_;
    size_t size_;
    size_t capacity_;
} array_stack_t;

/**
 * @brief Create an array_stack object with the given parameters
 * 
 * @param capacity the initial capacity of the stack
 * @param element_size size in bytes of the datatype to be stored
 * @return array_stack_t
 */
array_stack_t create_astack(size_t capacity, size_t element_size);

/**
 * @brief Destroys the given instance of array stack and releases its resources.
 * 
 * @param stack stack to be destroyed
 */
void destroy_astack(array_stack_t* stack);

/**
 * @brief Reuses a previously created array list and resets its paramaters
 * 
 * @param stack stack to be reused
 * @param capacity the new desired capacity of the list
 * @param element_size the size in bytes of the new element type
 */
void reuse_astack(array_stack_t* stack, size_t capacity, size_t element_size);

/**
 * @brief Resize the data buffer of the array stack to the given capacity
 * 
 * @param stack stack to be resized
 * @param new_capacity new capacity of the stack
 */
void reserve_astack(array_stack_t* stack, size_t new_capacity);

/**
 * @brief Returns the next capacity for a resized buffer from a previous known capacity
 * 
 * @param current_capacity old capacity of the buffer
 * @return size_t new capacity of the buffer
 */
size_t next_capacity_astack(size_t current_capacity);

/**
 * @brief Gets the address of the element at the given index
 * 
 * @param stack stack from which the element is retrieved
 * @param index index of the element to be retrieved
 * @return void* pointer to the element data
 */
void* get_element_astack(const array_stack_t* stack, size_t index);

/**
 * @brief Sets the value of the entry at the given index with passed value
 * 
 * @param stack stack in which the value is set
 * @param index index of the element to be set
 * @param data const pointer to the data which will be copied
 */
void set_element_astack(array_stack_t* stack, size_t index, const void* data);

/**
 * @brief Gets the address of the element that will be pop next from the stack
 * 
 * @param stack stack from which the element is retrieved
 * @return const void* const pointer to the element that will be poped next
 */
const void* top_astack(const array_stack_t* stack);

/**
 * @brief Adds the given element to the stack
 * 
 * @param stack stack in which the element will be added
 * @param data const pointer to the data of the element that will be added
 */
void push_astack(array_stack_t* stack, const void* data);

/**
 * @brief Removes an element from the array stack
 * 
 * @param stack stack from which the element is removed
 * @param data pointer where the element data will be copied to
 */
void pop_astack(array_stack_t* stack, void* data);

/**
 * @brief Returns if the given element is contained in the array stack
 * 
 * @param stack stack to be search in
 * @param element element to be searched
 * @param equal_func pointer to the data equality function
 * @return int 1 if contains, 0 if not contains
 */
int contains_astack(const array_stack_t* stack, const void* element, EQUALS_FUNC equal_func);

/**
 * @brief Wrapper for creating an int specialized array stack
 * 
 * @param capacity the initial capacity for the stack
 * @return array_stack_t
 */
array_stack_t create_int_astack(size_t capacity);

/**
 * @brief Getter wrapper for an int specialized array stack
 * 
 * @param stack stack from which the element is retrieved
 * @param index index of the element to be retrieved
 * @return int element retrieved
 */
int get_int_astack(const array_stack_t* stack, size_t index);

/**
 * @brief Setter wrapper for an int specialized array stack
 * 
 * @param stack stack where the element is set
 * @param index index of the element that will be set
 * @param value new value for the element
 */
void set_int_astack(array_stack_t* stack, size_t index, int value);

/**
 * @brief Wrapper for pushing an element into an int specialized array stack
 * 
 * @param stack stack in which the element is pushed
 * @param value value that will be pushed into the stack
 */
void push_int_astack(array_stack_t* stack, int value);

/**
 * @brief Wrapper for removing an element from an int specialized array stack
 * 
 * @param stack stack from which the element is removed
 * @return int value that was removed
 */
int pop_int_astack(array_stack_t* stack);

#endif /* DATA_STACK_H */