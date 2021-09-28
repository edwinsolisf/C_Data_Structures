#ifndef DATA_MATRIX_MATH_H
#define DATA_MATRIX_MATH_H

typedef struct data_mat2f_st
{
    union
    {
        float data[4];
        float x, y, z, w;
    };
} mat2f_t;

typedef struct data_mat2i_st
{
    union
    {
        int data[4];
        int x, y, z, w;
    };
} mat2i_t;

typedef struct data_mat3f_st
{
    float data[9];
} mat3f_t;

typedef struct data_mat3i_st
{
    int data[9];
} mat3i_t;

typedef struct data_mat4f_st
{
    float data[16];
} mat4f_t;

typedef struct data_mat4i_st
{
    int data[16];
} mat4i_t;

#endif /* DATA_MATRIX_MATH_H */