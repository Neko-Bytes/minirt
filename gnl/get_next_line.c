/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:26:19 by mknsteja          #+#    #+#             */
/*   Updated: 2025/06/16 08:30:30 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*result(char *buffer_str, char **rem, char *finder);
void	assign_rem(char **rem, char *buffer_str, int bytes_read);
char	*free_all(char **buffer_str, char **rem);
char	*free_final(char **rem, char *buffer_str, int bytes_read);

char	*get_next_line(int fd)
{
	static char	*rem = NULL;
	char		*buffer_str;
	char		*finder;
	int			bytes_read;

	finder = NULL;
	buffer_str = gc_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer_str || fd < 0 || BUFFER_SIZE <= 0)
		return (free_all(&buffer_str, &rem));
	if (rem)
		finder = gnl_strchr(rem, '\n');
	if (finder)
		return (result(buffer_str, &rem, finder));
	bytes_read = read(fd, buffer_str, BUFFER_SIZE);
	// printf("buffer_str: %d\n%s\n",bytes_read, buffer_str);
	while (bytes_read > 0)
	{
		assign_rem(&rem, buffer_str, bytes_read);
		if (!rem)
			return (free_all(&buffer_str, &rem));
		finder = gnl_strchr(rem, '\n');
		if (finder)
			return (result(buffer_str, &rem, finder));
		bytes_read = read(fd, buffer_str, BUFFER_SIZE);
	}
	return (free_final(&rem, buffer_str, bytes_read));
}

char	*free_final(char **rem, char *buffer_str, int bytes_read)
{
	char	*result;

	gc_free(buffer_str);
	buffer_str = NULL;
	if (bytes_read == -1)
	{
		gc_free(*rem);
		*rem = NULL;
		return (NULL);
	}
	result = NULL;
	if (rem && *rem && (**rem != '\0'))
	{
		result = gnl_strdup(*rem);
		gc_free(*rem);
		*rem = NULL;
		return (result);
	}
	gc_free(*rem);
	*rem = NULL;
	return (NULL);
}

char	*free_all(char **buffer_str, char **rem)
{
	if (buffer_str && *buffer_str)
	{
		gc_free(*buffer_str);
		*buffer_str = NULL;
	}
	if (rem && *rem)
	{
		gc_free(*rem);
		*rem = NULL;
	}
	return (NULL);
}

char	*result(char *buffer_str, char **rem, char *finder)
{
	char	*temp_rem;
	char	*result;

	// printf("rem: %s\n", *rem);
	result = gnl_substr(*rem, 0, finder - *rem + 1);
	temp_rem = *rem;
	*rem = gnl_strdup(finder + 1);
	if (!*rem || !result)
	{
		gc_free(temp_rem);
		gc_free(result);
		return (free_all(&buffer_str, rem));
	}
	if (**rem == '\0')
	{
		gc_free(*rem);
		*rem = NULL;
	}
	gc_free(temp_rem);
	gc_free(buffer_str);
	buffer_str = NULL;
	return (result);
}

void	assign_rem(char **rem, char *buffer_str, int bytes_read)
{
	char	*temp;

	buffer_str[bytes_read] = '\0';
	temp = *rem;
	*rem = gnl_strjoin(*rem, buffer_str);
	// printf("temp: %s\nbuffer_str:%d\n%s\nrem: %s\n",temp,bytes_read,buffer_str, *rem);
	if (!*rem)
	{
		if (temp)
			gc_free(temp);
		return ;
	}
	if (temp)
		gc_free(temp);
}
