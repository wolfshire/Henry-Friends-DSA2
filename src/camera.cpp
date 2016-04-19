#include <glm\gtx\transform.hpp>
#include <GLFW\glfw3.h>
#include "camera.h"
#include "gameobject.h"
#include "transform.h"

Camera* Camera::main = NULL;

Camera::Camera()
{
	type = EGameComponentType::CAMERA;
}

Camera* Camera::getMain() { return main; }
void Camera::setMain(Camera* newMain) { main = newMain; }

void Camera::update()
{
    proj = glm::perspective(75.0, 16.0 / 9, 0.01, 500.0);
    viewtrans = glm::translate(glm::mat4(1.0f), transform->pos);
    viewrotx = glm::rotate(viewtrans, transform->rot.x, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(viewrotx, transform->rot.y, glm::vec3(1.0f, 0.0f, 0.0f));

    //view = lookAt(transform->pos, transform->pos + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjectionMatrix() { return proj; }

glm::mat4 Camera::getViewMatrix() { return view; }