#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include <stdbool.h>
#include "../includes/entries.h"

static inline Vec3 vec_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline Vec3 vec_substract(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline Vec3 vec_scale(Vec3 v, float s) {
    return (Vec3){v.x * s, v.y * s, v.z * s};
}

static inline float dot_product(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline Vec3 vec_normalize(Vec3 v) {
    float len = sqrtf(dot_product(v, v));
    return (len == 0.0f) ? (Vec3){0, 0, 0} : vec_scale(v, 1.0f / len);
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

bool intersect(Vec3 direction, float *refl)
{
    Vec3 oc = vec_substract(camera.position, sphere.position);
    float half_b = dot_product(oc, direction);
    float c = dot_product(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = half_b * half_b - c;

    if (discriminant < 0.0f) return false;

    float sqrt_disc = sqrtf(discriminant);
    float t = -half_b - sqrt_disc;
    if (t < 0.0f) t = -half_b + sqrt_disc;
    if (t < 0.0f) return false;

    Vec3 Phit = vec_add(camera.position, vec_scale(direction, t));
    Vec3 normal = vec_normalize(vec_substract(Phit, sphere.position));
    *refl = -dot_product(direction, normal);

    return true;
}


Color rayTracing(Vec3 direction)
{
    float refl = 1;
    if (intersect(direction, &refl)) // Pass address of refl
    {
        return (Color){
            sphere.color.r * light.intensity * refl,
            sphere.color.g * light.intensity * refl,
            sphere.color.b * light.intensity * refl};
    }

    return (Color){0, 0, 0}; // Return black if no intersection
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
            Color color;
            mainImage((Vec2){x, y}, width, height, &color); // Pass color by pointer

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

void mainImage(Vec2 coord, int width, int height, Color *output)
{
    Vec3 ray_origin = camera.position;
    Vec2 uv = {
        (coord.x / (float)width) * 2.0f - 1.0f,
        (coord.y / (float)height) * 2.0f - 1.0f};
    uv.x *= (float)width / (float)height;
    uv.y = -uv.y;

    Vec3 direction = (Vec3){uv.x, uv.y, camera.zoom};
    direction = vec_substract(direction, ray_origin);
    direction = vec_normalize(direction);
    *output = rayTracing(direction);
}