#pragma once
#include <vector>
#include "gameobject.h"
#include "boundingbox.h"
#include <bitset>

class OctTree
{
public:
    OctTree();
	OctTree(BoundingBox&);
    OctTree(BoundingBox&, std::vector<GameObject*>&);
    ~OctTree();

    void addObject(GameObject*);

    void clearTree();
    void buildTree();
    void updateTree();
    OctTree* createNode(BoundingBox, std::vector<GameObject*>);

	void checkTree();

    OctTree* parent = nullptr;
private:
    BoundingBox region;
    std::vector<GameObject*> pending;
    std::vector<GameObject*> objects;
    OctTree** children = nullptr;

	bitset<8> active = 00000000;
    const int MIN_SIZE = 1;

    const int MAX_LIFE = 8;
    int curLife = -1;

    bool treeBuilt = false;
    bool treeReady = false;
};