#include <stdio.h>

#include "data_structures/vector_array/vector_array.h"

void print(void *i)
{
    printf("%d", *(int *)i);
}

int main()
{
    int test_num[] = {0, 12, 4, 5, 3, 154, 234567, -15, 5, 20};
    vector_array array = vector_create(sizeof(int), 1);

    size_t indexes[10];
    for (int i = 0; i < 10; i++)
    {
        size_t index = vector_add(array);
        indexes[i] = index;
        int *src = vector_get(array, index);
        *src = test_num[i];
    }

    for (int i = 9; i >= 0; i--)
    {
        vector_debug(array, print);
        vector_remove(array, indexes[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        size_t index = vector_add(array);
        indexes[i] = index;
        int *src = vector_get(array, index);
        *src = test_num[i];
    }

    vector_debug(array, print);
    for (int i = 0; i < 10; i++)
    {
        int *elem = vector_get(array, indexes[i]);
    }
}