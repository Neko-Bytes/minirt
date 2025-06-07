/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:11:26 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/07 17:37:37 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool parse_file(int fd, t_scene *scene) 
{
  char *line;
  char *trim;

  line = get_next_line(fd);
  while(line)
  {
    trim = ft_strtrim(line, " \t\n");
    gc_free(line);
    if(!trim)
      return (false);
    if(!trim[0] || ft_strncmp(line, "\n", 1) == 0)
    {
      gc_free(trim);
      line = get_next_line(fd);
      continue;
    }
    parse_elements(trim, scene);
    gc_free(trim);
    line = get_next_line(fd);
  }
}

bool parse_elements(char *trim, t_scene *scene)
{
  char **tokens;

  tokens = ft_split(trim, ' ');
  if(!tokens || !tokens[0])
    return (false);
  if(!ft_strncmp(tokens[0], "A", 1) && !parse_ambience(scene, tokens))
    return (false);
  else if(!ft_strncmp(tokens[0], "C", 1) && !parse_camera(scene, tokens))
      return (false);
  else if(!ft_strncmp(tokens[0], "L", 1) && !parse_light(scene, tokens))
      return (false);
  else if(!ft_strncmp(tokens[0], "sp", 2) && !parse_sphere(scene, tokens))
    return (false);
  else if(!ft_strncmp(tokens[0], "cy", 2) && !parse_cylinder(scene, tokens))
      return (false);
  else if(!ft_strncmp(tokens[0], "pl", 2) && !parse_plane(scene, tokens))
      return (false);
}
