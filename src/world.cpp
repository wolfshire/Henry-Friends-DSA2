#include "camera.h"
#include "flymove.h"
#include "world.h"
#include "mattype.h"
#include "model.h"
#include "meshrenderer.h"
#include "texture.h"
#include "shadermanager.h"
#include "asteroid.h"
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
    Texture* tex_missing = new Texture("missing.png");
    Texture* tex_blue = new Texture("blue.png");
    Texture* tex_green = new Texture("green.png");

    //materials
    Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);
    Material* mat_blue = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_blue);
    Material* mat_green = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_green);

    //models
    Model* mod_cube = new Model("cube");

    GameObject* blue = new GameObject();
    blue->transform->pos = vec3(5, 0, 0);
    MeshRenderer* blueRenderer = new MeshRenderer(mod_cube, mat_blue);
    blue->addComponent(blueRenderer);
    addObject(blue);

    GameObject* green = new GameObject();
    green->transform->pos = vec3(0, 5, 0);
    MeshRenderer* greenRenderer = new MeshRenderer(mod_cube, mat_green);
    green->addComponent(greenRenderer);
    addObject(green);

    GameObject* red = new GameObject();
    red->transform->pos = vec3(0, 0, 5);
    MeshRenderer* redRenderer = new MeshRenderer(mod_cube, mat_missing);
    red->addComponent(redRenderer);
    addObject(red);

    GameObject* asteroid = Asteroid::createAsteroid(5.0f, spawns[2]);
    addObject(asteroid);

    for (int i = 0; i < objects.size(); i++)
        (*objects[i]).init();
}

void World::update()
{
    //objects
    for (int i = 0; i < objects.size(); i++)
        (*objects[i]).update();
}

void World::render()
{
    for (int i = 0; i < objects.size(); i++)
        (*objects[i]).render();
}
