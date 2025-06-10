#ifndef TEST_H
#define TEST_H

#include "../includes/entries.h"
#include "../includes/vector_ops.h"
#include "../includes/object_array.h"
#include "../includes/gc.h"
#include "../includes/intersect.h"
#include "../includes/window.h"

t_object_vector init_scene_objects(void);
void init_scene(t_scene *scene);

#endif 