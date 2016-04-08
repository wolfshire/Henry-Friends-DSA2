#pragma once
#include <GL\glew.h>
#include <string>
#include "color.h"
using namespace std;

class Texture
{
public:
	Texture(string);

	GLuint getId();
private:
	void loadImage(string);

	const string TEX_DIR = "textures\\";
	const string MISSING = "missing.png";
	GLuint id;
};