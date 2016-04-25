#include <glm\gtx\transform.hpp>
#include <GLFW\glfw3.h>
#include "camera.h"
#include "gameobject.h"
#include "transform.h"
#include "input.h"

Camera* Camera::main = nullptr;

Camera::Camera()
{
	type = EGameComponentType::CAMERA;
    w = 16;
    h = 9;
}

Camera::Camera(int screenw, int screenh)
{
    type = EGameComponentType::CAMERA;
    w = screenw;
    h = screenh;
}

void Camera::setAspect(glm::vec2 aspect)
{
    w = aspect.x;
    h = aspect.y;
}

Camera* Camera::getMain() { return main; }
void Camera::setMain(Camera* newMain) { main = newMain; }

void Camera::update()
{
    proj = glm::perspective(75.0, (double)w / h, 0.01, 500.0);
    viewtrans = glm::translate(glm::mat4(1.0f), transform->pos);
    glm::vec3 euler = glm::eulerAngles(transform->rot);
    viewrotx = glm::rotate(viewtrans, euler.y, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(viewrotx, euler.x, glm::vec3(1.0f, 0.0f, 0.0f));

    //view = lookAt(transform->pos, transform->pos + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjectionMatrix() { return proj; }

glm::mat4 Camera::getViewMatrix() { return view; }