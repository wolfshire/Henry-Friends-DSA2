#include "engine.h"

#include <glm\gtc\type_ptr.hpp>

#include "input.h"
#include "texturemanager.h"
#include "fontmanager.h"
#include "gametime.h"
#include "shadermanager.h"
#include "camera.h"

Engine* Engine::instance = nullptr;

Engine::Engine()
{
    instance = this;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(1280, 720, "One Punch Command", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        std::cout << "Failed to init GLEW" << std::endl;
        exit(-1);
    }

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "Open GL Version: " << version << std::endl;

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
}

Engine::~Engine()
{

}

void Engine::init()
{
    glClearColor(101 / 255.0f, 156 / 255.0f, 239 / 255.0f, 1.0f);

    width = new int;
    height = new int;
    glfwGetWindowSize(window, width, height);
    Font::SX = 2.0f / *width;
    Font::SY = 2.0f / *height;

    glCullFace(GL_FRONT_AND_BACK);
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowSizeCallback(window, onResize);

    Input::init(window);
    TextureManager::init();
    FreeImage_SetOutputMessage(freeImageErrorHandler);
    FontManager::init();
    GameTime::init();
    ShaderManager::init();

	world.init();

    Input::setCursorLocked(true);
    blankCursor = Input::createBlankCursor();

    GUI_VIEW = glm::translate(glm::mat4(), glm::vec3(*width / 2, *height / 2, 0.0f));

    font = FontManager::getDefaultFont();

    defaultShader = ShaderManager::getDefaultShader();
    uniProj = defaultShader->getUniformLocation("proj");
    uniView = defaultShader->getUniformLocation("view");
    uniModel = defaultShader->getUniformLocation("model");
}

void Engine::update()
{
    GameTime::update();
    Input::update();

    if (Input::getKeyUp(GLFW_KEY_F3))
    {
        debug = !debug;
    }
    if (Input::getKeyUp(GLFW_KEY_F4))
    {
        renderDebug = !renderDebug;
    }
    if (Input::getKeyUp(GLFW_KEY_ESCAPE))
    {
        Input::setCursorLocked(!Input::getCursorLocked());
    }

    world.update();
}

void Engine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    defaultShader->bind();

    glUniformMatrix4fv(uniProj, 1, GL_FALSE,
        glm::value_ptr(Camera::getMain()->getProjectionMatrix()));

    glUniformMatrix4fv(uniView, 1, GL_FALSE,
        glm::value_ptr(Camera::getMain()->getViewMatrix()));

    world.render();
}

void Engine::renderGui()
{
    Shader* gui = ShaderManager::getShader("gui");
    gui->bind();

    glUniformMatrix4fv(gui->getUniformLocation("proj"), 1, GL_FALSE,
        glm::value_ptr(Camera::getMain()->getOrthographicMatrix()));

    glUniformMatrix4fv(gui->getUniformLocation("view"), 1, GL_FALSE,
        glm::value_ptr(glm::mat4()));

    font->setSize(18);
    font->renderText("+", 0, 0, Color(0.0f, 1.0f, 0.0f));

    //world.renderGui();

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

glm::vec2 Engine::getWindowSize()
{
    return glm::vec2(*width, *height);
}

void Engine::onResize(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
    Font::SX = 2.0f / w;
    Font::SY = 2.0f / h;
    Camera::getMain()->setAspect(glm::vec2(w, h));
}

void Engine::freeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char* message)
{
    std::cout << "\n*** ";

    if (fif != FIF_UNKNOWN)
        std::cout << FreeImage_GetFormatFromFIF(fif) << " Format\n";

    std::cout << message << " ***\n";
}