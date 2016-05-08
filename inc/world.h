#pragma once
#include <vector>
#include "gameobject.h"
#include "transform.h"
#include "texture.h"
#include "material.h"
using namespace std;

class World
{
public:
	World();
	~World();

	void addObject(GameObject*);
    GameObject* removeObjectAt(unsigned int);

	void init();
	void update();
	void render();

	void spawnAsteroid(Transform*);

	void buildCity();
	void buildSkyscraper(Texture*, Material*, vec3, vec3);
	void buildPlatform(Texture*, Material*, vec3, vec3);
private:
	vector<GameObject*> objects;
    vector<Transform*> spawns;
	int fistIndex;

    Material* mat_blue;
    Material* mat_red;
    Material* mat_green;
};