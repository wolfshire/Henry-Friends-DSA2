#include "move.h"
#include "input.h"
#include "transform.h"
#include "gametime.h"

Move::Move(int up, int down, int left, int right, int forward, int backward)
{
    type = EGameComponentType::MOVE;

    _up = up;
    _down = down;
    _left = left;
    _right = right;
    _for = forward;
    _back = backward;
}

void Move::update()
{
    if (Input::getKey(_up))
    {
        transform->pos.y -= moveSpeed * GameTime::dt;
    }
    if (Input::getKey(_down))
    {
        transform->pos.y += moveSpeed * GameTime::dt;
    }
    if (Input::getKey(_left))
    {
        transform->pos.x += moveSpeed * GameTime::dt;
    }
    if (Input::getKey(_right))
    {
        transform->pos.x -= moveSpeed * GameTime::dt;
    }
    if (Input::getKey(_for))
    {
        transform->pos.z -= moveSpeed * GameTime::dt;
    }
    if (Input::getKey(_back))
    {
        transform->pos.z += moveSpeed * GameTime::dt;
    }
}