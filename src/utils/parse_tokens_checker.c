/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:06:37 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/29 20:15:29 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include <stdbool.h>
#include <unistd.h>

static bool	int_checker(const char *s)
{
	int	i;
	int	len;

	if (!s || s[0] == '\0')
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	len = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		len++;
		i++;
	}
	if (len == 0 || s[i] != '\0')
		return (false);
	return (true);
}

static bool	scan_float(const char *s, int *dot, int *pre, int *post)
{
	int	i;

	i = 0;
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

static bool	float_checker(const char *s)
{
	int	dot;
	int	pre;
	int	post;

	if (!s || s[0] == '\0')
		return (false);
	dot = 0;
	pre = 0;
	post = 0;
	if (s[0] == '+' || s[0] == '-')
		s++;
	if (!scan_float(s, &dot, &pre, &post))
		return (false);
	if (pre + post == 0 || (dot && post == 0))
		return (false);
	return (true);
}

void	tokens_checker(const char *asset, char **tokens, t_scene **scene)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		i++;
		if (int_checker(tokens[i-1]))
			continue;
		else if (float_checker(tokens[i-1]))
			continue;
		else
			print_error(ft_strjoin(asset, "Invalid float or int provided\n"), (*scene)->data);
	}
	return;
}

void one_token_checker(const char *asset, char **token, t_scene **scene)
{
	if(int_checker(*token))
		return;
	else if(float_checker(*token))
			return;
	else
			print_error(ft_strjoin(asset, "Invalid float or int provided\n"), (*scene)->data);
}
