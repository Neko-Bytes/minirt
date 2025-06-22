/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:20:29 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/22 12:48:17 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_vector
{
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	element_size;
}			t_vector;

void		vector_init(t_vector *vec, size_t element_size,
				size_t initial_capacity);

void		vector_push_back(t_vector *vec, const void *element);

void		*vector_at(const t_vector *vec, size_t index);

size_t		vector_size(const t_vector *vec);

size_t		vector_capacity(const t_vector *vec);

void		vector_free(t_vector *vec);

#endif