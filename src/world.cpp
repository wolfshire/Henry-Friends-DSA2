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
	cam->transform->pos.y = -50; 
	//cam->transform->rot = glm::quat(0, 0, 0, 1);
    Camera* camera = new Camera();
    FlyMove* flymove = new FlyMove();
    cam->addComponent(camera);
    cam->addComponent(flymove);
    addObject(cam);

	numAsteroids = 5;

    Camera::setMain(camera);

    //spawn locations
    spawns.push_back(new Transform(vec3(100, -20, 0), vec3(0, 0, 0), vec3(4))); //city A >
    spawns.push_back(new Transform(vec3(-100, -20, 0), vec3(0, 0, 0), vec3(4))); //city B <
    spawns.push_back(new Transform(vec3(0, -30, 100), vec3(0, 0, 0), vec3(4))); //city C ^
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
	Material* mat_red = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_red);

	//builds the City
	buildCity();


    //models
    Model* mod_cube = new Model("cube");
	

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
	int random = rand() % 100;
	if (random == 0)
		spawnAsteroid(spawns[0]);
	else if (random == 1)
		spawnAsteroid(spawns[1]);
	else if (random == 2)
		spawnAsteroid(spawns[2]);
	else if (random == 3)
		spawnAsteroid(spawns[3]);

	cout << random << endl;

	

	for (unsigned int i = 0; i < objects.size(); i++) {
		(*objects[i]).update();
		//if the object has left the play area
		if (objects[i]->transform->pos.y > 150 || objects[i]->transform->pos.y < -150 || objects[i]->transform->pos.x > 150 || objects[i]->transform->pos.x < -150 || objects[i]->transform->pos.z > 150 || objects[i]->transform->pos.z < -150) {
			//delete object
		}
	}
	if (Input::getKeyDown(GLFW_KEY_E)) {
		//punch	
		punchFist(Camera::getMain()->transform);
	
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
	Texture* tex_missing = TextureManager::instance->getTexture("meteorite.png");
	Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);

	GameObject* asteroid = new GameObject();
	asteroid->transform = t;
	MeshRenderer* asteroidRenderer = new MeshRenderer(XYZ_UV, asteroidModel, mat_missing);
	Asteroid* asteroidComponent = new Asteroid();
	asteroid->addComponent(asteroidComponent);
	asteroid->addComponent(asteroidRenderer);
	addObject(asteroid);
}

void World::punchFist(Transform* t) {

	Texture* tex_red = TextureManager::instance->getTexture("red.png");
	Material* mat_red = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_red);

	Model* fistModel = new Model("cube");
	GameObject* fist = new GameObject();
	fist->transform->scale = vec3(.5, .9, .5);
	fist->transform->pos = vec3(0, 1, -10); //right below camera
	MeshRenderer* fistRenderer = new MeshRenderer(XYZ_UV, fistModel, mat_red);
	Fist* fistComponent = new Fist();
	fist->addComponent(fistComponent);
	fist->addComponent(fistRenderer);
	addObject(fist);
	fistIndex = objects.size() - 1;
	fist->transform->setTransform(t);
}

//creating city
void World::buildCity()
{
	//load city model
	Model* city_cube = new Model("skyscraper");
	Model* sun_sphere = new Model("asteroid");

	//city texture
	Texture* tex_city = TextureManager::instance->getTexture("emma.png");
	Texture* tex_city_platform = TextureManager::instance->getTexture("asphalt.png");
	Texture* tex_city_metal = TextureManager::instance->getTexture("test1.png");
	Texture* tex_sun = TextureManager::instance->getTexture("yellow.png");

	//city material
	Material* mat_city = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_city);
	Material* mat_city_platform = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_city_platform);
	Material* mat_city_building = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_city_metal);
	Material* mat_sun = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_sun);

	//load Game Object 
	GameObject* sun = new GameObject();
	sun->transform->pos = vec3(-80,-80,200);
	sun->transform->scale = vec3(20, 20, 20);
	MeshRenderer* sun_renderer = new MeshRenderer(EVertexFormat::XYZ_UV, sun_sphere, mat_sun);
	sun->addComponent(sun_renderer);
	addObject(sun);

	//builds platform				buildPlatform(Texture*, Material*, vec3(pos), vec3(scale))
	buildPlatform(tex_city_platform, mat_city_platform, vec3(0, 15, 50), vec3(100, 1, 100));

	int num_Buildings = 6;

	for (int i = 0; i < num_Buildings; i++)
	{
		//builds skyscraper             buildSkyscraper(Texture*, Material*, vec3(pos), vec3(scale))
		buildSkyscraper(tex_city_metal, mat_city_building, vec3(-80 + i * 30, 0, 100), vec3(5, 20 + rand() % 30, 5));
		buildSkyscraper(tex_city_metal, mat_city_building, vec3(-80 + i * 30, 0, 50), vec3(5, 20 + rand() % 30, 5));
		buildSkyscraper(tex_city_metal, mat_city_building, vec3(-80 + i * 30, 0, 0), vec3(5, 20 + rand() % 20, 5));
		buildSkyscraper(tex_city_metal, mat_city_building, vec3(-80 + i * 30, 0, -100), vec3(5, 20 + rand() % 30, 5));
		buildSkyscraper(tex_city_metal, mat_city_building, vec3(-80 + i * 30, 0, -50), vec3(5, 20 + rand() % 30, 5));
	}
}

void World::buildSkyscraper(Texture* t, Material* m, vec3 pos, vec3 scale)
{
	//load city model
	Model* city_Cube = new Model("cube");

	//load the texture
	Texture* city_Texture = t;

	//load the material
	Material* city_Material = m;

	//load Game Object 
	GameObject* building = new GameObject();
	building->transform->pos = pos;
	building->transform->scale = scale;
	MeshRenderer* renderer = new MeshRenderer(EVertexFormat::XYZ_UV, city_Cube, city_Material);
	building->addComponent(renderer);
	addObject(building);
}
void World::buildPlatform(Texture* t, Material* m, vec3 pos, vec3 scale)
{
	//load  model
	Model* platform_Cube = new Model("cube");

	//load the texture
	Texture* platform_Texture = t;

	//load the material
	Material* platform_Material = m;

	//load Game Object 
	GameObject* platform = new GameObject();
	platform->transform->pos = pos;
	platform->transform->scale = scale;
	MeshRenderer* renderer = new MeshRenderer(EVertexFormat::XYZ_UV, platform_Cube, platform_Material);
	platform->addComponent(renderer);
	addObject(platform);
}

