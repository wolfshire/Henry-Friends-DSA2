#include <glm\gtx\transform.hpp>
#include <GLFW\glfw3.h>
#include "camera.h"
#include "gameobject.h"
#include "transform.h"
#include "input.h"
#include <math.h>

Camera* Camera::main = nullptr;

Camera::Camera()
{
    type = EGameComponentType::CAMERA;
    w = 16;
    h = 9;
    midPoint = glm::vec2(1280 / 2, 720 / 2);
}

Camera::Camera(int screenw, int screenh)
{
    type = EGameComponentType::CAMERA;
    w = screenw;
    h = screenh;
    midPoint = glm::vec2(w / 2, h / 2);
}

void Camera::setAspect(glm::vec2 aspect)
{
    w = (int)aspect.x;
    h = (int)aspect.y;
}

Camera* Camera::getMain() { return main; }
void Camera::setMain(Camera* newMain) { main = newMain; }

void Camera::update()
{
    //set mouse position
    mousePos = Input::getMousePosition();
    float dx = -(mousePos.x - midPoint.x);
    float dy = mousePos.y - midPoint.y;

    glm::quat roty = glm::quat(glm::vec3(0, dx / sensitivity, 0));
    transform->rot = glm::normalize(transform->rot * roty);
    glm::quat rotx = glm::quat(glm::vec3(dy / sensitivity, 0, 0));
    transform->rot = glm::normalize(transform->rot * rotx);

    glm::vec3 e = glm::eulerAngles(transform->rot);

    if (e.x > 0.6f) e.x = 0.6f;
    if (e.x < -0.6f) e.x = -0.6f;

    transform->rot = glm::quat(e);

    proj = glm::perspective(75.0, (double)w / h, 0.01, 500.0);

    //pos, eye, up
    view = lookAt(transform->pos, transform->pos + glm::vec3(glm::vec4(0, 0, 1, 1.0f) * transform->rot), glm::vec3(0, 1.0f, 0));

    Input::resetCursor();
}

glm::mat4 Camera::getProjectionMatrix() { return proj; }

glm::mat4 Camera::getViewMatrix() { return view; }