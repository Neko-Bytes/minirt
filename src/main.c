/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/16 19:15:12 by kruseva          ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	int fd;
	t_scene *scene;
	
	scene = gc_malloc(sizeof(t_scene));
	if (!scene)
		print_error("Memory error initializing scene\n", NULL);
	parse_args(argc, argv, scene);
	fd = scene->fd;
	parse_file(fd, scene);
	scene->data = gc_malloc(sizeof(t_data));
	if (!scene->data)
		print_error("Memory error initializing data\n", scene->data);
	scene->data->width = 800; // Example width
	scene->data->height = 600; // Example height
	scene->data->camera = scene->camera;
	init_window_and_image(scene->data);

	render(scene);
	// mlx_key_hook(scene->data->mlx, key_hook, scene);

	mlx_loop(scene->data->mlx);
	mlx_terminate(scene->data->mlx);
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
