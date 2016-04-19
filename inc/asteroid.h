#pragma once
#include "gamec.h"

class Transform;
class Asteroid : public GameComponent
{
public:
    Asteroid();
    Asteroid(float);
    Asteroid(float, Transform*);
    void update() override;
    //static GameObject* createAsteroid(float);
    //static GameObject* createAsteroid(float, Transform*);

    float moveSpeed = 5.0f;
};
