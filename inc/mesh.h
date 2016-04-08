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
	int getDataCount();

	vector<int> indices;
	vector<float> data;
	bool hasUVs;
	bool hasNormals;
};