#ifndef DATA_ARRAY_LIST_H
#define DATA_ARRAY_LIST_H

/**
 * @file array_list.h
 * @author Edwin Solis (esolis6@gatech.edu)
 * @brief A type adjustable implementation of an array list
 * @version 0.1
 * @date 2021-10-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include "algorithm.h"

/**
 * @brief Struct representing an array list
 * 
 * @var capacity_ stores the maximum number of elements that the list can store
 * @var size_ stores the current number of elements in the list
 * @var element_size_ stores the size in bytes of the datatype being stored
 * @var data_ stores the pointer to the buffer of data
 */
typedef struct data_array_list_st
{
    size_t capacity_;
    size_t size_;
    size_t element_size_;
    void* data_;
} array_list_t;

/**
 * @brief Create a array list object with the given parameters
 * 
 * @param capacity the initial capacity of the array list
 * @param element_size_ size in bytes of the data to be stored
 * @return array_list_t
 */
array_list_t create_array_list(size_t capacity, size_t element_size_);

/**
 * @brief Destroys the given instance of the array list and releases its resources
 * 
 * @param list the array list to be destroyed
 */
void destroy_array_list(array_list_t* list);

/**
 * @brief Reuses a previously created array list and resets its parameters
 * 
 * @param list array list to be reused
 * @param capacity the new desired capacity of the list
 * @param element_size the size in bytes of the new element type
 */
void reuse_array_list(array_list_t* list, size_t capacity, size_t element_size);

/**
 * @brief Resizes the given array list to be given size
 *        If the new size is greater than the current size, the new spots will contain garbage values.
 * 
 * @param list list to be resized
 * @param new_size new size of the list
 */
void resize_array_list(array_list_t* list, size_t new_size);

/**
 * @brief Swaps the contents of the given array lists.
 * 
 * @param left left array list instance
 * @param right right array list instance
 */
void swap_array_list(array_list_t* left, array_list_t* right);

/**
 * @brief Resizes the data buffer of the array list to the given capacity
 * 
 * @param list list to be resized
 * @param new_capacity new capacity of the list
 */
void reserve_array_list(array_list_t* list, size_t new_capacity);

/**
 * @brief Returns the next capacity for a resized buffer from a previous known capacity
 * 
 * @param current_capacity old capacity of the buffer
 * @return size_t new capacity of the buffer
 */
size_t next_array_list_capacity(size_t current_capacity);

/**
 * @brief Adds the given element to the front of the list.
 * 
 * @param list list to be added to
 * @param element pointer to the data of the element to be added
 */
void push_front_array_list(array_list_t* list, const void* element);

/**
 * @brief Adds the given element to the back of the list.
 * 
 * @param list list to be added to
 * @param element pointer to the data of the element to be added
 */
void push_back_array_list(array_list_t* list, const void* element);

/**
 * @brief Adds the given element to the given index in the list.
 *        The index must be smaller than the size of the list
 * 
 * @param list list to be added to
 * @param index index of the position where the element will be added
 * @param element pointer to the data of the element to be added
 */
void insert_array_list(array_list_t* list, size_t index, const void* element);

/**
 * @brief Removes the first element in the array list and returns it
 * 
 * @param list list to be removed from
 * @param element pointer where the element data will be copied to
 */
void pop_front_array_list(array_list_t* list, void* element);

/**
 * @brief Removes the last element in the array list and returns it
 * 
 * @param list list to be removed from
 * @param element pointer where the element data will be copied to
 */
void pop_back_array_list(array_list_t* list, void* element);

/**
 * @brief Removes the element at the given index in the array list and returns it
 * 
 * @param list list to be removed from
 * @param index index of the element in the array
 * @param element pointer where the element data will be copied to
 */
void remove_array_list(array_list_t* list, size_t index, void* element);

/**
 * @brief Copies the contents of the data at the source address to the array list
 * 
 * @param list list to be copied into
 * @param src const pointer to a list of elements
 * @param count the number of elements in source to be copied
 */
void mem_copy_array_list(array_list_t* list, const void* src, size_t count);

/**
 * @brief Fills all the indices in the array list with the given element
 * 
 * @param list list to be filled
 * @param element pointer to the data of the element to be copied into the list
 */
void fill_array_list(array_list_t* list, const void* element);

/**
 * @brief Gets the address of the element at the given index in the list.
 * 
 * @param list list from which the element is retrieved
 * @param index index of the element to be retrieved
 * @return void* pointer to the element data
 */
void* get_element_array_list(const array_list_t* list, size_t index);

/**
 * @brief Sets the value of the entry at the given index with the value passed.
 * 
 * @param list list in which the value is set
 * @param index index of the element to be set
 * @param value const pointer to the data which will be copied
 */
void set_element_array_list(array_list_t* list, size_t index, const void* value);

/**
 * @brief Returns a pointer to the first element in the array list.
 * 
 * @param list list from which the value is retrieved
 * @return void* pointer to the first element
 */
void* front_array_list(const array_list_t* list);

/**
 * @brief Returns a pointer to the last element in the array list.
 * 
 * @param list list from which the value is retrieved.
 * @return void* pointer to the last element
 */
void* back_array_list(const array_list_t* list);

/**
 * @brief Returns if the given element is in the array list.
 * 
 * @param list list to be searched in
 * @param element element to be search
 * @param equal_func pointer to the data equality function
 * @return 1 if contains, 0 if not contains
 */
int contains_array_list(const array_list_t* list, const void* element, EQUALS_FUNC equal_func);

/**
 * @brief Returns if the given element is in the given sorted array list.
 * 
 * @param list sorted list to be searched in
 * @param element element to be search
 * @param order_func pointer to the data comparison function
 * @return 1 if contains, 0 if not contains
 */
int contains_sorted_array_list(const array_list_t* list, const void* element, LESS_THAN_FUNC order_func);

/**
 * @brief Wrapper for creating an int specialized array list
 * 
 * @param capacity initial capacity of the list
 * @return array_list_t of ints
 */
array_list_t create_int_alist(size_t capacity);

/**
 * @brief Wrapper for pushing an element to the front of an int specialized array list
 * 
 * @param list list to be added into
 * @param value value to be added
 */
void push_front_int_alist(array_list_t* list, int value);

/**
 * @brief Wrapper for pushing an element to the back of an int specialized array list
 * 
 * @param list list to be added into
 * @param value value to be added
 */
void push_back_int_alist(array_list_t* list, int value);

/**
 * @brief Wrapper for adding an element to the given index of an int specialized array list
 * 
 * @param list list to be added into
 * @param index index where the element will be added in
 * @param value value to be added
 */
void insert_int_alist(array_list_t* list, size_t index, int value);

/**
 * @brief Wrapper for removing and getting the first element in an int specialized array list
 * 
 * @param list list to be removed from
 * @return int value removed from the front
 */
int pop_front_int_alist(array_list_t* list);

/**
 * @brief Wrapper for removing and getting the last element in an int specialized array list
 * 
 * @param list list to be removed from
 * @return int value removed from the back
 */
int pop_back_int_alist(array_list_t* list);

/**
 * @brief Wrapper for removing and getting the element at the given index in an int specialized array list
 * 
 * @param list list to be removed from
 * @param index index where the value is removed
 * @return int value removed from the list
 */
int remove_int_alist(array_list_t* list, size_t index);

/**
 * @brief Getter wrapper for an int specialized array list
 * 
 * @param list list to be retrieved from
 * @param index index of the element to get
 * @return int value at the given index
 */
int get_int_alist(const array_list_t* list, size_t index);

/**
 * @brief Wrapper for setting the value of an element in an int specialized array list
 * 
 * @param list list where the element is set
 * @param index index of the element entry
 * @param value value to be set
 */
void set_int_alist(array_list_t* list, size_t index, int value);

/**
 * @brief Wrapper for getting the first element of an int specialized array list
 * 
 * @param list list to be retrieved from
 * @return int value at the front
 */
int front_int_alist(const array_list_t* list);

/**
 * @brief Wrapper for getting the last element of an int specialized array list
 * 
 * @param list list to be retrieved from
 * @return int value at the back
 */
int back_int_alist(const array_list_t* list);

#endif /* array_list_t_H */
