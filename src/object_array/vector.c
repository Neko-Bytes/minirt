/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:04:20 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/22 11:51:12 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gc.h"
#include "../../includes/vector.h"
#include <stdio.h>

void	vector_push_back(t_vector *vec, const void *element)
{
	void	*tmp;

	if (vec->size >= vec->capacity)
	{
		vec->capacity *= 2;
		tmp = gc_realloc(vec->data, vec->element_size, vec->element_size
				* vec->capacity);
		if (!tmp)
		{
			printf("Error: Failed to reallocate memory for vector\n");
			exit(EXIT_FAILURE);
		}
		vec->data = tmp;
	}
	ft_memcpy((char *)vec->data + (vec->size * vec->element_size), element,
		vec->element_size);
	vec->size++;
}

void	*vector_at(t_vector *vec, size_t index)
{
	if (index >= vec->size)
	{
		printf("Error: Vector index out of bounds\n");
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
