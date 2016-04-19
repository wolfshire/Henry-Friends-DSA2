#include <GLFW\glfw3.h>
#include "flymove.h"
#include "gameobject.h"
#include "gametime.h"
#include "input.h"
#include "transform.h"

FlyMove::FlyMove()
{
	type = EGameComponentType::FLY_MOVE;
}

void FlyMove::update()
{
	if (Input::getKey(GLFW_KEY_S))
	{
		transform->pos.z -= moveSpeed * GameTime::dt;
	}
	if (Input::getKey(GLFW_KEY_W))
	{
        transform->pos.z += moveSpeed * GameTime::dt;
	}
	if (Input::getKey(GLFW_KEY_D))
	{
        transform->pos.x += moveSpeed * GameTime::dt;
	}
	if (Input::getKey(GLFW_KEY_A))
	{
        transform->pos.x -= moveSpeed * GameTime::dt;
	}
	if (Input::getKey(GLFW_KEY_SPACE))
	{
        transform->pos.y -= moveSpeed * GameTime::dt;
	}
	if (Input::getKey(GLFW_KEY_LEFT_SHIFT))
	{
        transform->pos.y += moveSpeed * GameTime::dt;
	}
}