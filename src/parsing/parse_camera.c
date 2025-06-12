/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:37:14 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/10 22:46:16 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void assign_params(t_scene *scene, char **tokens);
static void check_params(t_scene *scene, t_camera *cam);

bool parse_camera(t_scene *scene, char **tokens)
{
	if(tokens_counter(tokens) != 4)
		print_error("Invalid number of inputs for camera\n", scene->data);
	if(!scene->camera)
		scene->camera = gc_malloc(sizeof(t_camera));
	else
		colorprint(MSG, "Camera struct already exists, replacing...\n");
}

static void assign_params(t_scene *scene, char **tokens)
{
	char **xyz;
	char **vec_xyz;
	t_camera *cam;

	cam = scene->camera;
	xyz = ft_split(tokens[1], ',');
	vec_xyz = ft_split(tokens[2], ',');
	if(tokens_counter(xyz) != 3 || tokens_counter(vec_xyz) != 3)
		print_error("Invalid input for camera coordinates\n", scene->data);
	cam->position.x = ft_atof(xyz[0]);
	cam->position.y = ft_atof(xyz[1]);
	cam->position.z = ft_atof(xyz[2]);
	cam->orientation.x = ft_atof(vec_xyz[0]);
	cam->orientation.y = ft_atof(vec_xyz[1]);
	cam->orientation.z = ft_atof(vec_xyz[2]);
	cam->fov = ft_atof(tokens[3]);
	check_params(scene, cam);
}

static void check_params(t_scene *scene, t_camera *cam)
{
	if(cam->fov < 0 || cam->fov > 100)
		print_error("Invalid input for fov.", scene->data);
	if(!cam->orientation.x || !cam->orientation.y || !cam->orientation.z)
		print_error("Invalid input for orientation vector", scene->data);
}
