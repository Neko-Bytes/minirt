#include <math.h>
#include "../includes/entries.h"
#include "../includes/vector_ops.h"
#include "../includes/object_array.h"
// test included
#include "test/test.h"


t_color rayTracing(t_vec3 direction, t_scene *scene) {
    t_color final_color = {0, 0, 0};
    float refl = 1.0f;
    int hit_type = 0; 
    int hit_index = -1;
    float closest_t = INFINITY;

    t_vec3 ray_origin = scene->camera->position;

    float plane_t = INFINITY;
    if (scene->objects.plane_count > 0) {
        intersectPlane(&scene->objects.planes[0], ray_origin, direction, &plane_t);
    }
    if (plane_t > 0) {
        closest_t = plane_t;
        hit_type = 2;
        hit_index = 0;
    }

    for (int i = 0; i < scene->objects.sphere_count; ++i) {
        float t = 0.0f, local_refl = 1.0f;
        if (intersectSphere(&scene->objects.spheres[i], ray_origin, direction, &local_refl, &t)) {
            if (t < closest_t) {
                closest_t = t;
                refl = local_refl;
                hit_type = 1;
                hit_index = i;
            }
        }
    }

    if (hit_type == 1) {
        t_sphere *sphere = &scene->objects.spheres[hit_index];
        final_color.r = sphere->color.r * scene->lights[0].intensity * refl;
        final_color.g = sphere->color.g * scene->lights[0].intensity * refl;
        final_color.b = sphere->color.b * scene->lights[0].intensity * refl;
    }
    else if (hit_type == 2) {
        t_plane *plane = &scene->objects.planes[hit_index];
        final_color.r += plane->color.r * scene->lights[0].intensity;
        final_color.g += plane->color.g * scene->lights[0].intensity;
        final_color.b += plane->color.b * scene->lights[0].intensity;
    }

    return final_color;
}


void mainImage(t_vec2 coord, int width, int height, t_color *output, t_camera *camera, t_scene *scene) {
    t_vec2 uv = {
        (coord.x / (float)width) * 2.0f - 1.0f,
        (coord.y / (float)height) * 2.0f - 1.0f
    };
    uv.x *= (float)width / (float)height;
    uv.y = -uv.y;

    t_vec3 direction = { uv.x, uv.y, camera->zoom };
    direction = vec_substract(direction, camera->position);
    direction = vec_normalize(direction);

    *output = rayTracing(direction, scene);
}
