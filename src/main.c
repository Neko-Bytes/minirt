#include "../includes/entries.h"
#include "../includes/window.h"
#include "../includes/vector_ops.h"
#include "../includes/ray_tracing.h"

void init_window_and_image(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->width, data->height, "miniRT");
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->img_data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);
}

int main(void)
{
    static t_camera_struct camera = {
        .position = {0, 0, -10},
        .orientation = {0, 0, 1},
        .fov = 70
    };

    t_data data;
    data.width = 800;
    data.height = 600;
    data.camera = &camera;

    init_window_and_image(&data);

    render(&data);

    mlx_key_hook(data.win, key_hook, &data);
    mlx_loop(data.mlx);

    return 0;
}
