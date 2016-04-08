#include <GL\glew.h>
#include "meshrenderer.h"

#include <iostream>
using namespace std;

MeshRenderer::MeshRenderer(Model* model, Material* mat)
{
	type = MESH_RENDERER;
	mesh = model->getMesh();
	material = mat;
}

MeshRenderer::~MeshRenderer() {}

void MeshRenderer::init()
{
    transform = gameObject->transform;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->getDataCount() * sizeof(float), &mesh->data[0], GL_STATIC_DRAW);
	
	int size = material->getDataSize();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, (void*)0);

	if (mesh->hasUVs)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, size, (void*)12);
	}

	if (mesh->hasNormals)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, size, (void*)20);
	}

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getNumIndices() * sizeof(int), &mesh->indices[0], GL_STATIC_DRAW);
}

void MeshRenderer::render()
{
    material->readyGL();
	glBindVertexArray(vao);

    glProgramUniformMatrix4fv(material->getShader()->getProgram(),
        material->getShader()->getUniformLocation("model"),
        1,
        GL_FALSE,
        &(transform->getModelMatrix())[0][0]);

	glDrawElements(GL_TRIANGLES, mesh->getNumIndices(), GL_UNSIGNED_INT, NULL);
}