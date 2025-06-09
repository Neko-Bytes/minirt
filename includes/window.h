#ifndef WINDOW_H
# define WINDOW_H

void render(t_data *data);
int key_hook(int keycode, void *param);
t_vec3 rotate_y(t_vec3 v, float angle);
t_vec3 rotate_x(t_vec3 v, float angle);

#endif 