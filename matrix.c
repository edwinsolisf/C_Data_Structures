#include "matrix.h"

#include <string.h>

matrix_t create_matrix(size_t element_size, size_t rows, size_t columns, const void* data)
{
    matrix_t out;

    out.element_size_ = element_size;
    out.rows_ = rows;
    out.columns_ = columns;
    out.data_ = malloc(element_size * rows *  columns);
    if (data != NULL)
        memcpy(out.data_, data, element_size * rows * columns);

    return out;
}

matrix_t clone_matrix(const matrix_t* matrix)
{
    matrix_t out;

    out.element_size_ = matrix->element_size_;
    out.rows_ = matrix->rows_;
    out.columns_ = matrix->columns_;
    out.data_ = malloc(out.element_size_ * out.rows_ * out.columns_);
    memcpy(out.data_, matrix->data_, out.rows_ * out.columns_ * out.element_size_);

    return out;
}

void copy_matrix(const matrix_t* source, matrix_t* destination)
{
    memcpy(destination->data_, source->data_, destination->element_size_ * destination->rows_ * destination->columns_);
}

void fill_matrix(matrix_t* matrix, const void* data)
{
    for (size_t i = 0; i < matrix->rows_; ++i)
    {
        for (size_t j = 0; j < matrix->columns_; ++j)
            set_element_matrix(matrix, i, j, data);
    }
}

void destroy_matrix(matrix_t* matrix)
{
    matrix->element_size_ = 0;
    matrix->rows_ = 0;
    matrix->columns_ = 0;
    free(matrix->data_);
    matrix->data_ = NULL;
}

void resize_matrix(matrix_t* matrix, size_t rows, size_t columns)
{
    if (rows != 0 && columns != 0)
    {
        if (rows * columns > matrix->rows_ * matrix->columns_)
            matrix->data_ = realloc(matrix->data_, rows * columns * matrix->element_size_);
        matrix->rows_ = rows;
        matrix->columns_ = columns;
    }
}

void reuse_matrix(matrix_t* matrix, size_t element_size, size_t rows, size_t columns, const void* data)
{
    if (rows * columns * element_size > matrix->columns_ * matrix->rows_ * matrix->element_size_)
        matrix->data_ = realloc(matrix->data_, rows * columns * element_size);
    matrix->rows_ = rows;
    matrix->columns_ = columns;
    matrix->element_size_ = element_size;
    
    if (data != NULL)
        memcpy(matrix->data_, data, element_size * rows * columns);
}

void swap_matrix(matrix_t* left, matrix_t* right)
{
    matrix_t temp = *left;

    *left = *right;
    *right = temp;
}

void set_element_matrix(matrix_t* matrix, size_t row, size_t column, const void* data)
{
    memcpy(get_element_matrix(matrix, row, column), data, matrix->element_size_);
}

void* get_element_matrix(const matrix_t* matrix, size_t row, size_t column)
{
    return matrix->data_ + matrix->element_size_ * ((matrix->columns_ * row) + column);
}

matrix_t create_int_matrix(size_t rows, size_t columns, const int* data)
{
    return create_matrix(sizeof(int), rows, columns, data);
}

void set_int_matrix(matrix_t* matrix, size_t row, size_t column, int data)
{
    set_element_matrix(matrix, row, column, &data);
}

int get_int_matrix(const matrix_t* matrix, size_t row, size_t column)
{
    return *(int*)get_element_matrix(matrix, row, column);
}
