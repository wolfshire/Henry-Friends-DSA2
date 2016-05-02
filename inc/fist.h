#pragma once
#include "gamec.h"
#include <glm\gtc\matrix_transform.hpp>

class Transform;
class Fist : public GameComponent
{
public:
	Fist();
	Fist(float);
	Fist(float, Transform*);
	void update() override;
	void punch();
	void reset();
	
	float moveSpeed = 5.0f;
	//keep moveSpeed to limit amount of punches per n seconds?
};
#pragma once
