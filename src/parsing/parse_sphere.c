/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:49 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:37:06 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ensure_space(t_scene *scene);
static void	set_sphere(t_scene *scene, t_sphere *sp, char **tokens);
static void	validate_sphere(t_scene *scene, t_sphere *sp);

bool	parse_sphere(t_scene **scene, char **tokens)
{
	t_sphere	*sp;

	if (tokens_counter(tokens) != 4)
		print_error("Sphere: wrong number of params\n", (*scene)->data);
	ensure_space((*scene));
	sp = &(*scene)->objects.spheres[(*scene)->objects.sp_count];
	set_sphere(*scene, sp, tokens);
	validate_sphere(*scene, sp);
	(*scene)->objects.sp_count++;
	return (true);
}

static void	ensure_space(t_scene *scene)
{
	size_t	new_size;

	if (!scene->objects.spheres)
	{
		scene->objects.sp_count = 0;
		scene->objects.spheres = gc_malloc(sizeof(t_sphere) * 1);
		if (!scene->objects.spheres)
			print_error("Sphere: alloc failed\n", scene->data);
	}
	else
	{
		if (scene->objects.sp_count + 1 > MAX_SPHERES)
			print_error("Sphere: max count exceeded\n",
				scene->data);
		new_size = scene->objects.sp_count + 1;
		scene->objects.spheres = gc_realloc(
			scene->objects.spheres,
			sizeof(t_sphere) * scene->objects.sp_count,
			sizeof(t_sphere) * new_size);
		if (!scene->objects.spheres)
			print_error("Sphere: realloc failed\n",
				scene->data);
	}
}

static void	set_sphere(t_scene *scene, t_sphere *sp, char **tokens)
{
	char	**xyz;
	char	**rgb;

	xyz = ft_split(tokens[1], ',');
	rgb = ft_split(tokens[3], ',');
	if (tokens_counter(xyz) != 3 || tokens_counter(rgb) != 3)
		print_error("Sphere: bad vec or color\n", scene->data);
	sp->position.x = ft_atof(xyz[0]);
	sp->position.y = ft_atof(xyz[1]);
	sp->position.z = ft_atof(xyz[2]);
	sp->radius     = ft_atof(tokens[2]) * 0.5f;
	sp->color.r    = ft_atoi(rgb[0]);
	sp->color.g    = ft_atoi(rgb[1]);
	sp->color.b    = ft_atoi(rgb[2]);
}

static void	validate_sphere(t_scene *scene, t_sphere *sp)
{
	if (sp->radius <= 0.0f)
		print_error("Sphere: invalid radius\n", scene->data);
	if (sp->color.r < 0 || sp->color.r > 255)
		print_error("Sphere: red out of range\n", scene->data);
	if (sp->color.g < 0 || sp->color.g > 255)
		print_error("Sphere: green out of range\n", scene->data);
	if (sp->color.b < 0 || sp->color.b > 255)
		print_error("Sphere: blue out of range\n", scene->data);
}
