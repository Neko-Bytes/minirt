/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:58 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/16 19:15:48 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/entries.h"
#include "../includes/intersect.h"
#include "../includes/object_array.h"
#include "../includes/window.h"
#include "test/test.h"


void	render(t_scene *scene)
{
	t_color color;
	int		ir;
	int		ig;
	int		ib;
	int		pixel;
	// printf("scene->data->width: %d\n", scene->data->width);
	// exit(0);
	mlx_image_t *img = (mlx_image_t *)scene->data->img;

	for (int y = 0; y < scene->data->height; y++)
	{
		for (int x = 0; x < scene->data->width; x++)
		{
			mainImage((t_vec2){x, y}, scene->data->width, scene->data->height, &color,
				scene);
			ir = (int)fminf(fmaxf(color.r, 0.0f), 255.0f);
			ig = (int)fminf(fmaxf(color.g, 0.0f), 255.0f);
			ib = (int)fminf(fmaxf(color.b, 0.0f), 255.0f);
			pixel = (ir << 24) | (ig << 16) | (ib << 8) | 255; // RGBA

				mlx_put_pixel(img, x, y, pixel);
		}
	}
	free_object_vector(&scene->objects);
}
t_vec3	rotate_y(t_vec3 v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	return ((t_vec3){v.x * cos_a + v.z * sin_a, v.y, -v.x * sin_a + v.z
		* cos_a});
}

t_vec3	rotate_x(t_vec3 v, float angle)
{
	float	cos_a;
	float	sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	return ((t_vec3){v.x, v.y * cos_a - v.z * sin_a, v.y * sin_a + v.z
		* cos_a});
}
