/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:30:05 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 14:35:42 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/include/MLX42/MLX42.h"
# include "entries.h"
# include "gc.h"
# include "intersect.h"
# include "keys.h"
# include "parser.h"
# include "utils.h"
# include "vector_ops.h"
# include "window.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_LIGHTS 5
# define MAX_CYLINDERS 5
# define MAX_PLANES 5
# define MAX_SPHERES 5

void	error_exit(t_data *data);
void	free_mlx(t_data *data);
void	print_error(char *msg, t_data *data);
void	check_params(t_scene *scene, t_camera *cam);
void	free_tokens(char **tok);
void	validate_cylinder(t_scene *scene, t_cylinder *cy);

#endif
