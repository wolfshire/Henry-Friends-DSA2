#pragma once
#include "gamec.h"

class Transform;
class Asteroid : public GameComponent
{
public:
    Asteroid();
    Asteroid(float);
    void update() override;

    float moveSpeed = 5.0f;
};
