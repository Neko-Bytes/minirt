#ifndef INTERSECT_H
# define INTERSECT_H

# include <stdbool.h>
# include "entries.h" // Include entries.h for type definitions
# include "vector_ops.h"


typedef struct s_cylinder_ray {
	const t_cylinder *cylinder;
	t_vec3 ray_origin;
	t_vec3 direction;
	t_vec3 axis_direction;
} t_cylinder_ray;

typedef struct s_cylinder_hit {
	float t;
	t_vec3 Phit;
} t_cylinder_hit;

typedef struct s_abc
{
	float	a;
	float	b;
	float	c;
	float	dir_dot_axis;
	float	oc_dot_axis;
} t_abc;

bool intersectSphere(const t_sphere *sphere, t_vec3 ray_origin, t_vec3 direction, float *refl, float *t_out);
bool intersectPlane(const t_plane *plane, t_vec3 ray_origin, t_vec3 direction, float *t_out);
t_color rayTracing(t_vec3 direction, t_scene *scene);
bool intersectCylinder(const t_cylinder *cylinder, t_vec3 ray_origin,
	t_vec3 direction, float *refl, float *t_out);

#endif