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

static void	assign_params(t_scene *scene, char **tokens, t_plane *pl);
static void	assign_rgb(t_scene *scene, char **tokens, t_plane *pl);
static void	check_params(t_scene *scene, t_plane *pl);
static void	add_plane(t_scene *scene, t_plane *pl);

/*
** tokens:
** [0] "pl"
** [1] x,y,z    point on plane
** [2] nx,ny,nz normal vector (non-zero)
** [3] R,G,B    each in [0,255]
*/
bool	parse_plane(t_scene *scene, char **tokens)
{
	t_plane	*pl;

	if (tokens_counter(tokens) != 4)
		print_error("Invalid number of inputs for plane", scene->data);
	pl = gc_malloc(sizeof(t_plane));
	assign_params(scene, tokens, pl);
	assign_rgb(scene, tokens, pl);
	check_params(scene, pl);
	add_plane(scene, pl);
	return (true);
}

static void	assign_params(t_scene *scene, char **tokens, t_plane *pl)
{
	char	**xyz;
	char	**n;

	xyz = ft_split(tokens[1], ',');
	if (tokens_counter(xyz) != 3)
		print_error("Invalid plane point", scene->data);
	pl->position.x = ft_atof(xyz[0]);
	pl->position.y = ft_atof(xyz[1]);
	pl->position.z = ft_atof(xyz[2]);
	gc_free(xyz);
	n = ft_split(tokens[2], ',');
	if (tokens_counter(n) != 3)
		print_error("Invalid plane normal", scene->data);
	pl->normal.x = ft_atof(n[0]);
	pl->normal.y = ft_atof(n[1]);
	pl->normal.z = ft_atof(n[2]);
	gc_free(n);
	// pl->closest_t = INFINITY; // not sure what is this!
	pl->next = NULL;
}

static void	assign_rgb(t_scene *scene, char **tokens, t_plane *pl)
{
	char	**rgb;

	rgb = ft_split(tokens[3], ',');
	if (tokens_counter(rgb) != 3)
		print_error("Invalid plane color", scene->data);
	pl->color.r = ft_atoi(rgb[0]);
	pl->color.g = ft_atoi(rgb[1]);
	pl->color.b = ft_atoi(rgb[2]);
	gc_free(rgb);
}

static void	check_params(t_scene *scene, t_plane *pl)
{
	if (pl->normal.x == 0 && pl->normal.y == 0 && pl->normal.z == 0)
		print_error("Plane normal vector cannot be zero", scene->data);
	if (pl->color.r < 0 || pl->color.r > 255
	 || pl->color.g < 0 || pl->color.g > 255
	 || pl->color.b < 0 || pl->color.b > 255)
		print_error("Plane color values must be in [0,255]", scene->data);
}

static void	add_plane(t_scene *scene, t_plane *pl)
{
	t_plane	*last;

	if (!scene->objects.planes)
	{
		scene->objects.planes = pl;
		return ;
	}
	last = scene->objects.planes;
	while (last->next)
		last = last->next;
	last->next = pl;
}
