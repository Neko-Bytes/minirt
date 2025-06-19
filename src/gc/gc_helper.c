/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:25:33 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 18:42:46 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gc.h"

void	*gc_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_mem;

	new_mem = gc_malloc(new_size);
	if (!new_mem)
		return (NULL);
	if (ptr && old_size > 0)
	{
		if (old_size < new_size)
			ft_memcpy(new_mem, ptr, old_size);
		else
			ft_memcpy(new_mem, ptr, new_size);
		gc_free(ptr);
	}
	return (new_mem);
}

void	gc_remove_node(t_gc_node **head, t_gc_node *prev, t_gc_node *cur)
{
	if (prev)
		prev->next = cur->next;
	else
		*head = cur->next;
	if (cur && cur->ptr)
		free(cur->ptr);
	if (cur)
		free(cur);
}
