/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:20:23 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 18:54:06 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Here I implement a simple dynamic array structure to hold
planes and spheres. This allows for easy addition of objects
without needing to know the final count beforehand.
This is similar to a vector in C++.
*/

void	vector_init(t_vector *vec, size_t element_size, size_t initial_capacity)
{
	if (!vec || element_size == 0 || initial_capacity == 0)
	{
		fprintf(stderr,
			"Error: Invalid parameters for vector initialization\n");
		exit(EXIT_FAILURE);
	}
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = initial_capacity;
	vec->element_size = element_size;
	vec->data = malloc(element_size * initial_capacity);
	if (!vec->data)
	{
		fprintf(stderr, "Error: Failed to allocate memory for vector\n");
		exit(EXIT_FAILURE);
	}
}

void	init_object_vector(t_object_vector *vec, int initial_capacity)
{
	if (!vec || initial_capacity <= 0)
	{
		fprintf(stderr,
			"Error: Invalid parameters for object vector initialization\n");
		exit(EXIT_FAILURE);
	}
	vector_init(&vec->planes_vec, sizeof(t_plane), initial_capacity);
	vector_init(&vec->spheres_vec, sizeof(t_sphere), initial_capacity);
	vector_init(&vec->cylinders_vec, sizeof(t_cylinder), initial_capacity);
}

void	vector_resize(t_vector *vec, size_t new_capacity)
{
	void	*new_data;

	if (!vec || new_capacity == 0)
	{
		fprintf(stderr, "Error: Invalid parameters for vector_resize\n");
		exit(EXIT_FAILURE);
	}
	new_data = malloc(vec->element_size * new_capacity);
	if (!new_data)
	{
		fprintf(stderr, "Error: Failed to allocate memory for vector\n");
		exit(EXIT_FAILURE);
	}
	if (vec->data)
	{
		memcpy(new_data, vec->data, vec->element_size * vec->size);
		free(vec->data);
	}
	vec->data = new_data;
	vec->capacity = new_capacity;
}

void	vector_push_back(t_vector *vec, const void *element)
{
	char	*dest;

	if (!vec || !element)
	{
		fprintf(stderr, "Error: Invalid parameters for vector_push_back\n");
		exit(EXIT_FAILURE);
	}
	if (vec->size >= vec->capacity)
	{
		vector_resize(vec, vec->capacity * 2);
	}
	dest = (char *)vec->data + (vec->size * vec->element_size);
	memcpy(dest, element, vec->element_size);
	vec->size++;
}
