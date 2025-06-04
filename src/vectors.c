#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include <stdbool.h>
#include "../includes/entries.h"

Vec3 vec_normalize(Vec3 v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (len == 0.0f)
        return (Vec3){0, 0, 0}; // Avoid division by zero
    return (Vec3){v.x / len, v.y / len, v.z / len};
}

Vec3 vec_substract(Vec3 vec_a, Vec3 vec_b)
{
    return (Vec3){
        vec_a.x - vec_b.x,
        vec_a.y - vec_b.y,
        vec_a.z - vec_b.z};
}

Vec3 vec_add(Vec3 vec_a, Vec3 vec_b)
{
    return (Vec3){
        vec_a.x + vec_b.x,
        vec_a.y + vec_b.y,
        vec_a.z + vec_b.z};
}

Vec3 vec_scale(Vec3 v, float t)
{
    return (Vec3){v.x * t, v.y * t, v.z * t};
}

float dot_product(Vec3 vec_a, Vec3 vec_b)
{
    return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
}

bool solveQuadratic(float a, float b, float c, float *t1, float *t2)
{
    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
    {
        return false; // No real roots, no intersection
    }
    if (discriminant == 0.0f)
    {
        *t2 = (-b) / (2.0f * a); // One real root
        *t1 = *t2;               // Assign the same value to t1
        if (*t2 < 0.0f)
        {
            return false; // Intersection is behind the camera
        }
        return true; // One intersection point
    }

    *t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
    *t2 = (-b - sqrtf(discriminant)) / (2.0f * a);
    if (*t1 < 0.0f && *t2 < 0.0f)
    {
        return false; // Both intersections are behind the camera
    }
    return true; // Two intersection points or one in front of the camera
}

bool intersect(Vec3 direction, float refl)
{
    float a = dot_product(direction, direction);
    float b = 2.0f * dot_product(vec_substract(camera.position, sphere.position), direction);
    float c = dot_product(vec_substract(camera.position, sphere.position), vec_substract(camera.position, sphere.position)) - sphere.radius * sphere.radius;

    float t1, t2;
    if (solveQuadratic(a, b, c, &t1, &t2))
    {
        if (t1 < 0.0f && t2 < 0.0f)
        {
            return false;
        }
        return true;
    }

    return false;
}

Color rayTracing(Vec3 direction)
{

    float refl = 1;
    if (intersect(direction, refl)) // Check if the ray intersects with the sphere
    {
        return  (Color){
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
    uv.x *= (float)width / (float)height; // Adjust aspect ratio

    Vec3 direction = (Vec3){uv.x, uv.y, camera.zoom};
    direction = vec_substract(direction, ray_origin);
    direction = vec_normalize(direction);
    *output = rayTracing(direction);
}