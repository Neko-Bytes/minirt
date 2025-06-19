/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:00:22 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 19:19:39 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "entries.h"
# include <stdbool.h>
# include <stdio.h>

typedef struct s_scene	t_scene;

bool					parse_args(int argc, char **argv, t_scene *scene);
bool					parse_file(int fd, t_scene *scene);
bool					parse_elements(char *trim, t_scene **scene);
bool					parse_ambience(t_scene **scene, char **tokens);
bool					parse_camera(t_scene **scene, char **tokens);
bool					parse_light(t_scene **scene, char **tokens);
bool					parse_sphere(t_scene **scene, char **tokens);
bool					parse_cylinder(t_scene **scene, char **tokens);
bool					parse_plane(t_scene **scene, char **tokens);

#endif
