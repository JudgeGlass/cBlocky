#include "camera.h"

void init_camera(camera_t *camera, u32 program_id) {
    glm_vec3_zero(camera->position);
    glm_vec3_zero(camera->rotation);

    camera->position[0] = 5.f;
    camera->position[1] = 65.0f;
    camera->position[2] = 25.0f;

    camera->cam_front[0] = 0.f;
    camera->cam_front[1] = 0.f;
    camera->cam_front[2] = -1.0f;

    camera->cam_up[0] = 0.0f;
    camera->cam_up[1] = 1.0f;
    camera->cam_up[2] = 0.0f;

    camera->yaw = -90.0f;
    camera->pitch = 0.0f;
}

void render_camera(camera_t *camera, u32 program_id) {
    GLint viewport_data[4];
    glGetIntegerv(GL_VIEWPORT, viewport_data);
    
    glm_perspective(glm_rad(45.0f), (f32) viewport_data[2] / (f32) viewport_data[3], 0.1f, 500.0f, camera->projection_matrix);
    glm_mat4_identity(camera->model);
    vec3 dest;
    glm_vec3_add(camera->position, camera->cam_front, dest);
    glm_lookat(camera->position, dest, camera->cam_up, camera->view_matrix);
    mat4 MVP;
    glm_mat4_mul(camera->projection_matrix, camera->view_matrix, MVP);
    glm_mat4_mul(MVP, camera->model, MVP);

    u32 matrix_location = glGetUniformLocation(program_id, "MVP");
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, (f32 *) MVP);
}

void move_camera_left(camera_t *camera, f32 amt){
    vec3 left;
    glm_vec3_cross(camera->cam_front, camera->cam_up, left);
    glm_vec3_normalize(left);
    glm_vec3_scale(left, CAMERA_SPEED * amt, left);
    glm_vec3_sub(camera->position, left, camera->position);
}

void move_camera_forward(camera_t *camera, f32 amt){
    glm_vec3_scale(camera->cam_front, CAMERA_SPEED * amt, camera->cam_front);
    glm_vec3_add(camera->position, camera->cam_front, camera->position);
}

void move_camera_backward(camera_t *camera, f32 amt){
    glm_vec3_scale(camera->cam_front, CAMERA_SPEED * amt, camera->cam_front);
    glm_vec3_sub(camera->position, camera->cam_front, camera->position);
}

void move_camera_right(camera_t *camera, f32 amt){
    vec3 right;
    glm_vec3_cross(camera->cam_front, camera->cam_up, right);
    glm_vec3_normalize(right);
    glm_vec3_scale(right, CAMERA_SPEED * amt, right);
    glm_vec3_add(camera->position, right, camera->position);
}

void move_camera_vertical(camera_t *camera, f32 amt){
    glm_vec3_scale(camera->cam_up, CAMERA_SPEED * amt, camera->cam_up);
    glm_vec3_add(camera->position, camera->cam_up, camera->position);
}

void update_camera(camera_t *camera){
    u32 mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    
    f32 x_offset = mouse_x - WINDOW_WIDTH / 2.0f;
    f32 y_offset = WINDOW_HEIGHT / 2.0f - mouse_y;

    const f32 sensitivity = 0.1f;
    x_offset *= sensitivity;
    y_offset *= sensitivity;

    camera->yaw += x_offset;
    camera->pitch += y_offset;


    if(camera->pitch > 89.0f){
        camera->pitch = 89.0f;
    }else if(camera->pitch < -89.0f){
        camera->pitch = -89.0f;
    }

    if(camera->yaw > 360.0f){
        camera->yaw = 0.0f;
    }else if(camera->yaw < 0.0f)
        camera->yaw = 360.0f;
    
    vec3 direction;
    direction[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    direction[1] = sin(glm_rad(camera->pitch));
    direction[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));

    // Used for raycasting later...
    //vec3 last_pos;

    // TODO: ADD RAYCASTING HERE

    glm_vec3_normalize(direction);
    glm_vec3_copy(direction, camera->cam_front);
}