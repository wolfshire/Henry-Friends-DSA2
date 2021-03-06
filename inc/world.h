#pragma once
#include <vector>
#include "gameobject.h"
#include "transform.h"
#include "texture.h"
#include "material.h"
#include "crosshair.h"
#include "octtree.h"
#include "fontmanager.h"
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
    void renderGui();

	void spawnAsteroid(vec3);
	void punchFist(Transform*);

    void buildOctTree();
	void buildCity();
	void buildSkyscraper(Texture*, Material*, vec3, vec3);
	void buildPlatform(Texture*, Material*, vec3, vec3);
	int Score();
	int CasualtyScore();
	string GameState();
	void changeGS(string);
	string WinState();

private:
	vector<GameObject*> objects;
    vector<vec3> spawns;
	int fistIndex;
	int numAsteroids;
	int score;
	int casualtyScore;
	string gameState;
	string winState;

    Crosshair crosshair;

    Material* mat_blue;
    Material* mat_red;
    Material* mat_green;
	Material* mat_sky;
    OctTree tree;

	float spawnTimer = 0.0f;
	float spawnFrequency = 3.0f;
};