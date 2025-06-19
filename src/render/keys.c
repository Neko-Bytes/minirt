/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:25:18 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 17:25:25 by kruseva          ###   ########.fr       */
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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;
	t_input	*input;
	bool	pressed;

	scene = (t_scene *)param;
	if (!scene || !scene->data || !scene->data->input)
		return ;
	input = scene->data->input;
	if (!scene || !scene->data)
		return ;
	pressed = keydata.action == MLX_PRESS;
	if (keydata.key == KEY_ESC && keydata.action == MLX_PRESS)
		mlx_close_window(scene->data->mlx);
	else if (keydata.key == KEY_UP)
		input->key_up = pressed;
	else if (keydata.key == KEY_DOWN)
		input->key_down = pressed;
	else if (keydata.key == KEY_LEFT)
		input->key_left = pressed;
	else if (keydata.key == KEY_RIGHT)
		input->key_right = pressed;
	else if (keydata.key == KEY_A)
		input->key_a = pressed;
	else if (keydata.key == KEY_D)
		input->key_d = pressed;
}

static bool	handle_camera_movement_keys(t_data *data, float move_speed)
{
	bool	moved;

	moved = false;
	if (data->input->key_up)
	{
		handle_camera_movement(KEY_UP, data, move_speed);
		moved = true;
	}
	if (data->input->key_down)
	{
		handle_camera_movement(KEY_DOWN, data, move_speed);
		moved = true;
	}
	if (data->input->key_left)
	{
		handle_camera_movement(KEY_LEFT, data, move_speed);
		moved = true;
	}
	if (data->input->key_right)
	{
		handle_camera_movement(KEY_RIGHT, data, move_speed);
		moved = true;
	}
	return (moved);
}

static bool	handle_camera_rotation_keys(t_data *data, float angle)
{
	bool	rotated;

	rotated = false;
	if (data->input->key_a)
	{
		handle_camera_rotation(KEY_A, data, angle);
		rotated = true;
	}
	if (data->input->key_d)
	{
		handle_camera_rotation(KEY_D, data, angle);
		rotated = true;
	}
	return (rotated);
}

void	game_loop(void *param)
{
	t_data	*data;
	float	move_speed;
	float	angle;
	bool	camera_moved;

	data = (t_data *)param;
	move_speed = 5.0f;
	angle = 1.0f;
	if (!data || !data->scene || !data->camera)
		return ;
	camera_moved = false;
	camera_moved |= handle_camera_movement_keys(data, move_speed);
	camera_moved |= handle_camera_rotation_keys(data, angle);
	if (camera_moved)
		render(data);
}
