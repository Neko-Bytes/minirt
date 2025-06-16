/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknsteja <mknsteja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:30:17 by mknsteja          #+#    #+#             */
/*   Updated: 2025/06/16 02:20:27 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include "../includes/gc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);
size_t gnl_strlen(const char *string);
char *gnl_strdup(const char *src);
char *gnl_strchr(const char *string, int character);
char *gnl_substr(const char *s, unsigned int start, size_t len);
char *gnl_strjoin(char const *s1, char const *s2);

#endif
