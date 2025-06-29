/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:12:55 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 14:32:53 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/entries.h"
#include "../../includes/object_array.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"
#include <unistd.h>

void	error_exit(t_data *data)
{
	close(data->scene->fd);
	free_mlx(data);
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

void	free_mlx(t_data *data)
{
	if (data && data->mlx)
	{
		if (data->img)
			mlx_delete_image(data->mlx, data->img);
		mlx_terminate(data->mlx);
	}
	return ;
}
