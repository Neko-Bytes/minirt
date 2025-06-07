/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:11:26 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/07 14:09:19 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

bool parse_file(int fd, t_scene *scene) 
{
  char *line;
  char *trim;

  line = get_next_line(fd);
  while(line)
  {
    trim = ft_strtrim(line, " \t\n");
    if(!trim)
      return (false);
    if(ft_strncmp(line, "\n", 1) == 0)
    {
      gc_free(line);
      gc_free(trim);
      line = get_next_line(fd);
      continue;
    }
    parse_elements(trim, scene);
    gc_free(line);
    gc_free(trim);
    line = get_next_line(fd);
  }
}

void parse_elements(char *trim, t_scene *scene)
{
  
}
