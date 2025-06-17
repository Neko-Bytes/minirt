#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Generic vector structure
typedef struct s_vector {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} t_vector;

// Initialize a vector with given element size and initial capacity
void vector_init(t_vector *vec, size_t element_size, size_t initial_capacity);

// Add an element to the vector
void vector_push_back(t_vector *vec, const void *element);

// Get element at index
void *vector_at(const t_vector *vec, size_t index);

// Get current size
size_t vector_size(const t_vector *vec);

// Get current capacity
size_t vector_capacity(const t_vector *vec);

// Free vector memory
void vector_free(t_vector *vec);

#endif 