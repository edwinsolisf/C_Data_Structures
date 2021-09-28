#ifndef DATA_MATRIX_H
#define DATA_MATRIX_H

/**
 * @file matrix.h
 * @author Edwin Solis (edwinsolisf12@gmail.com)
 * @brief A type adjustable implementation of a 2D matrix
 * @version 1.0
 * @date 2021-09-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>

/**
 * @brief Struct representing a 2D matrix stored in a row major order
 * 
 * @var rows_ stores the number of rows in the matrix
 * @var columns_ stores the number of columns in the matrix
 * @var element_size_ stores the size in bytes of the elements' type
 * @var data_ stores a pointer to the array of data
 */
typedef struct data_matrix_st
{
    size_t rows_;
    size_t columns_;
    size_t element_size_;
    void* data_;
} matrix_t;

/**
 * @brief Create a matrix object with the given parameters
 * 
 * @param element_size size in bytes of the data type to be stored
 * @param rows number of rows of the matrix
 * @param columns number of columns of the matrix
 * @param data inital data that the matrix will store (pass NULL to create a blank matrix)
 * @return matrix_t 
 */
matrix_t create_matrix(size_t element_size, size_t rows, size_t columns, const void* data);

/**
 * @brief Creates an exact deep copy of the given matrix
 * 
 * @param matrix matrix to be copied
 * @return matrix_t a clone of the matrix passed
 */
matrix_t clone_matrix(const matrix_t* matrix);

/**
 * @brief Copies the data in the source matrix to the destination matrix
 *        Matrix should be of the same data type and same dimensions
 * 
 * @param source matrix to be copied
 * @param destination matrix to be copied to (written to)
 */
void copy_matrix(const matrix_t* source, matrix_t* destination);

/**
 * @brief Destroys the instance of matrix passed and releases its resources
 * 
 * @param matrix matrix to be destroyed
 */
void destroy_matrix(matrix_t* matrix);

/**
 * @brief Fills all the entries of the matrix with the given data
 * 
 * @param matrix matrix to be filled
 * @param data data to be copied into the matrix entries
 */
void fill_matrix(matrix_t* matrix, const void* data);

/**
 * @brief Resizes the dimensions of the matrix while keeping its original data
 * 
 * @param matrix matrix to be resized
 * @param rows the number of rows of the new matrix
 * @param columns the number of columns of the new matrix
 */
void resize_matrix(matrix_t* matrix, size_t rows, size_t columns);

/**
 * @brief Reuses a previously created matrix instance and resets its parameters
 * 
 * @param matrix matrix to be reused
 * @param element_size size in bytes of the new data type to be stored
 * @param rows the number of rows of the new matrix
 * @param columns the number of columns of the new matrix
 * @param data the inital data that the array will store (pass NULL to create a blank matrix)
 */
void reuse_matrix(matrix_t* matrix, size_t element_size, size_t rows, size_t columns, const void* data);

/**
 * @brief Swaps the data of the two matrices given
 * 
 * @param left matrix to be swapped
 * @param right matrix to be swapped
 */
void swap_matrix(matrix_t* left, matrix_t* right);

/**
 * @brief Sets the value of the element in the array
 * 
 * @param matrix matrix to write the data in
 * @param row the row in which the element is in
 * @param column the column in which the element is in
 * @param data the data to be copied into the entry
 */
void set_element_matrix(matrix_t* matrix, size_t row, size_t column, const void* data);

/**
 * @brief Gets the address of the element in the matrix 
 * 
 * @param matrix matrix to search the element in
 * @param row the row in which the element is in
 * @param column the column in which the element is in
 * @return void* pointer to the element in the array
 */
void* get_element_matrix(const matrix_t* matrix, size_t row, size_t column);

/**
 * @brief Wrapper for creating an int specialized matrix
 * 
 * @param rows number of rows of the matrix
 * @param columns number of columns of the matrix
 * @param data inital data that the matrix will store (pass NULL to create a blank matrix)
 * @return matrix_t of ints
 */
matrix_t create_int_matrix(size_t rows, size_t columns, const int* data);

/**
 * @brief Wrapper for setting an entry in an int specialized matrix
 * 
 * @param matrix matrix to search the element in
 * @param row the row in which the element is in
 * @param column the column in which the element is in
 * @param data value to be copied into the entry
 */
void set_int_matrix(matrix_t* matrix, size_t row, size_t column, int data);

/**
 * @brief Wrapper for getting an entry in an int specialized matrix
 * 
 * @param matrix matrix to search the element in
 * @param row the row in which the element is in
 * @param column the column in which the element is in
 * @return int value of the entry
 */
int get_int_matrix(const matrix_t* matrix, size_t row, size_t column);

#endif /* DATA_MATRIX_H */
