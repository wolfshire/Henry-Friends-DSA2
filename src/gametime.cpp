#include "gametime.h"

float GameTime::dt = 0;
float GameTime::elapsed = 0;
double GameTime::lastTime = 0;

void GameTime::init()
{
	elapsed = 0;
	lastTime = 0;
}

void GameTime::update()
{
	dt = (float)(glfwGetTime() - lastTime);
	lastTime = glfwGetTime();
	elapsed += dt;
}