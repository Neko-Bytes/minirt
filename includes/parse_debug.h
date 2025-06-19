/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:12:20 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 19:19:34 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_DEBUG_H
# define PARSE_DEBUG_H

# include "minirt.h"

void	print_ambient(t_scene *scene);
void	print_camera(t_scene *scene);
void	print_lights(t_scene *scene);
void	print_spheres(t_scene *scene);
void	print_planes(t_scene *scene);
void	print_cylinders(t_scene *scene);
bool	run_parser_test(int argc, char **argv);

#endif
