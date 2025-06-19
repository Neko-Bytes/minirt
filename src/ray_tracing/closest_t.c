/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:11:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 17:23:38 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"

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

static void	update_closest_result(t_closest_result *result, float t, float refl,
		int hit_type)
{
	result->closest_t = t;
	result->refl = refl;
	result->hit_type = hit_type;
}

void	find_closest_plane(const t_scene *scene, t_ray ray,
		t_closest_result *result)
{
	size_t				i;
	size_t				count;
	t_plane				*plane;
	t_intersect_result	res;
	float				t;

	i = 0;
	count = get_plane_count(&scene->objects);
	while (i < count)
	{
		t = 0.0f;
		plane = get_plane(&scene->objects, i);
		res = intersect_plane(plane, ray.origin, ray.direction);
		if (res.hit && res.t < result->closest_t)
		{
			t = res.t;
			update_closest_result(result, t, res.refl, 2);
			result->hit_index = i;
		}
		i++;
	}
}

void	find_closest_sphere(const t_scene *scene, t_ray ray,
		t_closest_result *result)
{
	size_t				i;
	size_t				count;
	t_sphere			*sphere;
	t_intersect_result	res;
	float				t;

	i = 0;
	count = get_sphere_count(&scene->objects);
	while (i < count)
	{
		t = 0.0f;
		sphere = get_sphere(&scene->objects, i);
		res = intersect_sphere(sphere, ray.origin, ray.direction);
		if (res.hit && res.t < result->closest_t)
		{
			t = res.t;
			update_closest_result(result, t, res.refl, 1);
			result->hit_index = i;
		}
		i++;
	}
}

void	find_closest_cylinder(const t_scene *scene, t_ray ray,
		t_closest_result *result)
{
	size_t				i;
	size_t				count;
	t_cylinder			*cylinder;
	t_intersect_result	res;
	float				t;

	i = 0;
	count = get_cylinder_count(&scene->objects);
	while (i < count)
	{
		t = 0.0f;
		cylinder = get_cylinder(&scene->objects, i);
		res = intersect_cylinder(cylinder, ray.origin, ray.direction);
		if (res.hit && res.t < result->closest_t)
		{
			t = res.t;
			update_closest_result(result, t, res.refl, 3);
			result->hit_index = i;
		}
		i++;
	}
}
