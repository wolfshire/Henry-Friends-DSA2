#pragma once
#include <vector>
#include "gameobject.h"
#include "transform.h"
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

	void spawnAsteroid(float,float,float);

	void city();
	void buildSkyscraper();
private:
	vector<GameObject*> objects;
    vector<Transform*> spawns;
};