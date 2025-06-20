/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/20 13:15:35 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	init_scene_structs(t_scene **scene_ptr)
{
	*scene_ptr = gc_malloc(sizeof(t_scene));
	if (!*scene_ptr)
		print_error("Memory error initializing scene\n", NULL);
	(*scene_ptr)->data = gc_malloc(sizeof(t_data));
	if (!(*scene_ptr)->data)
		print_error("Memory error initializing data\n", NULL);
	(*scene_ptr)->data->width = 800;
	(*scene_ptr)->data->height = 600;
	(*scene_ptr)->data->input = gc_malloc(sizeof(t_input));
	if (!(*scene_ptr)->data->input)
		print_error("Memory error initializing input\n", NULL);
	(*scene_ptr)->data->input->key_up = false;
	(*scene_ptr)->data->input->key_down = false;
	(*scene_ptr)->data->input->key_left = false;
	(*scene_ptr)->data->input->key_right = false;
	(*scene_ptr)->data->input->key_a = false;
	(*scene_ptr)->data->input->key_d = false;
}

static void	open_and_parse_file(const char *filename, t_scene *scene)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Error: cannot open file\n", scene->data);
	parse_file(fd, scene);
	close(fd);
}

static void	setup_camera_and_scene(t_scene *scene)
{
	scene->data->camera = scene->camera;
	scene->data->scene = scene;
	scene->camera->orientation = vec_normalize(scene->camera->direction);
}

static void	run_event_loop_and_render(t_scene *scene)
{
	init_window_and_image(scene->data);
	render(scene->data);
	mlx_key_hook(scene->data->mlx, key_hook, scene);
	mlx_loop_hook(scene->data->mlx, game_loop, scene->data);
	mlx_loop(scene->data->mlx);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	(void)argc;
	init_scene_structs(&scene);
	open_and_parse_file(argv[1], scene);
	setup_camera_and_scene(scene);
	run_event_loop_and_render(scene);
	mlx_terminate(scene->data->mlx);
	colorprint(MSG, "Exiting program and cleaning up resources ...\n");
	free_object_vector(&scene->objects);
	vector_free(&scene->lights_vec);
	gc_free_all();
	return (0);
}
