#include "ordered_map.h"

#include <string.h>

ordered_map_t create_ordered_map(size_t key_size, size_t value_size, size_t capacity, LESS_THAN_FUNC order_function)
{
    ordered_map_t out;

    out.capacity_ = capacity;
    out.key_size_ = key_size;
    out.value_size_ = value_size;
    out.size_ = 0;
    out.data_ = malloc((key_size + value_size) * capacity);
    out.order_func_ = order_function;

    return out;
}

void destroy_ordered_map(ordered_map_t* map)
{
    map->capacity_ = 0;
    map->size_ = 0;
    map->key_size_ = 0;
    map->value_size_ = 0;
    map->order_func_ = NULL;
    free(map->data_);
}

void reserve_ordered_map(ordered_map_t* map, size_t new_capacity)
{
    if (new_capacity > map->capacity_)
    {
        map->data_ = realloc(map->data_, new_capacity * (map->key_size_ + map->value_size_));
        map->capacity_ = new_capacity;
    }
}

void reuse_ordered_map(ordered_map_t* map, size_t key_size, size_t value_size, size_t capacity, LESS_THAN_FUNC order_function)
{
    if ((key_size + value_size) * capacity > map->capacity_ * (map->key_size_ + map->value_size_))
        map->data_ = realloc(map->data_, (key_size + value_size) * capacity);
    
    map->size_ = 0;
    map->key_size_ = key_size;
    map->value_size_ = value_size;
    map->capacity_ = capacity;
    map->order_func_ = order_function;
}

size_t next_capacity_ordered_map(size_t capacity)
{
    return capacity ? capacity * 2 : 2;
}

void* get_ordered_map(const ordered_map_t* map, const void* key)
{
    return (void*)find_ordered_map(map, key) + map->key_size_;
}

void set_ordered_map(const ordered_map_t* map, const void* key, const void* data)
{
    void* pos = get_ordered_map(map, key);
    memcpy(pos, data, map->value_size_);
}

void* at_index_ordered_map(const ordered_map_t* map, size_t index)
{
    if (index < map->size_)
        return map->data_ + (index * (map->value_size_ + map->key_size_)) + map->key_size_;
    return NULL;
}

size_t key_index_ordered_map(const ordered_map_t* map, const void* key)
{
    const void* data = find_ordered_map(map, key);
    if (data != NULL)
        return ((uintptr_t)data - (uintptr_t)map->data_) / (map->key_size_ + map->value_size_);
    return SIZE_MAX;
}

const void* find_ordered_map(const ordered_map_t* map, const void* key)
{
    const void* position = binary_search(key, map->data_, map->size_, map->key_size_ + map->value_size_, map->order_func_);
    if (!(map->order_func_(position, key) || map->order_func_(key, position)))
        return position;
    return NULL;
}

const void* get_key_ordered_map(const ordered_map_t* map, size_t index)
{
    if (index < map->size_)
        return map->data_ + (map->key_size_ + map->value_size_) * index;
    return NULL;
}

void remove_pair_ordered_map(ordered_map_t* map, const void* key)
{
    void* position = (void*)binary_search(key, map->data_, map->size_, map->key_size_ + map->value_size_, map->order_func_);
    if (!(map->order_func_(position, key) || map->order_func_(key, position)))
    {
        memmove(position, position + map->key_size_ + map->value_size_,
            (uintptr_t)(map->data_ + map->size_ * (map->key_size_ + map->value_size_)) - (uintptr_t)position);
        --map->size_;
    }
}

void insert_pair_ordered_map(ordered_map_t* map, const void* key, const void* value)
{
    if (map->size_ == map->capacity_)
        reserve_ordered_map(map, next_capacity_ordered_map(map->capacity_));

    if (map->size_ == 0)
    {
        memcpy(map->data_, key, map->key_size_);
        memcpy(map->data_ + map->key_size_, value, map->value_size_);
        ++map->size_;
    }
    void* position = (void*)binary_search(key, map->data_, map->size_, map->key_size_ + map->value_size_, map->order_func_);

    if (map->order_func_(position, key) != map->order_func_(key, position))
    {
        size_t offset = (uintptr_t)(map->data_ + (map->size_ * (map->key_size_ + map->value_size_))) - (uintptr_t)position;
        memmove(position + map->key_size_ + map->value_size_, position, offset);
        memcpy(position, key, map->key_size_);
        memcpy(position + map->key_size_, value, map->value_size_);
        ++map->size_;
    }
}

void extract_pair_ordered_map(ordered_map_t* map, const void* key, void* value)
{
    void* position = (void*)binary_search(key, map->data_, map->size_, map->key_size_ + map->value_size_, map->order_func_);
    if (!(map->order_func_(position, key) || map->order_func_(key, position)))
    {
        memcpy(value, position + map->key_size_, map->value_size_);
        memmove(position, position + map->key_size_ + map->value_size_,
            (uintptr_t)(map->data_ + map->size_ * (map->key_size_ + map->value_size_)) - (uintptr_t)position);
        --map->size_;
    }
}

int contains_ordered_map(const ordered_map_t* map, const void* key)
{
    return sorted_array_contains(key, map->data_, map->size_, map->key_size_ + map->value_size_, map->order_func_);
}