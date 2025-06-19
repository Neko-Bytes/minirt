/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:26:16 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 17:26:27 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/entries.h"
#include "../../includes/minirt.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"

static void	put_pixel_color(mlx_image_t *img, int x, int y, t_color *color)
{
	int	ir;
	int	ig;
	int	ib;
	int	pixel;

	ir = (int)(fminf(fmaxf(color->r, 0.0f), 255.0f));
	ig = (int)(fminf(fmaxf(color->g, 0.0f), 255.0f));
	ib = (int)(fminf(fmaxf(color->b, 0.0f), 255.0f));
	pixel = (ir << 24) | (ig << 16) | (ib << 8) | 0xFF;
	mlx_put_pixel(img, x, y, pixel);
}

static void	render_row(int y, t_data *data, mlx_image_t *img)
{
	t_color		color;
	t_params	params;

	params.width = data->width;
	params.height = data->height;
	params.coord.x = 0;
	params.coord.y = y;
	while (params.coord.x < data->width)
	{
		main_image(&params, &color, data->scene);
		put_pixel_color(img, params.coord.x, params.coord.y, &color);
		params.coord.x++;
	}
}

static void	render_image(t_data *data, mlx_image_t *img)
{
	int	y;

	y = 0;
	while (y < data->height)
	{
		render_row(y, data, img);
		y++;
	}
}

void	render(t_data *data)
{
	mlx_image_t	*img;

	img = (mlx_image_t *)data->img;
	if (!data || !data->img || !data->camera || !data->scene)
		return ;
	render_image(data, img);
	mlx_image_to_window(data->mlx, img, 0, 0);
}
