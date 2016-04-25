#pragma once
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <unordered_map>
using namespace std;

class Input
{
public:
	Input();
	static void init(GLFWwindow*);
    static void update();
	static bool getKey(int);
    static bool getKeyUp(int);
    static bool getKeyDown(int);
	static char getKeyChar(int);
    static glm::vec2 getMousePosition();
	
private:
	static GLFWwindow* window;
    static unordered_map<int, bool> cur;
    static unordered_map<int, bool> prev;
    static unordered_map<int, bool> pressed;
    static unordered_map<int, bool> released;
	static double* mx;
	static double* my;

    static int VALID_KEYS[];
    static int NUM_KEYS;
};