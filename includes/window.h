#ifndef WINDOW_H
# define WINDOW_H

void render(t_data *data);
int key_hook(int keycode, void *param);
t_vec3_struct rotate_y(t_vec3_struct v, float angle);
t_vec3_struct rotate_x(t_vec3_struct v, float angle);

#endif 