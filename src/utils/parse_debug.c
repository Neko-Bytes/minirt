// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parse_debug.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kmummadi <kmummadi@student.42heilbronn.de  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/16 13:09:34 by kmummadi          #+#    #+#             */
// /*   Updated: 2025/06/16 13:32:45 by kmummadi         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/parse_debug.h"

// /* ─── Prototypes ───────────────────────────────────────────────────────────── */
// void  print_ambient(t_scene *scene);
// void  print_camera(t_scene *scene);
// void  print_lights(t_scene *scene);
// void  print_spheres(t_scene *scene);
// void  print_planes(t_scene *scene);
// void  print_cylinders(t_scene *scene);
// bool  run_parser_test(int argc, char **argv);

// /* ─── run_parser_test ───────────────────────────────────────────────────────── */
// bool  run_parser_test(int argc, char **argv)
// {
//     t_scene  *scene;
//     int       fd;

//     scene = gc_malloc(sizeof(*scene));
//     scene->data = gc_malloc(sizeof(*scene->data));
//     if (!scene->data)
//         print_error("Memory error initializing data\n", NULL);
//     parse_args(argc, argv, scene);
//     fd = scene->fd;
//     parse_file(fd, scene);

//     printf("======= Scene Summary =======\n");
//     print_ambient(scene);
//     print_camera(scene);
//     print_lights(scene);
//     print_spheres(scene);
//     print_planes(scene);
//     print_cylinders(scene);

//     close(fd);
//     return (true);
// }

// /* ─── Print Ambient ────────────────────────────────────────────────────────── */
// void  print_ambient(t_scene *scene)
// {
//     if (!scene->ambient)
//     {
//         printf("[ Ambient ]  none\n");
//         return;
//     }
//     printf("[ Ambient ]\n");
//     printf("  Intensity : %.2f\n", scene->ambient->intensity);
//     printf("  Color     : R=%d, G=%d, B=%d\n",
//         (int)scene->ambient->color.r,
//         (int)scene->ambient->color.g,
//         (int)scene->ambient->color.b);
// }

// /* ─── Print Camera ─────────────────────────────────────────────────────────── */
// void  print_camera(t_scene *scene)
// {
//     if (!scene->camera)
//     {
//         printf("[ Camera ]   none\n");
//         return;
//     }
//     printf("[ Camera ]\n");
//     printf("  Position    x=%.2f, y=%.2f, z=%.2f\n",
//         scene->camera->position.x,
//         scene->camera->position.y,
//         scene->camera->position.z);
//     printf("  Orientation x=%.2f, y=%.2f, z=%.2f\n",
//         scene->camera->orientation.x,
//         scene->camera->orientation.y,
//         scene->camera->orientation.z);
//     printf("  FOV         %.2f°\n", scene->camera->fov);
// }

// /* ─── Print Lights ─────────────────────────────────────────────────────────── */
// void  print_lights(t_scene *scene)
// {
//     int  i;
//     int  count;

//     count = scene->lights ? scene->lights->count : 0;
//     printf("[ Lights ]   %d\n", count);
//     i = 0;
//     while (i < count)
//     {
//         printf("  Light %d:\n", i + 1);
//         printf("    Position : x=%.2f, y=%.2f, z=%.2f\n",
//             scene->lights[i].position.x,
//             scene->lights[i].position.y,
//             scene->lights[i].position.z);
//         printf("    Intensity: %.2f\n",
//             scene->lights[i].intensity);
//         printf("    Color    : R=%d, G=%d, B=%d\n",
//             (int)scene->lights[i].color.r,
//             (int)scene->lights[i].color.g,
//             (int)scene->lights[i].color.b);
//         i++;
//     }
// }

// /* ─── Print Spheres ────────────────────────────────────────────────────────── */
// void  print_spheres(t_scene *scene)
// {
//     int         i;
//     t_sphere   *sph;
//     int         count;

//     count = scene->objects.sp_count;
//     printf("[ Spheres ]  %d\n", count);
//     i = 0;
//     while (i < count)
//     {
//         sph = &scene->objects.spheres[i];
//         printf("  Sphere %d:\n", i + 1);
//         printf("    Position: x=%.2f, y=%.2f, z=%.2f\n",
//             sph->position.x, sph->position.y, sph->position.z);
//         printf("    Radius  : %.2f\n", sph->radius);
//         printf("    Color   : R=%d, G=%d, B=%d\n",
//             (int)sph->color.r,
//             (int)sph->color.g,
//             (int)sph->color.b);
//         i++;
//     }
// }

// /* ─── Print Planes ──────────────────────────────────────────────────────────── */
// void  print_planes(t_scene *scene)
// {
//     int        i;
//     t_plane   *pl;
//     int        count;

//     count = scene->objects.pl_count;
//     printf("[ Planes ]   %d\n", count);
//     i = 0;
//     while (i < count)
//     {
//         pl = &scene->objects.planes[i];
//         printf("  Plane %d:\n", i + 1);
//         printf("    Point    : x=%.2f, y=%.2f, z=%.2f\n",
//             pl->position.x, pl->position.y, pl->position.z);
//         printf("    Normal   : x=%.2f, y=%.2f, z=%.2f\n",
//             pl->normal.x, pl->normal.y, pl->normal.z);
//         printf("    Color    : R=%d, G=%d, B=%d\n",
//             (int)pl->color.r,
//             (int)pl->color.g,
//             (int)pl->color.b);
//         i++;
//     }
// }

// /* ─── Print Cylinders ──────────────────────────────────────────────────────── */
// void  print_cylinders(t_scene *scene)
// {
//     int           i;
//     t_cylinder   *cy;
//     int           count;

//     count = scene->objects.cy_count;
//     printf("[ Cylinders ]%3d\n", count);
//     i = 0;
//     while (i < count)
//     {
//         cy = &scene->objects.cylinders[i];
//         printf("  Cylinder %d:\n", i + 1);
//         printf("    Position   : x=%.2f, y=%.2f, z=%.2f\n",
//             cy->position.x, cy->position.y, cy->position.z);
//         printf("    Orientation: x=%.2f, y=%.2f, z=%.2f\n",
//             cy->orientation.x,
//             cy->orientation.y,
//             cy->orientation.z);
//         printf("    Diameter   : %.2f\n", cy->diameter);
//         printf("    Height     : %.2f\n", cy->height);
//         printf("    Color      : R=%d, G=%d, B=%d\n",
//             (int)cy->color.r,
//             (int)cy->color.g,
//             (int)cy->color.b);
//         i++;
//     }
// }
