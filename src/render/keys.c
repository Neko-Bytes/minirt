/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:07:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/10 14:12:37 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/keys.h"

void	handle_camera_movement(int keycode, t_data *data, float move_speed)
{
	t_vec3	forward;
	t_vec3	right;

	forward = data->camera->orientation;
	right = (t_vec3){forward.z, 0, -forward.x};
	if (keycode == KEY_UP)
	{
		data->camera->position = vec_add(data->camera->position,
				vec_scale(forward, move_speed));
		printf("Camera position: (%f, %f, %f)\n", data->camera->position.x,
			data->camera->position.y, data->camera->position.z);
	}
	else if (keycode == KEY_DOWN)
	{
		data->camera->position = vec_substract(data->camera->position,
				vec_scale(forward, move_speed));
	}
	else if (keycode == KEY_LEFT)
	{
		data->camera->position = vec_substract(data->camera->position,
				vec_scale(right, move_speed));
	}
	else if (keycode == KEY_RIGHT)
	{
		data->camera->position = vec_add(data->camera->position,
				vec_scale(right, move_speed));
	}
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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	float	move_speed = 1.0f;
	static float angle = 0.2f; // Rotation angle in radians

	if (!param)
		return;
	data = (t_data *)param;

	if (keydata.key == KEY_ESC && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	else if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		handle_camera_movement(keydata.key, data, move_speed);
		handle_camera_rotation(keydata.key, data, angle);
		render(data);
	}
}
