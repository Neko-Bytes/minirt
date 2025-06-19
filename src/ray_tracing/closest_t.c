/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Home <Home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:11:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 17:12:50 by Home             ###   ########.fr       */
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

static void update_closest_result(t_closest_result *result, float t, float refl, int hit_type, size_t hit_index)
{
	result->closest_t = t;
	result->refl = refl;
	result->hit_type = hit_type;
	result->hit_index = hit_index;
}

void	find_closest_plane(const t_scene *scene, t_ray ray, t_closest_result *result)
{
	size_t i = 0, count = get_plane_count(&scene->objects);
	float t, local_refl = 1.0f;
	t_plane *plane;
	while (i < count)
	{
		t = 0.0f;
		plane = get_plane(&scene->objects, i);
		t_intersect_result res = intersect_plane(plane, ray.origin, ray.direction);
		if (res.hit && res.t < result->closest_t)
		{
			t = res.t;
			local_refl = res.refl;
			update_closest_result(result, t, local_refl, 2, i);
		}
		i++;
	}
}

void	find_closest_sphere(const t_scene *scene, t_ray ray, t_closest_result *result)
{
	size_t i = 0, count = get_sphere_count(&scene->objects);
	float t, local_refl;
	t_sphere *sphere;
	while (i < count)
	{
		t = 0.0f;
		local_refl = 1.0f;
		sphere = get_sphere(&scene->objects, i);
		t_intersect_result res = intersect_sphere(sphere, ray.origin, ray.direction);
		if (res.hit && res.t < result->closest_t)
		{
			t = res.t;
			local_refl = res.refl;
			update_closest_result(result, t, local_refl, 1, i);
		}
		i++;
	}
}

void	find_closest_cylinder(const t_scene *scene, t_ray ray, t_closest_result *result)
{
	size_t i = 0, count = get_cylinder_count(&scene->objects);
	float t, local_refl;
	t_cylinder *cylinder;
	while (i < count)
	{
		t = 0.0f;
		local_refl = 1.0f;
		cylinder = get_cylinder(&scene->objects, i);
		t_intersect_result res = intersect_cylinder(cylinder, ray.origin, ray.direction);
		if (res.hit && res.t < result->closest_t)
		{
			t = res.t;
			local_refl = res.refl;
			update_closest_result(result, t, local_refl, 3, i);
		}
		i++;
	}
}
