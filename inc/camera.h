#pragma once
#include "gamec.h"
#include <glm\gtc\matrix_transform.hpp>

class Camera : public GameComponent
{
public:
	Camera();
	void update() override;
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
	static Camera* getMain();
	static void setMain(Camera*);
private:
	static Camera* main;

    glm::mat4 proj;
    glm::mat4 viewtrans;
    glm::mat4 viewrotx;
    glm::mat4 view;
	glm::mat4 rotation;
	
	glm::vec2 mousePos;
	glm::vec2 lastPos;

	bool hasMoved;
};