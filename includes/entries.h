#ifndef ENTRIES_H
#define ENTRIES_H

typedef struct
{
    float r, g, b;
} Color;

typedef struct
{
    float x, y, z;
} Vec3;

typedef struct
{
    float x, y;
} Vec2;

typedef struct
{
    float intensity;
    Color color;
} Ambient;

typedef struct
{
    Vec3 position;
    Vec3 direction;
    float fov;
    float zoom;
} Camera;

typedef struct
{
    Vec3 position;
    float intensity;
    Color color;
} Light;

typedef struct
{
    Vec3 position;
    Vec3 normal;
    Color color;
} Plane;

typedef struct
{
    Vec3 position;
    float radius;
    Color color;
} Sphere;

typedef struct
{
    Vec3 position;
    Vec3 orientation;
    float diameter;
    float height;
    Color color;
} Cylinder;

// Hardcoded scene objects
static const Ambient ambient = {0.2f, {255, 255, 255}};
static const Camera camera = {
    .position = {0.0f, 0.0f, -5.0f}, // behind the scene
    .direction = {0.0f, 0.0f, 1.0f}, // looking forward
    .fov = 70.0f,
    .zoom = 1.0f};
static const Light light = {{-40, 0, 30}, 0.7f, {255, 255, 255}};
static const Plane plane = {{0, 0, 0}, {0, 1, 0}, {255, 0, 225}};
static const Sphere sphere = {{0, 0, 100}, 5.0f, {255, 0, 0}};
static const Cylinder cylinder = {{50.0f, 0.0f, 20.6f}, {0, 0, 1}, 14.2f, 21.42f, {10, 0, 255}};
void mainImage(Vec2 coord, int width, int height, Color *output);
void initImage();
#endif // SCENE_H
