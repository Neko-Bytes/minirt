#ifndef KEYS_H
#define KEYS_H

#include "entries.h"
#include "intersect.h"
#include "object_array.h"
#include "../includes/window.h"
#include "../src/test/test.h"


#define KEY_ESC 53
#define KEY_A 0
#define KEY_D 2
#define KEY_PLUS 43
#define KEY_MINUS 45
#define KEY_R 15
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124

void	handle_camera_movement(int keycode, t_data *data, float move_speed);
void	handle_camera_rotation(int keycode, t_data *data, float angle);
int	key_hook(int keycode, void *param);

#endif