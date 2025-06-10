#ifndef WINDOW_H
# define WINDOW_H

#include "keys.h"

void render(t_data *data);
t_vec3 rotate_y(t_vec3 v, float angle);
t_vec3 rotate_x(t_vec3 v, float angle);

#endif 