/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:16:51 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:18:09 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTRIES_H
# define ENTRIES_H

# include "../libft/libft.h"
# include "../minilibx/include/MLX42/MLX42.h"
# include "vector.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_scene	t_scene;

typedef struct s_color
{
	float				r;
	float				g;
	float				b;
}						t_color;

typedef struct s_vec3
{
	float				x;
	float				y;
	float				z;
}						t_vec3;

typedef struct s_vec2
{
	float				x;
	float				y;

}						t_vec2;

typedef struct s_ambient
{
	float				intensity;
	t_color				color;
}						t_ambient;

typedef struct s_camera
{
	t_vec3				position;
	t_vec3				direction;
	t_vec3				orientation;
	float				fov;
	float				zoom;
}						t_camera;

typedef struct s_input
{
	bool				key_up;
	bool				key_down;
	bool				key_left;
	bool				key_right;
	bool				key_a;
	bool				key_d;
}						t_input;

typedef struct s_data
{
	void				*mlx;
	mlx_image_t			*img;
	int					width;
	int					height;
	t_camera			*camera;
	t_scene				*scene;
	t_input				*input;
}						t_data;

typedef struct s_light
{
	t_vec3				position;
	float				intensity;
	t_color				color;
	int					count;
}						t_light;

typedef struct s_plane
{
	t_vec3				position;
	t_vec3				normal;
	t_color				color;
}						t_plane;

typedef struct s_sphere
{
	t_vec3				position;
	float				radius;
	t_color				color;
}						t_sphere;
typedef struct s_cylinder
{
	t_vec3				position;
	t_vec3				orientation;
	float				diameter;
	float				height;
	t_color				color;
	// struct s_cylinder *next;
}						t_cylinder;

typedef struct s_object_vector
{
	t_vector			planes_vec;
	t_vector			spheres_vec;
	t_vector			cylinders_vec;
}						t_object_vector;

typedef struct s_scene
{
	t_ambient			*ambient;
	t_camera			*camera;
	t_light				*lights;
	t_vector			lights_vec;
	t_object_vector		objects;
	t_data				*data;
}						t_scene;

#endif