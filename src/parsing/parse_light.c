/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 08:56:08 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/11 08:56:25 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ensure_space(t_scene *scene);
static void	fill_light(t_light *L, char **xyz,
				char **rgb, char **tokens);
static void	validate_light(t_scene *scene, t_light *L);

bool	parse_light(t_scene *scene, char **tokens)
{
	char	**xyz;
	char	**rgb;
	t_light	*L;

	if (tokens_counter(tokens) != 4)
		print_error("Light: wrong number of parameters\n", scene->data);
	xyz = ft_split(tokens[1], ',');
	rgb = ft_split(tokens[3], ',');
	if (tokens_counter(xyz) != 3 || tokens_counter(rgb) != 3)
		print_error("Light: bad vector or color format\n", scene->data);
	ensure_space(scene);
	L = &scene->lights[scene->lights->count];
	fill_light(L, xyz, rgb, tokens);
	validate_light(scene, L);
	scene->lights->count++;
	return (true);
}

static void	ensure_space(t_scene *scene)
{
	if (!scene->lights)
	{
		scene->lights->count = 0;
		scene->lights = gc_malloc(sizeof(t_light));
		if (!scene->lights)
			print_error("Light: alloc failed\n", scene->data);
	}
	else
	{
		if (scene->lights->count + 1 > MAX_LIGHTS)
			print_error("Light: max lights exceeded\n", scene->data);
		scene->lights = gc_realloc(scene->lights,
				sizeof(t_light) * scene->lights->count,
				sizeof(t_light) * (scene->lights->count + 1));
		if (!scene->lights)
			print_error("Light: realloc failed\n", scene->data);
	}
}

static void	fill_light(t_light *L, char **xyz,
				char **rgb, char **tokens)
{
	L->position.x = ft_atof(xyz[0]);
	L->position.y = ft_atof(xyz[1]);
	L->position.z = ft_atof(xyz[2]);
	L->color.r    = ft_atoi(rgb[0]);
	L->color.g    = ft_atoi(rgb[1]);
	L->color.b    = ft_atoi(rgb[2]);
	L->intensity  = ft_atof(tokens[2]);
}

static void	validate_light(t_scene *scene, t_light *L)
{
	if (L->intensity < 0.0f || L->intensity > 1.0f)
		print_error("Light: intensity out of range\n", scene->data);
	if (L->color.r < 0 || L->color.r > 255)
		print_error("Light: red out of range\n", scene->data);
	if (L->color.g < 0 || L->color.g > 255)
		print_error("Light: green out of range\n", scene->data);
	if (L->color.b < 0 || L->color.b > 255)
		print_error("Light: blue out of range\n", scene->data);
}
