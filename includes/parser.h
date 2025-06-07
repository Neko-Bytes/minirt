/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:00:22 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/07 14:09:21 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "entries.h"
#include <stdbool.h>
#include <stdio.h>

bool parse_args(int argc, char **argv);
void parse_elements(char *trim, t_scene *scene);

#endif
