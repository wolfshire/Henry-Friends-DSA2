#include "octtree.h"
#include "boxcollider.h"
#include "meshrenderer.h"
#include "shadermanager.h"
#include "camera.h"
#include "transform.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
using namespace glm;

OctTree::OctTree()
{
	region = BoundingBox();
	pending = std::vector<GameObject*>();
	objects = std::vector<GameObject*>();
	//children = new OctTree[8];

    boxes = std::vector<GameObject*>();
}


OctTree::OctTree(BoundingBox& reg)
{
	region = reg;
	pending = std::vector<GameObject*>();
	objects = std::vector<GameObject*>();
	//children = new OctTree[8];

    boxes = std::vector<GameObject*>();
}

OctTree::OctTree(BoundingBox& reg, std::vector<GameObject*>& pend)
{
	region = reg;
	pending = pend;
	objects = std::vector<GameObject*>();
	//children = new OctTree[8];

    boxes = std::vector<GameObject*>();
}

OctTree& OctTree::operator=(OctTree& other)
{
    region = other.region;
    pending = other.pending;
    objects = other.objects;
    children = other.children;

    return *this;
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

	//delete[] children;

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
				if (octant[i].contains(bc->getBoundingBox()))
				{
					octList[i].push_back(objects[index]);
					delist.push_back(index);
					break;
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
			active[i] = 1;
			children[i].buildTree();
		}
	}

    bufferData();
		
	treeBuilt = true;
	treeReady = true;
}

OctTree& OctTree::createNode(BoundingBox& region, std::vector<GameObject*> objList)
{
	//if (objList.size() == 0)
		//return NULL;

	OctTree ret = OctTree(region, objList);
	ret.parent = this;

	return ret;
}

void OctTree::checkTree()
{
    cout << children[0].active << endl;

	//check if this is a leaf
	if (active != 00000000) //not a leaf
	{
		//run this method of each active child
		for (int i = 0; i < 8; i++) {
			//get the bitshifted value of active
			bitset<8> newSet = active << i;
			//check if the leftmost value is 1
			if (newSet[0] == 1) {
				//if so run the check on that tree
				children[i].checkTree();
			}
		}
	}
	else //is a leaf - do collision check
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			BoxCollider* c = (BoxCollider*)(*objects[i]).getComponent(EGameComponentType::BOX_COLLIDER);

			if (c == nullptr) continue;

			c->colliding = false;
		}

		for (unsigned int i = 0; i < objects.size(); i++)
		{
			BoxCollider* c = (BoxCollider*)(*objects[i]).getComponent(EGameComponentType::BOX_COLLIDER);

			if (c == nullptr) continue;

			for (unsigned int k = i + 1; k < objects.size(); k++)
			{
				BoxCollider* bc = (BoxCollider*)(*objects[k]).getComponent(EGameComponentType::BOX_COLLIDER);

				if (bc == nullptr) continue;

				if (c->isColliding(bc) && c->gameObject->tag != bc->gameObject->tag)
				{
					c->colliding = true;
					bc->colliding = true;
                    cout << "colliding" << endl;
				}
				else
				{
					bc->colliding = false;
				}
			}
		}
	}
}

void OctTree::bufferData()
{
    //std::cout << "bufferdata" << std::endl;
    /*
    GameObject* box = new GameObject();
    box->transform->scale = region.getSize();
    Model* boxModel = new Model("cube");
    Material* matBox = new Material(EMaterialType::DEFAULT, ShaderManager::getDefaultShader());
    MeshRenderer* mr = new MeshRenderer(EVertexFormat::XYZ_UV, boxModel, matBox);
    mr->setWireframe(true);
    boxes.push_back(box);*/
}

void OctTree::render()
{
    //std::cout << "num boxes: " << boxes.size() << std::endl;
    /*
    for (unsigned int i = 0; i < boxes.size(); i++)
    {
        boxes[i]->render();
    }

    //remove old boxes
    if (parent == nullptr)
    {
        for (auto obj : boxes)
            delete obj;
        boxes.clear();
    }*/
}