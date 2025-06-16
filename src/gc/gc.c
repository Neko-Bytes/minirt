/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:58:01 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 01:42:00 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gc.h"

static t_gc_node  *g_gc_head = NULL;

/*
** Return the address of the head pointer so all GC functions
** can update the list.  Non-static so it's used and won't trigger
** -Wunused-function.
*/
t_gc_node  **gc_head_ptr(void)
{
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
	void			*mem;
	t_gc_node		*node;
	t_gc_node		**head;

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

void	*gc_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void		*new_mem;

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
		if (cur->ptr == ptr)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->ptr);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
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
		free(tmp->ptr);
		free(tmp);
	}
}

// Just for debugging purposes
// void gc_print_all(void) {
//   t_gc_node *cur;
//   size_t idx;
//   t_gc_node **head;
//
//   head = gc_head_ptr();
//   if (!*head) {
//     printf("[GC] no allocations tracked\n");
//     return;
//   }
//   cur = *head;
//   idx = 0;
//   printf("[GC] currently tracked allocations:\n");
//   while (cur) {
//     printf("  [%zu] %p\n", idx, cur->ptr);
//     idx++;
//     cur = cur->next;
//   }
// }
