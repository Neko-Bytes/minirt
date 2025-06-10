/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:20:23 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/10 17:58:51 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/object_array.h"

/*  
Here I implement a simple dynamic array structure to hold
planes and spheres. This allows for easy addition of objects
without needing to know the final count beforehand.
This is similar to a vector in C++.
*/

void init_object_vector(t_object_vector *vec, int initial_capacity) {
    vec->planes = malloc(sizeof(t_plane) * initial_capacity);
    vec->plane_count = 0;
    vec->plane_capacity = initial_capacity;

    vec->spheres = malloc(sizeof(t_sphere) * initial_capacity);
    vec->sphere_count = 0;
    vec->sphere_capacity = initial_capacity;

    vec->cylinders = malloc(sizeof(t_cylinder) * initial_capacity);
    vec->cylinder_count = 0;
    vec->cylinder_capacity = initial_capacity;
}

void add_plane(t_object_vector *vec, t_plane plane) {
    if (vec->plane_count >= vec->plane_capacity) {
        vec->plane_capacity *= 2;
        void *tmp = realloc(vec->planes, sizeof(t_plane) * vec->plane_capacity);
        if (!tmp) {
            fprintf(stderr, "Error\nrealloc failed for planes\n");
            exit(EXIT_FAILURE);
        }
        vec->planes = tmp;
    }
    vec->planes[vec->plane_count++] = plane;
}

void add_sphere(t_object_vector *vec, t_sphere sphere) {
    if (vec->sphere_count >= vec->sphere_capacity) {
        vec->sphere_capacity *= 2;
        void *tmp = realloc(vec->spheres, sizeof(t_sphere) * vec->sphere_capacity);
        if (!tmp) {
            fprintf(stderr, "Error\nrealloc failed for spheres\n");
            exit(EXIT_FAILURE);
        }
        vec->spheres = tmp;
    }
    vec->spheres[vec->sphere_count++] = sphere;
}

void add_cylinder(t_object_vector *vec, t_cylinder cylinder) {
    if (vec->cylinder_count >= vec->cylinder_capacity) {
        vec->cylinder_capacity *= 2;
        void *tmp = realloc(vec->cylinders, sizeof(t_cylinder) * vec->cylinder_capacity);
        if (!tmp) {
            fprintf(stderr, "Error\nrealloc failed for cylinders\n");
            exit(EXIT_FAILURE);
        }
        vec->cylinders = tmp;
    }
    vec->cylinders[vec->cylinder_count++] = cylinder;
}

void free_object_vector(t_object_vector *vec) {
    free(vec->planes);
    free(vec->spheres);
    free(vec->cylinders);
    vec->plane_count = 0;
    vec->plane_capacity = 0;
    vec->sphere_count = 0;
    vec->sphere_capacity = 0;
    vec->cylinder_count = 0;
    vec->cylinder_capacity = 0;
}

// Print the contents of the object vector for debugging
void print_object_vector(const t_object_vector *vec) {
    for (int i = 0; i < vec->plane_count; i++) {
        printf("Plane %d: Pos(%.2f %.2f %.2f), Normal(%.2f %.2f %.2f)\n",
               i,
               vec->planes[i].position.x,
               vec->planes[i].position.y,
               vec->planes[i].position.z,
               vec->planes[i].normal.x,
               vec->planes[i].normal.y,
               vec->planes[i].normal.z);
    }

    for (int i = 0; i < vec->sphere_count; i++) {
        printf("Sphere %d: Pos(%.2f %.2f %.2f), Radius(%.2f)\n",
               i,
               vec->spheres[i].position.x,
               vec->spheres[i].position.y,
               vec->spheres[i].position.z,
               vec->spheres[i].radius);
    }
}
