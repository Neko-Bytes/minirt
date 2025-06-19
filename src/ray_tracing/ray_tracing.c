/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:19:59 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 16:51:36 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"
#include "../../includes/light.h"
#include "../../includes/minirt.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"
#include <math.h>

static t_ray	initialize_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

static void	find_closest_objects(t_scene *scene, t_ray ray,
		t_closest_result *result)
{
	find_closest_plane(scene, ray, result);
	find_closest_sphere(scene, ray, result);
	find_closest_cylinder(scene, ray, result);
}

static t_hit_lookup	initialize_hit_lookup(t_closest_result result,
		t_vec3 hit_point)
{
	t_hit_lookup	lookup;

	lookup.hit_type = result.hit_type;
	lookup.hit_index = result.hit_index;
	lookup.hit_point = hit_point;
	return (lookup);
}

static t_hit_info	initialize_hit_info(t_vec3 hit_point, t_vec3 normal,
		t_color base_color, float closest_t)
{
	t_hit_info	hit;

	hit.hit_point = hit_point;
	hit.normal = normal;
	hit.base_color = base_color;
	hit.closest_t = closest_t;
	return (hit);
}

t_color	ray_tracing(t_vec3 direction, t_scene *scene)
{
	t_ray_tracing_vars	vars;

	vars.final_color = (t_color){0.0f, 0.0f, 0.0f};
	vars.result = assign_closest_result();
	vars.ray = initialize_ray(scene->camera->position, direction);
	find_closest_objects(scene, vars.ray, &vars.result);
	vars.hit_point = vec_add(scene->camera->position, vec_scale(direction,
				vars.result.closest_t));
	vars.lookup = initialize_hit_lookup(vars.result, vars.hit_point);
	get_hit_normal(scene, &vars.lookup, &vars.normal);
	get_hit_color(scene, &vars.lookup, &vars.base_color);
	vars.light = (t_light *)vector_at(&scene->lights_vec, 0);
	vars.hit = initialize_hit_info(vars.hit_point, vars.normal, vars.base_color,
			vars.result.closest_t);
	apply_shadow_and_diffuse(scene, &vars.hit, vars.light, &vars.final_color);
	apply_ambient(scene, vars.base_color, &vars.final_color);
	return (vars.final_color);
}
