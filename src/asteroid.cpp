#include "asteroid.h"
#include "gameobject.h"
#include "gametime.h"
#include "input.h"
#include "transform.h"

Asteroid::Asteroid()
{
    type = EGameComponentType::ASTEROID;
}

Asteroid::Asteroid(float speed)
{
	moveSpeed = speed;
}

void Asteroid::init()
{
    transform = gameObject->transform;

    gameObject->tag = EGameObjectType::GO_ASTEROID;
}

void Asteroid::update()
{
    transform->pos.y += moveSpeed * GameTime::dt;
}