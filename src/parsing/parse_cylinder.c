/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:19:41 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/12 09:00:28 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	assign_params(t_scene *scene, char **tokens, t_cylinder *cy);
static void	check_params(t_scene *scene, t_cylinder *cy);
static void	add_cylinder(t_scene *scene, t_cylinder *cy);
static void assign_rgb(t_scene *scene, t_cylinder *cy, char **tokens)

/*
** tokens:
** [0] "cy"
** [1] x,y,z           center coordinates
** [2] nx,ny,nz        axis vector
** [3] diameter        > 0
** [4] height          > 0
** [5] R,G,B           each in [0,255]
*/

bool	parse_cylinder(t_scene *scene, char **tokens)
{
	t_cylinder	*cy;

	if (tokens_counter(tokens) != 6)
		print_error("Invalid number of inputs for cylinder", scene->data);
	cy = gc_malloc(sizeof(t_cylinder));
	cy->next = NULL;
	assign_params(scene, tokens, cy);
	check_params(scene, cy);
	add_cylinder(scene, cy);
	return (true);
}

static void	assign_params(t_scene *scene, char **tokens, t_cylinder *cy)
{
	char	**xyzw;

	xyzw = ft_split(tokens[1], ',');
	if (tokens_counter(xyzw) != 3)
		print_error("Invalid cylinder center", scene->data);
	cy->position.x = ft_atof(xyzw[0]);
	cy->position.y = ft_atof(xyzw[1]);
	cy->position.z = ft_atof(xyzw[2]);
	xyzw = ft_split(tokens[2], ',');
	if (tokens_counter(xyzw) != 3)
		print_error("Invalid cylinder axis", scene->data);
	cy->orientation.x = ft_atof(xyzw[0]);
	cy->orientation.y = ft_atof(xyzw[1]);
	cy->orientation.z = ft_atof(xyzw[2]);
	cy->diameter = ft_atof(tokens[3]);
	cy->height   = ft_atof(tokens[4]);
	assign_rgb(scene, cy, tokens);
	gc_free(xyzw);
}

static void assign_rgb(t_scene *scene, t_cylinder *cy, char **tokens)
{
	char **rgb;

	rgb = ft_split(tokens[5], ',');
	if (tokens_counter(rgb) != 3)
		print_error("Invalid cylinder color", scene->data);
	cy->color.r = ft_atoi(rgb[0]);
	cy->color.g = ft_atoi(rgb[1]);
	cy->color.b = ft_atoi(rgb[2]);
	gc_free(rgb);
}

static void	check_params(t_scene *scene, t_cylinder *cy)
{
	if (cy->diameter <= 0)
		print_error("Cylinder diameter must be > 0", scene->data);
	if (cy->height <= 0)
		print_error("Cylinder height must be > 0", scene->data);
	if (cy->orientation.x == 0 && cy->orientation.y == 0 && cy->orientation.z == 0)
		print_error("Cylinder axis vector cannot be zero", scene->data);
	if (cy->color.r < 0 || cy->color.r > 255
	 || cy->color.g < 0 || cy->color.g > 255
	 || cy->color.b < 0 || cy->color.b > 255)
		print_error("Cylinder color values must be in [0,255]", scene->data);
}

static void	add_cylinder(t_scene *scene, t_cylinder *cy)
{
	t_cylinder	*last;

	if (!scene->objects.cylinders)
	{
		scene->objects.cylinders = cy;
		return ;
	}
	last = scene->objects.cylinders;
	while (last->next)
		last = last->next;
	last->next = cy;
}
