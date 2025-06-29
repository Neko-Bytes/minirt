/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:18:40 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/29 14:35:19 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "entries.h"
# include "vector_ops.h"
# include <stdbool.h>

# define T_MIN 0.001f

typedef struct s_cylinder_ray
{
	const t_cylinder	*cylinder;
	t_vec3				ray_origin;
	t_vec3				direction;
	t_vec3				axis_direction;
}						t_cylinder_ray;

typedef struct s_cylinder_hit
{
	float				t;
	t_vec3				phit;
}						t_cylinder_hit;

typedef struct s_abc
{
	float				a;
	float				b;
	float				c;
	float				dir_dot_axis;
	float				oc_dot_axis;
}						t_abc;

typedef struct s_cylinder_intersect_vars
{
	t_cylinder_ray		cray;
	t_abc				abc;
	t_cylinder_hit		hit;
	float				discriminant;
	t_vec3				cp;
	t_vec3				axis_proj;
	t_vec3				normal;
}						t_cylinder_intersect_vars;

typedef struct s_sphere_intersect_vars
{
	t_vec3				oc;
	float				half_b;
	float				c;
	float				discriminant;
	float				t;
	t_vec3				phit;
	t_vec3				normal;
}						t_sphere_intersect_vars;

typedef struct s_intersect_result
{
	bool				hit;
	float				t;
	float				refl;
}						t_intersect_result;

t_color					ray_tracing(t_vec3 direction, t_scene *scene);
t_intersect_result		intersect_sphere(const t_sphere *sphere,
							t_vec3 ray_origin, t_vec3 direction);
t_intersect_result		intersect_cylinder(const t_cylinder *cylinder,
							t_vec3 ray_origin, t_vec3 direction);
t_intersect_result		intersect_plane(const t_plane *plane, t_vec3 ray_origin,
							t_vec3 direction);
bool					find_cylinder_hit_t(const t_cylinder_ray *cray,
							t_abc *abc, t_cylinder_hit *hit,
							float discriminant);
float					disc_cylinder(t_vec3 ray_origin,
							const t_cylinder *cylinder, t_vec3 direction,
							t_abc *abc);

#endif