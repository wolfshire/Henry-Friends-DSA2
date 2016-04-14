#pragma once
#include "gamec.h"

class Transform;
class Asteroid : public GameComponent
{
public:
    Asteroid();
    void update() override;

    float moveSpeed = 5.0f;
};

