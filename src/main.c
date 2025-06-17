/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:06:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/16 21:23:27 by kruseva          ###   ########.fr       */
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
	
	// Get file descriptor from parse_args
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("Error: cannot open file\n", scene->data);
	
	parse_file(fd, scene);
	close(fd);  // Close the file descriptor after parsing

	// Debug printing
	printf("\n=== Scene Debug Information ===\n");
	
	// Check Ambient
	if (scene->ambient) {
		printf("\n[Ambient Light]\n");
		printf("Intensity: %.2f\n", scene->ambient->intensity);
		printf("Color: R=%.0f, G=%.0f, B=%.0f\n", 
			scene->ambient->color.r,
			scene->ambient->color.g,
			scene->ambient->color.b);
	} else {
		printf("\n[Ambient Light] Not set!\n");
	}

	// Check Camera
	if (scene->camera) {
		printf("\n[Camera]\n");
		printf("Position: (%.2f, %.2f, %.2f)\n", 
			scene->camera->position.x,
			scene->camera->position.y,
			scene->camera->position.z);
		printf("Direction: (%.2f, %.2f, %.2f)\n",
			scene->camera->direction.x,
			scene->camera->direction.y,
			scene->camera->direction.z);
		printf("FOV: %.2f\n", scene->camera->fov);
	} else {
		printf("\n[Camera] Not set!\n");
	}

	// Check Lights
	printf("\n[Lights] Count: %zu\n", vector_size(&scene->lights_vec));
	for (size_t i = 0; i < vector_size(&scene->lights_vec); i++) {
		t_light *light = (t_light *)vector_at(&scene->lights_vec, i);
		printf("Light %zu:\n", i + 1);
		printf("  Position: (%.2f, %.2f, %.2f)\n",
			light->position.x,
			light->position.y,
			light->position.z);
		printf("  Intensity: %.2f\n", light->intensity);
		printf("  Color: R=%.0f, G=%.0f, B=%.0f\n",
			light->color.r,
			light->color.g,
			light->color.b);
	}

	// Check Spheres
	printf("\n[Spheres] Count: %zu\n", get_sphere_count(&scene->objects));
	for (size_t i = 0; i < get_sphere_count(&scene->objects); i++) {
		t_sphere *sphere = get_sphere(&scene->objects, i);
		printf("Sphere %zu:\n", i + 1);
		printf("  Position: (%.2f, %.2f, %.2f)\n",
			sphere->position.x,
			sphere->position.y,
			sphere->position.z);
		printf("  Radius: %.2f\n", sphere->radius);
		printf("  Color: R=%.0f, G=%.0f, B=%.0f\n",
			sphere->color.r,
			sphere->color.g,
			sphere->color.b);
	}

	// Check Planes
	printf("\n[Planes] Count: %zu\n", get_plane_count(&scene->objects));
	for (size_t i = 0; i < get_plane_count(&scene->objects); i++) {
		t_plane *plane = get_plane(&scene->objects, i);
		printf("Plane %zu:\n", i + 1);
		printf("  Position: (%.2f, %.2f, %.2f)\n",
			plane->position.x,
			plane->position.y,
			plane->position.z);
		printf("  Normal: (%.2f, %.2f, %.2f)\n",
			plane->normal.x,
			plane->normal.y,
			plane->normal.z);
		printf("  Color: R=%.0f, G=%.0f, B=%.0f\n",
			plane->color.r,
			plane->color.g,
			plane->color.b);
	}

	// Check Cylinders
	printf("\n[Cylinders] Count: %zu\n", get_cylinder_count(&scene->objects));
	for (size_t i = 0; i < get_cylinder_count(&scene->objects); i++) {
		t_cylinder *cylinder = get_cylinder(&scene->objects, i);
		printf("Cylinder %zu:\n", i + 1);
		printf("  Position: (%.2f, %.2f, %.2f)\n",
			cylinder->position.x,
			cylinder->position.y,
			cylinder->position.z);
		printf("  Orientation: (%.2f, %.2f, %.2f)\n",
			cylinder->orientation.x,
			cylinder->orientation.y,
			cylinder->orientation.z);
		printf("  Diameter: %.2f\n", cylinder->diameter);
		printf("  Height: %.2f\n", cylinder->height);
		printf("  Color: R=%.0f, G=%.0f, B=%.0f\n",
			cylinder->color.r,
			cylinder->color.g,
			cylinder->color.b);
	}
	printf("\n=== End Scene Debug Information ===\n\n");
	
	scene->data->camera = scene->camera;
	scene->data->scene = scene;  // Set the scene pointer
	scene->camera->orientation = vec_normalize(scene->camera->direction);
	
	// Initialize window and image
	init_window_and_image(scene->data);
	
	// Initial render
	render(scene->data);
	
	// Set up key hook
	mlx_key_hook(scene->data->mlx, key_hook, scene);
	
	// Main loop
	mlx_loop(scene->data->mlx);
	
	// Cleanup
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
