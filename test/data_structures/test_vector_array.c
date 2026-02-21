#include <criterion/criterion.h>
#include <stdio.h>

#include "data_structures/vector_array/vector_array.h"

TestSuite(vector, .timeout = 1);

Test(vector, simple_add_get)
{
    int test_num[] = {0, 12, 4, 5, 3, 154, 234567, -15, 5, 20};
    vector_array array = vector_create(sizeof(int), 10);

    size_t indexes[10];
    for (int i = 0; i < 10; i++)
    {
        size_t index = vector_add(array);
        indexes[i] = index;
        int *src = vector_get(array, index);
        *src = test_num[i];
    }

    for (int i = 0; i < 10; i++)
    {
        int *elem = vector_get(array, indexes[i]);
        cr_expect_eq(*elem, test_num[i]);
    }
}

Test(vector, simple_add_resize)
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

    for (int i = 0; i < 10; i++)
    {
        int *elem = vector_get(array, indexes[i]);
        cr_expect_eq(*elem, test_num[i]);
    }
}

Test(vector, simple_rm)
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

    cr_expect(vector_remove(array, indexes[3]));

    for (int i = 0; i < 3; i++)
    {
        int *elem = vector_get(array, indexes[i]);
        cr_expect_eq(*elem, test_num[i]);
    }

    for (int i = 4; i < 10; i++)
    {
        int *elem = vector_get(array, indexes[i]);
        cr_expect_eq(*elem, test_num[i]);
    }
}

Test(vector, rm_rebuild)
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
        vector_remove(array, indexes[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        size_t index = vector_add(array);
        indexes[i] = index;
        int *src = vector_get(array, index);
        *src = test_num[i];
    }

    for (int i = 0; i < 10; i++)
    {
        int *elem = vector_get(array, indexes[i]);
        cr_expect_eq(*elem, test_num[i]);
    }
}

Test(vector, rm_borders)
{
    int test_num[] = {34, 67, 81, 12, 0, 2, -4, 82, 7, -32};
    vector_array array = vector_create(sizeof(int), 1);

    size_t indexes[10];
    for (int i = 0; i < 10; i++)
    {
        size_t index = vector_add(array);
        indexes[i] = index;
        int *src = vector_get(array, index);
        *src = test_num[i];
    }
    cr_expect(vector_remove(array, 9));
    cr_expect(vector_remove(array, 0));

    size_t index = vector_add(array);
    int *src = vector_get(array, index);
    *src = 3;

    index = vector_add(array);
    src = vector_get(array, index);
    *src = 24;

    int expected[] = {3, 67, 81, 12, 0, 2, -4, 82, 7, 24};
    for (int i = 0; i < 10; i++)
    {
        int *elem = vector_get(array, indexes[i]);
        cr_expect_eq(*elem, expected[i]);
    }
}
