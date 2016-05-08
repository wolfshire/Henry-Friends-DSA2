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

    proj = glm::perspective(75.0, (double)w / h, 0.01, 500.0);
    viewtrans = glm::translate(glm::mat4(1.0f), transform->pos);
    viewrotx = glm::rotate(viewtrans, transform->rot.x, glm::vec3(0.0f, 1.0f, 0.0f));

	view = lookAt(transform->pos, transform->pos + glm::vec3(glm::vec3(0, 0, 1) * transform->rot), glm::vec3(glm::vec3(0, 1, 0) * transform->rot)); //pos, fwd, up

	//view *= rotation;
    //view = glm::rotate(viewrotx, transform->rot.y, glm::vec3(1.0f, 0.0f, 0.0f));
	float xSpeed = std::abs(mousePos.x - midPoint.x);
	float ySpeed = std::abs(mousePos.y - midPoint.y);
	float sensitivity = 1000.0f; //larger = slower

	//cout << transform->rot.x << "," << transform->rot.y << "," << transform->rot.z << "," << transform->rot.w << endl;
	
	if (mousePos.x < midPoint.x) {
		transform->rot *= glm::quat_cast(glm::rotate(rotation, xSpeed / sensitivity, glm::vec3(0, 1, 0)));
	}
	if (mousePos.x > midPoint.x) {
		transform->rot *= glm::quat_cast(glm::rotate(rotation, -xSpeed / sensitivity, glm::vec3(0, 1, 0)));
	}
	if (mousePos.y > midPoint.y && glm::eulerAngles(transform->rot).x < 0.1f) {
		transform->rot *= glm::quat_cast(glm::rotate(rotation, ySpeed / sensitivity, glm::vec3(1, 0, 0)));
	}
	if (mousePos.y < midPoint.y && glm::eulerAngles(transform->rot).x > -0.75f) {
		transform->rot *= glm::quat_cast(glm::rotate(rotation, -ySpeed / sensitivity, glm::vec3(1, 0, 0)));
	}

	transform->rot.z = 0;

	//cout << "(mp)" << mousePos.x << "," << mousePos.y << endl;
	//cout << "(cp)" << midPoint.x << "," << midPoint.y << endl;

	Input::resetCursor();
}

glm::mat4 Camera::getProjectionMatrix() { return proj; }

glm::mat4 Camera::getViewMatrix() { return view; }