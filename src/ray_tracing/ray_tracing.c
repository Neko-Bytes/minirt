/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:19:59 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/10 17:57:18 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    for (int i = 0; i < scene->objects.plane_count; ++i) {
        float t = 0.0f, local_refl = 1.0f;
        if (intersectPlane(&scene->objects.planes[i], ray_origin, direction, &t)) {
            if (t < closest_t) {
                closest_t = t;
                refl = local_refl;
                hit_type = 2;
                hit_index = i;
            }
        }
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

    for (int i = 0; i < scene->objects.cylinder_count; ++i) {
        float t = 0.0f, local_refl = 1.0f;
        if (intersectCylinder(&scene->objects.cylinders[i], ray_origin, direction, &local_refl, &t)) {
            if (t < closest_t) {
                closest_t = t;
                refl = local_refl;
                hit_type = 3;
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
    else if (hit_type == 3) {
        t_cylinder *cylinder = &scene->objects.cylinders[hit_index];
        final_color.r += cylinder->color.r * scene->lights[0].intensity * refl;
        final_color.g += cylinder->color.g * scene->lights[0].intensity * refl;
        final_color.b += cylinder->color.b * scene->lights[0].intensity * refl;
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
