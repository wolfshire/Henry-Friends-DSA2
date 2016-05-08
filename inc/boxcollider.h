#pragma once
#include "collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(Mesh*);
    ~BoxCollider();

    void init() override;

    bool isColliding(Collider*) override;
protected:
    void calculate() override;
private:
    glm::vec3 min;
    glm::vec3 max;
};