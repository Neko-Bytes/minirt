#ifndef KEYS_H
#define KEYS_H

#include "entries.h"
#include "intersect.h"
#include "object_array.h"
#include "../includes/window.h"
#include "../src/test/test.h"

// MLX42 key codes
#define KEY_ESC MLX_KEY_ESCAPE
#define KEY_A MLX_KEY_A
#define KEY_D MLX_KEY_D
#define KEY_PLUS MLX_KEY_EQUAL
#define KEY_MINUS MLX_KEY_MINUS
#define KEY_R MLX_KEY_R
#define KEY_UP MLX_KEY_UP
#define KEY_DOWN MLX_KEY_DOWN
#define KEY_LEFT MLX_KEY_LEFT
#define KEY_RIGHT MLX_KEY_RIGHT

void	handle_camera_movement(int keycode, t_data *data, float move_speed);
void	handle_camera_rotation(int keycode, t_data *data, float angle);
void	key_hook(mlx_key_data_t keydata, void *param);

#endif