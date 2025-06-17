#include "../../includes/vector.h"
#include <stdio.h>

void vector_init(t_vector *vec, size_t element_size, size_t initial_capacity) {
    vec->data = malloc(element_size * initial_capacity);
    if (!vec->data) {
        fprintf(stderr, "Error: Failed to allocate memory for vector\n");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->element_size = element_size;
}

void vector_push_back(t_vector *vec, const void *element) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        void *tmp = realloc(vec->data, vec->element_size * vec->capacity);
        if (!tmp) {
            fprintf(stderr, "Error: Failed to reallocate memory for vector\n");
            exit(EXIT_FAILURE);
        }
        vec->data = tmp;
    }
    memcpy((char *)vec->data + (vec->size * vec->element_size), element, vec->element_size);
    vec->size++;
}

void *vector_at(t_vector *vec, size_t index) {
    if (index >= vec->size) {
        fprintf(stderr, "Error: Vector index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return (char *)vec->data + (index * vec->element_size);
}

size_t vector_size(const t_vector *vec) {
    return vec->size;
}

size_t vector_capacity(const t_vector *vec) {
    return vec->capacity;
}

void vector_free(t_vector *vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
} 