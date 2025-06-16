// #include "test.h"

// /*  
// Fun Scene: "Target Practice"
// - Red + white concentric spheres
// - Green laser cylinder
// - Gray reflective floor
// - Colorful back wall
// */

// // Ambient and camera setup
// static const t_ambient ambient = {0.15f, {255, 255, 255}};
// static const t_light light = {
//     .position = {0, 50, 0},
//     .intensity = 1.0f,
//     .color = {255, 255, 255}
// };
// static const t_camera camera = {
//     .position = {0.0f, 0.0f, -25.0f},
//     .direction = {0.0f, 0.0f, 1.0f},
//     .fov = 70.0f,
//     .zoom = 1.0f
// };

// // Ground plane (gray floor)
// static const t_plane floor_plane = {
//     .position = {0, -10.0f, 0},
//     .normal = {0, 1, 0},
//     .color = {50, 50, 50}
// };

// // Sun and planets (simplified scale & color)
// static const t_sphere sun     = {{0,    0, 50}, 8.0f,  {255, 204, 0}};
// static const t_sphere mercury = {{-12,  0, 50}, 0.8f,  {169, 169, 169}};
// static const t_sphere venus   = {{-16,  0, 50}, 1.2f,  {218, 165, 32}};
// static const t_sphere earth   = {{-20,  0, 50}, 1.3f,  {0, 102, 204}};
// static const t_sphere mars    = {{-24,  0, 50}, 1.0f,  {255, 69, 0}};
// static const t_sphere jupiter = {{-30,  0, 50}, 3.5f,  {205, 133, 63}};
// static const t_sphere saturn  = {{-42,  0, 50}, 3.0f,  {210, 180, 140}};  // Saturn
// static const t_sphere uranus  = {{-54,  0, 50}, 2.5f,  {175, 238, 238}};
// static const t_sphere neptune = {{-60,  0, 50}, 2.5f,  {0, 0, 128}};


// // Cylinder to represent Saturn’s ring (vertical for now)
// static const t_cylinder saturn_ring = {
//     .position = {-42, -1.0f, 50},
//     .orientation = {0, 1, 0},    // Flat (horizontal) ring
//     .diameter = 12.0f,           // Much wider than Saturn
//     .height = 0.2f,              // Very thin
//     .color = {220, 220, 160}     // Pale color for a realistic look
// };


// // static const t_cylinder axis_cylinder2 = {
// //     .position = {-30, -1.0f, 40},
// //     .orientation = {0, 1, 0},
// //     .diameter = 5.5f,
// //     .height = 0.5f,
// //     .color = {200, 200, 100}
// // };

// t_object_vector objects_vector;

// t_object_vector init_scene_objects(void)
// {
//     init_object_vector(&objects_vector, 20);

//     add_plane(&objects_vector, floor_plane);
//     add_sphere(&objects_vector, sun);
//     add_sphere(&objects_vector, mercury);
//     add_sphere(&objects_vector, venus);
//     add_sphere(&objects_vector, earth);
//     add_sphere(&objects_vector, mars);
//     add_sphere(&objects_vector, jupiter);
//     add_sphere(&objects_vector, saturn);
//     add_sphere(&objects_vector, uranus);
//     add_sphere(&objects_vector, neptune);
//     add_cylinder(&objects_vector, saturn_ring);
//     // add_cylinder(&objects_vector, axis_cylinder2);

//     return objects_vector;
// }

// void init_scene(t_scene *scene)
// {
//     scene->ambient = (t_ambient *)&ambient;
//     scene->camera = (t_camera *)&camera;
//     scene->lights = (t_light *)&light;
//     scene->objects = init_scene_objects();
//     scene->data = NULL;
// }


