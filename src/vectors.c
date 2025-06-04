#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    float x, y, z;
} Vec3;

struct Camera {
    Vec3 position;
    Vec3 direction;
   float zoom;
} camera;

struct Sphere {
    Vec3 position;
    float radius;
} sphere;


void setUpScene()
{
    camera.position = (Vec3){0.0f, 0.0f, 5.0f};
    camera.direction = (Vec3){0.0f, 0.0f, -1.0f};
    camera.zoom = 1.0f;

    sphere.position = (Vec3){0.0f, 0.0f, 0.0f};
    sphere.radius = 1.0f;
}

Vec3 vec_substract(Vec3 vec_a,Vec3 vec_b)
{
    return (Vec3){
        vec_a.x - vec_b.x,
        vec_a.y - vec_b.y,
        vec_a.z - vec_b.z
    };
}

Vec3 vec_add(Vec3 vec_a, Vec3 vec_b)
{
    return (Vec3){
        vec_a.x + vec_b.x,
        vec_a.y + vec_b.y,
        vec_a.z + vec_b.z
    };
}

Vec3 vec_scale(Vec3 v, float t) {
    return (Vec3){v.x * t, v.y * t, v.z * t};
}

float dot_product(Vec3 vec_a, Vec3 vec_b)
{
    return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
}
