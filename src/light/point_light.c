/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:07:04 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:11:37 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/light.h"
#include "../includes/vector_ops.h"

t_color	compute_diffuse(t_vec3 point, t_vec3 normal, t_light light,
		t_color base_color)
{
	t_vec3	light_dir;
	float	diff;
	t_color	result;

	light_dir = vec_normalize(vec_substract(light.position, point));
	diff = fmax(dot_product(normal, light_dir), 0.0f);
	result.r = base_color.r * light.intensity * diff;
	result.g = base_color.g * light.intensity * diff;
	result.b = base_color.b * light.intensity * diff;
	return (result);
}

float	spot_brightness(void)
{
	return (0.5f);
}
