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
#include "texturemanager.h"
#include "transform.h"
#include "world.h"
#include "material.h"
#include "model.h"
#include "meshrenderer.h"
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
Shader* defaultShader;
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

//test vars
Texture* tex_blue;
Material* mat_blue;
Model* mod_cube;
GameObject* test;

GLuint vao, vbo, ibo;
mat4 iden = mat4();

void init()
{
    glClearColor(101 / 255.0f, 156 / 255.0f, 239 / 255.0f, 1.0f);

    int* w = new int;
    int* h = new int;
    glfwGetWindowSize(window, w, h);
    Font::SX = 2.0f / *w;
    Font::SY = 2.0f / *h;

    Input::init(window);
    TextureManager::init();
    FreeImage_SetOutputMessage(freeImageErrorHandler);
    FontManager::init();
    GameTime::init();
    ShaderManager::init();
    world.init();

    font = FontManager::getDefaultFont();

    defaultShader = ShaderManager::getDefaultShader();
    uniProj = defaultShader->getUniformLocation("proj");
    uniView = defaultShader->getUniformLocation("view");

    //test
    tex_blue = TextureManager::instance->getTexture("blue.png");
    mat_blue = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader(), tex_blue);
    mod_cube = new Model("cube");

    test = new GameObject();
    test->transform->pos = vec3(0, 0, 5);
    MeshRenderer* testRenderer = new MeshRenderer(EVertexFormat::XYZ, mod_cube, mat_blue);
    test->addComponent(testRenderer);
    test->init();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    float verts[] = 
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    int indices[] =
    {
        0, 2, 3
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), &verts[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(int), &indices[0], GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
}

void update()
{
    GameTime::update();
    Input::update();

    if (Input::getKeyUp(GLFW_KEY_F3))
    {
        debug = !debug;
    }

    test->update();

    //world.update();
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glProgramUniformMatrix4fv(defaultShader->getProgram(), uniProj, 1, GL_FALSE,
        &(Camera::getMain()->getProjectionMatrix())[0][0]);

    glProgramUniformMatrix4fv(defaultShader->getProgram(), uniView, 1, GL_FALSE,
        &(Camera::getMain()->getViewMatrix())[0][0]);

    glProgramUniformMatrix4fv(defaultShader->getProgram(),
        defaultShader->getUniformLocation("model"),
        1,
        GL_FALSE,
        &(iden)[0][0]);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

    test->render();

    //world.render();
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

    glfwTerminate();

    return 0;
}