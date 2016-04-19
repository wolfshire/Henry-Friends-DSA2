#pragma once
#include <GL\glew.h>
#include <string>
#include <unordered_map>
#include "shader.h"

class ShaderManager
{
public:
	static void init();
	static Shader* getDefaultShader();
	static Shader* getShader(std::string);

	static ShaderManager* instance;
private:
    void load(std::string);

	ShaderManager();
	~ShaderManager();

	std::unordered_map<std::string, Shader*> loadedShaders;
};