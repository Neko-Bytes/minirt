/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:06:27 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:09:35 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/entries.h"
#include "../../includes/intersect.h"
#include "../../includes/light.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"

#define BIAS 0.001f

float	vec_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

bool	is_sphere_shadow(const t_scene *scene, t_vec3 point, t_light *light,
		float closest_t)
{
	size_t				i;
	t_vec3				light_dir;
	float				light_dist;
	t_intersect_result	res;
	float				t;

	i = 0;
	light_dir = vec_substract(light->position, point);
	light_dist = vec_length(light_dir);
	light_dir = vec_normalize(light_dir);
	while (i < get_sphere_count(&scene->objects))
	{
		res = intersect_sphere(get_sphere(&scene->objects, i), point,
				light_dir);
		if (res.hit)
		{
			t = res.t;
			if (t > BIAS && t < light_dist && t < closest_t)
			{
				return (true);
			}
		}
		i++;
	}
	return (false);
}

bool	is_plane_shadow(const t_scene *scene, t_vec3 point, t_light *light,
		float closest_t)
{
	size_t				i;
	t_vec3				light_dir;
	float				light_dist;
	t_intersect_result	res;
	float				t;

	i = 0;
	light_dir = vec_substract(light->position, point);
	light_dist = vec_length(light_dir);
	light_dir = vec_normalize(light_dir);
	while (i < get_plane_count(&scene->objects))
	{
		res = intersect_plane(get_plane(&scene->objects, i), point, light_dir);
		if (res.hit)
		{
			t = res.t;
			if (t > BIAS && t < light_dist && t < closest_t)
			{
				return (true);
			}
		}
		i++;
	}
	return (false);
}

bool	is_cylinder_shadow(const t_scene *scene, t_vec3 point, t_light *light,
		float closest_t)
{
	size_t				i;
	t_vec3				light_dir;
	float				light_dist;
	t_intersect_result	res;
	float				t;

	i = 0;
	light_dir = vec_substract(light->position, point);
	light_dist = vec_length(light_dir);
	light_dir = vec_normalize(light_dir);
	while (i < get_cylinder_count(&scene->objects))
	{
		res = intersect_cylinder(get_cylinder(&scene->objects, i), point,
				light_dir);
		if (res.hit)
		{
			t = res.t;
			if (t > BIAS && t < light_dist && t < closest_t)
			{
				return (true);
			}
		}
		i++;
	}
	return (false);
}

bool	is_shadow(const t_scene *scene, t_vec3 point, t_light *light,
		float closest_t)
{
	if (!scene)
		return (false);
	if (is_sphere_shadow(scene, point, light, closest_t))
		return (true);
	if (is_plane_shadow(scene, point, light, closest_t))
		return (true);
	if (is_cylinder_shadow(scene, point, light, closest_t))
		return (true);
	return (false);
}
