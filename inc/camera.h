#pragma once
#include "gamec.h"
#include "transform.h"

class Camera : public GameComponent
{
public:
	Camera();
	virtual void init();
	virtual void update();
    mat4 getProjectionMatrix();
    mat4 getViewMatrix();
	static Camera* getMain();
	static void setMain(Camera*);
private:
	static Camera* main;

	mat4 proj;
	mat4 viewtrans;
	mat4 viewrotx;
	mat4 view;

	bool hasMoved;
	Transform* trans;
};