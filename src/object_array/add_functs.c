/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:00:05 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/22 11:54:12 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"
#include <stdio.h>

void	vector_init(t_vector *vec, size_t element_size, size_t initial_capacity)
{
	vec->data = malloc(element_size * initial_capacity);
	if (!vec->data)
	{
		printf("Error: Failed to allocate memory for vector\n");
		exit(EXIT_FAILURE);
	}
	vec->size = 0;
	vec->capacity = initial_capacity;
	vec->element_size = element_size;
}
