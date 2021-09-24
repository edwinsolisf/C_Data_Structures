#include "algorithm.h"

const void* linear_search(const void* element, const void* array, size_t element_count, size_t element_size, EQUALS_FUNC equal_func)
{
    for (size_t i = 0; i < element_count; ++i)
    {
        const void* pos = array + (i * element_size);
        if (equal_func(element, pos))
            return (void*)pos;
    }

    return NULL;
}

const void* binary_search(const void* element, const void* array, size_t element_count, size_t element_size, LESS_THAN_FUNC order_func)
{
    if (element_count == 0)
        return array;

    const void* left = array;
    const void* right = array + (element_count - 1) * element_size;

    if (!order_func(left, element))
        return left;
    if (order_func(right, element))
        return right + element_size;
    else if (!order_func(element, right))
        return right;

    const void* current = left + ((((uintptr_t)right - (uintptr_t)left) / (element_size)) / 2) * element_size;

    while ((right - left) > element_size)
    {
        if (!(order_func(current, element) || order_func(element, current)))
            return current;
        else if (!order_func(current, element))
            right = current;
        else
            left = current;

        current = left + (((right - left) / (element_size)) / 2) * element_size;

    }

    return (order_func(current, element) ? current + element_size : current);
}

int array_contains(const void* element, const void* array, size_t element_count, size_t element_size, EQUALS_FUNC equal_func)
{
    return linear_search(element, array, element_count, element_size, equal_func) == NULL ? 0 : 1;
}

int sorted_array_contains(const void* element, const void* array, size_t element_count, size_t element_size, LESS_THAN_FUNC order_func)
{
    const void* position = binary_search(element, array, element_count, element_size, order_func);
    if (!(order_func(position, element) || order_func(element, position)))
        return 1;
    return 0;
}