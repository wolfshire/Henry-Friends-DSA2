#include "gametime.h"

double GameTime::dt = 0;
double GameTime::elapsed = 0;
double GameTime::lastTime = 0;

void GameTime::init()
{
	elapsed = 0;
	lastTime = 0;
}

void GameTime::update()
{
	dt = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	elapsed += dt;
}