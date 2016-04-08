#include "mesh.h"

Mesh::Mesh() {}
Mesh::~Mesh() {}

int Mesh::getNumIndices()
{
	return indices.size();
}

int Mesh::getDataCount()
{
	return data.size();
}
