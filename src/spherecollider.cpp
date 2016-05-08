#include "spherecollider.h"

SphereCollider::SphereCollider(Mesh* mesh, float rad) : Collider(mesh)
{
    radius = rad;
}

SphereCollider::~SphereCollider()
{

}