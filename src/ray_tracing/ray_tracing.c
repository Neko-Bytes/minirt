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
#include "../../includes/minirt.h"
#include "../../includes/vector_ops.h"
#include "../../includes/object_array.h"
#include "../../includes/light.h"
#include "../../includes/intersect.h"

#define DEBUG_RAYS 1

t_vec3 sphere_normal(t_sphere s, t_vec3 p)
{
    return vec_normalize(vec_substract(p, s.position));
}

t_vec3 cylinder_normal(t_cylinder c, t_vec3 p)
{
    t_vec3 ca = c.orientation;
    t_vec3 cp = vec_substract(p, c.position);
    float projection = dot_product(cp, ca);
    t_vec3 projected = vec_scale(ca, projection);
    t_vec3 normal = vec_substract(cp, projected);
    return vec_normalize(normal);
}

static void find_closest_plane(const t_scene *scene, t_vec3 ray_origin, t_vec3 direction, float *closest_t, float *refl, int *hit_type, int *hit_index)
{
    size_t i = 0;
    size_t count = get_plane_count(&scene->objects);
    while (i < count)
    {
        float t = 0.0f, local_refl = 1.0f;
        t_plane *plane = get_plane(&scene->objects, i);
        if (intersectPlane(plane, ray_origin, direction, &t))
        {
            if (t < *closest_t)
            {
                *closest_t = t;
                *refl = local_refl;
                *hit_type = 2;
                *hit_index = i;
            }
        }
        i++;
    }
}

static void find_closest_sphere(const t_scene *scene, t_vec3 ray_origin, t_vec3 direction, float *closest_t, float *refl, int *hit_type, int *hit_index)
{
    size_t i = 0;
    size_t count = get_sphere_count(&scene->objects);
    while (i < count)
    {
        float t = 0.0f, local_refl = 1.0f;
        t_sphere *sphere = get_sphere(&scene->objects, i);
        if (intersectSphere(sphere, ray_origin, direction, &local_refl, &t))
        {
            if (t < *closest_t)
            {
                *closest_t = t;
                *refl = local_refl;
                *hit_type = 1;
                *hit_index = i;
            }
        }
        i++;
    }
}

static void find_closest_cylinder(const t_scene *scene, t_vec3 ray_origin, t_vec3 direction, float *closest_t, float *refl, int *hit_type, int *hit_index)
{
    size_t i = 0;
    size_t count = get_cylinder_count(&scene->objects);
    while (i < count)
    {
        float t = 0.0f, local_refl = 1.0f;
        t_cylinder *cylinder = get_cylinder(&scene->objects, i);
        if (intersectCylinder(cylinder, ray_origin, direction, &local_refl, &t))
        {
            if (t < *closest_t)
            {
                *closest_t = t;
                *refl = local_refl;
                *hit_type = 3;
                *hit_index = i;
            }
        }
        i++;
    }
}

static void get_hit_normal_and_color(const t_scene *scene, int hit_type, int hit_index, t_vec3 hit_point, t_vec3 *normal, t_color *base_color)
{
    if (hit_type == 1)
    {
        t_sphere *sphere = get_sphere(&scene->objects, hit_index);
        *normal = sphere_normal(*sphere, hit_point);
        *base_color = sphere->color;
    }
    else if (hit_type == 2)
    {
        t_plane *plane = get_plane(&scene->objects, hit_index);
        *normal = plane->normal;
        *base_color = plane->color;
    }
    else if (hit_type == 3)
    {
        t_cylinder *cylinder = get_cylinder(&scene->objects, hit_index);
        *normal = cylinder_normal(*cylinder, hit_point);
        *base_color = cylinder->color;
    }
    else
    {
        *normal = (t_vec3){0.0f, 1.0f, 0.0f};
        *base_color = (t_color){0.5f, 0.5f, 0.5f};
    }
}

static void apply_shadow_and_diffuse(const t_scene *scene, t_vec3 hit_point, t_vec3 normal, t_color base_color, t_light *light, float closest_t, t_color *final_color)
{
    bool in_shadow = isShadow(scene, hit_point, light, closest_t);
    t_color diffuse = compute_diffuse(hit_point, normal, *light, base_color);
    float light_dist = vec_length(vec_substract(light->position, hit_point));
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
    float refl = 1.0f;
    (void)refl;
    int hit_type = 0;
    int hit_index = -1;
    float closest_t = INFINITY;
    t_vec3 ray_origin = scene->camera->position;

    find_closest_plane(scene, ray_origin, direction, &closest_t, &refl, &hit_type, &hit_index);
    find_closest_sphere(scene, ray_origin, direction, &closest_t, &refl, &hit_type, &hit_index);
    find_closest_cylinder(scene, ray_origin, direction, &closest_t, &refl, &hit_type, &hit_index);

    t_vec3 hit_point = vec_add(ray_origin, vec_scale(direction, closest_t));
    t_vec3 normal;
    t_color base_color;
    get_hit_normal_and_color(scene, hit_type, hit_index, hit_point, &normal, &base_color);

    t_light *light = (t_light *)vector_at(&scene->lights_vec, 0);
    apply_shadow_and_diffuse(scene, hit_point, normal, base_color, light, closest_t, &final_color);
    apply_ambient(scene, base_color, &final_color);
    return final_color;
}

static void validate_camera_and_scene(t_scene *scene)
{
    if (!scene->camera || !scene)
    {
        fprintf(stderr, "Error: Invalid input to mainImage.\n");
        exit(1);
    }
}

static void compute_camera_basis(t_vec3 camera_dir, t_vec3 *forward, t_vec3 *right, t_vec3 *up)
{
    *forward = vec_normalize(camera_dir);
    *right = vec_normalize(vec_cross((t_vec3){0.0f, 1.0f, 0.0f}, *forward));
    *up = vec_cross(*forward, *right);
}

static t_vec3 compute_ray_direction(t_vec2 coord, int width, int height, float aspect_ratio, float scale, t_vec3 forward, t_vec3 right, t_vec3 up)
{
    float x = (2.0f * ((coord.x + 0.5f) / width) - 1.0f) * aspect_ratio * scale;
    float y = (1.0f - 2.0f * ((coord.y + 0.5f) / height)) * scale;
    return vec_normalize(vec_add(
        vec_add(
            vec_scale(right, x),
            vec_scale(up, y)),
        vec_scale(forward, 1.0f)));
}

void mainImage(t_vec2 coord, int width, int height, t_color *output, t_scene *scene)
{
    validate_camera_and_scene(scene);

    float aspect_ratio = (float)width / (float)height;
    float fov = scene->camera->fov * (M_PI / 180.0f);
    float scale = tanf(fov / 2.0f);

    t_vec3 forward, right, up;
    compute_camera_basis(scene->camera->direction, &forward, &right, &up);

    t_vec3 direction = compute_ray_direction(coord, width, height, aspect_ratio, scale, forward, right, up);

    *output = rayTracing(direction, scene);
}
