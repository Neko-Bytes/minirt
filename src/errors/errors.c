/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:12:55 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 18:24:53 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/entries.h"
#include "../../includes/utils.h"
#include "../../includes/object_array.h"
#include "../../libft/libft.h"
#include <unistd.h>

void	error_exit(t_data *data)
{
	if (data && data->mlx)
	{
		mlx_terminate(data->mlx);
	}
	if (data && data->scene)
	{
		free_object_vector(&data->scene->objects);
		vector_free(&data->scene->lights_vec);
	}
	gc_free_all();
	ft_putstr_fd(RED "Exited :(\n" RESET, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	print_error(char *msg, t_data *data)
{
	if (!msg)
	{
		ft_putstr_fd(RED "\n[ERROR]: Unknown error\n" RESET, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(RED "\n[ERROR]: " RESET, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	ft_putstr_fd(RED "\nClosing miniRT ...\n" RESET, STDOUT_FILENO);
	error_exit(data);
}
