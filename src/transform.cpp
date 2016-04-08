#include "transform.h"

Transform::Transform()
{
	pos = vec3(0.0, 0.0, 0.0);
    rot = quat();
	scale = vec3(1.0, 1.0, 1.0);
}

Transform::Transform(vec3 p, vec3 r, vec3 s)
{
    pos = p;
    rot = quat(r);
    scale = s;
}

Transform::~Transform() {}

mat4 Transform::getModelMatrix()
{
    return glm::translate(mat4(), vec3(pos.x, -pos.y, pos.z)) * glm::mat4_cast(rot) * glm::scale(mat4(), scale);
}
