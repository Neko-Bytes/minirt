/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:11:26 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 02:35:47 by kmummadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	free_tokens(char **tok);
static char *safe_gnl(int fd, t_scene *scene);

bool parse_file(int fd, t_scene *scene) 
{
  char *line;
  char *trim;

  line = safe_gnl(fd, scene);
  while(line)
  {
    trim = ft_strtrim(line, " \t\n");
    gc_free(line);
    if(!trim)
      print_error("Issue with trimming\n", scene->data);
    if(!trim[0] || ft_strncmp(line, "\n", 1) == 0)
    {
      gc_free(trim);
      line = safe_gnl(fd, scene);
      continue;
    }
    if(parse_elements(trim, scene))
      print_error("Issue with parsing tokens\n", scene->data);
    gc_free(trim);
    line = safe_gnl(fd, scene);
  }

  return (true);
}

static char *safe_gnl(int fd, t_scene *scene)
{
  char *line;
  line = get_next_line(fd);
  if(!line)
    print_error("Issue with reading line\n", scene->data);
  return (line);
}

bool parse_elements(char *trim, t_scene *scene)
{
  char **tokens;

  tokens = ft_split(trim, ' ');
  if(!tokens || !tokens[0])
      print_error("Issue with tokens\n", scene->data);
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
  else
      print_error("Unkown type of element found!\n", scene->data);
  free_tokens(tokens);
  return (true);
}

static void	free_tokens(char **tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		gc_free(tok[i]);
		i++;
	}
	gc_free(tok);
}
