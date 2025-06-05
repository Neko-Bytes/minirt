#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "../includes/entries.h"
#include "../includes/ray_tracing.h"

void initImage()
{
    int width = 800;
    int height = 600;
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, width, height, "miniRT");
    void *img = mlx_new_image(mlx, width, height);

    int bpp, size_line, endian;
    char *img_data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            t_color_struct color;
            mainImage((t_vec2_struct){x, y}, width, height, &color);

            int ir = (int)fminf(fmaxf(color.r, 0.0f), 255.0f);
            int ig = (int)fminf(fmaxf(color.g, 0.0f), 255.0f);
            int ib = (int)fminf(fmaxf(color.b, 0.0f), 255.0f);
            int pixel = (ir << 16) | (ig << 8) | ib;
            int offset = y * size_line + x * (bpp / 8);
            *(int *)(img_data + offset) = pixel;
        }
    }

    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
    printf("Image initialized.\n");
} 