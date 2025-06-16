/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:19:41 by kmummadi          #+#    #+#             */
/*   Updated: 2025/06/16 18:32:59 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void ensure_space(t_scene *scene);
static void set_cylinder(t_scene *scene, char **tokens);
static void validate_cylinder(t_scene *scene, t_cylinder *cy);

bool parse_cylinder(t_scene **scene, char **tokens)
{
    t_cylinder *cy;

    if (tokens_counter(tokens) != 6)
        print_error("Cylinder: wrong number of params\n", (*scene)->data);
    ensure_space((*scene));
    cy = &(*scene)->objects.cylinders[(*scene)->objects.cy_count];
    set_cylinder((*scene), tokens);
    validate_cylinder((*scene), cy);
    (*scene)->objects.cy_count++;
    return (true);
}

static void ensure_space(t_scene *scene)
{
    size_t new_size;

    if (!scene->objects.cylinders)
    {
        scene->objects.cy_count = 0;
        scene->objects.cylinders = gc_malloc(sizeof(t_cylinder));
        if (!scene->objects.cylinders)
            print_error("Cylinder: alloc failed\n", scene->data);
    }
    else
    {
        if (scene->objects.cy_count + 1 > MAX_CYLINDERS)
            print_error("Cylinder: max count exceeded\n", scene->data);
        new_size = scene->objects.cy_count + 1;
        scene->objects.cylinders = gc_realloc(
            scene->objects.cylinders,
            sizeof(t_cylinder) * scene->objects.cy_count,
            sizeof(t_cylinder) * new_size);
        if (!scene->objects.cylinders)
            print_error("Cylinder: realloc failed\n", scene->data);
    }
}

static void set_cylinder(t_scene *scene, char **tokens)
{
    char **xyz;
    char **orient;
    char **rgb;
		t_cylinder *cy;

    xyz    = ft_split(tokens[1], ',');
    orient = ft_split(tokens[2], ',');
    rgb    = ft_split(tokens[5], ',');
		cy = scene->objects.cylinders;
    if (tokens_counter(xyz) != 3 || tokens_counter(orient) != 3
    || tokens_counter(rgb) != 3)
        print_error("Cylinder: bad vector or color\n", scene->data);
    cy->position.x    = ft_atof(xyz[0]);
    cy->position.y    = ft_atof(xyz[1]);
    cy->position.z    = ft_atof(xyz[2]);
    cy->orientation.x = ft_atof(orient[0]);
    cy->orientation.y = ft_atof(orient[1]);
    cy->orientation.z = ft_atof(orient[2]);
    cy->diameter      = ft_atof(tokens[3]);
    cy->height        = ft_atof(tokens[4]);
    cy->color.r       = ft_atoi(rgb[0]);
    cy->color.g       = ft_atoi(rgb[1]);
    cy->color.b       = ft_atoi(rgb[2]);
}

static void validate_cylinder(t_scene *scene, t_cylinder *cy)
{
    if (cy->diameter <= 0.0f)
        print_error("Cylinder: invalid diameter\n", scene->data);
    if (cy->height <= 0.0f)
        print_error("Cylinder: invalid height\n", scene->data);
    if (cy->orientation.x < -1.0f || cy->orientation.x > 1.0f
    || cy->orientation.y < -1.0f || cy->orientation.y > 1.0f
    || cy->orientation.z < -1.0f || cy->orientation.z > 1.0f)
        print_error("Cylinder: orientation out of range\n", scene->data);
    if (cy->color.r < 0 || cy->color.r > 255)
        print_error("Cylinder: red out of range\n", scene->data);
    if (cy->color.g < 0 || cy->color.g > 255)
        print_error("Cylinder: green out of range\n", scene->data);
    if (cy->color.b < 0 || cy->color.b > 255)
        print_error("Cylinder: blue out of range\n", scene->data);
}
