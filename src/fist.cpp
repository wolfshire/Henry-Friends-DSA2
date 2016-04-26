#include "fist.h"
#include "gameobject.h"
#include "gametime.h"
#include "input.h"
#include "transform.h"

Fist::Fist()
{
	type = EGameComponentType::FIST;
}

Fist::Fist(float speed)
{
	moveSpeed = speed;
}

Fist::Fist(float speed, Transform* t)
{
	moveSpeed = speed;
	transform = t;

}

void Fist::update()
{
	//transform->rot *= moveSpeed * GameTime::dt;
	

}

void Fist::punch() 
{
	
}

void Fist::reset() 
{

}
