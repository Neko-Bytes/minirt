#include "../../includes/intersect.h"
#include "../../includes/entries.h"
#include "../../includes/light.h"
#include "../../includes/vector_ops.h"
#include "../../includes/object_array.h"
// #include <cstddef>

#define BIAS 0.001f

float vec_length(t_vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

bool isShadow(const t_scene *scene, t_vec3 point, t_light *light, float closest_t) {
    if (!scene)
        return false;

    t_vec3 light_dir = vec_substract(light->position, point);
    float light_dist;
    light_dist = vec_length(light_dir);
    light_dir = vec_normalize(light_dir);

    // Check for intersection with any object in the scene
    for (size_t i = 0; i < get_sphere_count(&scene->objects); i++) {
        float t = 0.0f, local_refl = 1.0f;
        t_sphere *sphere = get_sphere(&scene->objects, i);
        if (intersectSphere(sphere, point, light_dir, &local_refl, &t)) {
            if (t > BIAS && t < light_dist && t < closest_t) {
                return true;
            }
        }
    }

    for (size_t i = 0; i < get_plane_count(&scene->objects); i++) {
        float t = 0.0f;
        t_plane *plane = get_plane(&scene->objects, i);
        if (intersectPlane(plane, point, light_dir, &t)) {
            if (t > BIAS && t < light_dist && t < closest_t) {
                return true;
            }
        }
    }

    for (size_t i = 0; i < get_cylinder_count(&scene->objects); i++) {
        float t = 0.0f, local_refl = 1.0f;
        t_cylinder *cylinder = get_cylinder(&scene->objects, i);
        if (intersectCylinder(cylinder, point, light_dir, &local_refl, &t)) {
            if (t > BIAS && t < light_dist && t < closest_t) {
                return true;
            }
        }
    }

    return false;
}