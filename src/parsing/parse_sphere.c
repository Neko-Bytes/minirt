/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:49 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/12 08:38:24 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	assign_params(t_scene *scene, char **tokens, t_sphere *sp);
static void	check_params(t_scene *scene, t_sphere *sp);
static void	add_sphere(t_scene *scene, t_sphere *sp);
static void	assign_rgb(t_scene *scene, t_sphere *sp, char **tokens);

/*
** tokens:
** [0] "sp"
** [1] x,y,z       center coordinates
** [2] diameter    > 0
** [3] R,G,B       each in [0,255]
*/
bool	parse_sphere(t_scene *scene, char **tokens)
{
	t_sphere	*sp;

	if (tokens_counter(tokens) != 4)
		print_error("Invalid number of inputs for sphere", scene->data);
	sp = gc_malloc(sizeof(t_sphere));
	sp->next = NULL;
	assign_params(scene, tokens, sp);
	check_params(scene, sp);
	add_sphere(scene, sp);
	return (true);
}

static void	assign_params(t_scene *scene, char **tokens, t_sphere *sp)
{
	char	**xyz;

	xyz = ft_split(tokens[1], ',');
	if (tokens_counter(xyz) != 3)
		print_error("Invalid sphere center", scene->data);
	sp->position.x = ft_atof(xyz[0]);
	sp->position.y = ft_atof(xyz[1]);
	sp->position.z = ft_atof(xyz[2]);
	gc_free(xyz);
	sp->radius = ft_atof(tokens[2]) * 0.5f;
	assign_rgb(scene, sp, tokens);
}

static void	assign_rgb(t_scene *scene, t_sphere *sp, char **tokens)
{
	char	**rgb;

	rgb = ft_split(tokens[3], ',');
	if (tokens_counter(rgb) != 3)
		print_error("Invalid sphere color", scene->data);
	sp->color.r = ft_atoi(rgb[0]);
	sp->color.g = ft_atoi(rgb[1]);
	sp->color.b = ft_atoi(rgb[2]);
	gc_free(rgb);
}

static void	check_params(t_scene *scene, t_sphere *sp)
{
	if (sp->radius <= 0)
		print_error("Sphere diameter must be > 0", scene->data);
	if (sp->color.r < 0 || sp->color.r > 255
	 || sp->color.g < 0 || sp->color.g > 255
	 || sp->color.b < 0 || sp->color.b > 255)
		print_error("Sphere color values must be in [0,255]", scene->data);
}

static void	add_sphere(t_scene *scene, t_sphere *sp)
{
	t_sphere	*last;

	if (!scene->objects.spheres)
	{
		scene->objects.spheres = sp;
		return ;
	}
	last = scene->objects.spheres;
	while (last->next)
		last = last->next;
	last->next = sp;
}
