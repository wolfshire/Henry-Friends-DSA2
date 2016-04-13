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
    Asteroid(double);
    Asteroid(double, Transform*);
    virtual void init();
    virtual void update();
    static GameObject* createAsteroid(double);
    static GameObject* createAsteroid(double, Transform*);

    double moveSpeed = 5.0f;
private:
    Transform* trans;
};

