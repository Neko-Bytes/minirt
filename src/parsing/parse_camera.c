/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:37:14 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 13:51:54 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	assign_params(t_scene **scene, char **tokens);
static void	assign_camera_position(t_scene *scene, char **xyz);
static void	assign_camera_orientation(t_scene *scene, char **vec_xyz);

bool	parse_camera(t_scene **scene, char **tokens)
{
	one_token_checker("Camera(FOV): ", &tokens[3], scene);
	if (tokens_counter(tokens) != 4)
		print_error("Invalid number of inputs for camera\n", (*scene)->data);
	if (!(*scene)->camera)
	{
		(*scene)->camera = gc_malloc(sizeof(t_camera));
		if (!(*scene)->camera)
			print_error("Malloc issue with camera\n", (*scene)->data);
	}
	else
		colorprint(MSG, "Camera struct already exists, replacing...\n");
	assign_params(scene, tokens);
	return (true);
}

static void	assign_params(t_scene **scene, char **tokens)
{
	char	**xyz;
	char	**vec_xyz;

	if (!(*scene)->camera)
	{
		(*scene)->camera = gc_malloc(sizeof(t_camera));
		if (!(*scene)->camera)
			print_error("Memory allocation failed for camera\n",
				(*scene)->data);
	}
	xyz = ft_split(tokens[1], ',');
	tokens_checker("Camera(xyz): ", xyz, scene);
	vec_xyz = ft_split(tokens[2], ',');
	tokens_checker("Camera(vector): ", vec_xyz, scene);
	assign_camera_position(*scene, xyz);
	assign_camera_orientation(*scene, vec_xyz);
	(*scene)->camera->fov = ft_atof(tokens[3]);
	check_params(*scene, (*scene)->camera);
	free_tokens(xyz);
	free_tokens(vec_xyz);
}

static void	assign_camera_position(t_scene *scene, char **xyz)
{
	if (!xyz || tokens_counter(xyz) != 3)
		print_error("Invalid input for camera position\n", scene->data);
	scene->camera->position.x = ft_atof(xyz[0]);
	scene->camera->position.y = ft_atof(xyz[1]);
	scene->camera->position.z = ft_atof(xyz[2]);
}

static void	assign_camera_orientation(t_scene *scene, char **vec_xyz)
{
	if (!vec_xyz || tokens_counter(vec_xyz) != 3)
		print_error("Invalid input for camera orientation\n", scene->data);
	scene->camera->orientation.x = ft_atof(vec_xyz[0]);
	scene->camera->orientation.y = ft_atof(vec_xyz[1]);
	scene->camera->orientation.z = ft_atof(vec_xyz[2]);
	scene->camera->direction.x = scene->camera->orientation.x;
	scene->camera->direction.y = scene->camera->orientation.y;
	scene->camera->direction.z = scene->camera->orientation.z;
}

void	validate_cylinder(t_scene *scene, t_cylinder *cy)
{
	float	orientation_length;

	orientation_length = sqrt(cy->orientation.x * cy->orientation.x
			+ cy->orientation.y * cy->orientation.y + cy->orientation.z
			* cy->orientation.z);
	if (orientation_length < 0.0001f)
		print_error("Cylinder: orientation vector cannot be zero\n",
			scene->data);
	cy->orientation.x /= orientation_length;
	cy->orientation.y /= orientation_length;
	cy->orientation.z /= orientation_length;
	if (cy->color.r < 0 || cy->color.r > 255)
		print_error("Cylinder: red component must be between 0 and 255\n",
			scene->data);
	if (cy->color.g < 0 || cy->color.g > 255)
		print_error("Cylinder: green component must be between 0 and 255\n",
			scene->data);
	if (cy->color.b < 0 || cy->color.b > 255)
		print_error("Cylinder: blue component must be between 0 and 255\n",
			scene->data);
}
