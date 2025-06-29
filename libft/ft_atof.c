/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:58:17 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/19 19:25:08 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

bool	float_checker(const char *s);

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

	if(!float_checker(text))
	{
		return (0.0);
	}
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

static bool	scan_float(const char *s, int *dot, int *pre, int *post)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == '.')
		{
			if (++(*dot) > 1)
				return (false);
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			if (*dot == 0)
				(*pre)++;
			else
				(*post)++;
		}
		else
			return (false);
		i++;
	}
	return (true);
}

bool	float_checker(const char *s)
{
	int	dot;
	int	pre;
	int	post;

	if (s == NULL || s[0] == '\0')
		return (false);
	dot = 0;
	pre = 0;
	post = 0;
	if (!scan_float(s, &dot, &pre, &post))
		return (false);
	if (pre == 0 || (dot == 1 && post == 0))
		return (false);
	return (true);
}
