/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:08 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 17:27:09 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gc.h"
#include "../../includes/minirt.h"

static void	validate_light(t_scene *scene, t_light *L);
static void	fill_light_position(t_light *light, char **xyz, t_scene *scene);
static void	fill_light_color(t_light *light, char **rgb, t_scene *scene);

bool	parse_light(t_scene **scene, char **tokens)
{
	t_light	*light;
	char	**xyz;
	char	**rgb;

	if (!scene || !*scene || !tokens)
		print_error("Light: invalid scene or tokens\n", (*scene)->data);
	if (tokens_counter(tokens) != 4)
		print_error("Light: wrong number of parameters\n", (*scene)->data);
	xyz = ft_split(tokens[1], ',');
	rgb = ft_split(tokens[3], ',');
	light = gc_malloc(sizeof(t_light));
	if (!light)
		print_error("Light: allocation failed\n", (*scene)->data);
	fill_light_position(light, xyz, *scene);
	light->intensity = ft_atof(tokens[2]);
	fill_light_color(light, rgb, *scene);
	validate_light(*scene, light);
	free_tokens(xyz);
	free_tokens(rgb);
	vector_push_back(&(*scene)->lights_vec, light);
	return (true);
}

static void	validate_light(t_scene *scene, t_light *L)
{
	if (L->intensity < 0.0f || L->intensity > 1.0f)
		print_error("Light: intensity must be between 0 and 1\n", scene->data);
	if (L->color.r < 0 || L->color.r > 255)
		print_error("Light: red component must be between 0 and 255\n",
			scene->data);
	if (L->color.g < 0 || L->color.g > 255)
		print_error("Light: green component must be between 0 and 255\n",
			scene->data);
	if (L->color.b < 0 || L->color.b > 255)
		print_error("Light: blue component must be between 0 and 255\n",
			scene->data);
}


static void	fill_light_position(t_light *light, char **xyz, t_scene *scene)
{
	if (!xyz || tokens_counter(xyz) != 3)
		print_error("Light: invalid position format\n", scene->data);
	light->position.x = ft_atof(xyz[0]);
	light->position.y = ft_atof(xyz[1]);
	light->position.z = ft_atof(xyz[2]);
}

static void	fill_light_color(t_light *light, char **rgb, t_scene *scene)
{
	if (!rgb || tokens_counter(rgb) != 3)
		print_error("Light: invalid color format\n", scene->data);
	light->color.r = ft_atoi(rgb[0]);
	light->color.g = ft_atoi(rgb[1]);
	light->color.b = ft_atoi(rgb[2]);
}
