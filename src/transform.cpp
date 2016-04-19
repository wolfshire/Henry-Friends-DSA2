#include "transform.h"

Transform::Transform()
{
	pos = glm::vec3(0.0, 0.0, 0.0);
    rot = glm::quat();
	scale = glm::vec3(1.0, 1.0, 1.0);
}

Transform::Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s)
{
    pos = p;
    rot = glm::quat(r);
    scale = s;
}

Transform::~Transform() {}

glm::mat4 Transform::getModelMatrix()
{
    return glm::translate(glm::mat4(), glm::vec3(pos.x, pos.y, pos.z)) * glm::mat4_cast(rot) * glm::scale(glm::mat4(), scale);
}

void Transform::rotate(glm::vec3 euler)
{
    rot = glm::normalize(rot * glm::quat(euler));
}