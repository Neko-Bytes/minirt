#ifndef LIGHT_H
#define LIGHT_H

#include "entries.h"



t_color compute_diffuse(t_vec3 point, t_vec3 normal, t_light light, t_color base_color);
#endif