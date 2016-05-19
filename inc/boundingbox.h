#pragma once
#include <glm\glm.hpp>

class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(glm::vec3, glm::vec3);
    ~BoundingBox();

    bool contains(BoundingBox&);
    glm::vec3 getSize();

    glm::vec3 min;
    glm::vec3 max;
    glm::vec3 center;
};