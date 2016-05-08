#pragma once
#include "gamec.h"

class Transform;
class Asteroid : public GameComponent
{
public:
    Asteroid();
    Asteroid(float);
    void init() override;
    void update() override;

    float moveSpeed = 10.0f;
};
