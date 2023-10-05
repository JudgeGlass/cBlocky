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
    camera->position[0] -= amt;
}

void move_camera_forward(camera_t *camera, f32 amt){
    // vec3 scale_amt;
    // vec3 original_cam_front;
    // glm_vec3_copy(camera->cam_front, original_cam_front);
    
    // glm_vec3_scale(camera->cam_front, amt, scale_amt);

    camera->position[2] -= amt;

    //glm_vec3_add(camera->position, scale_amt, camera->position);
}

void move_camera_backward(camera_t *camera, f32 amt){
    // vec3 scale_amt;
    // glm_vec3_scale(camera->cam_front, -amt, scale_amt);

    // glm_vec3_add(camera->position, scale_amt, camera->position);
    camera->position[2] += amt;
}

void move_camera_right(camera_t *camera, f32 amt){
    camera->position[0] -= amt;
}