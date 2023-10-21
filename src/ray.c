#include "ray.h"

void init_ray(ray_t *ray, vec3 cam_pos, f32 yaw, f32 pitch){
    glm_vec3_copy(cam_pos, ray->cam_pos);
    ray->yaw = yaw;
    ray->pitch = pitch;

    glm_vec3_copy(cam_pos, ray->start);
    glm_vec3_copy(cam_pos, ray->end);
}

void ray_step(ray_t *ray, f32 step){
    f32 x, y, z;
    y = step * sin(glm_rad(ray->pitch));

    f32 d = sqrt(step * step - y * y);

    z = d * sin(glm_rad(ray->yaw));
    x = d * cos(glm_rad(ray->yaw));

    ray->end[0] += x;
    ray->end[1] += y;
    ray->end[2] += z;
}

f32 ray_length(ray_t *ray){
    return glm_vec3_distance(ray->start, ray->end);
}

f32* ray_end(ray_t *ray){
    return ray->end;
}