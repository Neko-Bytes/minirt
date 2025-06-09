#include "../includes/vector_ops.h"
#include "../includes/entries.h"

void init_object_vector(t_object_vector *vec, int initial_capacity);
void add_plane(t_object_vector *vec, t_plane plane);
void add_sphere(t_object_vector *vec, t_sphere sphere);
void free_object_vector(t_object_vector *vec);
void print_object_vector(const t_object_vector *vec);