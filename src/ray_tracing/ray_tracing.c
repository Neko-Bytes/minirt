/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:19:59 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/16 21:54:27 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/entries.h"
#include "../includes/vector_ops.h"
#include "../includes/object_array.h"
#include "../includes/light.h"
// test included
#include "test/test.h"

t_vec3 sphere_normal(t_sphere s, t_vec3 p) {
    return vec_normalize(vec_substract(p, s.position));
}

t_vec3 cylinder_normal(t_cylinder c, t_vec3 p) {
    t_vec3 ca = c.orientation; // axis (normalized)
    t_vec3 cp = vec_substract(p, c.position);
    float projection = dot_product(cp, ca);
    t_vec3 projected = vec_scale(ca, projection);
    t_vec3 normal = vec_substract(cp, projected);
    return vec_normalize(normal);
}


t_color rayTracing(t_vec3 direction, t_scene *scene) {
    t_color final_color = {0, 0, 0};
    float refl = 1.0f;
    (void)refl;
    int hit_type = 0; 
    int hit_index = -1;
    float closest_t = INFINITY;

    if (!scene || !scene->camera) {
        fprintf(stderr, "ERROR: scene or camera is NULL!\n");
        exit(1);
    }
    
    t_vec3 ray_origin = scene->camera->position;
    
    for (int i = 0; i < scene->objects.pl_count; ++i) {
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

    for (int i = 0; i < scene->objects.sp_count; ++i) {
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

    for (int i = 0; i < scene->objects.cy_count; ++i) {
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

    t_vec3 hit_point = vec_add(ray_origin, vec_scale(direction, closest_t));

    t_vec3 normal;
    if (hit_type == 1) {
        normal = sphere_normal(scene->objects.spheres[hit_index], hit_point);
    } else if (hit_type == 2) {
        normal = scene->objects.planes[hit_index].normal;
    } else if (hit_type == 3) {
        normal = cylinder_normal(scene->objects.cylinders[hit_index], hit_point);
    }

    t_color base_color;
    if (hit_type == 1) {
        base_color = scene->objects.spheres[hit_index].color;
    } else if (hit_type == 2) {
        base_color = scene->objects.planes[hit_index].color;
    } else if (hit_type == 3) {
        base_color = scene->objects.cylinders[hit_index].color;
    }

    // Shadow check — ONLY NOW
    bool in_shadow = isShadow(scene, hit_point, closest_t);

    if (hit_type != 0) {
        final_color = compute_diffuse(hit_point, normal, scene->lights[0], base_color);
    } 

    if (in_shadow) {
        final_color = 
        (t_color){
            final_color.r * 0.5f,
            final_color.g * 0.5f,
            final_color.b * 0.5f
        };
    }

    return final_color;
}


void mainImage(t_vec2 coord, int width, int height, t_color *output, t_scene *scene) {
    if (!scene->camera || !scene) {
        fprintf(stderr, "Error: Invalid input to mainImage.\n");
        exit (1);
    }

    t_vec2 uv = {
        (coord.x / (float)width) * 2.0f - 1.0f,
        (coord.y / (float)height) * 2.0f - 1.0f
    };
    uv.x *= (float)width / (float)height;
    uv.y = -uv.y;

    t_vec3 direction = { uv.x, uv.y, scene->camera->zoom };
    direction = vec_substract(direction, scene->camera->position);
    direction = vec_normalize(direction);
    
    *output = rayTracing(direction, scene);
}
