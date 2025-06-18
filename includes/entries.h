#ifndef ENTRIES_H
#define ENTRIES_H

#include "../libft/libft.h"
#include "../minilibx/include/MLX42/MLX42.h"
#include "vector.h"
// #include "minirt.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Forward declarations
typedef struct s_scene t_scene;

typedef struct s_color {
  float r, g, b;
  // wasn't sure how to implement it
  // float a;
} t_color;

typedef struct s_vec3 {
  float x, y, z;
} t_vec3;

typedef struct s_vec2 {
  float x, y;
} t_vec2;

typedef struct s_ambient {
  float intensity;
  t_color color;
} t_ambient;

typedef struct s_camera {
  t_vec3 position;
  t_vec3 direction;
  t_vec3 orientation;
  float fov;
  float zoom;
} t_camera;

typedef struct s_input {
  bool key_up;
  bool key_down;
  bool key_left;
  bool key_right;
  bool key_a;
  bool key_d;
} t_input;

typedef struct s_data {
  void *mlx;
  mlx_image_t *img;
  int width;
  int height;
  t_camera *camera; // Ensure this is initialized before use
  t_scene *scene;   // Add scene pointer
  t_input *input; // Ensure this is initialized before use
} t_data;

typedef struct s_light {
  t_vec3 position;
  float intensity;
  t_color color;
  int count;
} t_light;

typedef struct s_plane {
  t_vec3 position;
  t_vec3 normal;
  t_color color;
} t_plane;

typedef struct s_sphere {
  t_vec3 position;
  float radius;
  t_color color;
} t_sphere;
typedef struct s_cylinder {
  t_vec3 position;
  t_vec3 orientation;
  float diameter;
  float height;
  t_color color;
  // struct s_cylinder *next;
} t_cylinder;

typedef struct s_object_vector {
    t_vector planes_vec;
    t_vector spheres_vec;
    t_vector cylinders_vec;
} t_object_vector;

typedef struct s_scene {
  t_ambient *ambient;
  t_camera *camera;
  t_light *lights;
  // int fd;
  t_vector lights_vec;
  t_object_vector objects;
  t_data *data;
} t_scene;

void mainImage(t_vec2 coord, int width, int height, t_color *output, t_scene *scene);

#endif // ENTRIES_H