#include "test.h"

/*  
Enhanced test scene with an ice cream cone inside a box made of planes.
*/

static const t_ambient ambient = {0.2f, {255, 255, 255}};
static const t_camera camera = {
    .position = {0.0f, 0.0f, -15.0f},
    .direction = {0.0f, 0.0f, 1.0f},
    .fov = 70.0f,
    .zoom = 1.0f
};
static const t_light light = {{-40, 60, 40}, 0.9f, {255, 255, 255}};

// Box planes
static const t_plane box_bottom = {{0, -10.0f, 0}, {0, 1, 0}, {180, 180, 180}};
static const t_plane box_top = {{0, 30.0f, 0}, {0, -1, 0}, {150, 150, 150}};
static const t_plane box_left = {{-20.0f, 0, 0}, {1, 0, 0}, {50, 200, 50}};
static const t_plane box_right = {{20.0f, 0, 0}, {-1, 0, 0}, {50, 200, 50}};
static const t_plane box_back = {{0, 0, 70}, {0, 0, -1}, {100, 100, 100}};

// Ice cream cone (cylinders and spheres)
static const t_cylinder cone_base = {{0, -10, 50}, {0, 1, 0}, 5.0f, 15.0f, {200, 150, 100}};
static const t_sphere scoop1 = {{0, 5, 50}, 4.0f, {255, 100, 100}};
static const t_sphere scoop2 = {{0, 10, 50}, 3.5f, {100, 255, 200}};
static const t_sphere scoop3 = {{0, 14, 50}, 3.0f, {150, 100, 255}};

t_object_vector objects_vector;

t_object_vector init_scene_objects(void)
{
    init_object_vector(&objects_vector, 20);
    // Box planes
    add_plane(&objects_vector, box_bottom);
    add_plane(&objects_vector, box_top);
    add_plane(&objects_vector, box_left);
    add_plane(&objects_vector, box_right);
    add_plane(&objects_vector, box_back);

    // Ice cream cone
    add_cylinder(&objects_vector, cone_base);
    add_sphere(&objects_vector, scoop1);
    add_sphere(&objects_vector, scoop2);
    add_sphere(&objects_vector, scoop3);

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
