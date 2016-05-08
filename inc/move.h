#pragma once
#include "gamec.h"

class Move : public GameComponent
{
public:
    //up, down, left, right, forward, backward
    Move(int, int, int, int, int, int);
    void update() override;

    float moveSpeed = 5.0f;
private:
    int _up;
    int _down;
    int _left;
    int _right;
    int _for;
    int _back;
};