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
static void free_tokens(char **tokens);

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
        (*scene)->camera = gc_malloc(sizeof(t_camera));
        if (!(*scene)->camera)
            print_error("Memory allocation failed for camera\n", (*scene)->data);
    }

    xyz = ft_split(tokens[1], ',');
    vec_xyz = ft_split(tokens[2], ',');

    if (!xyz || tokens_counter(xyz) != 3)
        print_error("Invalid input for camera position\n", (*scene)->data);
    if (!vec_xyz || tokens_counter(vec_xyz) != 3)
        print_error("Invalid input for camera orientation\n", (*scene)->data);

    (*scene)->camera->position.x = ft_atof(xyz[0]);
    (*scene)->camera->position.y = ft_atof(xyz[1]);
    (*scene)->camera->position.z = ft_atof(xyz[2]);

    (*scene)->camera->orientation.x = ft_atof(vec_xyz[0]);
    (*scene)->camera->orientation.y = ft_atof(vec_xyz[1]);
    (*scene)->camera->orientation.z = ft_atof(vec_xyz[2]);

    // Set direction to be the same as orientation initially
    (*scene)->camera->direction.x = (*scene)->camera->orientation.x;
    (*scene)->camera->direction.y = (*scene)->camera->orientation.y;
    (*scene)->camera->direction.z = (*scene)->camera->orientation.z;

    (*scene)->camera->fov = ft_atof(tokens[3]);

    check_params(*scene, (*scene)->camera);

    // Free temporary arrays
    free_tokens(xyz);
    free_tokens(vec_xyz);
}

static void check_params(t_scene *scene, t_camera *cam)
{
    float orientation_length;

    if (cam->fov < 0 || cam->fov > 180)
        print_error("Invalid input for FOV (must be between 0 and 180)\n", scene->data);

    orientation_length = sqrt(cam->orientation.x * cam->orientation.x + 
                            cam->orientation.y * cam->orientation.y + 
                            cam->orientation.z * cam->orientation.z);
    if (orientation_length < 0.0001f)
        print_error("Camera orientation vector cannot be zero\n", scene->data);

    // Normalize both orientation and direction vectors
    cam->orientation.x /= orientation_length;
    cam->orientation.y /= orientation_length;
    cam->orientation.z /= orientation_length;

    cam->direction.x = cam->orientation.x;
    cam->direction.y = cam->orientation.y;
    cam->direction.z = cam->orientation.z;
}

static void free_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}
