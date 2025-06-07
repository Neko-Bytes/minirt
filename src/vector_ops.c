#include "../includes/entries.h"

t_vec3_struct vec_add(t_vec3_struct a, t_vec3_struct b) {
    return (t_vec3_struct){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3_struct vec_substract(t_vec3_struct a, t_vec3_struct b) {
    return (t_vec3_struct){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3_struct vec_scale(t_vec3_struct v, float s) {
    return (t_vec3_struct){v.x * s, v.y * s, v.z * s};
}

float dot_product(t_vec3_struct a, t_vec3_struct b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3_struct vec_normalize(t_vec3_struct v) {
    float len = sqrtf(dot_product(v, v));
    return (len == 0.0f) ? (t_vec3_struct){0, 0, 0} : vec_scale(v, 1.0f / len);
} 