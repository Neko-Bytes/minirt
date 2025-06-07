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

bool intersectSphere(t_vec3_struct direction, float *refl, float *t_out)
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
    *t_out = t;

    return true;
}


bool intersectPlane(t_plane_struct plane, t_vec3_struct direction, t_vec3_struct *intersection_point, float *t_out)
{
    t_vec3_struct ray_to_plane = vec_substract(plane.position, camera.position);
    float denom = dot_product(plane.normal, direction);
    if (fabsf(denom) < 1e-6f)
        return false; // Ray is parallel to the plane

    float t = dot_product(ray_to_plane, plane.normal) / denom;
    if (t < 0.0f)
        return false; // Intersection is behind the camera

    *intersection_point = vec_add(camera.position, vec_scale(direction, t));
    *t_out = t;
    return true;
}

t_color_struct rayTracing(t_vec3_struct direction)
{
    float refl = 1.0f;
    float t_out = 0.0f;
    t_vec3_struct intersection_point;

    bool hit_sphere = intersectSphere(direction, &refl, &t_out);
    bool hit_plane = intersectPlane(plane, direction, &intersection_point, &t_out);

    t_color_struct final_color = {0, 0, 0};

    if (hit_plane)
    {
        final_color.r += plane.color.r * light.intensity;
        final_color.g += plane.color.g * light.intensity;
        final_color.b += plane.color.b * light.intensity;
    }

    if (hit_sphere)
    {
        final_color.r = sphere.color.r * light.intensity * refl;
        final_color.g = sphere.color.g * light.intensity * refl;
        final_color.b = sphere.color.b * light.intensity * refl;
    }

    return final_color;
}

void mainImage(t_vec2_struct coord, int width, int height, t_color_struct *output, t_camera_struct *camera)
{
    t_vec3_struct ray_origin = camera->position;
    t_vec2_struct uv = {
        (coord.x / (float)width) * 2.0f - 1.0f,
        (coord.y / (float)height) * 2.0f - 1.0f};
    uv.x *= (float)width / (float)height;
    uv.y = -uv.y;

    t_vec3_struct direction = (t_vec3_struct){uv.x, uv.y, camera->zoom};
    direction = vec_substract(direction, ray_origin);
    direction = vec_normalize(direction);
    *output = rayTracing(direction);
} 
