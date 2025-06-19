#ifndef LIGHT_H
#define LIGHT_H

#include "entries.h"
#include "vector_ops.h"

t_color compute_diffuse(t_vec3 point, t_vec3 normal, t_light light, t_color base_color);
float vec_length(t_vec3 v);
bool isShadow(const t_scene *scene, t_vec3 point, t_light *light, float closest_t);
float calculate_shadow(const t_scene *scene, t_vec3 point, t_light *light, float closest_t);
float spot_brightness();
#endif