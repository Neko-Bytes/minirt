#ifndef OBJECT_ARRAY_H
#define OBJECT_ARRAY_H

#include "entries.h"
#include "vector.h"

// Object vector specific functions
void init_object_vector(t_object_vector *vec, int initial_capacity);
void add_plane(t_object_vector *vec, t_plane plane);
void add_sphere(t_object_vector *vec, t_sphere sphere);
void add_cylinder(t_object_vector *vec, t_cylinder cylinder);
void free_object_vector(t_object_vector *vec);
void print_object_vector(const t_object_vector *vec);
void init_scene(t_scene *scene);

// Helper functions to access object vectors
t_plane *get_plane(const t_object_vector *vec, size_t index);
t_sphere *get_sphere(const t_object_vector *vec, size_t index);
t_cylinder *get_cylinder(const t_object_vector *vec, size_t index);
size_t get_plane_count(const t_object_vector *vec);
size_t get_sphere_count(const t_object_vector *vec);
size_t get_cylinder_count(const t_object_vector *vec);

#endif