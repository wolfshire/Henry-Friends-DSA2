#pragma once
#include <glm\glm.hpp>
#include "gamec.h"
#include "mesh.h"

class Collider : public GameComponent
{
public:
    Collider(Mesh*);
    ~Collider();

    void init() override;
    void update() override;
    virtual bool isColliding(Collider*);

    void setMesh(Mesh*);
protected:
    virtual void calculate();

    glm::vec3 center;
    Mesh* mesh;
};