/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:49:47 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:13:52 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_plane	*get_plane(const t_object_vector *vec, size_t index)
{
	return ((t_plane *)vector_at(&vec->planes_vec, index));
}

t_sphere	*get_sphere(const t_object_vector *vec, size_t index)
{
	return ((t_sphere *)vector_at(&vec->spheres_vec, index));
}

t_cylinder	*get_cylinder(const t_object_vector *vec, size_t index)
{
	return ((t_cylinder *)vector_at(&vec->cylinders_vec, index));
}

size_t	get_plane_count(const t_object_vector *vec)
{
	return (vector_size(&vec->planes_vec));
}

size_t	get_sphere_count(const t_object_vector *vec)
{
	return (vector_size(&vec->spheres_vec));
}
