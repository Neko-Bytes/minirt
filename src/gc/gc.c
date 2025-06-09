/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:58:01 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/05 20:59:37 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

typedef struct s_gc_node {
  void *ptr;
  struct s_gc_node *next;
} t_gc_node;

/*
 * gc_head_ptr():
 *   Returns the address of a function‐static pointer that holds the head
 *   of our linked list.
 */
static t_gc_node **gc_head_ptr(void) {
  static t_gc_node *head = NULL;
  return (&head);
}

/*
 * new_node:
 *   Allocates a new list node for tracking 'p'. On failure, prints perror
 *   and exits(EXIT_FAILURE).
 */
static t_gc_node *new_node(void *p) {
  t_gc_node *node;

  node = (t_gc_node *)malloc(sizeof(t_gc_node));
  if (!node) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  node->ptr = p;
  node->next = NULL;
  return (node);
}

void *gc_malloc(size_t size) {
  void *mem;
  t_gc_node *node;
  t_gc_node **head;

  mem = malloc(size);
  if (!mem) {
    fprintf(stderr, "Error\nmalloc failed\n");
    exit(EXIT_FAILURE);
  }
  node = new_node(mem);
  head = gc_head_ptr();
  node->next = *head;
  *head = node;
  return (mem);
}

void gc_free(void *ptr) {
  t_gc_node *prev;
  t_gc_node *cur;
  t_gc_node **head;

  if (!ptr)
    return;
  head = gc_head_ptr();
  if (!*head)
    return;
  prev = NULL;
  cur = *head;
  while (cur) {
    if (cur->ptr == ptr) {
      if (prev)
        prev->next = cur->next;
      else
        *head = cur->next;
      free(cur->ptr);
      free(cur);
      return;
    }
    prev = cur;
    cur = cur->next;
  }
}

void gc_free_all(void) {
  t_gc_node *tmp;
  t_gc_node **head;

  head = gc_head_ptr();
  while (*head) {
    tmp = *head;
    *head = (*head)->next;
    free(tmp->ptr);
    free(tmp);
  }
}

// Just for debugging purposes
void gc_print_all(void) {
  t_gc_node *cur;
  size_t idx;
  t_gc_node **head;

  head = gc_head_ptr();
  if (!*head) {
    printf("[GC] no allocations tracked\n");
    return;
  }
  cur = *head;
  idx = 0;
  printf("[GC] currently tracked allocations:\n");
  while (cur) {
    printf("  [%zu] %p\n", idx, cur->ptr);
    idx++;
    cur = cur->next;
  }
}
