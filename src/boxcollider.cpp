#include "boxcollider.h"
#include "transform.h"
#include "gameobject.h"

BoxCollider::BoxCollider(Mesh* mesh) : Collider(mesh)
{
    type = EGameComponentType::BOX_COLLIDER;
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::init()
{
    transform = gameObject->transform;

    calculate();
}

void BoxCollider::calculate()
{
    //initial values
    max = max = mesh->pos[0];

    //find min and max
    for (unsigned int i = 1; i < mesh->pos.size(); i++)
    {
        //set max
        if (mesh->pos[i].x > max.x) max.x = mesh->pos[i].x;
        if (mesh->pos[i].y > max.y) max.y = mesh->pos[i].y;
        if (mesh->pos[i].z > max.z) max.z = mesh->pos[i].z;
        //set max
        if (mesh->pos[i].x < min.x) min.x = mesh->pos[i].x;
        if (mesh->pos[i].y < min.y) min.y = mesh->pos[i].y;
        if (mesh->pos[i].z < min.z) min.z = mesh->pos[i].z;
    }

    //calculate centerpoint
    center = (min + max) / 2.0f;
}

bool BoxCollider::isColliding(Collider* other)
{
    BoxCollider* box = (BoxCollider*)other;

    glm::mat4 worldMatrix = transform->getTransformation();
    //Get all vectors in global space
    glm::vec3 ming = glm::vec3(worldMatrix * glm::vec4(min, 1.0f));
    glm::vec3 maxg = glm::vec3(worldMatrix * glm::vec4(max, 1.0f));

    glm::vec3 mino = glm::vec3(box->transform->getTransformation() * glm::vec4(box->min, 1.0f));
    glm::vec3 maxo = glm::vec3(box->transform->getTransformation() * glm::vec4(box->max, 1.0f));

    bool colliding = true;

    if (maxg.x < mino.x)
        colliding = false;
    if (ming.x > maxo.x)
        colliding = false;

    if (maxg.y < mino.y)
        colliding = false;
    if (ming.y > maxo.y)
        colliding = false;

    if (maxg.z < mino.z)
        colliding = false;
    if (ming.z > maxo.z)
        colliding = false;

    return colliding;
}