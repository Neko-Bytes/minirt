/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:14 by kruseva           #+#                #+#             */
/*   Updated: 2025/06/13 17:02:58 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/entries.h"
#include "../includes/intersect.h"
#include "../includes/object_array.h"
#include "../includes/vector_ops.h"

#define T_MIN 0.001f

t_intersect_result intersect_sphere(const t_sphere *sphere, t_vec3 ray_origin, t_vec3 direction)
{
	t_intersect_result result = { .hit = false, .t = 0.0f, .refl = 0.0f };
	t_vec3 oc = vec_substract(ray_origin, sphere->position);
	float half_b = dot_product(oc, direction);
	float c = dot_product(oc, oc) - sphere->radius * sphere->radius;
	float discriminant = half_b * half_b - c;
	if (discriminant < T_MIN)
		return result;
	float t = -half_b - sqrtf(discriminant);
	if (t < T_MIN)
		t = -half_b + sqrtf(discriminant);
	if (t < T_MIN)
		return result;
	t_vec3 Phit = vec_add(ray_origin, vec_scale(direction, t));
	t_vec3 normal = vec_normalize(vec_substract(Phit, sphere->position));
	result.refl = -dot_product(direction, normal);
	result.t = t;
	result.hit = true;
	return result;
}

bool	check_height_intersection(const t_cylinder *cylinder, t_vec3 Phit,
		t_vec3 axis_direction)
{
	float	height_at_intersection;

	height_at_intersection = dot_product(vec_substract(Phit,
				cylinder->position), axis_direction);
	if (height_at_intersection < -cylinder->height / 2.0f
		|| height_at_intersection > cylinder->height / 2.0f)
	{
		return (false);
	}
	return (true);
}

float disc_cylinder(t_vec3 ray_origin, const t_cylinder *cylinder, t_vec3 direction, t_abc *abc)
{
	float radius;
	t_vec3 oc;
	t_vec3 axis_direction;

	oc = vec_substract(ray_origin, cylinder->position);
	axis_direction = vec_normalize(cylinder->orientation);
	abc->dir_dot_axis = dot_product(direction, axis_direction);
	abc->oc_dot_axis = dot_product(oc, axis_direction);
	radius = cylinder->diameter / 2.0f;
	abc->a = dot_product(direction, direction) - abc->dir_dot_axis * abc->dir_dot_axis;
	abc->b = 2.0f * (dot_product(direction, oc) - abc->dir_dot_axis * abc->oc_dot_axis);
	abc->c = dot_product(oc, oc) - abc->oc_dot_axis * abc->oc_dot_axis - radius * radius;
	return (abc->b * abc->b - 4.0f * abc->a * abc->c);
}

static bool find_cylinder_hit_t(const t_cylinder_ray *cray, t_abc *abc, t_cylinder_hit *hit, float discriminant)
{
	float t1;
	float t2;
	t1 = (-abc->b - sqrtf(discriminant)) / (2.0f * abc->a);
	t2 = (-abc->b + sqrtf(discriminant)) / (2.0f * abc->a);
	if (t1 > 0.0f)
	{
		hit->Phit = vec_add(cray->ray_origin, vec_scale(cray->direction, t1));
		if (check_height_intersection(cray->cylinder, hit->Phit, cray->axis_direction))
		{
			hit->t = t1;
			return true;
		}
	}
	if (t2 > 0.0f)
	{
		hit->Phit = vec_add(cray->ray_origin, vec_scale(cray->direction, t2));
		if (check_height_intersection(cray->cylinder, hit->Phit, cray->axis_direction))
		{
			hit->t = t2;
			return true;
		}
	}
	return false;
}

t_intersect_result intersect_cylinder(const t_cylinder *cylinder, t_vec3 ray_origin, t_vec3 direction)
{
	t_intersect_result result = { .hit = false, .t = 0.0f, .refl = 0.0f };
	t_cylinder_ray cray;
	cray.cylinder = cylinder;
	cray.ray_origin = ray_origin;
	cray.direction = direction;
	cray.axis_direction = vec_normalize(cylinder->orientation);
	t_abc abc;
	t_cylinder_hit hit;
	float discriminant = disc_cylinder(cray.ray_origin, cray.cylinder, cray.direction, &abc);
	if (discriminant < T_MIN)
		return result;
	if (!find_cylinder_hit_t(&cray, &abc, &hit, discriminant))
		return result;
	t_vec3 cp = vec_substract(hit.Phit, cray.cylinder->position);
	t_vec3 axis_proj = vec_scale(cray.axis_direction, dot_product(cp, cray.axis_direction));
	t_vec3 normal = vec_normalize(vec_substract(cp, axis_proj));
	result.refl = -dot_product(cray.direction, normal);
	result.t = hit.t;
	result.hit = true;
	return result;
}

t_intersect_result intersect_plane(const t_plane *plane, t_vec3 ray_origin, t_vec3 direction)
{
	t_intersect_result result = { .hit = false, .t = 0.0f, .refl = 1.0f };
	float denom = dot_product(plane->normal, direction);
	if (fabsf(denom) < 1e-6f)
		return result;
	t_vec3 ray_to_plane = vec_substract(plane->position, ray_origin);
	float t = dot_product(ray_to_plane, plane->normal) / denom;
	if (t < T_MIN)
		return result;
	result.t = t;
	result.hit = true;
	return result;
}
