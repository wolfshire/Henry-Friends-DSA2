#include "octtree.h"
#include "boxcollider.h"
#include <glm\glm.hpp>
using namespace glm;

OctTree::OctTree()
{
    region = BoundingBox();
    pending = std::vector<GameObject*>();
    objects = std::vector<GameObject*>();
    children = new OctTree*[8];
    curLife = -1;
}

OctTree::OctTree(BoundingBox& reg, std::vector<GameObject*>& pend)
{
    region = reg;
    pending = pend;
    objects = std::vector<GameObject*>();
    children = new OctTree*[8];
    curLife = -1;
}

OctTree::~OctTree()
{
    if (parent != nullptr)
    {
        delete parent;
        parent = nullptr;
    }

    if (children != nullptr)
    {
        delete[] children;
        children = nullptr;
    }
}

void OctTree::clearTree()
{
    pending.clear();
    objects.clear();

    delete[] children;

    children = new OctTree*[8];
    curLife = -1;

    treeBuilt = false;
    treeReady = false;
}

void OctTree::addObject(GameObject* go)
{
    pending.push_back(go);
}

void OctTree::updateTree()
{
    if (!treeBuilt)
    {
        while (pending.size() > 0)
        {
            objects.push_back(pending[pending.size() - 1]);
            pending.pop_back();
        }

        buildTree();
    }
    else
    {
        while (pending.size() > 0)
        {
            objects.push_back(pending[pending.size() - 1]);
            pending.pop_back();
        }
    }

    treeReady = true;
}

void OctTree::buildTree()
{
    if (objects.size() <= 1)
        return;

    vec3 dim = region.max - region.min;

    if (dim == vec3(0))
    {
        //findEnclosingCube();
        dim = vec3(650, 650, 650.0f);//region.max - region.min;
    }

    if (dim.x < MIN_SIZE && dim.y < MIN_SIZE && dim.z < MIN_SIZE)
    {
        return;
    }

    vec3 half = dim / 2.0f;
    vec3 center = region.min + half;

    BoundingBox octant[8];
    octant[0] = BoundingBox(region.min, center);
    octant[1] = BoundingBox(vec3(center.x, region.min.y, region.min.z), vec3(region.max.x, center.y, center.z));
    octant[2] = BoundingBox(vec3(center.x, region.min.y, center.z), vec3(region.max.x, center.y, region.max.z));
    octant[3] = BoundingBox(vec3(region.min.x, region.min.y, center.z), vec3(center.x, center.y, region.max.z));
    octant[4] = BoundingBox(vec3(region.min.x, center.y, region.min.z), vec3(center.x, region.max.y, center.z));
    octant[5] = BoundingBox(vec3(center.x, center.y, region.min.z), vec3(region.max.x, region.max.y, center.z));
    octant[6] = BoundingBox(center, region.max);
    octant[7] = BoundingBox(vec3(region.min.x, center.y, center.z), vec3(center.x, region.max.y, region.max.z));

    std::vector<GameObject*> octList[8];

    for (int i = 0; i < 8; i++)
        octList[i] = std::vector<GameObject*>();

    std::vector<int> delist = std::vector<int>();

    for (unsigned int index = 0; index < objects.size(); index++)
    {
        BoxCollider* bc = (BoxCollider*)objects[index]->getComponent(EGameComponentType::BOX_COLLIDER);

        if (bc->min != bc->max)
        {
            for (int i = 0; i < 8; i++)
            {
                if (octant[i].contains(bc->getBoundingBox()))
                {
                    octList[i].push_back(objects[index]);
                    delist.push_back(index);
                    break;
                }
            }
        }
    }

    for (int i = delist.size() - 1; i >= 0; i--)
        objects.erase(objects.begin() + delist[i]);

    for (int i = 0; i < 8; i++)
    {
        if (octList[i].size() != 0)
        {
            children[i] = createNode(octant[i], octList[i]);
            active |= (unsigned int)(1 << i);
            children[i]->buildTree();
        }
    }

    treeBuilt = true;
    treeReady = true;
}

OctTree* OctTree::createNode(BoundingBox region, std::vector<GameObject*> objList)
{
    if (objList.size() == 0)
        return nullptr;

    OctTree* ret = new OctTree(region, objList);
    ret->parent = this;

    return ret;
}