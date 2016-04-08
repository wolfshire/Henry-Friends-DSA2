#include <iostream>
#include "SOIL.h"
#include "texture.h"
using namespace std;

Texture::Texture(string image)
{
	loadImage(image);
}

GLuint Texture::getId() { return id; }

void Texture::loadImage(string image)
{
    string path = TEX_DIR + image;
	const char* imageName = path.c_str();
    id = SOIL_load_OGL_texture(imageName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

	if (id == 0)
	{
		cout << "Error loading texture: " << image << endl;
		const char* missName = (TEX_DIR + MISSING).c_str();
		id = SOIL_load_OGL_texture(missName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}

	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}