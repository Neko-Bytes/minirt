/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:04:20 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/22 13:00:40 by kruseva          ###   ########.fr       */
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
			gc_free_all();
			exit(EXIT_FAILURE);
		}
		vec->data = tmp;
	}
	ft_memcpy((char *)vec->data + (vec->size * vec->element_size), element,
		vec->element_size);
	vec->size++;
	gc_free((void *)element);
}

size_t	vector_size(const t_vector *vec)
{
	return (vec->size);
}

size_t	vector_capacity(const t_vector *vec)
{
	return (vec->capacity);
}
