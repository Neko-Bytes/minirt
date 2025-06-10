#include "../includes/vector_ops.h"

t_vec3 vec_add(t_vec3 a, t_vec3 b) {
    return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 vec_substract(t_vec3 a, t_vec3 b) {
    return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3 vec_scale(t_vec3 v, float s) {
    return (t_vec3){v.x * s, v.y * s, v.z * s};
}

float dot_product(t_vec3 a, t_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec_normalize(t_vec3 v) {
    float len = sqrtf(dot_product(v, v));
    return (len == 0.0f) ? (t_vec3){0, 0, 0} : vec_scale(v, 1.0f / len);
} 