#include "vector_array.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector_array
{
    size_t elem_size;
    size_t elem_count;
    size_t offset_count;
    size_t capacity;
    size_t *offset_array;
    size_t *src_offset_array;
    void *data;
};

bool vector_resize(vector_array array, size_t new_capacity);

vector_array vector_create(size_t elem_size, size_t capacity)
{
    if (capacity == 0)
    {
        return NULL;
    }
    vector_array array = calloc(1, sizeof(struct vector_array));
    if (array == NULL)
        return NULL;

    array->elem_size = elem_size;
    vector_resize(array, capacity);

    return array;
}

void vector_destroy(vector_array array)
{
    if (!array)
        return;
    free(array->data);
    free(array);
}

void *vector_get(vector_array array, size_t index)
{
    if (!array || index >= array->offset_count)
    {
        return NULL;
    }

    size_t offset = array->offset_array[index];
    if (offset == SIZE_MAX)
    {
        return NULL;
    }
    return array->data + offset * array->elem_size;
}

bool vector_resize(vector_array array, size_t new_capacity)
{
    void *temp;

    temp = realloc(array->data, new_capacity * array->elem_size);
    if (temp == NULL)
        return false;
    array->data = temp;

    temp = realloc(array->offset_array, new_capacity * sizeof(size_t));
    if (temp == NULL)
        return false;
    array->offset_array = temp;

    temp = realloc(array->src_offset_array, new_capacity * sizeof(size_t));
    if (temp == NULL)
        return false;
    array->src_offset_array = temp;

    array->capacity = new_capacity;
    return true;
}

size_t vector_add(vector_array array)
{
    if (!array)
        return -1;
    if (array->capacity <= array->elem_count)
    {
        if (!vector_resize(array, array->capacity * 2))
        {
            return -1;
        }
    }

    if (array->offset_count == array->elem_count)
    {
        array->offset_array[array->elem_count] = array->elem_count;
        array->src_offset_array[array->elem_count] = array->elem_count;

        array->offset_count += 1;

        return array->elem_count++;

    }

    size_t offset = array->src_offset_array[array->elem_count];
    array->offset_array[offset] = array->elem_count;

    array->elem_count ++;
    return offset;
}

bool vector_remove(vector_array array, size_t index)
{
    if (!array || array->elem_count <= index)
    {
        return false;
    }
    size_t actual_index = array->offset_array[index];
    array->elem_count -= 1;
    size_t last_index = array->offset_array[array->elem_count];


    memcpy(array->data + actual_index * array->elem_size,
           array->data + array->elem_count * array->elem_size,
           array->elem_size);

    array->src_offset_array[actual_index] = last_index;
    array->src_offset_array[array->elem_count] = index;
    array->offset_array[last_index] = array->offset_array[index];
    array->offset_array[index] = SIZE_MAX;

    return true;
}

static void print_offset(size_t offset)
{
    if (offset == -1)
    {
        printf("NULL");
    }
    else
    {
        printf("%lu", offset);
    }
}

void vector_debug(vector_array array, void (*print) (void *))
{
    for (size_t i = 0; i < array->offset_count; i++)
    {
        print_offset(array->offset_array[i]);
        printf(",\t");
    }
    puts("");
    for (size_t i = 0; i < array->offset_count; i++)
    {
        print_offset(array->src_offset_array[i]);
        printf(",\t");
    }
    puts("");

    for (size_t i = 0; i < array->elem_count; i++)
    {
        print(array->data + i * array->elem_size);
        printf(",\t");
    }
    puts("\n");
}

size_t vector_get_size(vector_array array)
{
    return array->elem_count;
}

void *vector_get_data(vector_array array)
{
    return array->data;
}
