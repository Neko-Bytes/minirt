/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:00:22 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/07 17:26:55 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "entries.h"
#include <stdbool.h>
#include <stdio.h>

bool parse_args(int argc, char **argv);
bool parse_elements(char *trim, t_scene *scene);
bool parse_ambience(t_scene *scene, char **tokens);
bool parse_camera(t_scene *scene, char **tokens);
bool parse_light(t_scene *scene, char **tokens);
bool parse_sphere(t_scene *scene, char **tokens);
bool parse_cylinder(t_scene *scene, char **tokens);
bool parse_plane(t_scene *scene, char **tokens);

#endif
