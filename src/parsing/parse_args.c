/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:59:09 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 01:48:02 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	check_extension(char *name);
static int	open_file(char *name, t_scene *scene);

bool	parse_args(int argc, char **argv, t_scene *scene)
{
	int	fd;

	if (argc != 2)
		print_error("Usage: ./miniRT <scene.rt>\n", NULL);
	check_extension(argv[1]);
	fd = open_file(argv[1], scene);
	scene->fd = fd;
	return (true);
}

static void	check_extension(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 4 || ft_strncmp(name + len - 3, ".rt", 3) != 0)
		print_error("Error: file must end in .rt\n", NULL);
}

static int	open_file(char *name, t_scene *scene)
{
	int	fd;
	(void) scene;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		print_error("Error: cannot open file\n", NULL);
	return (fd);
}
