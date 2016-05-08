#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include "gamec.h"

class Transform : public GameComponent
{
public:
	Transform();
    Transform(glm::vec3, glm::vec3, glm::vec3);
	~Transform();
    void update() override;
    bool hasChanged();
    void setParent(Transform*);
	void setTransform(Transform*);
    void rotate(glm::vec3, float angle);

    glm::vec3 getRight();
    glm::vec3 getForward();
    glm::vec3 getUp();

    glm::mat4 getTransformation();
    glm::mat4 getParentMatrix();

    Transform* parent;
    glm::mat4 parentMatrix;

    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;
    
    glm::vec3 oldPos;
    glm::quat oldRot;
    glm::vec3 oldScale;
};