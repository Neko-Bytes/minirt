/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:20:23 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/16 17:41:11 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*  
Here I implement a simple dynamic array structure to hold
planes and spheres. This allows for easy addition of objects
without needing to know the final count beforehand.
This is similar to a vector in C++.
*/

// Generic vector implementation
void vector_init(t_vector *vec, size_t element_size, size_t initial_capacity) {
    if (!vec || element_size == 0 || initial_capacity == 0) {
        fprintf(stderr, "Error: Invalid parameters for vector initialization\n");
        exit(EXIT_FAILURE);
    }
    
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->element_size = element_size;
    
    vec->data = malloc(element_size * initial_capacity);
    if (!vec->data) {
        fprintf(stderr, "Error: Failed to allocate memory for vector\n");
        exit(EXIT_FAILURE);
    }
}

void vector_push_back(t_vector *vec, const void *element) {
    if (!vec || !element) {
        fprintf(stderr, "Error: Invalid parameters for vector_push_back\n");
        exit(EXIT_FAILURE);
    }

    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        void *new_data = malloc(vec->element_size * new_capacity);
        if (!new_data) {
            fprintf(stderr, "Error: Failed to allocate memory for vector\n");
            exit(EXIT_FAILURE);
        }
        
        if (vec->data) {
            memcpy(new_data, vec->data, vec->element_size * vec->size);
            free(vec->data);
        }
        
        vec->data = new_data;
        vec->capacity = new_capacity;
    }

    char *dest = (char *)vec->data + (vec->size * vec->element_size);
    memcpy(dest, element, vec->element_size);
    vec->size++;
}

void *vector_at(const t_vector *vec, size_t index) {
    if (!vec) {
        fprintf(stderr, "Error: NULL vector in vector_at\n");
        exit(EXIT_FAILURE);
    }
    if (index >= vec->size) {
        fprintf(stderr, "Error: Vector index %zu out of bounds (size: %zu)\n", index, vec->size);
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

void init_object_vector(t_object_vector *vec, int initial_capacity) {
    if (!vec || initial_capacity <= 0) {
        fprintf(stderr, "Error: Invalid parameters for object vector initialization\n");
        exit(EXIT_FAILURE);
    }
    
    vector_init(&vec->planes_vec, sizeof(t_plane), initial_capacity);
    vector_init(&vec->spheres_vec, sizeof(t_sphere), initial_capacity);
    vector_init(&vec->cylinders_vec, sizeof(t_cylinder), initial_capacity);
}

void add_plane(t_object_vector *vec, t_plane plane) {
    vector_push_back(&vec->planes_vec, &plane);
}

void add_sphere(t_object_vector *vec, t_sphere sphere) {
    vector_push_back(&vec->spheres_vec, &sphere);
}

void add_cylinder(t_object_vector *vec, t_cylinder cylinder) {
    vector_push_back(&vec->cylinders_vec, &cylinder);
}

void free_object_vector(t_object_vector *vec) {
    vector_free(&vec->planes_vec);
    vector_free(&vec->spheres_vec);
    vector_free(&vec->cylinders_vec);
}

// Helper functions to access object vectors
t_plane *get_plane(const t_object_vector *vec, size_t index) {
    return (t_plane *)vector_at(&vec->planes_vec, index);
}

t_sphere *get_sphere(const t_object_vector *vec, size_t index) {
    return (t_sphere *)vector_at(&vec->spheres_vec, index);
}

t_cylinder *get_cylinder(const t_object_vector *vec, size_t index) {
    return (t_cylinder *)vector_at(&vec->cylinders_vec, index);
}

size_t get_plane_count(const t_object_vector *vec) {
    return vector_size(&vec->planes_vec);
}

size_t get_sphere_count(const t_object_vector *vec) {
    return vector_size(&vec->spheres_vec);
}

size_t get_cylinder_count(const t_object_vector *vec) {
    return vector_size(&vec->cylinders_vec);
}

