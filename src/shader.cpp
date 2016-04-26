#include <GL\glew.h>
#include <string>
#include <fstream>
#include <iostream>
#include "shader.h"

Shader::Shader(std::string name)
{
    load(name);
}

GLuint Shader::getProgram()
{
	return program;
}

GLuint Shader::getUniformLocation(std::string name)
{
    return uniforms[name];
}

void Shader::bind()
{
    glUseProgram(program);
}

void Shader::addUniform(std::string name)
{
    //if the key doesn't already exist, add it
    if (uniforms.find(name) == uniforms.end())
        uniforms[name] = glGetUniformLocation(program, name.c_str());
}

std::string Shader::readText(std::string filename, std::vector<std::string>* unis)
{
    std::cout << "Reading shader file: " << filename << std::endl;
    std::ifstream file("shaders\\" + filename);
    std::string line;
    std::string text;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.find("uniform") != std::string::npos)
            {
                std::string part = split(line, ' ')[2];
                unis->push_back(part.substr(0, part.length() - 1));
            }

            text += line + "\n";
        }

        file.close();
    }

    std::cout << "Finished read" << std::endl;
	std::cout << text << std::endl;
	return text;
}

void Shader::load(std::string name)
{
    std::cout << "Loading shader: " << name << std::endl;

    std::vector<std::string>* unis = new std::vector<std::string>();
    std::string v = readText(name + ".vs", unis);
    std::string f = readText(name + ".fs", unis);
    const char* vert = v.c_str();
    const char* frag = f.c_str();

    std::cout << "Compiling vertex shader" << std::endl;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vert, NULL);
    glCompileShader(vs);

    int success = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (GL_TRUE != success)
    {
        std::cout << "ERROR: GL vertex shader index " << vs << " did not compile" << std::endl;
        exit(-1);
    }

    std::cout << "Compiling fragment shader" << std::endl;
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &frag, NULL);
    glCompileShader(fs);

    success = -1;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (GL_TRUE != success)
    {
        std::cout << "ERROR: GL fragment shader index " << fs << " did not compile" << std::endl;
        exit(-1);
    }

    std::cout << "Reserving pointer for shader" << std::endl;
    program = glCreateProgram();

    if (program == 0)
    {
        std::cout << "ERROR: Unable to create program space for shader" << std::endl;
        exit(-1);
    }

    std::cout << "Linking vertex and fragment" << std::endl;
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glGetShaderiv(program, GL_LINK_STATUS, &success);
    if (GL_TRUE != success)
    {
        std::cout << "ERROR: shader '" << name << "' did not link properly" << std::endl;
        exit(-1);
    }

    glUseProgram(program);

    //add all uniforms to map
    while (unis->size() > 0)
    {
        addUniform(unis->at(unis->size() - 1));
        unis->pop_back();
    }

    glUseProgram(0);

    std::cout << "Loaded shader!" << std::endl;
}

std::vector<std::string> &Shader::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> Shader::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}