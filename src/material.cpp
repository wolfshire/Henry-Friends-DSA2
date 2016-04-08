#include "material.h"
#include "shadermanager.h"

Material::Material(EMaterialType tp, string name)
{
	type = tp;
	shader = ShaderManager::getShader(name);
}

Material::Material(EMaterialType tp, Shader* shade)
{
	type = tp;
	shader = shade;
}

Material::Material(EMaterialType tp, Shader* shade, Texture* tex)
{
    type = tp;
    shader = shade;
    texture = tex;
}

Shader* Material::getShader()
{
	return shader;
}

EMaterialType Material::getType()
{
	return type;
}

int Material::getDataSize()
{
	switch (type)
	{
	case EMaterialType::DEFAULT:
		return 32;
	case EMaterialType::COLOR:
		return 28;
	default:
		return 0;
	}
}

void Material::readyGL()
{
    glUseProgram(getShader()->getProgram());
    glBindTexture(GL_TEXTURE_2D, texture->getId());
}