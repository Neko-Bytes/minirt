/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:49 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 17:27:19 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	validate_sphere(t_scene *scene, t_sphere *sp);
static void	fill_sphere_position(t_sphere *sphere, char **coords,
				t_scene *scene);
static void	fill_sphere_color(t_sphere *sphere, char **rgb, t_scene *scene);

bool	parse_sphere(t_scene **scene, char **tokens)
{
	t_sphere	sphere;
	char		**coords;
	char		**rgb;

	if (tokens_counter(tokens) != 4)
		print_error("Sphere: wrong number of params\n", (*scene)->data);
	coords = ft_split(tokens[1], ',');
	fill_sphere_position(&sphere, coords, *scene);
	sphere.radius = ft_atof(tokens[2]);
	if (sphere.radius <= 0.0f)
		print_error("Sphere: invalid radius\n", (*scene)->data);
	rgb = ft_split(tokens[3], ',');
	fill_sphere_color(&sphere, rgb, *scene);
	validate_sphere(*scene, &sphere);
	add_sphere(&(*scene)->objects, sphere);
	return (true);
}

static void	fill_sphere_position(t_sphere *sphere, char **coords,
		t_scene *scene)
{
	if (!coords || tokens_counter(coords) != 3)
		print_error("Sphere: invalid position format\n", scene->data);
	sphere->position.x = ft_atof(coords[0]);
	sphere->position.y = ft_atof(coords[1]);
	sphere->position.z = ft_atof(coords[2]);
}

static void	fill_sphere_color(t_sphere *sphere, char **rgb, t_scene *scene)
{
	if (!rgb || tokens_counter(rgb) != 3)
		print_error("Sphere: invalid color format\n", scene->data);
	sphere->color.r = ft_atoi(rgb[0]);
	sphere->color.g = ft_atoi(rgb[1]);
	sphere->color.b = ft_atoi(rgb[2]);
}

static void	validate_sphere(t_scene *scene, t_sphere *sp)
{
	if (sp->radius <= 0.0f)
		print_error("Sphere: invalid radius\n", scene->data);
	if (sp->color.r < 0 || sp->color.r > 255)
		print_error("Sphere: red component must be between 0 and 255\n",
			scene->data);
	if (sp->color.g < 0 || sp->color.g > 255)
		print_error("Sphere: green component must be between 0 and 255\n",
			scene->data);
	if (sp->color.b < 0 || sp->color.b > 255)
		print_error("Sphere: blue component must be between 0 and 255\n",
			scene->data);
}
