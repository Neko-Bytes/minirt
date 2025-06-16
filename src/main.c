/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/16 02:37:11 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


// static bool  run_parser_test(int argc, char **argv);

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
	colorprint(MSG, "Exiting program and cleaning up resources ...\n");
	gc_free_all();
	return (0);
}

// int main(int argc, char **argv)
// {
// 	run_parser_test(argc, argv);
// 	gc_free_all();
// }
//
// static bool  run_parser_test(int argc, char **argv)
// {
//     t_scene  *scene;
//     int      fd;
//
//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <scene.rt>\n", argv[0]);
//         return (false);
//     }
//     scene = gc_malloc(sizeof(t_scene));
//     scene->data = gc_malloc(sizeof(*scene->data));
//     if (!scene->data)
//         print_error("Test: memory error for scene.data\n", NULL);
//     if (!parse_args(argc, argv, scene))
//         return (false);
//     fd = scene->fd;
//     if (!parse_file(fd, scene))
//         return (false);
//     printf("Parsing succeeded:\n");
//     printf("  Lights:    %d\n", scene->lights->count);
//     printf("  Spheres:   %d\n", scene->objects.sp_count);
//     printf("  Planes:    %d\n", scene->objects.pl_count);
//     printf("  Cylinders: %d\n", scene->objects.cy_count);
//     return (true);
// }
