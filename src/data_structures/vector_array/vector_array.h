#ifndef ARRAY_H
#define ARRAY_H
#include <stdbool.h>
#include <stddef.h>

// Allows insertion(can't choose where) deletion and get in constant time
struct vector_array;
typedef struct vector_array *vector_array;

vector_array vector_create(size_t elem_size, size_t capacity);
void vector_destroy(vector_array array);
void *vector_get(vector_array array, size_t index);
size_t vector_add(vector_array array);
bool vector_remove(vector_array array, size_t index);
size_t vector_get_size(vector_array array);
void *vector_get_data(vector_array array);
void vector_debug(vector_array array, void (*print) (void *));

#endif /* ! ARRAY_H */
