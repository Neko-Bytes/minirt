/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:59:09 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/07 14:02:09 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool parse_args(int argc, char **argv) 
{
  char *dot;
  int len;

  if (argc != 2)
    return (false);
  len = ft_strlen(argv[1]);
  if(!(argv[1][len - 3] == '.' && argv[1][len - 2] == 'r' && argv[1][len - 1] == 't'))
    return (false);
  return (true);
}
