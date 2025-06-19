/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:18:59 by kruseva           #+#    #+#             */
/*   Updated: 2025/06/19 19:19:03 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "entries.h"
# include "vector_ops.h"

t_color	compute_diffuse(t_vec3 point, t_vec3 normal, t_light light,
			t_color base_color);
float	vec_length(t_vec3 v);
bool	is_shadow(const t_scene *scene, t_vec3 point, t_light *light,
			float closest_t);
float	calculate_shadow(const t_scene *scene, t_vec3 point, t_light *light,
			float closest_t);
float	spot_brightness(void);
#endif