/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/10 14:06:03 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/entries.h"
#include "../includes/gc.h"
#include "../includes/intersect.h"
#include "../includes/vector_ops.h"
#include "../includes/window.h"
#include "../includes/keys.h"

void	init_window_and_image(t_data *data)
{
	data->mlx = mlx_init(data->width, data->height, "miniRT", true);
	if (!data->mlx)
		exit(1);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img)
		exit(1);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}


int	main(void)
{
	static t_camera	camera = {.position = {0, 0, -10}, .orientation = {0, 0, 1},
			.fov = 70};
	t_data			data;

	data.width = 800;
	data.height = 600;
	data.camera = &camera;
	init_window_and_image(&data);
	render(&data);
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	printf("Exiting program and cleaning up resources.\n");
	return (0);
}
