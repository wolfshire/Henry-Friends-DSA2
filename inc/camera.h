#pragma once
#include "gamec.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>

class Camera : public GameComponent
{
public:
	Camera();
    Camera(int, int);
	void update() override;
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
    glm::mat4 getOrthographicMatrix();
    void setAspect(glm::vec2);
	static Camera* getMain();
	static void setMain(Camera*);
private:
	static Camera* main;

    float sensitivity = 1000.0f; //larger = slower

    int w;
    int h;
    glm::mat4 proj;
    glm::mat4 ortho;
    glm::mat4 view;
	glm::mat4 rotation;
	
	glm::vec2 mousePos;
	glm::vec2 midPoint;

	bool hasMoved;
};