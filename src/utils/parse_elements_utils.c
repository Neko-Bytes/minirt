/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:57:48 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 14:34:38 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	tokens_counter(char **tokens)
{
	int	i;

	if (!tokens || !*tokens)
		return (-1);
	i = 0;
	while (tokens[i])
	{
		i++;
	}
	return (i);
}

char	*safe_gnl(int fd, t_scene *scene)
{
	char	*line;

	errno = 0;
	line = get_next_line(fd);
	if (!line && errno != 0)
		print_error("Issue with reading line\n", scene->data);
	return (line);
}

void	tokens_printer(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("%d: %s\n", i, tokens[i]);
		i++;
	}
}

void	free_tokens(char **tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		gc_free(tok[i]);
		i++;
	}
	gc_free(tok);
}

bool	validate_element_counts(char **tokens, t_scene **scene)
{
	if (!ft_strncmp(tokens[0], "A", 1) && (*scene)->ambient)
	{
		((*scene)->ambient->count)++;
		if ((*scene)->ambient->count > 1)
			print_error("Double occurrence of 'A' found in .rt file\n",
				(*scene)->data);
	}
	if (!ft_strncmp(tokens[0], "C", 1) && (*scene)->camera)
	{
		((*scene)->camera->count)++;
		if ((*scene)->camera->count > 1)
			print_error("Double occurrence of 'C' found in .rt file\n",
				(*scene)->data);
	}
	if (!ft_strncmp(tokens[0], "L", 1) && (*scene)->lights)
	{
		((*scene)->lights->count)++;
		if ((*scene)->lights->count > 10)
			print_error("Too many lights in .rt file\n", (*scene)->data);
	}
	return (true);
}
