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

/*  
Here I implement a simple dynamic array structure to hold
planes and spheres. This allows for easy addition of objects
without needing to know the final count beforehand.
This is similar to a vector in C++.
*/

void init_object_vector(t_object_vector *vec, int initial_capacity) {
    vec->planes = malloc(sizeof(t_plane) * initial_capacity);
    vec->pl_count = 0;
    vec->pl_capacity = initial_capacity;

    vec->spheres = malloc(sizeof(t_sphere) * initial_capacity);
    vec->sp_count = 0;
    vec->sp_capacity = initial_capacity;

    vec->cylinders = malloc(sizeof(t_cylinder) * initial_capacity);
    vec->cy_count = 0;
    vec->cy_capacity = initial_capacity;
}

void add_plane(t_object_vector *vec, t_plane plane) {
    if (vec->pl_count >= vec->pl_capacity) {
        vec->pl_capacity *= 2;
        void *tmp = realloc(vec->planes, sizeof(t_plane) * vec->pl_capacity);
        if (!tmp) {
            fprintf(stderr, "Error\nrealloc failed for planes\n");
            exit(EXIT_FAILURE);
        }
        vec->planes = tmp;
    }
    vec->planes[vec->pl_count++] = plane;
}

void add_sphere(t_object_vector *vec, t_sphere sphere) {
    if (vec->sp_count >= vec->sp_capacity) {
        vec->sp_capacity *= 2;
        void *tmp = realloc(vec->spheres, sizeof(t_sphere) * vec->sp_capacity);
        if (!tmp) {
            fprintf(stderr, "Error\nrealloc failed for spheres\n");
            exit(EXIT_FAILURE);
        }
        vec->spheres = tmp;
    }
    vec->spheres[vec->sp_count++] = sphere;
}

void add_cylinder(t_object_vector *vec, t_cylinder cylinder) {
    if (vec->cy_count >= vec->cy_capacity) {
        vec->cy_capacity *= 2;
        void *tmp = realloc(vec->cylinders, sizeof(t_cylinder) * vec->cy_capacity);
        if (!tmp) {
            fprintf(stderr, "Error\nrealloc failed for cylinders\n");
            exit(EXIT_FAILURE);
        }
        vec->cylinders = tmp;
    }
    vec->cylinders[vec->cy_count++] = cylinder;
}

void free_object_vector(t_object_vector *vec) {
    free(vec->planes);
    free(vec->spheres);
    free(vec->cylinders);
    vec->pl_count = 0;
    vec->pl_capacity = 0;
    vec->sp_count = 0;
    vec->sp_capacity = 0;
    vec->cy_count = 0;
    vec->cy_capacity = 0;
}

// // Print the contents of the object vector for debugging
// void print_object_vector(const t_object_vector *vec) {
//     for (int i = 0; i < vec->pl_count; i++) {
//         printf("Plane %d: Pos(%.2f %.2f %.2f), Normal(%.2f %.2f %.2f)\n",
//                i,
//                vec->planes[i].position.x,
//                vec->planes[i].position.y,
//                vec->planes[i].position.z,
//                vec->planes[i].normal.x,
//                vec->planes[i].normal.y,
//                vec->planes[i].normal.z);
//     }

//     for (int i = 0; i < vec->sp_count; i++) {
//         printf("Sphere %d: Pos(%.2f %.2f %.2f), Radius(%.2f)\n",
//                i,
//                vec->spheres[i].position.x,
//                vec->spheres[i].position.y,
//                vec->spheres[i].position.z,
//                vec->spheres[i].radius);
//     }
// }
