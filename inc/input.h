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
    static bool getMouse(int);
    static bool getMouseUp(int);
    static bool getMouseDown(int);
    static glm::vec2 getMousePosition();
    static glm::vec2 getMouseDelta();
    static void setCursorLocked(bool);
    static bool getCursorLocked();
    static GLFWcursor* createBlankCursor();
    static void setCursor(GLFWcursor*);
    static void clearCursor();
private:
	static GLFWwindow* window;
    static unordered_map<int, bool> cur;
    static unordered_map<int, bool> prev;
    static unordered_map<int, bool> pressed;
    static unordered_map<int, bool> released;
    static double* mx;
    static double* my;
    static double* lx;
    static double* ly;
    static int left;
    static int right;
    static int middle;
    static int leftPrev;
    static int rightPrev;
    static int middlePrev;

    static bool lockCursor;

    static int VALID_KEYS[];
    static int NUM_KEYS;
};