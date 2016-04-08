#pragma once
#include <glm\glm.hpp>
using namespace glm;

class Vertex
{
public:
	Vertex();
	Vertex(vec3);
	Vertex(vec3, vec2);
	Vertex(vec3, vec2, vec3);
	~Vertex();

	bool operator==(const Vertex);

	const static int SIZE = 8;
	vec3 pos;
	vec2 uv;
	vec3 norm;
};