#pragma once
#include "gamec.h"

class FlyMove : public GameComponent
{
public:
	FlyMove();
	void update() override;

	float moveSpeed = 5.0f;
};