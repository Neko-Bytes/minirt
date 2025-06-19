/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_a_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:36:19 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:06:47 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersect.h"
#include "../../includes/light.h"
#include "../../includes/minirt.h"
#include "../../includes/object_array.h"
#include "../../includes/vector_ops.h"
#include <math.h>

void	get_hit_normal(const t_scene *scene, t_hit_lookup *lookup,
		t_vec3 *normal)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (lookup->hit_type == 1)
	{
		sphere = get_sphere(&scene->objects, lookup->hit_index);
		*normal = sphere_normal(*sphere, lookup->hit_point);
	}
	else if (lookup->hit_type == 2)
	{
		plane = get_plane(&scene->objects, lookup->hit_index);
		*normal = plane->normal;
	}
	else if (lookup->hit_type == 3)
	{
		cylinder = get_cylinder(&scene->objects, lookup->hit_index);
		*normal = cylinder_normal(*cylinder, lookup->hit_point);
	}
	else
	{
		*normal = (t_vec3){0.0f, 1.0f, 0.0f};
	}
}

void	get_hit_color(const t_scene *scene, t_hit_lookup *lookup,
		t_color *base_color)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (lookup->hit_type == 1)
	{
		sphere = get_sphere(&scene->objects, lookup->hit_index);
		*base_color = sphere->color;
	}
	else if (lookup->hit_type == 2)
	{
		plane = get_plane(&scene->objects, lookup->hit_index);
		*base_color = plane->color;
	}
	else if (lookup->hit_type == 3)
	{
		cylinder = get_cylinder(&scene->objects, lookup->hit_index);
		*base_color = cylinder->color;
	}
	else
	{
		*base_color = (t_color){0.5f, 0.5f, 0.5f};
	}
}

void	apply_shadow_and_diffuse(const t_scene *scene, t_hit_info *hit,
		t_light *light, t_color *final_color)
{
	bool	in_shadow;
	t_color	diffuse;
	float	spot;
	float	light_dist;
	float	shadow_factor;

	in_shadow = is_shadow(scene, hit->hit_point, light, hit->closest_t);
	diffuse = compute_diffuse(hit->hit_point, hit->normal, *light,
			hit->base_color);
	spot = spot_brightness();
	diffuse.r *= spot;
	diffuse.g *= spot;
	diffuse.b *= spot;
	light_dist = vec_length(vec_substract(light->position, hit->hit_point));
	shadow_factor = 1.0f;
	if (in_shadow)
	{
		shadow_factor = 0.3f + (0.2f * (1.0f - fminf(light_dist / 10.0f,
						1.0f)));
	}
	final_color->r += diffuse.r * shadow_factor;
	final_color->g += diffuse.g * shadow_factor;
	final_color->b += diffuse.b * shadow_factor;
}

void	apply_ambient(const t_scene *scene, t_color base_color,
		t_color *final_color)
{
	if (scene->ambient)
	{
		final_color->r += base_color.r * scene->ambient->intensity
			* (scene->ambient->color.r / 255.0f);
		final_color->g += base_color.g * scene->ambient->intensity
			* (scene->ambient->color.g / 255.0f);
		final_color->b += base_color.b * scene->ambient->intensity
			* (scene->ambient->color.b / 255.0f);
	}
}

t_closest_result	assign_closest_result(void)
{
	t_closest_result	result;

	result.closest_t = INFINITY;
	result.refl = 1.0f;
	result.hit_type = 0;
	result.hit_index = -1;
	return (result);
}
