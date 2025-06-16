/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:30:05 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 14:59:54 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "../gnl/get_next_line.h"
#include "../libft/libft.h"
#include "../minilibx/include/MLX42/MLX42.h"
#include "entries.h"
// #include "exits.h"
#include "gc.h"
#include "intersect.h"
#include "keys.h"
#include "parser.h"
#include "utils.h"
#include "vector_ops.h"
#include "window.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LIGHTS 5
#define MAX_CYLINDERS 5
#define MAX_PLANES 5
#define MAX_SPHERES 5

void error_exit(t_data *data);
void print_error(char *msg, t_data *data);
// void render(t_data *data, t_scene *scene);

// typedef enum s_error {
//   MEM,
//   ARGS,
//   RTFILE,
//   MLX,
//   WINDOW,
//   IMAGE,
//   SCENE,
//   AMBIENT,
//   CAM,
//   LIGHT,
//   OBJ,
//   CYLINDER,
//   PLANE,
//   SPHERE,
// } t_error

#endif
