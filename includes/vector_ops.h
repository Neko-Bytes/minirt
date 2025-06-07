#ifndef VECTOR_OPS_H
# define VECTOR_OPS_H

# include "entries.h"

t_vec3_struct vec_add(t_vec3_struct a, t_vec3_struct b);
t_vec3_struct vec_substract(t_vec3_struct a, t_vec3_struct b);
t_vec3_struct vec_scale(t_vec3_struct v, float s);
float dot_product(t_vec3_struct a, t_vec3_struct b);
t_vec3_struct vec_normalize(t_vec3_struct v);

#endif 