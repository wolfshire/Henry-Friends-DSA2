#pragma once
#include <GL\glew.h>
#include <string>
#include "shader.h"
#include "mattype.h"
#include "texture.h"
using namespace std;

class Material
{
public:
	Material(EMaterialType, string);
	Material(EMaterialType, Shader*);
    Material(EMaterialType, Shader*, Texture*);

	Shader* getShader();
	EMaterialType getType();
	int getDataSize();

    void readyGL();
private:
	Shader* shader;
	EMaterialType type;
    Texture* texture;
};