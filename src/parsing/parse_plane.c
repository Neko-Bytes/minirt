/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:49 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:37:06 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	validate_plane(t_scene *scene, t_plane *pl);

bool	parse_plane(t_scene **scene, char **tokens)
{
	t_plane		plane;
	char		**coords;
	char		**normal;
	char		**rgb;

	if (tokens_counter(tokens) != 4)
		print_error("Plane: wrong number of params\n", (*scene)->data);
	
	// Parse position
	coords = ft_split(tokens[1], ',');
	if (!coords || tokens_counter(coords) != 3)
		print_error("Plane: invalid position format\n", (*scene)->data);
	plane.position.x = ft_atof(coords[0]);
	plane.position.y = ft_atof(coords[1]);
	plane.position.z = ft_atof(coords[2]);
	
	// Parse normal vector
	normal = ft_split(tokens[2], ',');
	if (!normal || tokens_counter(normal) != 3)
		print_error("Plane: invalid normal vector format\n", (*scene)->data);
	plane.normal.x = ft_atof(normal[0]);
	plane.normal.y = ft_atof(normal[1]);
	plane.normal.z = ft_atof(normal[2]);

	// Parse color
	rgb = ft_split(tokens[3], ',');
	if (!rgb || tokens_counter(rgb) != 3)
		print_error("Plane: invalid color format\n", (*scene)->data);
	plane.color.r = ft_atoi(rgb[0]);
	plane.color.g = ft_atoi(rgb[1]);
	plane.color.b = ft_atoi(rgb[2]);

	validate_plane(*scene, &plane);
	add_plane(&(*scene)->objects, plane);
	return (true);
}

static void	validate_plane(t_scene *scene, t_plane *pl)
{
	float	normal_length;

	normal_length = sqrt(pl->normal.x * pl->normal.x + 
						pl->normal.y * pl->normal.y + 
						pl->normal.z * pl->normal.z);
	if (normal_length < 0.0001f)
		print_error("Plane: normal vector cannot be zero\n", scene->data);
	
	// Normalize the normal vector
	pl->normal.x /= normal_length;
	pl->normal.y /= normal_length;
	pl->normal.z /= normal_length;

	if (pl->color.r < 0 || pl->color.r > 255)
		print_error("Plane: red component must be between 0 and 255\n", scene->data);
	if (pl->color.g < 0 || pl->color.g > 255)
		print_error("Plane: green component must be between 0 and 255\n", scene->data);
	if (pl->color.b < 0 || pl->color.b > 255)
		print_error("Plane: blue component must be between 0 and 255\n", scene->data);
}
