#include "crosshair.h"
#include "shadermanager.h"
#include "shader.h"
#include "texturemanager.h"
#include "texture.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>

Crosshair::Crosshair()
{

}

Crosshair::Crosshair(int xx, int yy)
{
    x = xx - 16;
    y = yy - 16;

    init();
}

Crosshair::~Crosshair()
{

}

void Crosshair::init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /*float points[] = {
        x, y, 0, 0,
        x + 32, y, 1, 0,
        x + 32, y + 32, 1, 1,
        x, y + 32, 0, 1
    };*/

    float points[] = {
        0, 0, 0, 0,
        x, 0, 1, 0,
        x, y, 1, 1,
        0, x, 0, 1
    };

    int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    float stride = sizeof(float) * 4;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, stride, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, stride, (void*)(2 * sizeof(float)));

    model = glm::translate(glm::mat4(), glm::vec3(1280 / 2, 720 / 2, 0.0f));
}

void Crosshair::render()
{
    Shader* gui = ShaderManager::getShader("gui");
    gui->bind();

    Texture* tex = TextureManager::instance->getTexture("crosshair.png");
    tex->bind();

    glBindVertexArray(vao);

    glUniformMatrix4fv(gui->getUniformLocation("model"), 1, GL_FALSE,
        glm::value_ptr(glm::mat4()));//model));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}