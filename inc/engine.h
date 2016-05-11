#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>

#include "shader.h"
#include "world.h"
#include "font.h"

class Engine
{
public:
    Engine();
    ~Engine();

    glm::vec2 getWindowSize();

    static Engine* instance;
private:
    void init();
    void update();
    void render();
    void renderGui();

    //callbacks
    static void onResize(GLFWwindow*, int, int);
    static void freeImageErrorHandler(FREE_IMAGE_FORMAT, const char*);

    //Engine vars
    GLFWwindow* window;
    int* width;
    int* height;
    Shader* defaultShader;
    GLuint uniProj;
    GLuint uniView;
    GLuint uniModel;
    World world;
    Font* font;
    GLFWcursor* blankCursor;

    glm::mat4 GUI_VIEW;

    //option vars
    bool showGui = true;
    bool debug = false;
    bool renderDebug = false;

    //info vars
    double lastFrames = 0;
    double lastTime;
    int numFrames = 0;
    double frameTime;
};