/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:39:45 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 18:42:55 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
#define GC_H

#include "../includes/exits.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_gc_node {
  void *ptr;
  struct s_gc_node *next;
} t_gc_node;

/*
 * gc_head_ptr():
 *   Returns the address of a function‐static pointer that holds the head
 *   of our linked list.
 */
t_gc_node **gc_head_ptr(void);

/*
 * gc_malloc:
 *   Allocates 'size' bytes, registers the returned pointer in the GC list,
 *   and returns that pointer. On failure, prints "Error\nmalloc failed\n"
 *   and exits.
 */
void	gc_remove_node(t_gc_node **head, t_gc_node *prev, t_gc_node *cur);
void *gc_malloc(size_t size);
void *gc_realloc(void *ptr, size_t old_size, size_t new_size);

/*
 * gc_free:
 *   If 'ptr' was previously allocated via gc_malloc, removes it from the
 *   GC list and frees it. If ptr is NULL or not found, does nothing.
 */
void gc_free(void *ptr);

/*
 * gc_clear_all:
 *   Frees any remaining allocated blocks in the GC list.
 *   After this, the list is empty. Safe to call multiple times.
 */
void gc_free_all(void);

/*
 * gc_print_all:
 *   Prints all currently tracked allocations (pointer addresses). Useful
 *   for debugging: shows which nodes remain in the GC list.
 */
void gc_print_all(void);

#endif
