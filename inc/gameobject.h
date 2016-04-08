#pragma once
#include <vector>
#include "gamec.h"
#include "transform.h"
using namespace std;

class GameObject
{
public:
	GameObject();
    GameObject(vec3, vec3, vec3);
	~GameObject();

	void addComponent(GameComponent*);

	//gets the first component from the list of type T
	template <typename T>
	T getComponent(T);

	void init();
	void update();
	void render();

	GameObject* getParent();
	void setParent(GameObject*);
	int getNumChildren();
	void addChild(GameObject*);
	GameObject* getChild(int);

	Transform* transform;
private:
	vector<GameComponent*> components;
	vector<GameObject*> children;
	GameObject* parent;
};