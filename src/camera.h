#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL/glew.h>
#include <cglm/cglm.h>

#include "types.h"

typedef struct {
    vec3 position;
    vec3 cam_front;
    vec3 cam_up;
    vec3 rotation;
    mat4 view_matrix;
    mat4 projection_matrix;
    mat4 model;
} camera_t;

void init_camera(camera_t *camera, u32 program_id);
void render_camera(camera_t *camera, u32 program_id);

void move_camera_left(camera_t *camera, f32 amt);
void move_camera_right(camera_t *camera, f32 amt);
void move_camera_forward(camera_t *camera, f32 amt);
void move_camera_backward(camera_t *camera, f32 amt);
void move_camera_vertical(camera_t *camera, f32 amt);

#endif