#include "mesh.h"

void draw_mesh(const mesh_t *mesh, u32 texture_id){
    glBindVertexArray(mesh->VAO);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);

    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(texture_id, 0);

    //Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    // Texture data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->TBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count / 3);


    glDisableVertexAttribArray(0);

    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
