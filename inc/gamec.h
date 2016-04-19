#pragma once
#include "igamec.h"
#include "gamectype.h"

class GameObject;
class Transform;
class GameComponent : public IGameComponent
{
public:
	GameComponent();
	~GameComponent();

    virtual void init();
    virtual void update();
    virtual void render();

	EGameComponentType type;
	GameObject* gameObject;
    Transform* transform;
};