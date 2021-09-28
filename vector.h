#ifndef DATA_VECTOR_H
#define DATA_VECTOR_H

#include <stdlib.h>

typedef struct data_vector_st
{
    size_t dimensions_;
    size_t element_size_;
    void* data_;
} vector_t;

vector_t create_vector(size_t dimensions, size_t element_size, const void* data);
void destroy_vector(vector_t* vector);

void resize_vector(vector_t* vector, size_t dimensions);
void reuse_vector(vector_t* vector, size_t dimensions, size_t element_size, const void* data);
void swap_vector(vector_t* left, vector_t* right);

void* get_element_vector(const vector_t* vector, size_t index);
void set_element_vector(vector_t* vector, size_t index, const void* data);

void fill_vector(vector_t* vector, const void* data);

vector_t create_int_vector(size_t dimensions, const int* data);
int get_int_vector(const vector_t* vector, size_t index);
void set_int_vector(vector_t* vector, size_t index, int value);
void fill_int_vector(vector_t* vector, int value);

#endif /* DATA_VECTOR_H */