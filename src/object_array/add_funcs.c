/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:46:41 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 18:56:12 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	add_plane(t_object_vector *vec, t_plane plane)
{
	vector_push_back(&vec->planes_vec, &plane);
}

void	add_sphere(t_object_vector *vec, t_sphere sphere)
{
	vector_push_back(&vec->spheres_vec, &sphere);
}

void	add_cylinder(t_object_vector *vec, t_cylinder cylinder)
{
	vector_push_back(&vec->cylinders_vec, &cylinder);
}

void	free_object_vector(t_object_vector *vec)
{
	vector_free(&vec->planes_vec);
	vector_free(&vec->spheres_vec);
	vector_free(&vec->cylinders_vec);
}

size_t	get_cylinder_count(const t_object_vector *vec)
{
	return (vector_size(&vec->cylinders_vec));
}
