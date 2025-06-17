/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:49 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:37:06 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	validate_cylinder(t_scene *scene, t_cylinder *cy);

bool	parse_cylinder(t_scene **scene, char **tokens)
{
	t_cylinder	cylinder;
	char		**coords;
	char		**orientation;
	char		**rgb;

	if (tokens_counter(tokens) != 6)
		print_error("Cylinder: wrong number of params\n", (*scene)->data);
	
	// Parse position
	coords = ft_split(tokens[1], ',');
	if (!coords || tokens_counter(coords) != 3)
		print_error("Cylinder: invalid position format\n", (*scene)->data);
	cylinder.position.x = ft_atof(coords[0]);
	cylinder.position.y = ft_atof(coords[1]);
	cylinder.position.z = ft_atof(coords[2]);

	// Parse orientation vector
	orientation = ft_split(tokens[2], ',');
	if (!orientation || tokens_counter(orientation) != 3)
		print_error("Cylinder: invalid orientation format\n", (*scene)->data);
	cylinder.orientation.x = ft_atof(orientation[0]);
	cylinder.orientation.y = ft_atof(orientation[1]);
	cylinder.orientation.z = ft_atof(orientation[2]);

	// Parse diameter
	cylinder.diameter = ft_atof(tokens[3]);
	if (cylinder.diameter <= 0.0f)
		print_error("Cylinder: invalid diameter\n", (*scene)->data);

	// Parse height
	cylinder.height = ft_atof(tokens[4]);
	if (cylinder.height <= 0.0f)
		print_error("Cylinder: invalid height\n", (*scene)->data);

	// Parse color
	rgb = ft_split(tokens[5], ',');
	if (!rgb || tokens_counter(rgb) != 3)
		print_error("Cylinder: invalid color format\n", (*scene)->data);
	cylinder.color.r = ft_atoi(rgb[0]);
	cylinder.color.g = ft_atoi(rgb[1]);
	cylinder.color.b = ft_atoi(rgb[2]);

	validate_cylinder(*scene, &cylinder);
	add_cylinder(&(*scene)->objects, cylinder);
	return (true);
}

static void	validate_cylinder(t_scene *scene, t_cylinder *cy)
{
	float	orientation_length;

	orientation_length = sqrt(cy->orientation.x * cy->orientation.x + 
							cy->orientation.y * cy->orientation.y + 
							cy->orientation.z * cy->orientation.z);
	if (orientation_length < 0.0001f)
		print_error("Cylinder: orientation vector cannot be zero\n", scene->data);
	
	// Normalize the orientation vector
	cy->orientation.x /= orientation_length;
	cy->orientation.y /= orientation_length;
	cy->orientation.z /= orientation_length;

	if (cy->color.r < 0 || cy->color.r > 255)
		print_error("Cylinder: red component must be between 0 and 255\n", scene->data);
	if (cy->color.g < 0 || cy->color.g > 255)
		print_error("Cylinder: green component must be between 0 and 255\n", scene->data);
	if (cy->color.b < 0 || cy->color.b > 255)
		print_error("Cylinder: blue component must be between 0 and 255\n", scene->data);
}
