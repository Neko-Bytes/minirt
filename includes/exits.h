/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:17:45 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 01:33:41 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXITS_H
#define EXITS_H

#include "entries.h"

// void fatal_error(t_error error, t_data *data);
void error_exit(t_data *data);
void print_error(char *msg, t_data *data);

#endif
