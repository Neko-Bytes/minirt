#ifndef ENTRIES_H
#define ENTRIES_H

#include "mlx.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define KEY_ESC 53
#define KEY_PLUS 43
#define KEY_MINUS 45
#define KEY_R 15
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124

typedef struct s_color {
  float r, g, b;
  float a;
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

typedef struct s_data {
  void *mlx;
  void *win;
  void *img;
  char *img_data;
  int bpp;
  int size_line;
  int endian;
  int width;
  int height;
  t_camera *camera;
} t_data;

typedef struct s_light {
  t_vec3 position;
  float intensity;
  t_color color;
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
} t_cylinder;

typedef struct s_scene {
  t_ambient *ambient;
  t_camera *camera;
  t_light *lights;
  t_sphere *spheres;
  t_plane *planes;
  t_cylinder *cylinders;
  t_data *data;
} t_scene;

// Hardcoded scene objects
static const t_ambient_struct ambient = {0.2f, {255, 255, 255}};
static const t_camera_struct camera = {.position = {0.0f, 0.0f, -5.0f},
                                       .direction = {0.0f, 0.0f, 1.0f},
                                       .fov = 70.0f,
                                       .zoom = 1.0f};
static const t_light_struct light = {{-40, 0, 30}, 0.7f, {255, 255, 255}};
static const t_plane_struct plane = {{0, 0, 0}, {0, 1, 0}, {255, 0, 225}};
static const t_sphere_struct sphere = {{0, 0, 100}, 5.0f, {255, 0, 0}};
static const t_cylinder_struct cylinder = {
    {50.0f, 0.0f, 20.6f}, {0, 0, 1}, 14.2f, 21.42f, {10, 0, 255}};

void mainImage(t_vec2_struct coord, int width, int height,
               t_color_struct *output, t_camera_struct *camera);

#endif // ENTRIES_H
