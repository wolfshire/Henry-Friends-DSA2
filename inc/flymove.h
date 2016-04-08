#pragma once
#include "gamec.h"

class Transform;
class FlyMove : public GameComponent
{
public:
	FlyMove();
	virtual void init();
	virtual void update();

	double moveSpeed = 5.0f;
private:
	Transform* trans;
};