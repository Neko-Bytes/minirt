/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:58:17 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/10 19:06:18 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	skip_whitespace(const char **cursor)
{
	while (**cursor == ' ' || **cursor == '\t')
		(*cursor)++;
}

void	parse_fraction(const char **cursor, float *result)
{
	float	divisor;

	divisor = 10.0f;
	(*cursor)++;
	while (**cursor >= '0' && **cursor <= '9')
	{
		*result += (**cursor - '0') / divisor;
		divisor *= 10.0f;
		(*cursor)++;
	}
}

float	ft_atof(const char *text)
{
	float	result;
	float	sign;

	if (text == NULL)
		return (0.0f);
	result = 0.0f;
	sign = 1.0f;
	if (*text == '-' || *text == '+')
	{
		if (*text == '-')
			sign = -1.0f;
		text++;
	}
	while (*text >= '0' && *text <= '9')
	{
		result = result * 10.0f + (*text - '0');
		text++;
	}
	if (*text == '.')
		parse_fraction(&text, &result);
	return (result * sign);
}

