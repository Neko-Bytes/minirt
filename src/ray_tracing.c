#include <math.h>
#include "../includes/entries.h"
#include "../includes/vector_ops.h"

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
        return true;
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
    if (intersect(direction, &refl))
    {
        return (t_color_struct){
            sphere.color.r * light.intensity * refl,
            sphere.color.g * light.intensity * refl,
            sphere.color.b * light.intensity * refl};
    }

    return (t_color_struct){0, 0, 0};
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
