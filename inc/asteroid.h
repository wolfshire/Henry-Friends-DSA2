#pragma once
#include "gamec.h"
#include "gameobject.h"
#include "gametime.h"
#include "transform.h"
#include "input.h"
#include "model.h"
#include "meshrenderer.h"
#include "material.h"
#include "shadermanager.h"

class Transform;
class Asteroid : public GameComponent
{
public:
    Asteroid();
    Asteroid(float);
    Asteroid(float, Transform*);
    void update() override;
    static GameObject* createAsteroid(float);
    static GameObject* createAsteroid(float, Transform*);
private:
    float moveSpeed = 5.0f;
};

