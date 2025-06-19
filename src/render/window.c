/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:58 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/18 18:07:45 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"

void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	vector_init(&scene->lights_vec, sizeof(t_light), 10);  // Start with capacity of 10
	init_object_vector(&scene->objects, 10);  // Start with capacity of 10
	scene->data = NULL;
}

static void put_pixel_color(mlx_image_t *img, int x, int y, t_color *color)
{
	int ir = (int)(fminf(fmaxf(color->r, 0.0f), 255.0f));
	int ig = (int)(fminf(fmaxf(color->g, 0.0f), 255.0f));
	int ib = (int)(fminf(fmaxf(color->b, 0.0f), 255.0f));
	int pixel = (ir << 24) | (ig << 16) | (ib << 8) | 0xFF; // RGBA format with full alpha
	mlx_put_pixel(img, x, y, pixel);
}

static void render_row(int y, t_data *data, mlx_image_t *img)
{
	int x = 0;
	t_color color;
	while (x < data->width)
	{
		mainImage((t_vec2){x, y}, data->width, data->height, &color, data->scene);
		put_pixel_color(img, x, y, &color);
		x++;
	}
}

static void render_image(t_data *data, mlx_image_t *img)
{
	int y = 0;
	while (y < data->height)
	{
		render_row(y, data, img);
		y++;
	}
}

void render(t_data *data)
{
	mlx_image_t *img = (mlx_image_t *)data->img;
	if (!data || !data->img || !data->camera || !data->scene)
		return;
	render_image(data, img);
	mlx_image_to_window(data->mlx, img, 0, 0);
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
