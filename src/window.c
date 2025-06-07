#include <stdio.h>
#include <math.h>
#include "../includes/entries.h"
#include "../includes/ray_tracing.h"

void render(t_data *data);

int key_hook(int keycode, void *param)
{
    t_data *data = (t_data *)param;

    float move_speed = 1.0;
    t_vec3_struct forward = data->camera->orientation;
    t_vec3_struct right = (t_vec3_struct){forward.z, 0, -forward.x};

    if (keycode == 65307) 
        exit(0);
    if (keycode == KEY_UP)
    {
        data->camera->position = vec_add(data->camera->position, vec_scale(forward, move_speed));
        printf("Camera position: (%f, %f, %f)\n", data->camera->position.x, data->camera->position.y, data->camera->position.z);
    }
    else if (keycode == KEY_DOWN)
        data->camera->position = vec_substract(data->camera->position, vec_scale(forward, move_speed));
    else if (keycode == KEY_LEFT)
        data->camera->position = vec_substract(data->camera->position, vec_scale(right, move_speed));
    else if (keycode == KEY_RIGHT)
        data->camera->position = vec_add(data->camera->position, vec_scale(right, move_speed));

    render(data);
    return 0;
}


void render(t_data *data)
{
    for (int y = 0; y < data->height; y++)
    {
        for (int x = 0; x < data->width; x++)
        {
            t_color_struct color;
            mainImage((t_vec2_struct){x, y}, data->width, data->height, &color, data->camera);

            int ir = (int)fminf(fmaxf(color.r, 0.0f), 255.0f);
            int ig = (int)fminf(fmaxf(color.g, 0.0f), 255.0f);
            int ib = (int)fminf(fmaxf(color.b, 0.0f), 255.0f);
            int pixel = (ir << 16) | (ig << 8) | ib;
            int offset = y * data->size_line + x * (data->bpp / 8);
            *(int *)(data->img_data + offset) = pixel;
        }
    }

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

