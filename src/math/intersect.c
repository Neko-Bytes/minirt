/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:14 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/13 17:02:58 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/entries.h"
#include "../includes/intersect.h"
#include "../includes/object_array.h"
#include "../includes/vector_ops.h"
// test included
#include "test/test.h"


bool	intersectSphere(const t_sphere *sphere, t_vec3 ray_origin,
		t_vec3 direction, float *refl, float *t_out)
{
	t_vec3	oc;
	float	half_b;
	float	c;
	float	discriminant;
	float	t;
	t_vec3	Phit;
	t_vec3	normal;

	oc = vec_substract(ray_origin, sphere->position);
	half_b = dot_product(oc, direction);
	c = dot_product(oc, oc) - sphere->radius * sphere->radius;
	discriminant = half_b * half_b - c;
	if (discriminant < 0.0f)
		return (false);
	t = -half_b - sqrtf(discriminant);
	if (t < 0.0f)
		t = -half_b + sqrtf(discriminant);
	if (t < 0.0f)
		return (false);
	Phit = vec_add(ray_origin, vec_scale(direction, t));
	normal = vec_normalize(vec_substract(Phit, sphere->position));
	*refl = -dot_product(direction, normal);
	*t_out = t;
	return (true);
}

bool	checkHeightIntersection(const t_cylinder *cylinder, t_vec3 Phit,
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

		float	radius;
	// float	dir_dot_axis;
	// float	oc_dot_axis;
	t_vec3	oc;
	t_vec3	axis_direction;
	oc = vec_substract(ray_origin, cylinder->position);
	axis_direction = vec_normalize(cylinder->orientation);
	abc->dir_dot_axis = dot_product(direction, axis_direction);
	abc->oc_dot_axis = dot_product(oc, axis_direction);
	oc = vec_substract(ray_origin, cylinder->position);
	radius = cylinder->diameter / 2.0f;
		abc->a = dot_product(direction, direction) - abc->dir_dot_axis * abc->dir_dot_axis;
	abc->b = 2.0f * (dot_product(direction, oc) - abc->dir_dot_axis * abc->oc_dot_axis);
	abc->c = dot_product(oc, oc) - abc->oc_dot_axis * abc->oc_dot_axis - radius * radius;
	return (abc->b * abc->b - 4.0f * abc->a * abc->c);
}

bool	intersectCylinder(const t_cylinder *cylinder, t_vec3 ray_origin,
		t_vec3 direction, float *refl, float *t_out)
{
	// t_vec3	oc;
	t_vec3	axis_direction;
	t_abc	abc;
	// float	radius;
	// float	dir_dot_axis;
	// float	oc_dot_axis;
	// float	a;
	// float	b;
	// float	c;

	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;
	bool	hit_found;
	float	t;
	t_vec3	Phit;
	t_vec3	cp;
	t_vec3	axis_proj;
	t_vec3	normal;

	// oc = vec_substract(ray_origin, cylinder->position);
	axis_direction = vec_normalize(cylinder->orientation);
	// radius = cylinder->diameter / 2.0f;
	// dir_dot_axis = dot_product(direction, axis_direction);
	// oc_dot_axis = dot_product(oc, axis_direction);
	// a = dot_product(direction, direction) - dir_dot_axis * dir_dot_axis;
	// b = 2.0f * (dot_product(direction, oc) - dir_dot_axis * oc_dot_axis);
	// c = dot_product(oc, oc) - oc_dot_axis * oc_dot_axis - radius * radius;
	discriminant = disc_cylinder(ray_origin, cylinder, direction, &abc);
	if (discriminant < 0.0f)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	t1 = (-abc.b - sqrt_disc) / (2.0f * abc.a);
	t2 = (-abc.b + sqrt_disc) / (2.0f * abc.a);
	hit_found = false;
	t = -1.0f;
	if (t1 > 0.0f)
	{
		Phit = vec_add(ray_origin, vec_scale(direction, t1));
		if (checkHeightIntersection(cylinder, Phit, axis_direction))
		{
			t = t1;
			hit_found = true;
		}
	}
	if (!hit_found && t2 > 0.0f)
	{
		Phit = vec_add(ray_origin, vec_scale(direction, t2));
		if (checkHeightIntersection(cylinder, Phit, axis_direction))
		{
			t = t2;
			hit_found = true;
		}
	}
	if (!hit_found)
		return (false);
	cp = vec_substract(Phit, cylinder->position);
	axis_proj = vec_scale(axis_direction, dot_product(cp, axis_direction));
	normal = vec_normalize(vec_substract(cp, axis_proj));
	*refl = -dot_product(direction, normal);
	*t_out = t;
	return (true);
}

bool	intersectPlane(const t_plane *plane, t_vec3 ray_origin,
		t_vec3 direction, float *t_out)
{
	float	denom;
	t_vec3	ray_to_plane;
	float	t;

	denom = dot_product(plane->normal, direction);
	if (fabsf(denom) < 1e-6f)
		return (false);
	ray_to_plane = vec_substract(plane->position, ray_origin);
	t = dot_product(ray_to_plane, plane->normal) / denom;
	if (t < 0.0f)
		return (false);
	*t_out = t;
	return (true);
}
