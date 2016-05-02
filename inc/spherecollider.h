#pragma once
#include "collider.h"

class SphereCollider : public Collider
{
public:
    SphereCollider(Mesh*, float);
    ~SphereCollider();
private:
    float radius;
};