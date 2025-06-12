#include "test.h"

/*  
Fun Scene: "Target Practice"
- Red + white concentric spheres
- Green laser cylinder
- Gray reflective floor
- Colorful back wall
*/

// Ambient and camera setup
static const t_ambient ambient = {0.15f, {255, 255, 255}};
static const t_camera camera = {
    .position = {0.0f, 0.0f, -25.0f},
    .direction = {0.0f, 0.0f, 1.0f},
    .fov = 70.0f,
    .zoom = 1.0f
};
static const t_light light = {{30, 30, -10}, 0.9f, {255, 255, 255}};

// Ground plane (gray floor)
static const t_plane floor_plane = {
    .position = {0, -8.0f, 0},
    .normal = {0, 1, 0},
    .color = {180, 180, 180}
};

// Back wall (adds depth)
static const t_plane back_wall = {
    .position = {0, 0, 100},
    .normal = {0, 0, -1},
    .color = {100, 150, 255}
};

// Spheres - target pattern
static const t_sphere center_sphere = {{0, 0, 50}, 2.0f, {255, 0, 0}};
static const t_sphere ring1 = {{0, 0, 50}, 4.0f, {255, 255, 255}};
static const t_sphere ring2 = {{0, 0, 50}, 6.0f, {255, 0, 0}};
static const t_sphere ring3 = {{0, 0, 50}, 8.0f, {255, 255, 255}};


t_object_vector objects_vector;

t_object_vector init_scene_objects(void)
{
    init_object_vector(&objects_vector, 10);
    
    // Planes
    add_plane(&objects_vector, floor_plane);
    add_plane(&objects_vector, back_wall);
    
    // Spheres (target)
    add_sphere(&objects_vector, ring3);
    add_sphere(&objects_vector, ring2);
    add_sphere(&objects_vector, ring1);
    add_sphere(&objects_vector, center_sphere);
    

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
