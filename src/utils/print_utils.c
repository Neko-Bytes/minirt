/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:46:00 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 15:08:13 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	colorprint(t_log log, char *msg)
{
	const char	*color;

	if (log == MSG)
		color = YELLOW;
	else if (log == FAILURE || log == WARNING)
		color = RED;
	else if (log == SUCCESS)
		color = GREEN;
	ft_putstr_fd(color, 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd(RESET, 1);
}
