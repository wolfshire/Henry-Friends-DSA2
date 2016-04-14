#include <iostream>
#include "texture.h"
using namespace std;

Texture::Texture(GLuint texID)
{
    id = texID;
}

Texture::~Texture()
{
    
}

GLuint Texture::getId() { return id; }

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}