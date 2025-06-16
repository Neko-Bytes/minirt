/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:57:48 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 08:58:49 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void tokens_printer(char **tokens);

int tokens_counter(char **tokens)
{
    int i;

    if(!tokens || !*tokens)
        return (-1);
    i = 0;
    while(tokens[i])
    {
        i++;
    }
    // tokens_printer(tokens);
    return (i);
}

void tokens_printer(char **tokens)
{
    int i;

    i = 0;
    while(tokens[i])
    {
        printf("%d: %s\n",i, tokens[i]);
        i++;
    }
}
