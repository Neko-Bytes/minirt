/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:08 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:35:50 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/gc.h"

// static void	ensure_space(t_scene *scene);
// static void	fill_light(t_light *L, char **xyz,
				// char **rgb, char **tokens);
static void	validate_light(t_scene *scene, t_light *L);
static void	free_tokens(char **tokens);

bool	parse_light(t_scene **scene, char **tokens)
{
	t_light		*light;
	char		**xyz;
	char		**rgb;

	if (!scene || !*scene || !tokens)
		print_error("Light: invalid scene or tokens\n", (*scene)->data);

	if (tokens_counter(tokens) != 4)
		print_error("Light: wrong number of parameters\n", (*scene)->data);
	
	xyz = ft_split(tokens[1], ',');
	if (!xyz || tokens_counter(xyz) != 3)
		print_error("Light: invalid position format\n", (*scene)->data);
	
	rgb = ft_split(tokens[3], ',');
	if (!rgb || tokens_counter(rgb) != 3)
		print_error("Light: invalid color format\n", (*scene)->data);

	// Allocate light using gc_malloc
	light = gc_malloc(sizeof(t_light));
	if (!light)
		print_error("Light: allocation failed\n", (*scene)->data);

	// Parse position
	light->position.x = ft_atof(xyz[0]);
	light->position.y = ft_atof(xyz[1]);
	light->position.z = ft_atof(xyz[2]);

	// Parse intensity
	light->intensity = ft_atof(tokens[2]);

	// Parse color
	light->color.r = ft_atoi(rgb[0]);
	light->color.g = ft_atoi(rgb[1]);
	light->color.b = ft_atoi(rgb[2]);

	validate_light(*scene, light);

	// Free temporary arrays
	free_tokens(xyz);
	free_tokens(rgb);

	// Add light to vector
	vector_push_back(&(*scene)->lights_vec, light);
	return (true);
}

// static void	ensure_space(t_scene *scene)
// {
// 	if (!scene->lights)
// 	{
// 		scene->lights = gc_malloc(sizeof(t_light));
// 		if (!scene->lights)
// 			print_error("Light: allocation failed\n", scene->data);
// 		scene->lights->count = 0;
// 	}
// 	else
// 	{
// 		if (scene->lights->count + 1 > MAX_LIGHTS)
// 			print_error("Light: maximum number of lights exceeded\n", scene->data);
// 		scene->lights = gc_realloc(scene->lights,
// 				sizeof(t_light) * scene->lights->count,
// 				sizeof(t_light) * (scene->lights->count + 1));
// 		if (!scene->lights)
// 			print_error("Light: reallocation failed\n", scene->data);
// 	}
// }

// static void	fill_light(t_light *L, char **xyz,
// 				char **rgb, char **tokens)
// {
// 	L->position.x = ft_atof(xyz[0]);
// 	L->position.y = ft_atof(xyz[1]);
// 	L->position.z = ft_atof(xyz[2]);
// 	L->color.r    = ft_atoi(rgb[0]);
// 	L->color.g    = ft_atoi(rgb[1]);
// 	L->color.b    = ft_atoi(rgb[2]);
// 	L->intensity  = ft_atof(tokens[2]);
// }

static void	validate_light(t_scene *scene, t_light *L)
{
	if (L->intensity < 0.0f || L->intensity > 1.0f)
		print_error("Light: intensity must be between 0 and 1\n", scene->data);
	if (L->color.r < 0 || L->color.r > 255)
		print_error("Light: red component must be between 0 and 255\n", scene->data);
	if (L->color.g < 0 || L->color.g > 255)
		print_error("Light: green component must be between 0 and 255\n", scene->data);
	if (L->color.b < 0 || L->color.b > 255)
		print_error("Light: blue component must be between 0 and 255\n", scene->data);
}

static void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
