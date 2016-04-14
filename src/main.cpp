#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <iostream>
#include <sstream>
#include "camera.h"
#include "gametime.h"
#include "input.h"
#include "font.h"
#include "fontmanager.h"
#include "shadermanager.h"
#include "transform.h"
#include "world.h"
using namespace std;

#include <glm\gtx\transform.hpp>
using namespace glm;

//functions
void init();
void update();
void render();
void renderGui();
void freeImageErrorHandler(FREE_IMAGE_FORMAT, const char*);
void cleanup();

//Engine vars
GLFWwindow* window;
GLuint defShader;
GLuint uniProj;
GLuint uniView;
World world;
Font* font;

//option vars
bool showGui = true;
bool debug = false;

//info vars
double lastFrames = 0;
double lastTime;
int numFrames = 0;
double frameTime;

void init()
{
    glClearColor(101 / 255.0f, 156 / 255.0f, 239 / 255.0f, 1.0f);

    int* w = new int;
    int* h = new int;
    glfwGetWindowSize(window, w, h);
    Font::SX = 2.0f / *w;
    Font::SY = 2.0f / *h;

    FreeImage_Initialise(true);
    std::cout << "FreeImage version: " << FreeImage_GetVersion() << std::endl;
    FreeImage_SetOutputMessage(freeImageErrorHandler);

    Input::init(window);
    FontManager::init();
    GameTime::init();
    ShaderManager::init();
    world.init();

    font = FontManager::getDefaultFont();

    defShader = ShaderManager::getDefaultShader()->getProgram();
    uniProj = glGetUniformLocation(defShader, "proj");
    uniView = glGetUniformLocation(defShader, "view");
}

void update()
{
    GameTime::update();
    Input::update();

    if (Input::getKeyUp(GLFW_KEY_F3))
    {
        debug = !debug;
    }

    world.update();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glProgramUniformMatrix4fv(defShader, uniProj, 1, GL_FALSE,
        &(Camera::getMain()->getProjectionMatrix())[0][0]);

    glProgramUniformMatrix4fv(defShader, uniView, 1, GL_FALSE,
        &(Camera::getMain()->getViewMatrix())[0][0]);

    world.render();
}

void renderGui()
{
    if (debug)
    {
        int y = 0;

        font->setSize(18);
        ostringstream stream;
        stream << lastFrames;
        font->renderText("FPS: " + stream.str(), -1 + 4 * Font::SX, 1 - (y += 18) * Font::SY, Color(0.0f, 1.0f, 0.0f));
        stream.str(""); stream.clear();
        stream << frameTime;
        font->renderText("Frame Time: " + stream.str(), -1 + 4 * Font::SX, 1 - (y += 18) * Font::SY, Color(0.0f, 1.0f, 0.0f));

        //main cam debug
        vec3 pos = Camera::getMain()->gameObject->transform->pos;
        stream.str(""); stream.clear();
        stream << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")";
        font->renderText("Camera Pos: " + stream.str(), -1 + 4 * Font::SX, 1 - (y += 18) * Font::SY, Color(0.0f, 1.0f, 0.0f));
    }
}

void cleanup()
{
    FreeImage_DeInitialise();
}

void freeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char* message)
{
    std::cout << "\n*** ";

    if (fif != FIF_UNKNOWN)
        std::cout << FreeImage_GetFormatFromFIF(fif) << " Format\n";

    std::cout << message << " ***\n";
}

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(1280, 720, "One Punch Command", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "Open GL Version: " << version << endl;

    init();
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetTime() - lastTime >= 1.0)
        {
            frameTime = 1000.0 / numFrames;
            lastFrames = numFrames;
            numFrames = 0;
            lastTime += 1.0;
        }

        update();
        render();
        if (showGui) renderGui();

        glFlush();

        glfwSwapBuffers(window);
        glfwPollEvents();

        numFrames++;
    }

    cleanup();

    glfwTerminate();

    return 0;
}