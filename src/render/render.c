/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:00:59 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 17:25:59 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"

void	init_window_and_image(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "miniRT", true);
	if (!data->mlx)
		exit(1);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
	{
		mlx_terminate(data->mlx);
		exit(1);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
	{
		mlx_delete_image(data->mlx, data->img);
		mlx_terminate(data->mlx);
		exit(1);
	}
}

void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	vector_init(&scene->lights_vec, sizeof(t_light), 10);
	init_object_vector(&scene->objects, 10);
	scene->data = NULL;
	if (scene->camera)
	{
		scene->camera->direction = vec_normalize(scene->camera->direction);
	}
}

t_vec3	rotate_y(t_vec3 v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	return ((t_vec3){v.x * cos_a + v.z * sin_a, v.y, -v.x * sin_a + v.z
		* cos_a});
}

t_vec3	rotate_x(t_vec3 v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	return ((t_vec3){v.x, v.y * cos_a - v.z * sin_a, v.y * sin_a + v.z
		* cos_a});
}

void	handle_camera_rotation(int keycode, t_data *data, float angle)
{
	t_vec3	center;
	t_vec3	dir;

	if (keycode == KEY_A || keycode == KEY_D)
	{
		center = vec_add(data->camera->position,
				vec_scale(data->camera->orientation, 0.2f));
		dir = vec_substract(data->camera->position, center);
		if (keycode == KEY_A)
			dir = rotate_y(dir, -angle);
		else if (keycode == KEY_D)
			dir = rotate_y(dir, angle);
		data->camera->position = vec_add(center, dir);
		data->camera->orientation = vec_normalize(vec_substract(center,
					data->camera->position));
	}
}
