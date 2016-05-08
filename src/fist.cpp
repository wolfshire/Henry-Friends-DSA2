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

void Fist::update()
{
<<<<<<< HEAD
	//cout << "Fist update" << endl;
	transform->pos += glm::vec3(glm::vec4(0, 0, 5+ moveSpeed * GameTime::dt, 0) * transform->rot);
=======
	transform->pos += glm::vec3(glm::vec4(0, 0, moveSpeed * GameTime::dt, 0) * transform->rot);
>>>>>>> e704e8ea8540283efc8b2b81914d12f3d797a891
}

void Fist::punch() 
{
	cout << "Fist punch" << endl;
}

void Fist::reset() 
{

}
