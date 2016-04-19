#pragma once
#include <GLFW\glfw3.h>

class GameTime
{
public:
	static void init();
	static void update();
	static float dt;
	static float elapsed;
private:
	static double lastTime;
};