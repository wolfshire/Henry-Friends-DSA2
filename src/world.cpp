#include "camera.h"
#include "flymove.h"
#include "world.h"
#include "mattype.h"
#include "model.h"
#include "material.h"
#include "meshrenderer.h"
#include "texture.h"
#include "texturemanager.h"
#include "shadermanager.h"
#include "asteroid.h"
#include "transform.h"
#include "fist.h"
#include <iostream>
#include "input.h"

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>		/* time */

World::World() {}
World::~World() {}

void World::addObject(GameObject* o)
{
	o->init();
    objects.push_back(o);
}

void World::init()
{
	//random seed
	srand(time(NULL));

    //objects
    GameObject* cam = new GameObject();
    cam->transform->pos.z = -10;
	//cam->transform->rot = glm::quat(0, 0, 0, 1);
    Camera* camera = new Camera();
    FlyMove* flymove = new FlyMove();
    cam->addComponent(camera);
    cam->addComponent(flymove);
    addObject(cam);

    Camera::setMain(camera);

    //spawn locations
    spawns.push_back(new Transform(vec3(100, -20, 0), vec3(0, 0, 0), vec3(4))); //city A >
    spawns.push_back(new Transform(vec3(-100, -20, 0), vec3(0, 0, 0), vec3(4))); //city B <
    spawns.push_back(new Transform(vec3(0, -20, 100), vec3(0, 0, 0), vec3(4))); //city C ^
    spawns.push_back(new Transform(vec3(0, -20, -100), vec3(0, 0, 0), vec3(4))); //city D v

    //textures
    Texture* tex_missing = TextureManager::instance->getTexture("emma.png");
    Texture* tex_blue = TextureManager::instance->getTexture("blue.png");
    Texture* tex_green = TextureManager::instance->getTexture("green.png");
	Texture* tex_red = TextureManager::instance->getTexture("red.png");

    //materials
    Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);
    Material* mat_blue = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_blue);
    Material* mat_green = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_green);
	Material *mat_red = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_red);

    //models
    Model* mod_cube = new Model("cube");
	Model* fistModel = new Model("cube");

	city();

	GameObject* fist = new GameObject();
	fist->transform->scale = vec3(.5, .9, .5);
	fist->transform->pos = vec3(0, 1, -10); //right below camera
	MeshRenderer* fistRenderer = new MeshRenderer(XYZ_UV, fistModel, mat_red);
	Fist* fistComponent = new Fist();
	fist->addComponent(fistComponent);
	fist->addComponent(fistRenderer);
	addObject(fist);
	fistIndex = objects.size() - 1;

    /*GameObject* parent = new GameObject();
    parent->transform->pos = vec3(3, 3, 3);
    MeshRenderer* parentRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, mod_cube, mat_red);
    parent->addComponent(parentRenderer);
    GameObject* child = new GameObject();
    child->transform->pos = vec3(1, 1, 1);
    MeshRenderer* childRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, mod_cube, mat_missing);
    child->addComponent(childRenderer);
    parent->addChild(child);
    addObject(parent);*/

    /*for (unsigned int i = 0; i < objects.size(); i++)
        (*objects[i]).init();*/
}

void World::update()
{
	int random = rand() % 400;
	if (random == 0)
		spawnAsteroid(spawns[0]);
	else if (random == 1)
		spawnAsteroid(spawns[1]);
	else if (random == 2)
		spawnAsteroid(spawns[2]);
	else if (random == 3)
		spawnAsteroid(spawns[3]);

	for (unsigned int i = 0; i < objects.size(); i++) {
		(*objects[i]).update();
		//if the object has left the play area
		if (objects[i]->transform->pos.y > 150 || objects[i]->transform->pos.y < -150 || objects[i]->transform->pos.x > 150 || objects[i]->transform->pos.x < -150 || objects[i]->transform->pos.z > 150 || objects[i]->transform->pos.z < -150) {
			//delete object
		}
	}
	if (Input::getKeyDown(GLFW_KEY_E)) {
		objects[fistIndex]->transform = objects[0]->transform;
		//cout << "e pressed" << endl;
	}
}

void World::render()
{
    for (unsigned int i = 0; i < objects.size(); i++)
        (*objects[i]).render();
}

void World::spawnAsteroid(Transform* t)
{
	cout << "spawn asteroid" << endl;
	Model* asteroidModel = new Model("asteroid");
	Texture* tex_missing = TextureManager::instance->getTexture("emma.png");
	Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);

	GameObject* asteroid = new GameObject();
	asteroid->transform = t;
	MeshRenderer* asteroidRenderer = new MeshRenderer(XYZ_UV, asteroidModel, mat_missing);
	Asteroid* asteroidComponent = new Asteroid();
	asteroid->addComponent(asteroidComponent);
	asteroid->addComponent(asteroidRenderer);
	addObject(asteroid);
}

//creating city
void World::city()
{
	//load city model
	Model* city_cube = new Model("cube");

	//city texture
	Texture* tex_city = TextureManager::instance->getTexture("emma.png");
	Texture* tex_city_platform = TextureManager::instance->getTexture("platform.png");
	Texture* tex_city_metal = TextureManager::instance->getTexture("metal.png");

	//city material
	Material* mat_city = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_city);
	Material* mat_city_platform = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_city_platform);
	Material* mat_city_building = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_city_metal);


	//create test cube
	GameObject* blue = new GameObject();
	blue->transform->pos = vec3(0,0,100);
	blue->transform->scale = vec3(3, 3, 3);
	MeshRenderer* blueRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, city_cube, mat_city);
	blue->addComponent(blueRenderer);
	addObject(blue);

	//create city platform
	GameObject* platform = new GameObject();
	platform->transform->pos = vec3(0, 15, 50);
	platform->transform->scale = vec3(100, 1, 100);
	MeshRenderer* platRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, city_cube, mat_city_platform);
	platform->addComponent(platRenderer);
	addObject(platform);

	//create building
	GameObject* building1 = new GameObject();
	building1->transform->pos = vec3(30, 0, 100);
	building1->transform->scale = vec3(5, 50, 5);
	MeshRenderer* buildingRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, city_cube, mat_city_building);
	building1->addComponent(buildingRenderer);
	addObject(building1);

	//create building
	GameObject* building2 = new GameObject();
	building2->transform->pos = vec3(-30, 0, 100);
	building2->transform->scale = vec3(5, 30, 5);
	MeshRenderer* buildingRenderer2 = new MeshRenderer(EVertexFormat::XYZ_UV, city_cube, mat_city_building);
	building2->addComponent(buildingRenderer2);
	addObject(building2);
}

void World::buildSkyscraper()
{
	//nothin' yet
}
