#ifndef VECTOR_OPS_H
# define VECTOR_OPS_H

# include "entries.h"

t_vec3 vec_add(t_vec3 a, t_vec3 b);
t_vec3 vec_substract(t_vec3 a, t_vec3 b);
t_vec3 vec_scale(t_vec3 v, float s);
float dot_product(t_vec3 a, t_vec3 b);
t_vec3 vec_normalize(t_vec3 v);

#endif 