#include "boundingbox.h"

BoundingBox::BoundingBox()
{
    min = glm::vec3(0);
    max = glm::vec3(0);
    center = (min + max) / 2.0f;
}

BoundingBox::BoundingBox(glm::vec3 _min, glm::vec3 _max)
{
    min = _min;
    max = _max;
    center = (min + max) / 2.0f;
}

BoundingBox::~BoundingBox()
{

}

bool BoundingBox::contains(BoundingBox& other)
{
    return min.x < other.min.x &&
        min.y < other.min.y &&
        min.z < other.min.z &&
        max.x > other.max.x &&
        max.y > other.max.y &&
        max.z > other.max.z;
}

glm::vec3 BoundingBox::getSize()
{
    return max - min;
}