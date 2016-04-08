#include <iostream>
#include <fstream>
#include "model.h"
#include "helper.h"
using namespace std;

Model::Model(string modelName)
{
	name = modelName;
	load();
}

Model::~Model() {}

Mesh* Model::getMesh()
{
	return mesh;
}

void Model::load()
{
	cout << "Loading " << name << " model..." << endl;
	readModelData();
}

void Model::readModelData()
{
	cout << "Reading data" << endl;

	ifstream inFile;
	string line;
	vector<string> data;

	inFile.open(MODEL_DIR + name + ".obj");

	if (inFile.is_open())
	{
		while (getline(inFile, line))
			data.push_back(line);
		
		inFile.close();

		genMeshData(data);
	}
	else
		cout << "Failed to read model data" << endl;
}

void Model::genMeshData(vector<string> lines)
{
	vector<vec3> points;
	vector<vec2> uvs;
	vector<vec3> norms;
	vector<string> f;
	bool hasUVs = false;
	bool hasNormals = false;

	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i].find("vt") == 0)
		{
			hasUVs = true;
			vector<string> tokens = split(lines[i].substr(3, lines[i].length() - 3), ' ');
			uvs.push_back(vec2(stof(tokens[0]), stof(tokens[1])));
		}
		else if (lines[i].find("vn") == 0)
		{
			hasNormals = true;
			vector<string> tokens = split(lines[i].substr(3, lines[i].length() - 3), ' ');
			norms.push_back(vec3(stof(tokens[0]), stof(tokens[1]), stof(tokens[2])));
		}
		else if (lines[i].find("v") == 0)
		{
			vector<string> tokens = split(lines[i].substr(2, lines[i].length() - 2), ' ');
			points.push_back(vec3(stof(tokens[0]), stof(tokens[1]), stof(tokens[2])));
		}
		else if (lines[i].find("f") == 0)
		{
			vector<string> verts = split(lines[i].substr(2, lines[i].length() - 2), ' ');
			f.push_back(verts[0]);
			f.push_back(verts[1]);
			f.push_back(verts[2]);
		}
	}

	vector<string> indices;

	//create verts for all the data
	vector<Vertex> verts;
	for (int i = 0; i < f.size(); i++)
	{
		indices.clear();
		indices = split(f[i], '/');

		Vertex v;
		v.pos = points[stoi(indices[0]) - 1];

		if (hasUVs)
			v.uv = uvs[stoi(indices[1]) - 1];

		if (hasNormals)
			v.norm = norms[stoi(indices[2]) - 1];

		verts.push_back(v);
	}

	vector<int> index;
	vector<Vertex> nodup;
	nodup.push_back(verts[0]);
	index.push_back(0);
	int c = 0;
	for (int i = 1; i < verts.size(); i++)
	{
		bool eq = false;

		for (int k = 0; k < nodup.size(); k++)
		{
			if (verts[i] == nodup[k])
			{
				index.push_back(k);
				eq = true;
				break;
			}
		}

		if (!eq)
		{
			c++;
			index.push_back(nodup.size());
			nodup.push_back(verts[i]);
		}
	}

	if (mesh != NULL)
		delete mesh;

	mesh = new Mesh();
	mesh->indices = index;
	mesh->data = toVectorFloat(nodup, hasUVs, hasNormals);
	mesh->hasUVs = hasUVs;
	mesh->hasNormals = hasNormals;
}