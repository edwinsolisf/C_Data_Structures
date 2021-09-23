#ifndef DATA_MATRIX_H
#define DATA_MATRIX_H

#include <stdlib.h>

typedef struct
{
    size_t rows_;
    size_t columns_;
    size_t element_size_;
    void* data_;
} matrix_t;

matrix_t create_matrix(size_t element_size, size_t rows, size_t columns);
void destroy_matrix(matrix_t* matrix);

void resize_matrix(matrix_t* matrix, size_t rows, size_t columns);
void reuse_matrix(matrix_t* matrix, size_t element_size, size_t rows, size_t columns);

void set_element_matrix(matrix_t* matrix, size_t row, size_t column, const void* data);
void* get_element_matrix(const matrix_t* matrix, size_t row, size_t column);

matrix_t create_int_matrix(size_t rows, size_t columns);
void set_int_matrix(matrix_t* matrix, size_t row, size_t column, int data);
int get_int_matrix(const matrix_t* matrix, size_t row, size_t column);

#endif /* DATA_MATRIX_H */
