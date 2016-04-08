#pragma once
#include "model.h"
#include "mesh.h"
#include "gamec.h"
#include "material.h"
#include <GLFW\glfw3.h>
#include "gameobject.h"

class Transform;
class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Model*, Material*);
	~MeshRenderer();
	void init() override;
	void render() override;
private:
	Mesh* mesh;
	Material* material;
    Transform* transform;

	GLuint vao;
	GLuint vbo;
	GLuint ibo;
};