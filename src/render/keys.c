/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:07:45 by kruseva           #+#                #+#             */
/*   Updated: 2025/06/16 15:35:50 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/keys.h"

void	handle_camera_movement(int keycode, t_data *data, float move_speed)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	old_pos;

	forward = data->camera->orientation;
	right = (t_vec3){forward.z, 0, -forward.x};
	old_pos = data->camera->position;
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

void	game_loop(void *param)
{
	t_data	*data;
	float	move_speed;
	float	angle;
	bool	camera_moved;

	data = (t_data *)param;
	move_speed = 5.0f;
	angle = 0.2f;
	if (!data || !data->scene || !data->camera)
		return ;
	camera_moved = false;
	if (data->input->key_up)
	{
		handle_camera_movement(KEY_UP, data, move_speed);
		camera_moved = true;
	}
	if (data->input->key_down)
	{
		handle_camera_movement(KEY_DOWN, data, move_speed);
		camera_moved = true;
	}
	if (data->input->key_left)
	{
		handle_camera_movement(KEY_LEFT, data, move_speed);
		camera_moved = true;
	}
	if (data->input->key_right)
	{
		handle_camera_movement(KEY_RIGHT, data, move_speed);
		camera_moved = true;
	}
	if (data->input->key_a || data->input->key_d)
	{
		if (data->input->key_a)
			handle_camera_rotation(KEY_A, data, angle);
		if (data->input->key_d)
			handle_camera_rotation(KEY_D, data, angle);
		camera_moved = true;
	}
	if (camera_moved)
		render(data);
}
