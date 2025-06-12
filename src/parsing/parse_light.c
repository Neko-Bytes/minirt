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

static void assign_params(t_scene *scene, char **xyz, char **rgb, char **tokens);
static void check_params(t_scene *scene);
static void add_light(t_light **lights);

bool parse_light(t_scene *scene, char **tokens)
{
	char *xyz;
	char *rgb;

	if(tokens_counter(tokens) != 4)
		print_error("Invalid number of parameters for light\n", scene->data);
	xyz = ft_split(tokens[1], ',');
	rgb = ft_split(tokens[3], ',');
	if(tokens_counter(xyz) != 3 || tokens_counter(rgb) != 3)
		print_error("Invalid input for light\n", scene->data);
	if(!scene->lights)
	{
		scene->lights = gc_malloc(sizeof(t_light));
		scene->lights->next = NULL;
	}
	else
	{
		colorprint(MSG, "Appending extra light...\n");
		add_light(&scene->lights);
	}
	assign_params(scene, xyz, rgb, tokens);
	return(true);
}

static void add_light(t_light **lights)
{
	t_light *curr;
	t_light *next;
	t_light *new;

	curr = *lights;
	next = curr->next;
	while(curr->next)
		curr = curr->next;
	new = gc_malloc(sizeof(t_light));
	new->next = NULL;
	curr->next = new;
}

static void assign_params(t_scene *scene, char **xyz, char **rgb, char **tokens)
{
	t_light *light;

	light = scene->lights;
	while(light->next)
		light = light->next;
	light->position.x = ft_atof(xyz[0]);
	light->position.y = ft_atof(xyz[1]);
	light->position.z = ft_atof(xyz[2]);
	light->color.r = ft_atoi(rgb[0]);
	light->color.g = ft_atoi(rgb[1]);
	light->color.b = ft_atoi(rgb[2]);
	light->intensity = ft_atof(tokens[2]);
	check_params(scene);
}

static void check_params(t_scene *scene)
{
	t_light *light;
	
	light = scene->lights;
	while(light->next)
		light = light->next;
	if(light->intensity < 0 || light->intensity > 1)
		print_error("Wrong input for light intensity\n", scene->data);
	if(light->color.r < 0 || light->color.r > 255)
		print_error("Invalid input for light->color->red.\n", scene->data);
	if(light->color.g < 0 || light->color.g > 255)
		print_error("Invalid input for light->color->green.\n", scene->data);
	if(light->color.b < 0 || light->color.b > 255)
		print_error("Invalid input for light->color->blue.\n", scene->data);
}
