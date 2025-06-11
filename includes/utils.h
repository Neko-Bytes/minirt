/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:59:35 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/10 19:57:02 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

// COLORS
#define RESET "\033[0m"

/* Styles */
#define BOLD "\033[1m"
#define UNDER "\033[4m"

/* Foreground (text) colors */
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

/* Bright variants */
#define BBLACK "\033[90m"
#define BRED "\033[91m"
#define BGREEN "\033[92m"
#define BYELLOW "\033[93m"
#define BBLUE "\033[94m"
#define BMAGENTA "\033[95m"
#define BCYAN "\033[96m"
#define BWHITE "\033[97m"

typedef enum s_log { MSG, WARNING, SUCCESS, FAILURE } t_log;

int tokens_couter(char **tokens);
void colorprint(t_log log, char *msg);

#endif
