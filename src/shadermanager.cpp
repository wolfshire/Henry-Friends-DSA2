#include "shader.h"
#include "shadermanager.h"

ShaderManager* ShaderManager::instance = new ShaderManager();

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {}

void ShaderManager::init()
{
	instance->load("default");
    instance->load("color");
    instance->load("font");
}

Shader* ShaderManager::getDefaultShader() { return instance->loadedShaders["default"]; }

Shader* ShaderManager::getShader(std::string name)
{
	if (instance->loadedShaders[name] == NULL)
        instance->load(name);

	return instance->loadedShaders[name];
}

void ShaderManager::load(std::string name)
{
    loadedShaders[name] = new Shader(name);
}