#include "../includes/light.h"
#include "../includes/intersect.h"

float vec_length(t_vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
bool isShadow(const t_scene *scene, t_vec3 point, float closest_t) {
    const float EPSILON = 0.001f;
    t_light *light = &scene->lights[0];
    t_vec3 light_dir = vec_normalize(vec_substract(light->position, point));
    float distance_to_light = vec_length(vec_substract(light->position, point));
    t_vec3 shadow_ray_origin = vec_add(point, vec_scale(light_dir, EPSILON));
    float t_out, refl;

    // Check all spheres
    for (int i = 0; i < scene->objects.sphere_count; i++) {
        if (intersectSphere(&scene->objects.spheres[i], shadow_ray_origin, light_dir, &refl, &t_out)) {
            if (t_out > EPSILON && t_out < distance_to_light && t_out < closest_t) {
                return true;
            }
        }
    }

    // Check all planes
    for (int i = 0; i < scene->objects.plane_count; i++) {
        if (intersectPlane(&scene->objects.planes[i], shadow_ray_origin, light_dir, &t_out)) {
            if (t_out > EPSILON && t_out < distance_to_light && t_out < closest_t) {
                return true;
            }
        }
    }

    // Check all cylinders
    for (int i = 0; i < scene->objects.cylinder_count; i++) {
        if (intersectCylinder(&scene->objects.cylinders[i], shadow_ray_origin, light_dir, &refl, &t_out)) {
            if (t_out > EPSILON && t_out < distance_to_light && t_out < closest_t) {
                return true;
            }
        }
    }

    return false;
}
