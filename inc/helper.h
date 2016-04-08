#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<string> split(string s, char delim)
{
	vector<string> elems;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
		elems.push_back(item);

	return elems;
}

vector<float> toVectorFloat(vector<Vertex> verts, bool hasUV, bool hasNormal)
{
	vector<float> data;

	for (int i = 0; i < verts.size(); i++)
	{
		data.push_back(verts[i].pos.x);
		data.push_back(verts[i].pos.y);
		data.push_back(verts[i].pos.z);

		if (hasUV)
		{
			data.push_back(verts[i].uv.x);
			data.push_back(verts[i].uv.y);
		}

		if (hasNormal)
		{
			data.push_back(verts[i].norm.x);
			data.push_back(verts[i].norm.y);
			data.push_back(verts[i].norm.z);
		}
	}

	return data;
}