/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/18 18:10:38 by kruseva          ###   ########.fr       */
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
	{
		mlx_terminate(data->mlx);
		exit(1);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
	{
		mlx_delete_image(data->mlx, data->img);
		mlx_terminate(data->mlx);
		exit(1);
	}
}


int	main(int argc, char **argv)
{
	(void)argc;
	
	int fd;
	t_scene *scene;
	
	scene = gc_malloc(sizeof(t_scene));
	if (!scene)
		print_error("Memory error initializing scene\n", NULL);
	
	// Initialize scene data
	scene->data = gc_malloc(sizeof(t_data));
	if (!scene->data)
		print_error("Memory error initializing data\n", NULL);
	scene->data->width = 800;
	scene->data->height = 600;

	// initialize key input
	scene->data->input = gc_malloc(sizeof(t_input));
	if (!scene->data->input)
		print_error("Memory error initializing input\n", NULL);
	scene->data->input->key_up = false;
	scene->data->input->key_down = false;
	scene->data->input->key_left = false;
	scene->data->input->key_right = false;
	scene->data->input->key_a = false;
	scene->data->input->key_d = false;
	
	// Get file descriptor from parse_args
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("Error: cannot open file\n", scene->data);
	
	parse_file(fd, scene);
	close(fd);  // Close the file descriptor after parsing

	
	scene->data->camera = scene->camera;
	scene->data->scene = scene;  // Set the scene pointer
	scene->camera->orientation = vec_normalize(scene->camera->direction);
	
	// Initialize window and image
	init_window_and_image(scene->data);
	
	render(scene->data);
	
	// Set up key hook
	mlx_key_hook(scene->data->mlx, key_hook, scene);
	// Set up game loop
	mlx_loop_hook(scene->data->mlx, game_loop, scene->data);
	
	// Main loop
	mlx_loop(scene->data->mlx);
	
	// Cleanup
	mlx_terminate(scene->data->mlx);
	colorprint(MSG, "Exiting program and cleaning up resources ...\n");
	gc_free_all();
	return (0);
}
