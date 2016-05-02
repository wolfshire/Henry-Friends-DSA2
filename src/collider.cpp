#include "collider.h"

Collider::Collider(Mesh* _mesh)
{
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

}

void Collider::setMesh(Mesh* newMesh)
{
    mesh = newMesh;
    calculate();
}

void Collider::calculate()
{

}