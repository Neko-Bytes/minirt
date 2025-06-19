#ifndef OBJECT_ARRAY_H
# define OBJECT_ARRAY_H

# include "entries.h"
# include "vector.h"

typedef struct s_way
{
	t_vec3			forward;
	t_vec3			right;
	t_vec3			up;
}					t_way;

typedef struct s_params
{
	t_vec2 coord; // Pixel coordinates
	int width;    // Image width
	int height;   // Image height
}					t_params;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;

typedef struct s_closest_result
{
	float			closest_t;
	float			refl;
	int				hit_type;
	int				hit_index;
}					t_closest_result;

typedef struct s_closest_args
{
	const t_scene	*scene;
	t_vec3			ray_origin;
	t_vec3			direction;
	float			*closest_t;
	float			*refl;
	int				*hit_type;
	int				*hit_index;
}					t_closest_args;

typedef struct s_hit_info
{
	t_vec3			hit_point;
	t_vec3			normal;
	t_color			base_color;
	float			closest_t;
}					t_hit_info;

typedef struct s_hit_lookup
{
	int				hit_type;
	int				hit_index;
	t_vec3			hit_point;
}					t_hit_lookup;

typedef struct s_ray_tracing_vars
{
	t_color				final_color;
	t_closest_result	result;
	t_ray				ray;
	t_vec3				hit_point;
	t_vec3				normal;
	t_color				base_color;
	t_hit_lookup		lookup;
	t_light				*light;
	t_hit_info			hit;
}	t_ray_tracing_vars;

// Object vector specific functions
void				init_object_vector(t_object_vector *vec,
						int initial_capacity);
void				add_plane(t_object_vector *vec, t_plane plane);
void				add_sphere(t_object_vector *vec, t_sphere sphere);
void				add_cylinder(t_object_vector *vec, t_cylinder cylinder);
void				free_object_vector(t_object_vector *vec);
void				print_object_vector(const t_object_vector *vec);

// Helper functions to access object vectors
t_plane				*get_plane(const t_object_vector *vec, size_t index);
t_sphere			*get_sphere(const t_object_vector *vec, size_t index);
t_cylinder			*get_cylinder(const t_object_vector *vec, size_t index);
size_t				get_plane_count(const t_object_vector *vec);
size_t				get_sphere_count(const t_object_vector *vec);
size_t				get_cylinder_count(const t_object_vector *vec);

void				init_window_and_image(t_data *data);
void				init_scene(t_scene *scene);
t_vec3				rotate_y(t_vec3 v, float angle);
t_vec3				rotate_x(t_vec3 v, float angle);
void				handle_camera_rotation(int keycode, t_data *data,
						float angle);

// closest_t.c
void				find_closest_plane(const t_scene *scene, t_ray ray,
						t_closest_result *result);
void				find_closest_sphere(const t_scene *scene, t_ray ray,
						t_closest_result *result);
void				find_closest_cylinder(const t_scene *scene, t_ray ray,
						t_closest_result *result);
t_vec3				sphere_normal(t_sphere s, t_vec3 p);
t_vec3				cylinder_normal(t_cylinder c, t_vec3 p);

// color_output.c
t_vec3				compute_ray_direction(t_params *params, float aspect_ratio,
						float scale, t_way *way);
void				compute_camera_basis(t_vec3 camera_dir, t_way *way);
void				main_image(t_params *params, t_color *output,
						t_scene *scene);

// shadow_a_color.c
void				get_hit_normal(const t_scene *scene, t_hit_lookup *lookup,
						t_vec3 *normal);
void				get_hit_color(const t_scene *scene, t_hit_lookup *lookup,
						t_color *base_color);
void				apply_shadow_and_diffuse(const t_scene *scene,
						t_hit_info *hit, t_light *light, t_color *final_color);
void				apply_ambient(const t_scene *scene, t_color base_color,
						t_color *final_color);
t_closest_result	assign_closest_result(void);

#endif