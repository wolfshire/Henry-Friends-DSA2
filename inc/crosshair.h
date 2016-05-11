#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

class Crosshair
{
public:
    Crosshair();
    Crosshair(int, int);
    ~Crosshair();

    void render();
private:
    void init();

    int x;
    int y;

    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    glm::mat4 model;
};