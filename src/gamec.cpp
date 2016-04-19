#include "gamec.h"
#include "gameobject.h"

#include <iostream>
using namespace std;

GameComponent::GameComponent() {}
GameComponent::~GameComponent() {}

void GameComponent::init()
{
    transform = gameObject->transform;
}

void GameComponent::update()
{

}

void GameComponent::render()
{

}