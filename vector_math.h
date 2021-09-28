#ifndef DATA_VECTOR_MATH_H
#define DATA_VECTOR_MATH_H

typedef struct data_vec2f_st
{
    union
    {
        float data[2];
        struct {
            float x, y;
        };
    };
} vec2f_t;

typedef struct data_vec2i_st
{
    union
    {
        int data[2];
        struct {
            int x, y;
        };
    };    
} vec2i_t;

typedef struct data_vec3f_st
{
    union
    {
        float data[3];
        struct {
            float x, y, z;
        };
    };
} vec3f_t;

typedef struct data_vec3i_st
{
    union
    {
        int data[3];
        struct {
            int x, y, z;
        };
    };    
} vec3i_t;

typedef struct data_vec4f_st
{
    union
    {
        float data[4];
        struct {
            float x, y, z, w;
        };
    };
} vec4f_t;

typedef struct data_vec4i_st
{
    union
    {
        int data[4];
        struct {
            int x, y, z, w;
        };
    };    
} vec4i_t;

#endif /* DATA_VECTOR_MATH_H */