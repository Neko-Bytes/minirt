/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:12:55 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 01:29:46 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exits.h"
#include <unistd.h>

// static const char  *errors[] = {
//        "Memory allocation error.\n",
//        "Invalid arguments. Usage: ./miniRT [.rt file/path]\n",
//        "Could not open or read file.\n",
//        "Failed to create MLX window.\n",
//        "Failed to create MLX image.\n",
//        "Scene data error.\n",
//        "Scene must include an ambient light.\n",
//        "Scene must include a camera.\n",
//        "Scene may only contain one light object.\n",
//        "Inputs for cylinder is invalid\n"
//        "Inputs for plane is invalid\n"
//        "Inputs for sphere is invalid\n"
// };

// void fatal_error(t_error error, t_data *data)
// {
//    ft_putstr_fd(RED "[ERROR]: " RESET, STDERR_FILENO);
//    ft_putstr_fd(errors[error], STDERR_FILENO);
//    ft_putstr_fd("\n", STDERR_FILENO);
//    ft_putstr_fd(RED "\n Closing miniRT ...\n" RESET, STDOUT_FILENO);
//    error_exit(data);
// }

void error_exit(t_data *data)
{
   // MLX windows to be closed
   gc_free_all();
   ft_putstr_fd(RED "\n Exited :(\n" RESET, STDOUT_FILENO);
   exit(EXIT_FAILURE);
}

void print_error(char *msg, t_data *data)
{
   ft_putstr_fd(RED "[ERROR]: " RESET, STDERR_FILENO);
   ft_putstr_fd(msg, STDERR_FILENO);
   ft_putstr_fd("\n", STDERR_FILENO);
   ft_putstr_fd(RED "\n Closing miniRT ...\n" RESET, STDOUT_FILENO);
   error_exit(data);
}
