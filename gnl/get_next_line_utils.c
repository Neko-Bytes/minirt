/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:04:45 by mknsteja          #+#    #+#             */
/*   Updated: 2025/06/16 09:21:35 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

size_t	gnl_strlen(const char *string)
{
	int	length;

	if (!string)
		return (0);
	length = 0;
	while (string[length])
	{
		length++;
	}
	return ((size_t)length);
}

char	*gnl_strdup(const char *src)
{
	char	*new_string;
	int		i;

	if (!src)
		return (NULL);
	new_string = gc_malloc(sizeof(char) * gnl_strlen(src) + 1);
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		new_string[i] = src[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*gnl_strchr(const char *string, int character)
{
	char	*str;

	if (!string)
		return (NULL);
	str = (char *)string;
	while (*str)
	{
		if (*str == (unsigned char)character)
			return (str);
		str++;
	}
	if ((unsigned char)character == '\0')
		return (str);
	return (NULL);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = gnl_strlen(s);
	if (start >= s_len)
		return (gnl_strdup(""));
	i = 0;
	if (len > s_len - start)
		len = s_len - start;
	str = gc_malloc((sizeof(char) * len) + 1);
	if (str == NULL)
		return (NULL);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strdup(s2));
	else if (!s2)
		return (gnl_strdup(s1));
	string = gc_malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (string == NULL)
		return (NULL);
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j])
		string[i++] = s2[j++];
	string[i] = '\0';
	return (string);
}
