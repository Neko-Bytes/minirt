/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:52:39 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:14:31 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*vector_at(const t_vector *vec, size_t index)
{
	if (!vec)
	{
		fprintf(stderr, "Error: NULL vector in vector_at\n");
		exit(EXIT_FAILURE);
	}
	if (index >= vec->size)
	{
		fprintf(stderr, "Error: Vector index %zu out of bounds (size: %zu)\n",
			index, vec->size);
		exit(EXIT_FAILURE);
	}
	return ((char *)vec->data + (index * vec->element_size));
}

size_t	vector_size(const t_vector *vec)
{
	return (vec->size);
}

size_t	vector_capacity(const t_vector *vec)
{
	return (vec->capacity);
}

void	vector_free(t_vector *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
}
