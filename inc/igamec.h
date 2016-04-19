#pragma once

#include <iostream>
using namespace std;

class IGameComponent
{
public:
	virtual ~IGameComponent() {}
	virtual void init() { cout << "igc init" << endl; }
	virtual void update() {}
	virtual void render() {}
};