/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:12:08 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 17:33:39 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void		ambience_checker(t_scene *scene);
static void	fill_ambient_color(t_ambient *ambient, char **rgb, t_scene *scene);

bool	parse_ambience(t_scene **scene, char **tokens)
{
	char	**rgb;

	if (tokens_counter(tokens) != 3)
		print_error("Ambience: Invalid number of arguments.", (*scene)->data);
	if (!(*scene)->ambient)
	{
		(*scene)->ambient = gc_malloc(sizeof(t_ambient));
		if (!(*scene)->ambient)
			print_error("Ambience: Malloc issues\n", (*scene)->data);
	}
	else
		colorprint(MSG, "Ambient struct already exists, replacing ...\n");
	(*scene)->ambient->intensity = ft_atof(tokens[1]);
	rgb = ft_split(tokens[2], ',');
	fill_ambient_color((*scene)->ambient, rgb, *scene);
	ambience_checker((*scene));
	free_tokens(rgb);
	return (true);
}

static void	fill_ambient_color(t_ambient *ambient, char **rgb, t_scene *scene)
{
	if (!rgb || !*rgb || tokens_counter(rgb) != 3)
		print_error("Ambience: Invalid arguments fo RGB.", scene->data);
	ambient->color.r = ft_atoi(rgb[0]);
	ambient->color.g = ft_atoi(rgb[1]);
	ambient->color.b = ft_atoi(rgb[2]);
}

void	ambience_checker(t_scene *scene)
{
	t_ambient	*copy;

	copy = scene->ambient;
	if (copy->intensity < 0 || copy->intensity > 1)
		print_error("Invalid input for ambience intensity", scene->data);
	if (copy->color.r < 0 || copy->color.r > 255)
		print_error("Invalid input for color red", scene->data);
	if (copy->color.g < 0 || copy->color.g > 255)
		print_error("Invalid input for color green", scene->data);
	if (copy->color.b < 0 || copy->color.b > 255)
		print_error("Invalid input for color blue", scene->data);
	return ;
}

bool	validate_element_counts(char **tokens, t_scene **scene, int *a_count,
		int *c_count)
{
	if (!ft_strncmp(tokens[0], "A", 1))
	{
		(*a_count)++;
		if (*a_count > 1)
			print_error("Double occurrence of 'A' found in .rt file\n",
				(*scene)->data);
	}
	if (!ft_strncmp(tokens[0], "C", 1))
	{
		(*c_count)++;
		if (*c_count > 1)
			print_error("Double occurrence of 'C' found in .rt file\n",
				(*scene)->data);
	}
	return (true);
}

void	check_params(t_scene *scene, t_camera *cam)
{
	float	orientation_length;

	if (cam->fov < 0 || cam->fov > 180)
		print_error("Invalid input for FOV (must be between 0 and 180)\n",
			scene->data);
	orientation_length = sqrt(cam->orientation.x * cam->orientation.x
			+ cam->orientation.y * cam->orientation.y + cam->orientation.z
			* cam->orientation.z);
	if (orientation_length < 0.0001f)
		print_error("Camera orientation vector cannot be zero\n", scene->data);
	cam->orientation.x /= orientation_length;
	cam->orientation.y /= orientation_length;
	cam->orientation.z /= orientation_length;
	cam->direction.x = cam->orientation.x;
	cam->direction.y = cam->orientation.y;
	cam->direction.z = cam->orientation.z;
}
