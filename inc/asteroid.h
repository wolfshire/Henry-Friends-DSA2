#pragma once
#include "gamec.h"

class Transform;
class Asteroid : public GameComponent
{
public:
    Asteroid();
    virtual void init();
    virtual void update();

    double moveSpeed = 5.0f;
private:
    Transform* trans;
};

