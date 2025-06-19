/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:09:27 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 16:50:33 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/entries.h" // Ensure this is included for t_params
#include "../../includes/intersect.h"
#include "../../includes/light.h"
#include "../../includes/minirt.h"
#include "../../includes/object_array.h" // Ensure this is included for t_way
#include "../../includes/vector_ops.h"
#include <math.h>

void	validate_camera_and_scene(t_scene *scene)
{
	if (!scene->camera || !scene)
	{
		fprintf(stderr, "Error: Invalid input to main_image.\n");
		exit(1);
	}
}

void	compute_camera_basis(t_vec3 camera_dir, t_way *way)
{
	way->forward = vec_normalize(camera_dir);
	way->right = vec_normalize(vec_cross((t_vec3){0.0f, 1.0f, 0.0f},
				way->forward));
	way->up = vec_cross(way->right, way->forward);
}

t_vec3	compute_ray_direction(t_params *params, float aspect_ratio, float scale,
		t_way *way)
{
	float	x;
	float	y;
	t_vec3	ray_dir;

	x = (2.0f * ((params->coord.x + 0.5f) / params->width) - 1.0f)
		* aspect_ratio * scale;
	y = (2.0f * ((params->coord.y + 0.5f) / params->height) - 1.0f) * scale;
	ray_dir = vec_normalize(vec_add(vec_add(vec_scale(way->right, x),
					vec_scale(way->up, y)), vec_scale(way->forward, 1.0f)));
	return (ray_dir);
}

t_vec3	sphere_normal(t_sphere s, t_vec3 p)
{
	return (vec_normalize(vec_substract(p, s.position)));
}

void	main_image(t_params *params, t_color *output, t_scene *scene)
{
	float	aspect_ratio;
	float	fov;
	float	scale;
	t_vec3	direction;
	t_way	way;

	if (!params || !scene || !scene->camera)
	{
		fprintf(stderr, "Error: Invalid input to main_image.\n");
		exit(1);
	}
	aspect_ratio = (float)params->width / (float)params->height;
	fov = scene->camera->fov * (M_PI / 180.0f);
	scale = tanf(fov / 2.0f);
	compute_camera_basis(scene->camera->direction, &way);
	direction = compute_ray_direction(params, aspect_ratio, scale, &way);
	*output = ray_tracing(direction, scene);
}
