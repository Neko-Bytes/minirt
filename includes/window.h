#ifndef WINDOW_H
# define WINDOW_H

#include "keys.h"


void	render(t_scene *scene);
t_vec3 rotate_y(t_vec3 v, float angle);
t_vec3 rotate_x(t_vec3 v, float angle);

#endif 