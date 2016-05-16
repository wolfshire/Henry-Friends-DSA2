#include "camera.h"
#include "boxcollider.h"
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
#include "move.h"
#include "gametime.h"
#include "fontmanager.h"

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

GameObject* World::removeObjectAt(unsigned int index)
{
    if (index < 0 || index >= objects.size())
        throw new exception("Index out of bounds: " + index);

    GameObject* removedObject = objects[index];
    objects.erase(objects.begin() + index);

    return removedObject;

	//increase casualty score
	casualtyScore++;
}

void World::init()
{
	//initialize scores
	casualtyScore = 0;
	score = 0;

    //random seed
    srand((unsigned int)time(NULL));

	//tree
	tree = new OctTree(BoundingBox(glm::vec3(-350, -350, -350.0f), glm::vec3(350, 350, 350.0f)));
    crosshair = Crosshair(1280 / 2, 720 / 2);

    //objects
    GameObject* cam = new GameObject();
    cam->transform->pos.z = -75;
    cam->transform->pos.y = -75;
    Camera* camera = new Camera();
    FlyMove* flymove = new FlyMove();
    cam->addComponent(camera);
    cam->addComponent(flymove);
    addObject(cam);
	

    numAsteroids = 5;

    Camera::setMain(camera);

    //textures
    Texture* tex_missing = TextureManager::instance->getTexture("emma.png");
    Texture* tex_blue = TextureManager::instance->getTexture("blue.png");
    Texture* tex_green = TextureManager::instance->getTexture("green.png");
    Texture* tex_red = TextureManager::instance->getTexture("red.png");
    Texture* tex_sky = TextureManager::instance->getTexture("sky.png");

    //materials
    Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);
    mat_blue = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_blue);
    mat_green = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_green);
    mat_red = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_red);
    mat_sky = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_sky);

    //models
    Model* mod_cube = new Model("cube");
    Model* fistModel = new Model("cube");

    //builds the City
    buildCity();

    //collision test objs
    /*
    GameObject* one = new GameObject();
    one->transform->pos = vec3(-2, -30, 0);
    MeshRenderer* oneR = new MeshRenderer(XYZ_UV, mod_cube, mat_green);
    one->addComponent(oneR);
    BoxCollider* oneBC = new BoxCollider(mod_cube->getMesh());
    one->addComponent(oneBC);
    Move* oneM = new Move(GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4, GLFW_KEY_5, GLFW_KEY_6);
    one->addComponent(oneM);
    addObject(one);

    GameObject* two = new GameObject();
    two->transform->pos = vec3(2, -30, 0);
    MeshRenderer* twoR = new MeshRenderer(XYZ_UV, mod_cube, mat_green);
    two->addComponent(twoR);
    twoR->setMaterial(mat_red);
    BoxCollider* twoBC = new BoxCollider(mod_cube->getMesh());
    two->addComponent(twoBC);
    Move* twoM = new Move(GLFW_KEY_KP_7, GLFW_KEY_KP_9, GLFW_KEY_KP_4, GLFW_KEY_KP_6, GLFW_KEY_KP_8, GLFW_KEY_KP_5);
    two->addComponent(twoM);
    addObject(two);*/

    //skybox loading
    GameObject* skybox = new GameObject();
    skybox->transform->scale = vec3(275);
    skybox->transform->rot = glm::quat(glm::vec3(3.1415926f, 0, 0.0f));
    Model* skyboxModel = new Model("skybox");
    MeshRenderer* skyRenderer = new MeshRenderer(XYZ_UV, skyboxModel, mat_sky);
    skybox->addComponent(skyRenderer);
    addObject(skybox);
}

void World::update()
{
	//increase hero aptitude(score)
	score ++;

    spawnTimer += GameTime::dt;
    //set spawn vector
    spawns.clear();
    for (unsigned int i = 0; i < objects.size(); i++)
        if ((*objects[i]).tag == EGameObjectType::GO_CITY)
            spawns.push_back((*objects[i]).transform->pos + vec3(0, -100, 0));

    //spawn asteroid
    if (spawnTimer > spawnFrequency && spawns.size() > 0)
    {
        spawnTimer = 0;
        int random = rand() % spawns.size();
        spawnAsteroid(spawns[random]);

        if (spawnFrequency > .5f)
            spawnFrequency -= 0.025f;
    }

    if (Input::getMouseUp(0))
    {
        //punch	
        punchFist(Camera::getMain()->transform);
    }

    //update all game objects
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        (*objects[i]).update();

        //if the object has left the play area
        if (objects[i]->transform->pos.y > 300 || objects[i]->transform->pos.y < -300 ||
            objects[i]->transform->pos.x > 300 || objects[i]->transform->pos.x < -300 ||
            objects[i]->transform->pos.z > 300 || objects[i]->transform->pos.z < -300)
        {
            removeObjectAt(i);
            i--;
        }
    }

    buildOctTree();

	//check tree collisions
	tree->checkTree();

    //checking the booleans
    for (unsigned int i = 0; i < objects.size(); i++)
    {
		//get all of the box colliders
		BoxCollider* b = (BoxCollider*)objects[i]->getComponent(EGameComponentType::BOX_COLLIDER);
		//if they're colliding, remove the objects
		if (b != nullptr) if (b->colliding) removeObjectAt(i); 
    }

	if (casualtyScore >= 3000)
	{
		//end Game
	}
}

void World::render()
{
    for (unsigned int i = 0; i < objects.size(); i++)
        (*objects[i]).render();
}

void World::renderGui()
{
    crosshair.render();
}

void World::spawnAsteroid(vec3 pos)
{
    Model* asteroidModel = new Model("asteroid");
    Texture* tex_missing = TextureManager::instance->getTexture("meteorite.png");
    Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);

    GameObject* asteroid = new GameObject();
    asteroid->transform->scale = vec3(3);
    asteroid->transform->pos = pos;
    MeshRenderer* asteroidRenderer = new MeshRenderer(XYZ_UV, asteroidModel, mat_missing);
    BoxCollider* bc = new BoxCollider(asteroidModel->getMesh());
    asteroid->addComponent(bc);
    Asteroid* asteroidComponent = new Asteroid();
    asteroid->addComponent(asteroidComponent);
    asteroid->addComponent(asteroidRenderer);
    addObject(asteroid);
}

void World::buildOctTree()
{
    tree->clearTree();

    for (auto obj : objects)
    {
        BoxCollider* bc = (BoxCollider*)(*obj).getComponent(EGameComponentType::BOX_COLLIDER);

        if (bc != nullptr)
            tree->addObject(obj);
    }

    tree->updateTree();
    tree->buildTree();
}

void World::punchFist(Transform* t)
{
    Texture* tex_red = TextureManager::instance->getTexture("red.png");
    Material* mat_red = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_red);

    Model* fistModel = new Model("cube");
    GameObject* fist = new GameObject();
    fist->transform->scale = vec3(.5, .9, .5);
    fist->transform->pos = vec3(0, 1, -10); //right below camera
    MeshRenderer* fistRenderer = new MeshRenderer(XYZ_UV, fistModel, mat_red);
    BoxCollider* bc = new BoxCollider(fistModel->getMesh());
    fist->addComponent(bc);
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
    sun->transform->pos = vec3(-100, -180, 200);
    sun->transform->scale = vec3(20, 20, 20);
    MeshRenderer* sun_renderer = new MeshRenderer(EVertexFormat::XYZ_UV, sun_sphere, mat_sun);
    sun->addComponent(sun_renderer);
    addObject(sun);

    //builds platform				buildPlatform(Texture*, Material*, vec3(pos), vec3(scale))
    buildPlatform(tex_city_platform, mat_city_platform, vec3(0, 15, 50), vec3(300, 1, 300));

    int num_Buildings = 8;

    for (int i = 0; i < num_Buildings; i++)
    {
        //builds skyscraper             buildSkyscraper(Texture*, Material*, vec3(pos), vec3(scale))
        buildSkyscraper(tex_city_metal, mat_city_building, vec3(-100 + i * 30, 0, 100), vec3(5, 20 + rand() % 30, 5));
        buildSkyscraper(tex_city_metal, mat_city_building, vec3(-100 + i * 30, 0, 50), vec3(5, 20 + rand() % 30, 5));
		buildSkyscraper(tex_city_metal, mat_city_building, vec3(-100 + i * 30, 0, 150), vec3(5, 20 + rand() % 30, 5));
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
    BoxCollider* bc = new BoxCollider(city_Cube->getMesh());
    building->addComponent(bc);
    MeshRenderer* renderer = new MeshRenderer(EVertexFormat::XYZ_UV, city_Cube, city_Material);
    building->addComponent(renderer);
    building->tag = EGameObjectType::GO_CITY;
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

int World::Score()
{
	return score;
}

int World::CasualtyScore()
{
	return casualtyScore;
}
