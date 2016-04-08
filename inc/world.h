#pragma once
#include <vector>
#include "gameobject.h"
using namespace std;

class World
{
public:
	World();
	~World();

	void addObject(GameObject*);

	void init();
	void update();
	void render();
private:
	vector<GameObject*> objects;
};