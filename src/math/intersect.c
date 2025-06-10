/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:14 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/10 14:06:18 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/entries.h"
#include "../includes/intersect.h"
#include "../includes/object_array.h"
#include "../includes/vector_ops.h"
#include <math.h>
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
