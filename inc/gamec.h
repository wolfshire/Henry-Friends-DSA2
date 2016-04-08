#pragma once
#include "igamec.h"
#include "gamectype.h"

class GameObject;
class GameComponent : public IGameComponent
{
public:
	GameComponent();
	~GameComponent();

	EGameComponentType type;
	GameObject* gameObject;
};