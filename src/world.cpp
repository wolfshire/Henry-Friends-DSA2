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

World::World() {}
World::~World() {}

void World::addObject(GameObject* o)
{
    objects.push_back(o);
}

void World::init()
{
    //objects
    GameObject* cam = new GameObject();
    cam->transform->pos.z = -10;
    Camera* camera = new Camera();
    FlyMove* flymove = new FlyMove();
    cam->addComponent(camera);
    cam->addComponent(flymove);
    addObject(cam);

    Camera::setMain(camera);

    //spawn locations
    spawns.push_back(new Transform(vec3(30, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1))); //city A >
    spawns.push_back(new Transform(vec3(-30, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1))); //city B <
    spawns.push_back(new Transform(vec3(0, 0, 30), vec3(0, 0, 0), vec3(1, 1, 1))); //city C ^
    spawns.push_back(new Transform(vec3(0, 0, -30), vec3(0, 0, 0), vec3(1, 1, 1))); //city D v

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
	Model* asteroidModel = new Model("asteroid");
	Model* fistModel = new Model("cube");

    GameObject* blue = new GameObject();
    blue->transform->pos = vec3(5, 0, 0);
    MeshRenderer* blueRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, mod_cube, mat_blue);
    blue->addComponent(blueRenderer);
    addObject(blue);
    
    GameObject* green = new GameObject();
    green->transform->pos = vec3(0, 5, 0);
    MeshRenderer* greenRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, mod_cube, mat_green);
    green->addComponent(greenRenderer);
    addObject(green);

    GameObject* red = new GameObject();
    red->transform->pos = vec3(0, 0, 5);
    MeshRenderer* redRenderer = new MeshRenderer(EVertexFormat::XYZ_UV, mod_cube, mat_missing);
    red->addComponent(redRenderer);
    addObject(red);
	
	for (int i = 0; i < 10; i++) {
		GameObject* asteroid = new GameObject();
		asteroid->transform->pos = vec3(0, -10 * i, 10);
		MeshRenderer* asteroidRenderer = new MeshRenderer(XYZ_UV, asteroidModel, mat_missing);
		Asteroid* asteroidComponent = new Asteroid();
		asteroid->addComponent(asteroidComponent);
		asteroid->addComponent(asteroidRenderer);
		addObject(asteroid);
	}

	GameObject* fist = new GameObject();
	fist->transform->scale = vec3(.5, .9, .5);
	fist->transform->pos = vec3(0, 1, -10); //right below camera
	MeshRenderer* fistRenderer = new MeshRenderer(XYZ_UV, fistModel, mat_red);
	Fist* fistComponent = new Fist();
	fist->addComponent(fistComponent);
	fist->addComponent(fistRenderer);
	addObject(fist);

    for (unsigned int i = 0; i < objects.size(); i++)
        (*objects[i]).init();
}

void World::update()
{
    for (unsigned int i = 0; i < objects.size(); i++)
        (*objects[i]).update();
}

void World::render()
{
    for (unsigned int i = 0; i < objects.size(); i++)
        (*objects[i]).render();
}
