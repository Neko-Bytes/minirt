/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teja <teja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:30:05 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 01:59:56 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "../gnl/get_next_line.h"
#include "../minilibx/include/MLX42/MLX42.h"
#include "entries.h"
#include "exits.h"
#include "gc.h"
#include "intersect.h"
#include "keys.h"
#include "libft.h"
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
