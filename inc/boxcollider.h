#pragma once
#include "collider.h"
#include "boundingbox.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(Mesh*);
    ~BoxCollider();

    void init() override;

    bool isColliding(Collider*) override;
    BoundingBox getTransformedBoundingBox();
    BoundingBox getBoundingBox();
    glm::vec3 getBounds();

	bool colliding = false;

    glm::vec3 min;
    glm::vec3 max;
protected:
    void calculate() override;
};