#pragma once
#include <string>
#include <vector>
#include "mesh.h"

class Model
{
public:
	Model(std::string);
	~Model();

	Mesh* getMesh();
private:
	void load();
	void readModelData();
	void genMeshData(std::vector<std::string>);

	const std::string MODEL_DIR = "models\\";
    std::string name;
	Mesh* mesh = nullptr;
};