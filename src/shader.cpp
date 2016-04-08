#include <string>
#include "shader.h"
using namespace std;

Shader::Shader(GLuint loc)
{
	shader = loc;
}

GLuint Shader::getProgram()
{
	return shader;
}

void Shader::addUniform(string name)
{
    unordered_map<string, GLuint>::const_iterator i = uniforms.find(name);

    //if the key doesn't already exist, add it
    if (i == uniforms.end())
        uniforms[name] = glGetUniformLocation(shader, name.c_str());
}

GLuint Shader::getUniformLocation(string name)
{
	return uniforms[name];
}

void Shader::setUniformi(string name, int value)
{
	glProgramUniform1i(shader, getUniformLocation(name), value);
}

void Shader::setUniformf(string name, float value)
{
	glProgramUniform1f(shader, getUniformLocation(name), value);
}

void Shader::setUniformd(string name, double value)
{
	glProgramUniform1d(shader, getUniformLocation(name), value);
}

void Shader::setUniform2f(string name, const vec2& value)
{
	glProgramUniform2f(shader, getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform3f(string name, const vec3& value)
{
	glProgramUniform3f(shader, getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform4f(string name, const vec4& value)
{
    glProgramUniform4f(shader, getUniformLocation(name), value.x, value.y, value.z, value.w);
}