#pragma once
#include <GL\glew.h>

class Texture
{
public:
	Texture(GLuint);
    ~Texture();

	GLuint getId();
    void bind();

    GLuint id;
};