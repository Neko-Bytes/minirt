/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:58:01 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/22 12:55:23 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gc.h"

/*
** Return the address of the head pointer so all GC functions
** can update the list.  Non-static so it's used and won't trigger
** -Wunused-function.
*/
t_gc_node	**gc_head_ptr(void)
{
	static t_gc_node	*g_gc_head = NULL;

	return (&g_gc_head);
}

/*
 * new_node:
 *   Allocate a tracking node for pointer 'p'.
 *   Returns NULL on failure (caller must free 'p' if non-NULL).
 */
static t_gc_node	*new_node(void *p)
{
	t_gc_node	*node;

	node = malloc(sizeof(t_gc_node));
	if (!node)
		return (NULL);
	node->ptr = p;
	node->next = NULL;
	return (node);
}

void	*gc_malloc(size_t size)
{
	void		*mem;
	t_gc_node	*node;
	t_gc_node	**head;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, size);
	node = new_node(mem);
	if (!node)
	{
		free(mem);
		return (NULL);
	}
	head = gc_head_ptr();
	node->next = *head;
	*head = node;
	return (mem);
}

void	gc_free(void *ptr)
{
	t_gc_node	**head;
	t_gc_node	*cur;
	t_gc_node	*prev;

	if (!ptr)
		return ;
	head = gc_head_ptr();
	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (cur->ptr && cur->ptr == ptr)
		{
			gc_remove_node(head, prev, cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	ptr = NULL;
}

void	gc_free_all(void)
{
	t_gc_node	*tmp;
	t_gc_node	**head;

	head = gc_head_ptr();
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->ptr)
			free(tmp->ptr);
		if (tmp)
			free(tmp);
	}
}
