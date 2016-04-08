#pragma once
#include <GLFW\glfw3.h>

class GameTime
{
public:
	static void init();
	static void update();
	static double dt;
	static double elapsed;
private:
	static double lastTime;
};