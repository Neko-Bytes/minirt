#ifndef ENTRIES_H
#define ENTRIES_H

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mlx.h"

# define KEY_ESC 53
# define KEY_PLUS 43
# define KEY_MINUS 45
# define KEY_R 15
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct s_color_struct
{
    float r, g, b;
} t_color_struct;

typedef struct s_vec3_struct
{
    float x, y, z;
} t_vec3_struct;

typedef struct s_vec2_struct
{
    float x, y;
} t_vec2_struct;

typedef struct s_ambient_struct
{
    float intensity;
    t_color_struct color;
} t_ambient_struct;

typedef struct s_camera_struct
{
    t_vec3_struct position;
    t_vec3_struct direction;
    t_vec3_struct orientation;
    float fov;
    float zoom;
} t_camera_struct;

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
    t_camera_struct *camera;
} t_data;


typedef struct s_light_struct
{
    t_vec3_struct position;
    float intensity;
    t_color_struct color;
} t_light_struct;

typedef struct s_plane_struct
{
    t_vec3_struct position;
    t_vec3_struct normal;
    t_color_struct color;
} t_plane_struct;

typedef struct s_sphere_struct
{
    t_vec3_struct position;
    float radius;
    t_color_struct color;
} t_sphere_struct;

typedef struct s_cylinder_struct
{
    t_vec3_struct position;
    t_vec3_struct orientation;
    float diameter;
    float height;
    t_color_struct color;
} t_cylinder_struct;

// Hardcoded scene objects
static const t_ambient_struct ambient = {0.2f, {255, 255, 255}};
static const t_camera_struct camera = {
    .position = {0.0f, 0.0f, -5.0f},
    .direction = {0.0f, 0.0f, 1.0f},
    .fov = 70.0f,
    .zoom = 1.0f};
static const t_light_struct light = {{-40, 0, 30}, 0.7f, {255, 255, 255}};
static const t_plane_struct plane = {{0, 0, 0}, {0, 1, 0}, {255, 0, 225}};
static const t_sphere_struct sphere = {{0, 0, 100}, 5.0f, {255, 0, 0}};
static const t_cylinder_struct cylinder = {{50.0f, 0.0f, 20.6f}, {0, 0, 1}, 14.2f, 21.42f, {10, 0, 255}};

void mainImage(t_vec2_struct coord, int width, int height, t_color_struct *output, t_camera_struct *camera);

#endif // ENTRIES_H
