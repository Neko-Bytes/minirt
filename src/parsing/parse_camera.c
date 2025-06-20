/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:37:14 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 17:33:35 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	assign_params(t_scene **scene, char **tokens);
static void	assign_camera_position(t_scene *scene, char **xyz);
static void	assign_camera_orientation(t_scene *scene, char **vec_xyz);

bool	parse_camera(t_scene **scene, char **tokens)
{
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
	vec_xyz = ft_split(tokens[2], ',');
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