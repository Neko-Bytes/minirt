/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Home <Home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:59:09 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 13:57:46 by Home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	check_extension(char *name, t_scene *scene);

bool	parse_args(int argc, char **argv, t_scene *scene)
{
	if (argc != 2)
		print_error("Usage: ./miniRT <scene.rt>\n", scene->data);
	check_extension(argv[1], scene);
	return (true);
}

static void	check_extension(char *name, t_scene *scene)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 4 || ft_strncmp(name + len - 3, ".rt", 3) != 0)
		print_error("Error: file must end in .rt\n", scene->data);
}