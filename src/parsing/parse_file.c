/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:11:26 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:35:22 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <errno.h>

static void	free_tokens(char **tok);
static char *safe_gnl(int fd, t_scene *scene);

bool parse_file(int fd, t_scene *scene) 
{
  char *line;
  char *trim;

  // Initialize the object vector with a reasonable initial capacity
  init_object_vector(&scene->objects, 10);
  // Initialize the lights vector
  vector_init(&scene->lights_vec, sizeof(t_light), 5);

  while (1)
  {
    line = safe_gnl(fd, scene);
    if (!line)
      break;
    trim = ft_strtrim(line, " \t\n");
    if (!trim)
      print_error("Memory allocation failed\n", scene->data);
    if (trim[0] != '\0')
      parse_elements(trim, &scene);
    gc_free(trim);
    gc_free(line);
  }

  return (true);
}

static char *safe_gnl(int fd, t_scene *scene)
{
  char *line;
  // static int count = 0;

  errno = 0;
  line = get_next_line(fd);
  // count++;
  if(!line && errno != 0)
    print_error("Issue with reading line\n", scene->data);
  return (line);
}

bool parse_elements(char *trim, t_scene **scene)
{
  char **tokens;

  // printf("trim: %s\n", trim);
  tokens = ft_split(trim, ' ');
  if(!tokens || !tokens[0])
      print_error("Issue with tokens\n", (*scene)->data);
  tokens_counter(tokens);
  if(!ft_strncmp(tokens[0], "A", 1) && parse_ambience(scene, tokens))
    return (true);
  else if(!ft_strncmp(tokens[0], "C", 1) && parse_camera(scene, tokens))
      return (true);
  else if(!ft_strncmp(tokens[0], "L", 1) && parse_light(scene, tokens))
      return (true);
  else if(!ft_strncmp(tokens[0], "sp", 2) && parse_sphere(scene, tokens))
    return (true);
  else if(!ft_strncmp(tokens[0], "cy", 2) && parse_cylinder(scene, tokens))
      return (true);
  else if(!ft_strncmp(tokens[0], "pl", 2) && parse_plane(scene, tokens))
      return (true);
  else
      print_error("Unkown type of element found!\n", (*scene)->data);
  free_tokens(tokens);
  return (false);
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
