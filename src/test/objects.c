#include "test.h"

/*  
This is just a simple test file to demonstrate
how to set up a scene with hardcoded objects
and how to initialize the scene.
*/

// Hardcoded scene objects
static const t_ambient ambient = {0.2f, {255, 255, 255}};
static const t_camera camera = {.position = {0.0f, 0.0f, -5.0f},
                                       .direction = {0.0f, 0.0f, 1.0f},
                                       .fov = 70.0f,
                                       .zoom = 1.0f};
static const t_light light = {{-40, 0, 30}, 0.7f, {255, 255, 255}};
static const t_plane floor_plane = {
    .position = {0, -10.0f, 0},
    .normal   = {0, 1, 0},
    .color    = {200, 200, 200}
};


static const t_sphere sphere = {{0, 0, 100}, 5.0f, {255, 0, 0}};
static const t_sphere sphere2 = {{-10, 0, 50}, 3.0f, {0, 255, 0}};
static const t_sphere sphere3 = {{10, 0, 50}, 3.0f, {0, 0, 255}};
// static const t_cylinder cylinder = {
//     {50.0f, 0.0f, 20.6f}, {0, 0, 1}, 14.2f, 21.42f, {10, 0, 255}};

t_object_vector objects_vector;

t_object_vector init_scene_objects(void)
{
    init_object_vector(&objects_vector, 10);
    // add_plane(&objects_vector, plane);
    add_plane(&objects_vector, floor_plane);
    add_sphere(&objects_vector, sphere);
    add_sphere(&objects_vector, sphere2);
    add_sphere(&objects_vector, sphere3);
    return objects_vector;
}

void init_scene(t_scene *scene)
{
    scene->ambient = (t_ambient *)&ambient;
    scene->camera = (t_camera *)&camera;
    scene->lights = (t_light *)&light;
    scene->objects = init_scene_objects();
    scene->data = NULL; 
}
