#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include <stdbool.h>
# include "../includes/entries.h"
# include "vector_ops.h"

bool solveQuadratic(float a, float b, float c, float *t1, float *t2);
bool intersect(t_vec3_struct direction, float *refl);
t_color_struct rayTracing(t_vec3_struct direction);

#endif 