/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:22:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:12:34 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector_ops.h"

float	dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec_normalize(t_vec3 v)
{
	float	len;

	len = sqrtf(dot_product(v, v));
	if (len == 0.0f)
		return ((t_vec3){0, 0, 0});
	else
		return (vec_scale(v, 1.0f / len));
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x});
}
