/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:12:08 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:31:20 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void ambience_checker(t_scene *scene);
static void fill_ambient_color(t_ambient *ambient, char **rgb, t_scene *scene);

bool parse_ambience(t_scene **scene, char **tokens)
{
	char **rgb;

	if(tokens_counter(tokens) != 3)
		print_error("Ambience: Invalid number of arguments.", (*scene)->data);
	if(!(*scene)->ambient)
	{
		(*scene)->ambient = gc_malloc(sizeof(t_ambient));
		if(!(*scene)->ambient)
			print_error("Ambience: Malloc issues\n", (*scene)->data);
	}
	else
		colorprint(MSG, "Ambient struct already exists, replacing ...\n");
	(*scene)->ambient->intensity = ft_atof(tokens[1]);
	rgb = ft_split(tokens[2], ',');
	fill_ambient_color((*scene)->ambient, rgb, *scene);
	ambience_checker((*scene));
	return (true);
}

static void fill_ambient_color(t_ambient *ambient, char **rgb, t_scene *scene)
{
	if(!rgb || !*rgb || tokens_counter(rgb) != 3)
		print_error("Ambience: Invalid arguments fo RGB.", scene->data);
	ambient->color.r = ft_atoi(rgb[0]);
	ambient->color.g = ft_atoi(rgb[1]);
	ambient->color.b = ft_atoi(rgb[2]);
}

void ambience_checker(t_scene *scene)
{
	t_ambient *copy = scene->ambient;
	if(copy->intensity < 0 || copy->intensity > 1)
		print_error("Invalid input for ambience intensity", scene->data);
	if(copy->color.r < 0 || copy->color.r > 255)
		print_error("Invalid input for color red", scene->data);
	if(copy->color.g < 0 || copy->color.g > 255)
		print_error("Invalid input for color green", scene->data);
	if(copy->color.b < 0 || copy->color.b > 255)
		print_error("Invalid input for color blue", scene->data);
	return;
}
