/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:30:05 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/07 19:19:53 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "../gnl/get_next_line.h"
#include "../libft/libft.h"
#include "entries.h"
#include "exits.h"
#include "gc.h"
#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum s_error {
  MEM,
  ARGS,
  RTFILE,
  MLX,
  WINDOW,
  IMAGE,
  SCENE,
  AMBIENT,
  CAM,
  LIGHT,
  OBJ,
  CYLINDER,
  PLANE,
  SPHERE,
} t_error

#endif
