#include "collider.h"

Collider::Collider(Mesh* _mesh)
{
    type = EGameComponentType::COLLIDER;

    mesh = _mesh;
}

Collider::~Collider()
{

}

void Collider::init()
{
    calculate();
}

void Collider::update()
{

}

bool Collider::isColliding(Collider* other)
{
    return false;
}

void Collider::setMesh(Mesh* newMesh)
{
    mesh = newMesh;
    calculate();
}

void Collider::calculate()
{

}