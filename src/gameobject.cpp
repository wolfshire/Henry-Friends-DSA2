#include <typeinfo>
#include "camera.h"
#include "flymove.h"
#include "gameobject.h"
#include "meshrenderer.h"
#include "asteroid.h"
#include "transform.h"

GameObject::GameObject()
{
	transform = new Transform();
}

GameObject::GameObject(vec3 pos, vec3 rot, vec3 scale)
{
    transform = new Transform(pos, rot, scale);
}

GameObject::~GameObject() {}

void GameObject::addComponent(GameComponent* igc)
{
	igc->gameObject = this;
	components.push_back(igc);
}

template<typename T>
inline T GameObject::getComponent(T comp)
{
	for (int i = 0; i < components.size(); i++)
		if (typeid(comp).name() == typeid(components[i]).name())
			return components[i];

	return NULL;
}

void GameObject::init()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		switch (components[i]->type)
		{
		case CAMERA:
			dynamic_cast<Camera*>(components[i])->init();
			continue;
		case MESH_RENDERER:
			dynamic_cast<MeshRenderer*>(components[i])->init();
			continue;
		case FLY_MOVE:
			dynamic_cast<FlyMove*>(components[i])->init();
			continue;
        case ASTEROID:
            dynamic_cast<Asteroid*>(components[i])->init();
            continue;
		default:
			cout << "Error: Unknown component type: " << components[i]->type << endl;
			continue;
		}
	}

	for (unsigned int i = 0; i < children.size(); i++)
		(*children[i]).init();
}

void GameObject::update()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		switch (components[i]->type)
		{
		case CAMERA:
			dynamic_cast<Camera*>(components[i])->update();
			continue;
		case FLY_MOVE:
			dynamic_cast<FlyMove*>(components[i])->update();
			continue;
        case ASTEROID:
            dynamic_cast<Asteroid*>(components[i])->update();
            continue;
		default:
			//cout << "Error: Unknown component type: " << components[i]->type << endl;
			continue;
		}
	}

	for (unsigned int i = 0; i < children.size(); i++)
		(*children[i]).update();
}

void GameObject::render()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		switch (components[i]->type)
		{
		case MESH_RENDERER:
			dynamic_cast<MeshRenderer*>(components[i])->render();
			continue;
		default:
			//cout << "Error: Unknown component type: " << components[i]->type << endl;
			continue;
		}
	}

	for (unsigned int i = 0; i < children.size(); i++)
		(*children[i]).render();
}

int GameObject::getNumChildren() { return children.size(); }

GameObject* GameObject::getParent()
{
	return parent;
}

void GameObject::setParent(GameObject* parent)
{
	this->parent = parent;
    transform->parent = parent->transform;
}

void GameObject::addChild(GameObject* child)
{
	child->setParent(this);
	children.push_back(child);
}

GameObject* GameObject::getChild(int index)
{
	if (index < getNumChildren())
		return children[index];
	
	throw new exception("Index out of bounds");
}