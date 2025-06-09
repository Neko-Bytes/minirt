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
#define KEY_A 0
#define KEY_D 2
#define KEY_PLUS 43
#define KEY_MINUS 45
#define KEY_R 15
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124


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
  float closest_t;
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

typedef struct s_object_vector {
    t_plane  *planes;
    int       plane_count;
    int       plane_capacity;

    t_sphere *spheres;
    int       sphere_count;
    int       sphere_capacity;
    // I haven't added cylinders yet
} t_object_vector;

typedef struct s_scene {
  t_ambient *ambient;
  t_camera *camera;
  t_light *lights;
  t_object_vector objects; //now the scene holds all the objects packed in a vector
  t_data *data;
} t_scene;


void mainImage(t_vec2 coord, int width, int height, t_color *output, t_camera *camera, t_scene *scene);

#endif // ENTRIES_H
