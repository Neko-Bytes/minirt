#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include <stdbool.h>
#include "../includes/entries.h"

// Use new type names from entries.h
static inline t_vec3_struct vec_add(t_vec3_struct a, t_vec3_struct b) {
    return (t_vec3_struct){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline t_vec3_struct vec_substract(t_vec3_struct a, t_vec3_struct b) {
    return (t_vec3_struct){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline t_vec3_struct vec_scale(t_vec3_struct v, float s) {
    return (t_vec3_struct){v.x * s, v.y * s, v.z * s};
}

static inline float dot_product(t_vec3_struct a, t_vec3_struct b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline t_vec3_struct vec_normalize(t_vec3_struct v) {
    float len = sqrtf(dot_product(v, v));
    return (len == 0.0f) ? (t_vec3_struct){0, 0, 0} : vec_scale(v, 1.0f / len);
}



bool solveQuadratic(float a, float b, float c, float *t1, float *t2)
{
    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
    {
        return false;
    }
    if (discriminant == 0.0f)
    {
        *t2 = (-b) / (2.0f * a);
        *t1 = *t2;
        if (*t2 < 0.0f)
        {
            return false;
        }
        return true; // One intersection point
    }

    *t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
    *t2 = (-b - sqrtf(discriminant)) / (2.0f * a);
    if (*t1 < 0.0f && *t2 < 0.0f)
    {
        return false;
    }
    return true;
}

bool intersect(t_vec3_struct direction, float *refl)
{
    t_vec3_struct oc = vec_substract(camera.position, sphere.position);
    float half_b = dot_product(oc, direction);
    float c = dot_product(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = half_b * half_b - c;

    if (discriminant < 0.0f) return false;

    float sqrt_disc = sqrtf(discriminant);
    float t = -half_b - sqrt_disc;
    if (t < 0.0f) t = -half_b + sqrt_disc;
    if (t < 0.0f) return false;

    t_vec3_struct Phit = vec_add(camera.position, vec_scale(direction, t));
    t_vec3_struct normal = vec_normalize(vec_substract(Phit, sphere.position));
    *refl = -dot_product(direction, normal);

    return true;
}

t_color_struct rayTracing(t_vec3_struct direction)
{
    float refl = 1;
    if (intersect(direction, &refl)) // Pass address of refl
    {
        return (t_color_struct){
            sphere.color.r * light.intensity * refl,
            sphere.color.g * light.intensity * refl,
            sphere.color.b * light.intensity * refl};
    }

    return (t_color_struct){0, 0, 0}; // Return black if no intersection
}

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
            mainImage((t_vec2_struct){x, y}, width, height, &color); // Pass color by pointer

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

void mainImage(t_vec2_struct coord, int width, int height, t_color_struct *output)
{
    t_vec3_struct ray_origin = camera.position;
    t_vec2_struct uv = {
        (coord.x / (float)width) * 2.0f - 1.0f,
        (coord.y / (float)height) * 2.0f - 1.0f};
    uv.x *= (float)width / (float)height;
    uv.y = -uv.y;

    t_vec3_struct direction = (t_vec3_struct){uv.x, uv.y, camera.zoom};
    direction = vec_substract(direction, ray_origin);
    direction = vec_normalize(direction);
    *output = rayTracing(direction);
}