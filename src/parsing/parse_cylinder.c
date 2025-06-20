/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:49 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 17:27:02 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	validate_cylinder(t_scene *scene, t_cylinder *cy);
static void	fill_cylinder_position(t_cylinder *cylinder, char **coords,
				t_scene *scene);
static void	fill_cylinder_orientation(t_cylinder *cylinder, char **orientation,
				t_scene *scene);
static void	fill_cylinder_color(t_cylinder *cylinder, char **rgb,
				t_scene *scene);

static void	parse_cylinder_tokens(t_cylinder *cylinder, t_scene *scene, char **tokens)
{
	char	**coords;
	char	**orientation;
	char	**rgb;

	if (tokens_counter(tokens) != 6)
		print_error("Cylinder: wrong number of params\n", scene->data);

	coords = ft_split(tokens[1], ',');
	fill_cylinder_position(cylinder, coords, scene);
	free_tokens(coords);

	orientation = ft_split(tokens[2], ',');
	fill_cylinder_orientation(cylinder, orientation, scene);
	free_tokens(orientation);

	cylinder->diameter = ft_atof(tokens[3]);
	if (cylinder->diameter <= 0.0f)
		print_error("Cylinder: invalid diameter\n", scene->data);

	cylinder->height = ft_atof(tokens[4]);
	if (cylinder->height <= 0.0f)
		print_error("Cylinder: invalid height\n", scene->data);

	rgb = ft_split(tokens[5], ',');
	fill_cylinder_color(cylinder, rgb, scene);
	free_tokens(rgb);

	validate_cylinder(scene, cylinder);
}

bool	parse_cylinder(t_scene **scene, char **tokens)
{
	t_cylinder	cylinder;

	parse_cylinder_tokens(&cylinder, *scene, tokens);
	add_cylinder(&(*scene)->objects, cylinder);
	return (true);
}

static void	fill_cylinder_position(t_cylinder *cylinder, char **coords,
		t_scene *scene)
{
	if (!coords || tokens_counter(coords) != 3)
		print_error("Cylinder: invalid position format\n", scene->data);
	cylinder->position.x = ft_atof(coords[0]);
	cylinder->position.y = ft_atof(coords[1]);
	cylinder->position.z = ft_atof(coords[2]);
}

static void	fill_cylinder_orientation(t_cylinder *cylinder, char **orientation,
		t_scene *scene)
{
	if (!orientation || tokens_counter(orientation) != 3)
		print_error("Cylinder: invalid orientation format\n", scene->data);
	cylinder->orientation.x = ft_atof(orientation[0]);
	cylinder->orientation.y = ft_atof(orientation[1]);
	cylinder->orientation.z = ft_atof(orientation[2]);
}

static void	fill_cylinder_color(t_cylinder *cylinder, char **rgb,
		t_scene *scene)
{
	if (!rgb || tokens_counter(rgb) != 3)
		print_error("Cylinder: invalid color format\n", scene->data);
	cylinder->color.r = ft_atoi(rgb[0]);
	cylinder->color.g = ft_atoi(rgb[1]);
	cylinder->color.b = ft_atoi(rgb[2]);
}

static void	validate_cylinder(t_scene *scene, t_cylinder *cy)
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
