#pragma once
#include <vector>
#include "vertex.h"
using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();

	int getNumIndices();

	vector<int> indices;
	vector<glm::vec3> pos;
    vector<glm::vec2> uvs;
    vector<glm::vec3> norms;
	bool hasUVs;
	bool hasNormals;
};