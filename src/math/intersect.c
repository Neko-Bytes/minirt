/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:14 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/10 17:53:47 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/entries.h"
#include "../includes/intersect.h"
#include "../includes/object_array.h"
#include "../includes/vector_ops.h"
// test included
#include "test/test.h"

bool	solveQuadratic(float a, float b, float c, float *t1, float *t2)
{
	float	discriminant;
	float	sqrt_disc;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	*t1 = (-b - sqrt_disc) / (2.0f * a);
	*t2 = (-b + sqrt_disc) / (2.0f * a);
	return (true);
}

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

bool checkHeightIntersection(const t_cylinder *cylinder, t_vec3 Phit, t_vec3 axis_direction)
{
	float height_at_intersection = dot_product(vec_substract(Phit, cylinder->position), axis_direction);
	if (height_at_intersection < -cylinder->height / 2.0f
		|| height_at_intersection > cylinder->height / 2.0f)
	{
		return (false);
	}
	return (true);
}

bool	intersectCylinder(const t_cylinder *cylinder, t_vec3 ray_origin,
		t_vec3 direction, float *refl, float *t_out)
{
	t_vec3	oc;
	t_vec3	axis_direction;
	float	cylinder_radius;
	float	half_b;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	t_vec3	Phit;
	bool	height_at_intersection;
	t_vec3	axis_projection;
	t_vec3	normal;

	oc = vec_substract(ray_origin, cylinder->position);
	half_b = dot_product(oc, direction);
	axis_direction = vec_normalize(cylinder->orientation);
	cylinder_radius = cylinder->diameter / 2.0f;
	a = dot_product(direction, direction) - powf(dot_product(direction,
				axis_direction), 2);
	b = 2 * (dot_product(direction, oc) - dot_product(direction, axis_direction)
			* dot_product(oc, axis_direction));
	c = dot_product(oc, oc) - powf(dot_product(oc, axis_direction), 2)
		- cylinder_radius * cylinder_radius;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
	{
		return (false);
	}
	t = -half_b - sqrtf(discriminant) / (2.0f * a);
	if (t < 0.0f)
	{
		t = -half_b + sqrtf(discriminant) / (2.0f * a);
	}
	Phit = vec_add(ray_origin, vec_scale(direction, t));
	height_at_intersection = checkHeightIntersection(cylinder, Phit, axis_direction);
	if (!height_at_intersection)
	{
		return (false);
	}
	axis_projection = vec_scale(axis_direction, dot_product(vec_substract(Phit,
					cylinder->position), axis_direction));
	normal = vec_normalize(vec_substract(vec_substract(Phit,
					cylinder->position), axis_projection));
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
