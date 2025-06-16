/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:37:14 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:40:08 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void assign_params(t_scene **scene, char **tokens);
static void check_params(t_scene *scene, t_camera *cam);

bool parse_camera(t_scene **scene, char **tokens)
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

static void assign_params(t_scene **scene, char **tokens)
{
    char **xyz;
    char **vec_xyz;

    if (!(*scene)->camera)
    {
        (*scene)->camera = malloc(sizeof(t_camera));
        if (!(*scene)->camera)
            print_error("Memory allocation failed for camera\n", (*scene)->data);
    }

    xyz = ft_split(tokens[1], ',');
    vec_xyz = ft_split(tokens[2], ',');

    if (tokens_counter(xyz) != 3 || tokens_counter(vec_xyz) != 3)
        print_error("Invalid input for camera coordinates\n", (*scene)->data);

    (*scene)->camera->position.x = ft_atof(xyz[0]);
    (*scene)->camera->position.y = ft_atof(xyz[1]);
    (*scene)->camera->position.z = ft_atof(xyz[2]);

    (*scene)->camera->orientation.x = ft_atof(vec_xyz[0]);
    (*scene)->camera->orientation.y = ft_atof(vec_xyz[1]);
    (*scene)->camera->orientation.z = ft_atof(vec_xyz[2]);

    (*scene)->camera->fov = ft_atof(tokens[3]);

    check_params(*scene, (*scene)->camera);
}


static void check_params(t_scene *scene, t_camera *cam)
{
	if (cam->fov < 0 || cam->fov > 100)
		print_error("Invalid input for fov.", scene->data);
	// if(!cam->orientation.x || !cam->orientation.y || !cam->orientation.z)
	// 	print_error("Invalid input for orientation vector", scene->data);
}
