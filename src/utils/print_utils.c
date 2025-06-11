/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:46:00 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/10 19:56:25 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void colorprint(t_log log, char *msg)
{
    const char *color;

    if(log == MSG)
        color = YELLOW;
    else if(log == FAILURE || log == WARNING)
        color = RED;
    else if(log == SUCCESS)
        color = GREEN;
    ft_putstr_fd(color, 1);
    ft_putstr_fd(msg, 1);
    ft_putstr_fd(RESET, 1);
}
