#include "vector.h"

#include <string.h>

vector_t create_vector(size_t dimensions, size_t element_size, const void* data)
{
    vector_t out;

    out.dimensions_ = dimensions;
    out.element_size_ = element_size;
    out.data_ = malloc(dimensions * element_size);
    if (data != NULL)
        memcpy(out.data_, data, dimensions * element_size);

    return out;
}

void destroy_vector(vector_t* vector)
{
    vector->dimensions_ = 0;
    vector->element_size_ = 0;
    free(vector->data_);
    vector->data_ = NULL;
}

void resize_vector(vector_t* vector, size_t dimensions)
{
    if (dimensions != 0)
    {
        if (dimensions >  vector->dimensions_)
            vector->data_ = realloc(vector->data_, dimensions * vector->element_size_);
        vector->dimensions_ = dimensions;
    }
}

void reuse_vector(vector_t* vector, size_t dimensions, size_t element_size, const void* data)
{
    if (dimensions * element_size > vector->dimensions_ * vector->element_size_)
        vector->data_ = realloc(vector->data_, dimensions * element_size);
    vector->element_size_ = element_size;
    vector->dimensions_ = dimensions;
   
    if (data != NULL)
        memcpy(vector->data_, data, element_size * dimensions);
}

void swap_vector(vector_t* left, vector_t* right)
{
    vector_t temp = *left;

    *left = *right;
    *right = temp;
}

void* get_element_vector(const vector_t* vector, size_t index)
{
    return index < vector->dimensions_? vector->data_ + (index * vector->element_size_) : NULL;
}

void set_element_vector(vector_t* vector, size_t index, const void* data)
{
    memcpy(get_element_vector(vector, index), data, vector->element_size_);
}

void fill_vector(vector_t* vector, const void* data)
{
    for (size_t i = 0; i < vector->dimensions_; ++i)
        set_element_vector(vector, i, data);
}

vector_t create_int_vector(size_t dimensions, const int* data)
{
    return create_vector(dimensions, sizeof(int), data);
}

int get_int_vector(const vector_t* vector, size_t index)
{
    return *(int*)get_element_vector(vector, index);
}

void set_int_vector(vector_t* vector, size_t index, int value)
{
    set_element_vector(vector, index, &value);
}

void fill_int_vector(vector_t* vector, int value)
{
    fill_vector(vector, &value);
}