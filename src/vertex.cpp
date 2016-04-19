#include "vertex.h"

Vertex::Vertex() {}
Vertex::Vertex(vec3 pos) : Vertex(pos, vec2(0, 0)) {}
Vertex::Vertex(vec3 pos, vec2 uv) : Vertex(pos, uv, vec3(0, 1, 0)) {}
Vertex::Vertex(vec3 pos, vec2 uv, vec3 norm)
{
	this->pos = pos;
	this->uv = uv;
	this->norm = norm;
}

Vertex::~Vertex() {}

bool Vertex::operator==(const Vertex other)
{
	return pos == other.pos && uv == other.uv && norm == other.norm;
}