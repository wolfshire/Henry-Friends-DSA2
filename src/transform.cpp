#include "transform.h"

Transform::Transform()
{
	pos = glm::vec3(0.0, 0.0, 0.0);
    rot = glm::quat();
	scale = glm::vec3(1.0, 1.0, 1.0);

    oldPos = pos;
    oldRot = rot;
    oldScale = scale;

    parent = nullptr;
    parentMatrix = glm::mat4();
}

Transform::Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s)
{
    pos = p;
    rot = glm::quat(r);
    scale = s;

    oldPos = pos;
    oldRot = rot;
    oldScale = scale;

    parent = nullptr;
    parentMatrix = glm::mat4();
}

void Transform::setTransform(Transform* other) {
	pos.x = other->transform->pos.x;
	pos.y = other->transform->pos.y;
	pos.z = other->transform->pos.z;
	rot.x = other->transform->rot.x;
	rot.y = other->transform->rot.y;
	rot.z = other->transform->rot.z;
	rot.w = other->transform->rot.w;
}

Transform::~Transform() {}

void Transform::update()
{
    oldPos = pos;
    oldRot = rot;
    oldScale = scale;
}

bool Transform::hasChanged()
{
    if (parent != nullptr && parent->hasChanged())
        return true;

    if (pos != oldPos)
        return true;

    if (rot != oldRot)
        return true;

    if (scale != oldScale)
        return true;

    return false;
}

void Transform::setParent(Transform* par)
{
    parent = par;
}

glm::mat4 Transform::getTransformation()
{
    glm::mat4 trans = glm::translate(glm::mat4(), pos);
    glm::mat4 mrot = glm::mat4_cast(rot);
    glm::mat4 mscale = glm::scale(glm::mat4(), scale);

    return getParentMatrix() * (trans * (mrot * mscale));
}

glm::mat4 Transform::getParentMatrix()
{
    if (parent != nullptr && parent->hasChanged())
        parentMatrix = parent->getTransformation();

    return parentMatrix;
}

void Transform::rotate(glm::vec3 euler)
{
    rot = glm::normalize(rot * glm::quat(euler));
}

