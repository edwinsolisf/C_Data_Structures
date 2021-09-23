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

void set_element_matrix(matrix_t* matrix, size_t row, size_t column, const void* data)
{
    memcpy(get_element_matrix(matrix, row, column), data, matrix->element_size_);
}

void* get_element_matrix(const matrix_t* matrix, size_t row, size_t column)
{
    return matrix->data_ + matrix->element_size_ * (matrix->columns_ * row + column);
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
