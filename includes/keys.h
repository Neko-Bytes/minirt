#ifndef KEYS_H
#define KEYS_H

#include "entries.h"
#include "intersect.h"
#include "object_array.h"
#include "../includes/window.h"

// MLX42 key codes
#define KEY_ESC MLX_KEY_ESCAPE // Exit program
#define KEY_A MLX_KEY_A        // Rotate camera left
#define KEY_D MLX_KEY_D        // Rotate camera right
#define KEY_UP MLX_KEY_UP      // Move camera forward
#define KEY_DOWN MLX_KEY_DOWN  // Move camera backward
#define KEY_LEFT MLX_KEY_LEFT  // Move camera left
#define KEY_RIGHT MLX_KEY_RIGHT // Move camera right

void	handle_camera_movement(int keycode, t_data *data, float move_speed);
void	handle_camera_rotation(int keycode, t_data *data, float angle);
void	key_hook(mlx_key_data_t keydata, void *param);
void	game_loop(void *param);
#endif