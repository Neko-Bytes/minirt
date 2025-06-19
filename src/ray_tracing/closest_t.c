/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:11:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 16:53:08 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"
#include "../../includes/light.h"
#include "../../includes/minirt.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"
#include <math.h>

t_vec3	sphere_normal(t_sphere s, t_vec3 p)
{
	return (vec_normalize(vec_substract(p, s.position)));
}

t_vec3	cylinder_normal(t_cylinder c, t_vec3 p)
{
	t_vec3	ca;
	t_vec3	cp;
	float	projection;
	t_vec3	projected;
	t_vec3	normal;

	ca = c.orientation;
	cp = vec_substract(p, c.position);
	projection = dot_product(cp, ca);
	projected = vec_scale(ca, projection);
	normal = vec_substract(cp, projected);
	return (vec_normalize(normal));
}

void	find_closest_plane(const t_scene *scene, t_ray ray,
		t_closest_result *result)
{
	size_t	i;
	size_t	count;
	float	t;
	float	local_refl;
	t_plane	*plane;

	t = 0.0f;
	i = 0;
	count = get_plane_count(&scene->objects);
	while (i < count)
	{
		t = 0.0f;
		local_refl = 1.0f;
		plane = get_plane(&scene->objects, i);
		if (intersect_plane(plane, ray.origin, ray.direction, &t))
		{
			if (t < result->closest_t)
			{
				result->closest_t = t;
				result->refl = local_refl;
				result->hit_type = 2;
				result->hit_index = i;
			}
		}
		i++;
	}
}

void	find_closest_sphere(const t_scene *scene, t_ray ray,
		t_closest_result *result)
{
	size_t		i;
	size_t		count;
	float		t;
	float		local_refl;
	t_sphere	*sphere;

	t = 0.0f;
	i = 0;
	count = get_sphere_count(&scene->objects);
	while (i < count)
	{
		t = 0.0f;
		local_refl = 1.0f;
		sphere = get_sphere(&scene->objects, i);
		if (intersectSphere(sphere, ray.origin, ray.direction, &local_refl, &t))
		{
			if (t < result->closest_t)
			{
				result->closest_t = t;
				result->refl = local_refl;
				result->hit_type = 1;
				result->hit_index = i;
			}
		}
		i++;
	}
}

void	find_closest_cylinder(const t_scene *scene, t_ray ray,
		t_closest_result *result)
{
	size_t		i;
	size_t		count;
	float		t;
	float		local_refl;
	t_cylinder	*cylinder;

	i = 0;
	t = 0.0f;
	count = get_cylinder_count(&scene->objects);
	while (i < count)
	{
		t = 0.0f;
		local_refl = 1.0f;
		cylinder = get_cylinder(&scene->objects, i);
		if (intersectCylinder(cylinder, ray.origin, ray.direction, &local_refl,
				&t))
		{
			if (t < result->closest_t)
			{
				result->closest_t = t;
				result->refl = local_refl;
				result->hit_type = 3;
				result->hit_index = i;
			}
		}
		i++;
	}
}
