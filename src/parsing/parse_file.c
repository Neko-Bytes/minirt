/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:11:26 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 20:40:41 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	handle_element_type(char **tokens, t_scene **scene);
static void	empty_checker(int line_count, t_scene **scene);

bool	parse_file(int fd, t_scene *scene)
{
	char	*line;
	char	*trim;
	int		line_count;

	line_count = 0;
	init_object_vector(&scene->objects, 10);
	vector_init(&scene->lights_vec, sizeof(t_light), 5);
	while (1)
	{
		line = safe_gnl(fd, scene);
		if (!line)
			break ;
		trim = ft_strtrim(line, " \t\n");
		if (!trim)
			print_error("Memory allocation failed\n", scene->data);
		if (trim[0] != '\0')
			parse_elements(trim, &scene);
		gc_free(trim);
		gc_free(line);
		line_count++;
	}
	empty_checker(line_count, &scene);
	return (true);
}

bool	parse_elements(char *trim, t_scene **scene)
{
	char	**tokens;

	tokens = ft_split(trim, ' ');
	if (!tokens || !tokens[0])
		print_error("Issue with tokens\n", (*scene)->data);
	tokens_counter(tokens);
	if (handle_element_type(tokens, scene))
	{
		validate_element_counts(tokens, scene);
		free_tokens(tokens);
		return (true);
	}
	validate_element_counts(tokens, scene);
	free_tokens(tokens);
	return (false);
}

static bool	handle_element_type(char **tokens, t_scene **scene)
{
	if (!ft_strncmp(tokens[0], "A", 1) && parse_ambience(scene, tokens))
		return (true);
	else if (!ft_strncmp(tokens[0], "C", 1) && parse_camera(scene, tokens))
		return (true);
	else if (!ft_strncmp(tokens[0], "L", 1) && parse_light(scene, tokens))
		return (true);
	else if (!ft_strncmp(tokens[0], "sp", 2) && parse_sphere(scene, tokens))
		return (true);
	else if (!ft_strncmp(tokens[0], "cy", 2) && parse_cylinder(scene, tokens))
		return (true);
	else if (!ft_strncmp(tokens[0], "pl", 2) && parse_plane(scene, tokens))
		return (true);
	else
		print_error("Unkown type of element found!\n", (*scene)->data);
	return (false);
}

static void	empty_checker(int line_count, t_scene **scene)
{
	bool	status;

	status = true;
	if (!line_count)
	{
		status = false;
		colorprint(FAILURE, "Empty file!\n");
	}
	if (!(*scene)->ambient || (*scene)->ambient->count <= 0)
	{
		status = false;
		colorprint(FAILURE, "No Ambience provided\n");
	}
	if (!(*scene)->camera || (*scene)->camera->count <= 0)
	{
		status = false;
		colorprint(FAILURE, "No Camera provided\n");
	}
	if (!(*scene)->lights_vec.data || (*scene)->lights_vec.size <= 0)
	{
		status = false;
		colorprint(FAILURE, "No Lights provided\n");
	}
	if (!status)
		print_error("Please provide valid scene arguments\n", (*scene)->data);
}
