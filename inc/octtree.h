#pragma once
#include <vector>
#include "gameobject.h"
#include "boundingbox.h"

class OctTree
{
public:
    OctTree();
    OctTree(BoundingBox&, std::vector<GameObject*>&);
    ~OctTree();

    void addObject(GameObject*);

    void clearTree();
    void buildTree();
    void updateTree();
    OctTree* createNode(BoundingBox, std::vector<GameObject*>);

    OctTree* parent = nullptr;
private:
    BoundingBox region;
    std::vector<GameObject*> pending;
    std::vector<GameObject*> objects;
    OctTree** children = nullptr;

    unsigned int active = 0;
    const int MIN_SIZE = 1;

    const int MAX_LIFE = 8;
    int curLife = -1;

    bool treeBuilt = false;
    bool treeReady = false;
};