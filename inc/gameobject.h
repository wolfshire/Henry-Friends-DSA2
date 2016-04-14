#pragma once
#include <glm\gtc\matrix_transform.hpp>
#include <vector>
using namespace std;

class Transform;
class GameComponent;
class GameObject
{
public:
	GameObject();
    GameObject(glm::vec3, glm::vec3, glm::vec3);
	~GameObject();

	void addComponent(GameComponent*);

	//gets the first component from the list of type T
	template <typename T>
	T getComponent(T);

	void init();
	void update();
	void render();

	GameObject* getParent();
	void setParent(GameObject*);
	int getNumChildren();
	void addChild(GameObject*);
	GameObject* getChild(int);

	Transform* transform;
private:
	vector<GameComponent*> components;
	vector<GameObject*> children;
	GameObject* parent;
};