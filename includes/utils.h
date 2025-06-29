/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:59:35 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 12:59:06 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "../includes/minirt.h"
#include "entries.h"
#include <errno.h>

#define RESET "\033[0m"

#define BOLD "\033[1m"
#define UNDER "\033[4m"

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define BBLACK "\033[90m"
#define BRED "\033[91m"
#define BGREEN "\033[92m"
#define BYELLOW "\033[93m"
#define BBLUE "\033[94m"
#define BMAGENTA "\033[95m"
#define BCYAN "\033[96m"
#define BWHITE "\033[97m"

typedef enum s_log { MSG, WARNING, SUCCESS, FAILURE } t_log;

int tokens_counter(char **tokens);
void colorprint(t_log log, char *msg);
void free_tokens(char **tok);
bool validate_element_counts(char **tokens, t_scene **scene);
char *safe_gnl(int fd, t_scene *scene);
void tokens_checker(const char *asset, char **tokens, t_scene **scene);
void tokens_printer(char **tokens);

#endif
