#ifndef DATA_ORDERED_SET_H
#define DATA_ORDERED_SET_H

/**
 * @file set.h
 * @author Edwin Solis (edwinsolisf12@gmail.com)
 * @brief A type adjustable implementation of an ordered_set
 * @version 0.1
 * @date 2021-08-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "algorithm.h"

#include <stdlib.h>

/**
 * @brief Struct representing an ordered_set
 * Stores a unique element of a type, and orders it in ascending order
 * size_ stores the number of elements
 * capacity_ stores the maximum number of elements the current data_ array can store
 * element_size_ stores the size in bytes of the elements' type
 * data_ stores the pointer to the array of data
 * order_func_ stores a pointer to the comparison function for the type
 */
typedef struct data_ordered_set_st
{
    size_t size_;
    size_t capacity_;
    size_t element_size_;
    void* data_;
    LESS_THAN_FUNC order_func_;
} ordered_set_t;

/**
 * @brief Create an ordered set with the given parameters
 * 
 * @param capacity initial capacity that the set should be able to store
 * @param element_size size in bytes of the data types to be stored
 * @param order_function function pointer to the comparison function for the type
 * @return ordered_set 
 */
ordered_set_t create_ordered_set(size_t capacity, size_t element_size, LESS_THAN_FUNC order_function);

/**
 * @brief Destroy the instance ordered_set passed.
 *        Cleans up the array and resets all parameters.
 * 
 * @param set set to be destroyed
 */
void destroy_ordered_set(ordered_set_t* set);

/**
 * @brief Resizes the data buffer to the new given capacity
 * 
 * @param set ordered_set which buffer will be resized
 * @param new_capacity the new carrying capacity of the buffer
 */
void reserve_ordered_set(ordered_set_t* set, size_t new_capacity);

/**
 * @brief Reuses a previously created ordered_set and resets its parameters
 * 
 * @param set ordered_set to be repurposed
 * @param capacity the new desired capacity of the buffer
 * @param element_size the size in bytes of the new data type
 * @param order_function the new comparison function for the set
 */
void reuse_ordered_set(ordered_set_t* set, size_t capacity, size_t element_size, LESS_THAN_FUNC order_function);

/**
 * @brief Returns the next capacity for a resized buffer from a previous known capacity
 * 
 * @param capacity the old capacity of the buffer
 * @return the new capacity of the buffer
 */
size_t next_capacity_ordered_set(size_t capacity);

/**
 * @brief Gets the address of the element at the given index in the set
 * 
 * @param set the ordered_set from which the element is retrieved
 * @param index the index of the element to be retrieved
 * @return const pointer to the data
 */
const void* get_element_ordered_set(const ordered_set_t* set, size_t index);

/**
 * @brief Removes the given element from the ordered_set
 * 
 * @param set the ordered_set to be removed from
 * @param element the element to be removed
 */
void remove_element_ordered_set(ordered_set_t* set, const void* element);

/**
 * @brief Inserts the given element to the ordered_set
 * 
 * @param set the ordered_set to be added to
 * @param element the element to be added
 */
void insert_element_ordered_set(ordered_set_t* set, const void* element);

/**
 * @brief Searches for the given element in the set and returns 1 if it is in the ordered set
 *        else it returns 0
 * 
 * @param set the ordered_set to be searched
 * @param element the element to be searched
 * @return 1 if contains, 0 if does not contain
 */
int contains_ordered_set(const ordered_set_t* set, const void* element);

/**
 * @brief Wrapper for creating an int specialized ordered_set
 * 
 * @param capacity initial capacity that the set should be able to store
 * @return ordered_set of ints
 */
ordered_set_t create_int_oset(size_t capacity);

/**
 * @brief Wrapper for reusing an int specialized ordered_set
 * 
 * @param set set to be reused
 * @param capacity new capacity of the ordered_set
 */
void reuse_int_oset(ordered_set_t* set, size_t capacity);

/**
 * @brief Wrapper for inserting an element in an int specialized ordered_set
 * 
 * @param set ordered_set to be inserted to
 * @param val value to be inserted
 */
void insert_int_oset(ordered_set_t* set, int val);

/**
 * @brief Wrapper for removing an element in an int specialized ordered_set
 * 
 * @param set ordered_set to be removed from
 * @param val value to be removed
 */
void remove_int_oset(ordered_set_t* set, int val);

/**
 * @brief Getter wrapper an int specialized ordered_set
 * 
 * @param set the ordered_set from which the element is retrieved
 * @param index index of the element in the set
 * @return value at index
 */
int get_int_oset(const ordered_set_t* set, int index);

/**
 * @brief Wrapper for an int specialized ordered_set of the contains function
 * 
 * @param set the ordered_set to be searched
 * @param value value to be searched
 * @return 1 if contains, 0 if does not contain
 */
int contains_int_oset(const ordered_set_t* set, int value);

/**
 * @brief Prints the information and elements of an ordered_set of ints
 * 
 * @param set ordered_set to be printed
 */
void print_int_oset(const ordered_set_t* set);

#endif /* DATA_SET_H */
