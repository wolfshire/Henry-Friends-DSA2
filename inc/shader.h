#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace glm;

class Shader
{
public:
	Shader(std::string);

	GLuint getProgram();
    void bind();
	GLuint getUniformLocation(std::string);
private:
    void load(std::string);
    std::string readText(std::string, std::vector<std::string>*);
    void addUniform(std::string);
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);

	GLuint program;
	std::unordered_map<std::string, GLuint> uniforms;
};