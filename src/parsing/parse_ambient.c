/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:12:08 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/10 20:03:56 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void ambience_checker(t_scene *scene);

bool parse_ambience(t_scene *scene, char **tokens)
{
	char **rgb;

	if(tokens_couter(tokens) != 3)
		print_error("Invalid number of arguments for ambience.", scene->data);
	if(!scene->ambient)
		scene->ambient = gc_malloc(sizeof(t_ambient));
	else
		colorprint(MSG, "Ambient struct already exists, replacing ...\n");
	scene->ambient->intensity = ft_atof(tokens[1]);
	rgb = ft_split(tokens[2], ',');
	if(!rgb || !*rgb || tokens_couter(rgb) != 3)
		print_error("Invalid arguments fo RGB.", scene->data);
	scene->ambient->color.r = ft_atoi(rgb[0]);
	scene->ambient->color.g = ft_atoi(rgb[1]);
	scene->ambient->color.b = ft_atoi(rgb[2]);
	ambience_checker(scene);
	return (true);
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
