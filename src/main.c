/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/16 13:34:34 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

int	main(int argc, char **argv)
{
        /* ─── Do you want to use the parser? Uncomment this :) ───────────────────────────────────────────────────────────── */
        // (void)argc;
        // (void)argv;
        // int fd;
        // t_scene *scene;
        // t_data *data;
        //
        // scene->data = gc_malloc(sizeof(*scene->data));
        // if (!scene->data)
        //     print_error("Memory error initializing data\n", NULL);
        // parse_args(argc, argv, scene);
        // fd = scene->fd;
        // parse_file(fd, scene);
        // data = scene->data;



        /* ─── Your code ───────────────────────────────────────────────────────────── */
        (void)argc;
        (void)argv;
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
	colorprint(MSG, "Exiting program and cleaning up resources ...\n");
	gc_free_all();
	return (0);
}





/*
 *  If you want to debug parser, use the run_parser_test function in main as shown below
 */

// #include "../includes/parse_debug.h"
//
// /* ─── Entry Point ───────────────────────────────────────────────────────────── */
// int main(int argc, char **argv)
// {
//     if (!run_parser_test(argc, argv))
//         return (1);
//     gc_free_all();
//     return (0);
// }
//
