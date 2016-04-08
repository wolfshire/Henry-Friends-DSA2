#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include "shader.h"
#include "shadermanager.h"
using namespace std;

ShaderManager* ShaderManager::instance = new ShaderManager();

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {}

void ShaderManager::init()
{
	load("default");
	load("color");
    load("font");

    //instance->loadedShaders["default"]->addUniform("tex");
}

Shader* ShaderManager::getDefaultShader() { return instance->loadedShaders["default"]; }

Shader* ShaderManager::getShader(string name)
{
	if (instance->loadedShaders[name] == NULL)
		load(name);

	return instance->loadedShaders[name];
}

string ShaderManager::readText(string filename)
{
	cout << "Reading contents" << endl;
	ifstream file("shaders\\" + filename);
	string line;
	string text;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			text += line + "\n";
		}

		file.close();
	}

	cout << "Finished read" << endl;
	return text;
}

void ShaderManager::load(string name)
{
	cout << "Loading shader: " << name << endl;

	string v = readText(name + ".vs");
	string f = readText(name + ".fs");
	const char* vert = v.c_str();
	const char* frag = f.c_str();

	cout << "Compiling vertex shader" << endl;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vert, NULL);
	glCompileShader(vs);

	int success = -1;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (GL_TRUE != success)
	{
		cout << "ERROR: GL vertex shader index " << vs << " did not compile" << endl;
		exit(-1);
	}

	cout << "Compiling fragment shader" << endl;
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &frag, NULL);
	glCompileShader(fs);

	success = -1;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (GL_TRUE != success)
	{
		cout << "ERROR: GL fragment shader index " << fs << " did not compile" << endl;
		exit(-1);
	}

	cout << "Reserving pointer for shader" << endl;
	Shader* shader = new Shader(glCreateProgram());
	instance->loadedShaders[name] = shader;

	if (shader->getProgram() == 0)
	{
		cout << "ERROR: Unable to create program space for shader" << endl;
		exit(-1);
	}

	cout << "Linking vertex and fragment" << endl;
	glAttachShader(shader->getProgram(), vs);
	glAttachShader(shader->getProgram(), fs);
	glLinkProgram(shader->getProgram());

	glGetShaderiv(shader->getProgram(), GL_LINK_STATUS, &success);
	if (GL_TRUE != success)
	{
		cout << "ERROR: shader '" << name << "' did not link properly" << endl;
		exit(-1);
	}

	cout << "Loaded!" << endl;
}