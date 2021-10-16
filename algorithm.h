#ifndef DATA_ALGORITHM_H
#define DATA_ALGORITHM_H

/**
 * @file algorithm.h
 * @author Edwin Solis (esolis6@gatech.edu)
 * @brief Implementation of general common useful algorithms
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>

/**
 * @brief Function signature of the comparison of two pieces of data.
 *        It should behave as the < operator in the following manner: *left < *right
 */
typedef int(*LESS_THAN_FUNC)(const void* left, const void* right);

/**
 * @brief Function signature of the equality of two pieces of data
 *        It should behave as the == operator in the follwing manner: *left == *right;
 */
typedef int(*EQUALS_FUNC)(const void* left, const void* right);

/**
 * @brief Searches the address of an element in the given array
 *        If the element is not in the array, the function returns NULL
 * 
 * @param element pointer to the element to be search
 * @param array pointer to the array to be searched
 * @param element_count number of elements in the array
 * @param element_size size in bytes of each of the element's data type
 * @param equal_func pointer to the equality function
 * @return pointer to the address of the (possible) position of the element
 */
const void* linear_search(const void* element, const void* array, size_t element_count, size_t element_size, EQUALS_FUNC equal_func);

/**
 * @brief Searches the address of an element in the given sorted array
 *        If the element is not in the array, the function returns the position were it would be if it was
 * 
 * @param element pointer to the element to be search
 * @param array pointer to the array to be searched
 * @param element_count number of elements in the array
 * @param element_size size in bytes of each of the element's data type
 * @param order_func pointer to the comparison function
 * @return pointer to the address of the (possible) position of the element
 */
const void* binary_search(const void* element, const void* array, size_t element_count, size_t element_size, LESS_THAN_FUNC order_func);

/**
 * @brief Searches the existance of an element in the given array
 *        If the element is in the array return 1, else returns 0
 * 
 * @param element pointer to the element to be search
 * @param array pointer to the array to be searched
 * @param element_count number of elements in the array
 * @param element_size size in bytes of each of the element's data type
 * @param equal_func pointer to the comparison function
 * @return 1 if contains, 0 if does not contain
 */
int array_contains(const void* element, const void* array, size_t element_count, size_t element_size, EQUALS_FUNC equal_func);

/**
 * @brief Searches the existance of an element in the sorted array
 *        If the element is in the array return 1, else returns 0
 * 
 * @param element pointer to the element to be search
 * @param array pointer to the array to be searched
 * @param element_count number of elements in the array
 * @param element_size size in bytes of each of the element's data type
 * @param equal_func pointer to the equality function
 * @return 1 if contains, 0 if does not contain
 */
int sorted_array_contains(const void* element, const void* array, size_t element_count, size_t element_size, LESS_THAN_FUNC equal_func);

#endif /* DATA_ALGORITHM_H */