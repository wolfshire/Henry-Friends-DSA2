#pragma once
#include <GL\glew.h>
#include <FreeImage.h>
#include <cstring>

class Texture
{
public:
	//constructor/destructor
	Texture(GLuint);
	~Texture();
	//methods
	GLuint getId();
    void bind();
	void LoadTexture(std::string);
	//variables
	std::string m_sFileName;
    GLuint m_nTextureID;
};