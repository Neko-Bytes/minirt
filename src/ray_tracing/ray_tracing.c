/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:19:59 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 15:16:34 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../includes/minirt.h"
#include "../../includes/vector_ops.h"
#include "../../includes/object_array.h"
#include "../../includes/light.h"
#include "../../includes/intersect.h"

typedef struct s_hit_info {
    t_vec3 hit_point;
    t_vec3 normal;
    t_color base_color;
    float closest_t;
} t_hit_info;

typedef struct s_hit_lookup {
    int hit_type;
    int hit_index;
    t_vec3 hit_point;
} t_hit_lookup;

static void get_hit_normal_and_color(const t_scene *scene, t_hit_lookup *lookup, t_vec3 *normal, t_color *base_color)
{
    if (lookup->hit_type == 1)
    {
        t_sphere *sphere = get_sphere(&scene->objects, lookup->hit_index);
        *normal = sphere_normal(*sphere, lookup->hit_point);
        *base_color = sphere->color;
    }
    else if (lookup->hit_type == 2)
    {
        t_plane *plane = get_plane(&scene->objects, lookup->hit_index);
        *normal = plane->normal;
        *base_color = plane->color;
    }
    else if (lookup->hit_type == 3)
    {
        t_cylinder *cylinder = get_cylinder(&scene->objects, lookup->hit_index);
        *normal = cylinder_normal(*cylinder, lookup->hit_point);
        *base_color = cylinder->color;
    }
    else
    {
        *normal = (t_vec3){0.0f, 1.0f, 0.0f};
        *base_color = (t_color){0.5f, 0.5f, 0.5f};
    }
}

static void apply_shadow_and_diffuse(const t_scene *scene, t_hit_info *hit, t_light *light, t_color *final_color)
{
    bool in_shadow = isShadow(scene, hit->hit_point, light, hit->closest_t);
    t_color diffuse = compute_diffuse(hit->hit_point, hit->normal, *light, hit->base_color);
    float spot = spot_brightness();
    diffuse.r *= spot;
    diffuse.g *= spot;
    diffuse.b *= spot;
    float light_dist = vec_length(vec_substract(light->position, hit->hit_point));
    float shadow_factor = 1.0f;
    if (in_shadow)
    {
        shadow_factor = 0.3f + (0.2f * (1.0f - fminf(light_dist / 10.0f, 1.0f)));
    }
    final_color->r += diffuse.r * shadow_factor;
    final_color->g += diffuse.g * shadow_factor;
    final_color->b += diffuse.b * shadow_factor;
}

static void apply_ambient(const t_scene *scene, t_color base_color, t_color *final_color)
{
    if (scene->ambient)
    {
        final_color->r += base_color.r * scene->ambient->intensity * (scene->ambient->color.r / 255.0f);
        final_color->g += base_color.g * scene->ambient->intensity * (scene->ambient->color.g / 255.0f);
        final_color->b += base_color.b * scene->ambient->intensity * (scene->ambient->color.b / 255.0f);
    }
}

t_color rayTracing(t_vec3 direction, t_scene *scene)
{
    t_color final_color = {0, 0, 0};
    t_closest_result result = {
        .closest_t = INFINITY,
        .refl = 1.0f,
        .hit_type = 0,
        .hit_index = -1
    };
    t_vec3 ray_origin = scene->camera->position;
    t_ray ray = { .origin = ray_origin, .direction = direction };

    find_closest_plane(scene, ray, &result);
    find_closest_sphere(scene, ray, &result);
    find_closest_cylinder(scene, ray, &result);

    t_vec3 hit_point = vec_add(ray_origin, vec_scale(direction, result.closest_t));
    t_vec3 normal;
    t_color base_color;
    t_hit_lookup lookup = { result.hit_type, result.hit_index, hit_point };
    get_hit_normal_and_color(scene, &lookup, &normal, &base_color);

    t_light *light = (t_light *)vector_at(&scene->lights_vec, 0);
    t_hit_info hit = { hit_point, normal, base_color, result.closest_t };
    apply_shadow_and_diffuse(scene, &hit, light, &final_color);
    apply_ambient(scene, base_color, &final_color);
    return final_color;
}
