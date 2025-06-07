#include <stdio.h>
#include <math.h>
#include "../includes/entries.h"
#include "../includes/ray_tracing.h"
#include "../includes/window.h"

void handle_camera_movement(int keycode, t_data *data, float move_speed)
{
    t_vec3_struct forward = data->camera->orientation;
    t_vec3_struct right = (t_vec3_struct){forward.z, 0, -forward.x};

    if (keycode == KEY_UP)
    {
        data->camera->position = vec_add(data->camera->position, vec_scale(forward, move_speed));
        printf("Camera position: (%f, %f, %f)\n", data->camera->position.x, data->camera->position.y, data->camera->position.z);
    }
    else if (keycode == KEY_DOWN)
    {
        data->camera->position = vec_substract(data->camera->position, vec_scale(forward, move_speed));
    }
    else if (keycode == KEY_LEFT)
    {
        data->camera->position = vec_substract(data->camera->position, vec_scale(right, move_speed));
    }
    else if (keycode == KEY_RIGHT)
    {
        data->camera->position = vec_add(data->camera->position, vec_scale(right, move_speed));
    }
}

void handle_camera_rotation(int keycode, t_data *data, float angle)
{
    if (keycode == KEY_A || keycode == KEY_D)
    {
        t_vec3_struct center = vec_add(data->camera->position, vec_scale(data->camera->orientation, 0.2f));
        t_vec3_struct dir = vec_substract(data->camera->position, center);

        if (keycode == KEY_A)
            dir = rotate_y(dir, -angle);
        else if (keycode == KEY_D)
            dir = rotate_y(dir, angle);

        data->camera->position = vec_add(center, dir);
        data->camera->orientation = vec_normalize(vec_substract(center, data->camera->position));
    }
}

int key_hook(int keycode, void *param)
{
    static float angle = 0.2; // Rotation angle in radians
    t_data *data = (t_data *)param;

    float move_speed = 1.0;

    if (keycode == KEY_ESC)
        exit(0);
    else
    {
        handle_camera_movement(keycode, data, move_speed);
        handle_camera_rotation(keycode, data, angle);
    }

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

t_vec3_struct rotate_y(t_vec3_struct v, float angle)
{
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);

    return (t_vec3_struct){
        v.x * cos_a + v.z * sin_a,
        v.y,
        -v.x * sin_a + v.z * cos_a};
}

t_vec3_struct rotate_x(t_vec3_struct v, float angle)
{
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);

    return (t_vec3_struct){
        v.x,
        v.y * cos_a - v.z * sin_a,
        v.y * sin_a + v.z * cos_a};
}
