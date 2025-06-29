/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:49 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 13:29:02 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	fill_cylinder_position(t_cylinder *cylinder, char **coords,
				t_scene *scene);
static void	fill_cylinder_orientation(t_cylinder *cylinder, char **orientation,
				t_scene *scene);
static void	fill_cylinder_color(t_cylinder *cylinder, char **rgb,
				t_scene *scene);

static void	parse_cylinder_tokens(t_cylinder *cylinder, t_scene *scene,
		char **tokens)
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
	tokens_checker("Cylinder(diameter): ", ft_split(tokens[3], ' '), &scene);
	cylinder->diameter = ft_atof(tokens[3]);
	if (cylinder->diameter <= 0.0f)
		print_error("Cylinder: invalid diameter\n", scene->data);
	tokens_checker("Cylinder(height): ", ft_split(tokens[4], ' '), &scene);
	cylinder->height = ft_atof(tokens[4]);
	if (cylinder->height <= 0.0f)
		print_error("Cylinder(height): invalid height\n", scene->data);
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
	tokens_checker("Cylinder(coords): ", coords, &scene);
	cylinder->position.x = ft_atof(coords[0]);
	cylinder->position.y = ft_atof(coords[1]);
	cylinder->position.z = ft_atof(coords[2]);
}

static void	fill_cylinder_orientation(t_cylinder *cylinder, char **orientation,
		t_scene *scene)
{
	if (!orientation || tokens_counter(orientation) != 3)
		print_error("Cylinder: invalid orientation format\n", scene->data);
	tokens_checker("Cylinder(orientation): ", orientation, &scene);
	cylinder->orientation.x = ft_atof(orientation[0]);
	cylinder->orientation.y = ft_atof(orientation[1]);
	cylinder->orientation.z = ft_atof(orientation[2]);
}

static void	fill_cylinder_color(t_cylinder *cylinder, char **rgb,
		t_scene *scene)
{
	if (!rgb || tokens_counter(rgb) != 3)
		print_error("Cylinder: invalid color format\n", scene->data);
	tokens_checker("Cylinder(rgb): ", rgb, &scene);
	cylinder->color.r = ft_atoi(rgb[0]);
	cylinder->color.g = ft_atoi(rgb[1]);
	cylinder->color.b = ft_atoi(rgb[2]);
}
