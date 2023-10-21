#ifndef __RAY_H__
#define __RAY_H__

#include <cglm/cglm.h>
#include "types.h"

typedef struct {
    vec3 cam_pos;
    f32 yaw;
    f32 pitch;
    vec3 start;
    vec3 end;
} ray_t;

void init_ray(ray_t *ray, vec3 cam_pos, f32 yaw, f32 pitch);
void ray_step(ray_t *ray, f32 step);
f32 ray_length(ray_t *ray);
f32* ray_end(ray_t *ray);

#endif