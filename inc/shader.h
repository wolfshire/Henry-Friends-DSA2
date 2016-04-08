#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include <unordered_map>
using namespace std;
using namespace glm;

class Shader
{
public:
	Shader(GLuint);

	GLuint getProgram();
    void addUniform(string);
	GLuint getUniformLocation(string);
	void setUniformi(string, int);
	void setUniformf(string, float);
	void setUniformd(string, double);
	void setUniform2f(string, const vec2&);
	void setUniform3f(string, const vec3&);
	void setUniform4f(string, const vec4&);
private:
	GLuint shader;
	unordered_map<string, GLuint> uniforms;
};