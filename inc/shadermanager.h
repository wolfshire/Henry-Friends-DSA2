#pragma once
#include <GL\glew.h>
#include <string>
#include <unordered_map>
#include "shader.h"
using namespace std;

class ShaderManager
{
public:
	static void init();
	static Shader* getDefaultShader();
	static Shader* getShader(string);

	static ShaderManager* instance;
private:
    static string readText(string);
    static void load(string);

	ShaderManager();
	~ShaderManager();

	unordered_map<string, Shader*> loadedShaders;
};