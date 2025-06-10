#ifndef INTERSECT_H
# define INTERSECT_H

# include <stdbool.h>
# include "../includes/entries.h"
# include "vector_ops.h"

bool solveQuadratic(float a, float b, float c, float *t1, float *t2);
bool intersectSphere(const t_sphere *sphere, t_vec3 ray_origin, t_vec3 direction, float *refl, float *t_out);
bool intersectPlane(const t_plane *plane, t_vec3 ray_origin, t_vec3 direction, float *t_out);
t_color rayTracing(t_vec3 direction, t_scene *scene);
bool intersectCylinder(const t_cylinder *cylinder, t_vec3 ray_origin,
	t_vec3 direction, float *refl, float *t_out);

#endif 