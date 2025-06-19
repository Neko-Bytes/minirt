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

static bool find_cylinder_hit_t(const t_cylinder_ray *cray, t_abc *abc, t_cylinder_hit *hit)
{
	float discriminant = disc_cylinder(cray->ray_origin, cray->cylinder, cray->direction, abc);
	if (discriminant < 0.0f)
		return false;
	float sqrt_disc = sqrtf(discriminant);
	float t1 = (-abc->b - sqrt_disc) / (2.0f * abc->a);
	float t2 = (-abc->b + sqrt_disc) / (2.0f * abc->a);
	if (t1 > 0.0f)
	{
		hit->Phit = vec_add(cray->ray_origin, vec_scale(cray->direction, t1));
		if (checkHeightIntersection(cray->cylinder, hit->Phit, cray->axis_direction))
		{
			hit->t = t1;
			return true;
		}
	}
	if (t2 > 0.0f)
	{
		hit->Phit = vec_add(cray->ray_origin, vec_scale(cray->direction, t2));
		if (checkHeightIntersection(cray->cylinder, hit->Phit, cray->axis_direction))
		{
			hit->t = t2;
			return true;
		}
	}
	return false;
}

static void compute_cylinder_normal_and_refl(const t_cylinder_ray *cray, const t_cylinder_hit *hit, float *refl)
{
	t_vec3 cp = vec_substract(hit->Phit, cray->cylinder->position);
	t_vec3 axis_proj = vec_scale(cray->axis_direction, dot_product(cp, cray->axis_direction));
	t_vec3 normal = vec_normalize(vec_substract(cp, axis_proj));
	*refl = -dot_product(cray->direction, normal);
}

bool	intersectCylinder(const t_cylinder *cylinder, t_vec3 ray_origin,
		t_vec3 direction, float *refl, float *t_out)
{
	t_cylinder_ray cray;
	cray.cylinder = cylinder;
	cray.ray_origin = ray_origin;
	cray.direction = direction;
	cray.axis_direction = vec_normalize(cylinder->orientation);
	t_abc abc;
	t_cylinder_hit hit;
	if (!find_cylinder_hit_t(&cray, &abc, &hit))
		return false;
	compute_cylinder_normal_and_refl(&cray, &hit, refl);
	*t_out = hit.t;
	return true;
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
