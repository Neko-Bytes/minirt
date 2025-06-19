/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:04:11 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:21:33 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/entries.h"
#include "../includes/intersect.h"
#include "../includes/object_array.h"
#include "../includes/vector_ops.h"

t_intersect_result	intersect_cylinder(const t_cylinder *cylinder,
		t_vec3 ray_origin, t_vec3 direction)
{
	t_intersect_result			result;
	t_cylinder_intersect_vars	vars;

	result.hit = false;
	result.t = 0.0f;
	result.refl = 0.0f;
	vars.cray.cylinder = cylinder;
	vars.cray.ray_origin = ray_origin;
	vars.cray.direction = direction;
	vars.cray.axis_direction = vec_normalize(cylinder->orientation);
	vars.discriminant = disc_cylinder(vars.cray.ray_origin, vars.cray.cylinder,
			vars.cray.direction, &vars.abc);
	if (vars.discriminant < T_MIN)
		return (result);
	if (!find_cylinder_hit_t(&vars.cray, &vars.abc, &vars.hit,
			vars.discriminant))
		return (result);
	vars.cp = vec_substract(vars.hit.phit, vars.cray.cylinder->position);
	vars.axis_proj = vec_scale(vars.cray.axis_direction, dot_product(vars.cp,
				vars.cray.axis_direction));
	vars.normal = vec_normalize(vec_substract(vars.cp, vars.axis_proj));
	result.refl = -dot_product(vars.cray.direction, vars.normal);
	result.t = vars.hit.t;
	result.hit = true;
	return (result);
}

t_intersect_result	intersect_sphere(const t_sphere *sphere, t_vec3 ray_origin,
		t_vec3 direction)
{
	t_intersect_result		result;
	t_sphere_intersect_vars	vars;

	result.hit = false;
	result.t = 0.0f;
	result.refl = 1.0f;
	vars.oc = vec_substract(ray_origin, sphere->position);
	vars.half_b = dot_product(vars.oc, direction);
	vars.c = dot_product(vars.oc, vars.oc) - sphere->radius * sphere->radius;
	vars.discriminant = vars.half_b * vars.half_b - vars.c;
	if (vars.discriminant < T_MIN)
		return (result);
	vars.t = -vars.half_b - sqrtf(vars.discriminant);
	if (vars.t < T_MIN)
		vars.t = -vars.half_b + sqrtf(vars.discriminant);
	if (vars.t < T_MIN)
		return (result);
	vars.phit = vec_add(ray_origin, vec_scale(direction, vars.t));
	vars.normal = vec_normalize(vec_substract(vars.phit, sphere->position));
	result.refl = -dot_product(direction, vars.normal);
	result.t = vars.t;
	result.hit = true;
	return (result);
}
