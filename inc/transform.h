#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>

using namespace glm;

class Transform
{
public:
	Transform();
    Transform(vec3,vec3,vec3);
	~Transform();
    mat4 getModelMatrix();

	vec3 pos;
	quat rot;
	vec3 scale;
};