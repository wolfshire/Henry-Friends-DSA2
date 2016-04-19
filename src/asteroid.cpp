#include "asteroid.h"

Asteroid::Asteroid()
{
    type = EGameComponentType::ASTEROID;
}

Asteroid::Asteroid(float speed)
{
    moveSpeed = speed;
}

Asteroid::Asteroid(float speed, Transform* t)
{
    moveSpeed = speed;
    trans = t;
}

void Asteroid::update()
{
    trans->pos.y -= moveSpeed * GameTime::dt;
    //std::cout << "asteroid: " << trans->pos.y << std::endl;
}

GameObject* Asteroid::createAsteroid(float speed)
{
    //texturing
    Texture* tex_missing = new Texture("missing.png");
    Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);
    //create game object
    GameObject* asteroid = new GameObject(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    Model* asteroidModel = new Model("asteroid");
    MeshRenderer* asteroidRenderer = new MeshRenderer(asteroidModel, mat_missing);
    Asteroid* asteroidComponent = new Asteroid(speed);
    //add components
    asteroid->addComponent(asteroidRenderer);
    asteroid->addComponent(asteroidComponent);
    //return
    return asteroid;
}

GameObject * Asteroid::createAsteroid(float speed, Transform* t)
{
    //texturing
    Texture* tex_missing = new Texture("missing.png");
    Material* mat_missing = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_missing);
    //create game object
    GameObject* asteroid = new GameObject(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    Model* asteroidModel = new Model("asteroid");
    MeshRenderer* asteroidRenderer = new MeshRenderer(asteroidModel, mat_missing);
    Asteroid* asteroidComponent = new Asteroid(speed, t);
    //add components
    asteroid->addComponent(asteroidRenderer);
    asteroid->addComponent(asteroidComponent);
    //return
    return asteroid;
}
