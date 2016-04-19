#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include "gamec.h"

class Transform : public GameComponent
{
public:
	Transform();
    Transform(glm::vec3, glm::vec3, glm::vec3);
	~Transform();
    glm::mat4 getModelMatrix();

    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;
};