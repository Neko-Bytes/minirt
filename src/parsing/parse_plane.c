/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:13:44 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/12 09:21:56 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ensure_space(t_scene *scene);
static void	set_plane(t_scene *scene, t_plane *pl, char **tokens);
static void	validate_plane(t_scene *scene, t_plane *pl);

bool	parse_plane(t_scene *scene, char **tokens)
{
	t_plane	*pl;

	if (tokens_counter(tokens) != 4)
		print_error("Plane: wrong number of params\n",
			scene->data);
	ensure_space(scene);
	pl = &scene->objects.planes[scene->objects.pl_count];
	set_plane(scene, pl, tokens);
	validate_plane(scene, pl);
	scene->objects.pl_count++;
	return (true);
}

static void	ensure_space(t_scene *scene)
{
	size_t	new_size;

	if (!scene->objects.planes)
	{
		scene->objects.pl_count = 0;
		scene->objects.planes = gc_malloc(sizeof(t_plane));
		if (!scene->objects.planes)
			print_error("Plane: alloc failed\n", scene->data);
	}
	else
	{
		if (scene->objects.pl_count + 1 > MAX_PLANES)
			print_error("Plane: max count exceeded\n",
				scene->data);
		new_size = scene->objects.pl_count + 1;
		scene->objects.planes = gc_realloc(
			scene->objects.planes,
			sizeof(t_plane) * scene->objects.pl_count,
			sizeof(t_plane) * new_size);
		if (!scene->objects.planes)
			print_error("Plane: realloc failed\n",
				scene->data);
	}
}

static void	set_plane(t_scene *scene, t_plane *pl, char **tokens)
{
	char	**xyz;
	char	**norm;
	char	**rgb;

	xyz  = ft_split(tokens[1], ',');
	norm = ft_split(tokens[2], ',');
	rgb  = ft_split(tokens[3], ',');
	if (tokens_counter(xyz) != 3 || tokens_counter(norm) != 3 ||
	    tokens_counter(rgb) != 3)
		print_error("Plane: bad vec or color\n", scene->data);
	pl->position.x = ft_atof(xyz[0]);
	pl->position.y = ft_atof(xyz[1]);
	pl->position.z = ft_atof(xyz[2]);
	pl->normal.x   = ft_atof(norm[0]);
	pl->normal.y   = ft_atof(norm[1]);
	pl->normal.z   = ft_atof(norm[2]);
	pl->color.r    = ft_atoi(rgb[0]);
	pl->color.g    = ft_atoi(rgb[1]);
	pl->color.b    = ft_atoi(rgb[2]);
}

static void	validate_plane(t_scene *scene, t_plane *pl)
{
	if (pl->normal.x < -1.0f || pl->normal.x > 1.0f ||
	    pl->normal.y < -1.0f || pl->normal.y > 1.0f ||
	    pl->normal.z < -1.0f || pl->normal.z > 1.0f)
		print_error("Plane: normal out of range\n", scene->data);
	if (pl->color.r < 0 || pl->color.r > 255)
		print_error("Plane: red out of range\n", scene->data);
	if (pl->color.g < 0 || pl->color.g > 255)
		print_error("Plane: green out of range\n", scene->data);
	if (pl->color.b < 0 || pl->color.b > 255)
		print_error("Plane: blue out of range\n", scene->data);
}
