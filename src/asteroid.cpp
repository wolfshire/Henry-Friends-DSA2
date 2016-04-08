#include "asteroid.h"
#include "gameobject.h"
#include "gametime.h"
#include "transform.h"
#include "input.h"

Asteroid::Asteroid()
{
    type = EGameComponentType::ASTEROID;
}

void Asteroid::init()
{
    trans = gameObject->transform;
}

void Asteroid::update()
{
    trans->pos.y -= moveSpeed * GameTime::dt;
    std::cout << "asteroid: " << trans->pos.y << std::endl;
}