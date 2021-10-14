#ifndef DATA_ORDERED_MAP
#define DATA_ORDERED_MAP

#include <stdlib.h>

/**
 * @file ordered_map.h
 * @author Edwin Solis (edwinsolisf12@gmail.com)
 * @brief A type adjustable implementation of an ordered_map
 * @version 0.1
 * @date 2021-09-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "algorithm.h"

#include <stdlib.h>

/**
 * @brief Struct representing an ordered_map
 *        Stores a unique pair of a key and value, and orders it in ascending order
 * @var size_ stores the number of elements
 * @var capacity_ stores the maximum number of elements the current data_ array can store
 * @var element_size_ stores the size in bytes of the elements' type
 * @var data_ stores the pointer to the array of data
 * @var order_func_ stores a pointer to the comparison function for the type
 */
typedef struct data_ordered_map_st
{
    size_t size_;
    size_t capacity_;
    size_t key_size_;
    size_t value_size_;
    void* data_;
    LESS_THAN_FUNC order_func_;
} ordered_map_t;

/**
 * @brief Create an ordered map with the given parameters
 * 
 * @param key_size size in bytes of the key data types to be stored
 * @param value_size size in bytes of the value data types to be stored
 * @param capacity initial capacity that the set should be able to store
 * @param order_function function pointer to the comparison function for the type
 * @return ordered_map
 */
ordered_map_t create_ordered_map(size_t key_size, size_t value_size, size_t capacity, LESS_THAN_FUNC order_function);

/**
 * @brief Destroy the instance ordered_map passed.
 *        Cleans up the array and resets all parameters.
 * 
 * @param map map to be destroyed
 */
void destroy_ordered_map(ordered_map_t* map);

/**
 * @brief Resizes the data buffer to the new given capacity
 * 
 * @param map ordered_map which buffer will be resized
 * @param new_capacity the new carrying capacity of the buffer
 */
void reserve_ordered_map(ordered_map_t* map, size_t new_capacity);

/**
 * @brief Reuses a previously created ordered_map and resets its parameters
 * 
 * @param map ordered_map to be repurposed
 * @param key_size size in bytes of the key data types to be stored
 * @param value_size size in bytes of the value data types to be stored
 * @param capacity the new desired capacity of the buffer
 * @param order_function the new comparison function for the map
 */
void reuse_ordered_map(ordered_map_t* map, size_t key_size, size_t value_size, size_t capacity, LESS_THAN_FUNC order_function);

/**
 * @brief Returns the next capacity for a resized buffer from a previous known capacity
 * 
 * @param capacity the old capacity of the buffer
 * @return the new capacity of the buffer
 */
size_t next_capacity_ordered_map(size_t capacity);

/**
 * @brief Gets the address of the value with the given key in the map
 * 
 * @param map the ordered_set from which the element is retrieved
 * @param key the key of the element to be retrieved
 * @return pointer to the data
 */
void* get_ordered_map(const ordered_map_t* map, const void* key);

/**
 * @brief Sets the new value of the element with the given key in the map
 * 
 * @param map the ordered_map in which the element is set
 * @param key the key of the element to be set
 * @param data the data to copy into the value
 */
void set_ordered_map(const ordered_map_t* map, const void* key, const void* data);

/**
 * @brief Returns current index of the key in the given arrangement of the map.
 *        If the key is not in the map it returns SIZE_MAX
 * 
 * @param map the ordered_map from which the key is searched
 * @param key the key to search
 * @return size_t index of the key
 */
size_t key_index_ordered_map(const ordered_map_t* map, const void* key);

/**
 * @brief Gets the address of the value at the given index of the map
 * 
 * @param map the ordered_map in which the value is retrieved
 * @param index the index of the element
 * @return pointer to the data
 */
void* at_index_ordered_map(const ordered_map_t* map, size_t index);

/**
 * @brief Gets the address of the key in the map
 * 
 * @param map the map to search in
 * @param key the key of the value to search
 * @return const pointer to the key position
 */
const void* find_ordered_map(const ordered_map_t* map, const void* key);

/**
 * @brief Gets the key at the given index in the ordered map
 * 
 * @param map the map to search to in
 * @param index the index of the key
 * @return const pointer to the key position
 */
const void* get_key_index_ordered_map(const ordered_map_t* map, size_t index);

/**
 * @brief Removes the given element from the ordered_map
 * 
 * @param map the ordered_map to be removed from
 * @param key the key of the pair to be removed
 */
void remove_pair_ordered_map(ordered_map_t* map, const void* key);

/**
 * @brief Inserts the given pair into the ordered_map
 * 
 * @param map the ordered_map to be added to
 * @param key the key of the value to be added
 * @param value the value to be added
 */
void insert_pair_ordered_map(ordered_map_t* map, const void* key, const void* value);

/**
 * @brief Removes the given element from the ordered_map and returns the value with the given key
 * 
 * @param map the ordered_map to be removed from
 * @param key the key of the value to be removed
 * @param value pointer to be written to
 */
void extract_pair_ordered_map(ordered_map_t* map, const void* key, void* value);

/**
 * @brief Searches for the given key in the map and returns 1 if it is in the ordered map
 *        else it returns 0
 * 
 * @param map the ordered_map to be searched
 * @param key the key to be searched
 * @return 1 if contains, 0 if does not contain
 */
int contains_ordered_map(const ordered_map_t* map, const void* key);

#endif /* DATA_ORDERED_MAP */