#include <GL\glew.h>
#include "meshrenderer.h"
#include "transform.h"
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
using namespace std;

MeshRenderer::MeshRenderer(EVertexFormat fmt, Model* model, Material* mat)
{
    type = MESH_RENDERER;

    format = fmt;
    mesh = model->getMesh();
    defMat = material = mat;
    bufferUsageHint = GL_STREAM_DRAW;
    drawMode = GL_TRIANGLES;

    setStride();
    createBuffers();
    loadData();
    load();
}

MeshRenderer::~MeshRenderer()
{
    delete mesh;
    delete material;

    if (defMat != nullptr)
    {
        delete defMat;
    }

    delete transform;
}

void MeshRenderer::init()
{
    GameComponent::init();
}

void MeshRenderer::clear()
{
    indexPos = 0;
    vertPos = 0;
}

void MeshRenderer::loadData()
{
    for (unsigned int i = 0; i < mesh->pos.size(); i++)
        if (mesh->hasUVs)
            addVertex(mesh->pos[i], mesh->uvs[i]);
        else
            addVertex(mesh->pos[i]);

    for (unsigned int i = 0; i < mesh->indices.size(); i++)
        addIndex(mesh->indices[i]);
}

void MeshRenderer::setFormat(EVertexFormat fmt)
{
    format = fmt;
    setStride();
    clear();
}

void MeshRenderer::setStride()
{
    switch (format)
    {
    case XYZ:
        stride = sizeof(float) * 3;
        break;
    case XYZ_COLOR:
        stride = sizeof(float) * 7;
        break;
    case XYZ_UV:
        stride = sizeof(float) * 5;
        break;
    }

    attributeCount = stride / sizeof(float);
}

void MeshRenderer::createBuffers()
{
    if (loaded) return;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
}

void MeshRenderer::deleteBuffers()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void MeshRenderer::load()
{
    if (loaded) return;

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertPos * sizeof(float), &verts[0], bufferUsageHint);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPos * sizeof(int), &indices[0], bufferUsageHint);

    switch (format)
    {
    case XYZ:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, 0);
        break;
    case XYZ_COLOR:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, false, stride, (void*)12);
        break;
    case XYZ_UV:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, stride, (void*)12);
        break;
    }

    loaded = true;
}

void MeshRenderer::reload()
{
    if (!loaded) return;

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertPos * sizeof(float), &verts[0], bufferUsageHint);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexPos * sizeof(int), &indices[0], bufferUsageHint);
}

void MeshRenderer::addVertex(float x, float y, float z)
{
    if (format != XYZ)
    {
        std::cout << "Vertex must be of same format type as buffer" << std::endl;
        return;
    }

    verts[vertPos++] = x;
    verts[vertPos++] = y;
    verts[vertPos++] = z;
}

void MeshRenderer::addVertex(const glm::vec3& v)
{
    addVertex(v.x, v.y, v.z);
}

void MeshRenderer::addVertex(float x, float y, float z, float u, float v)
{
    if (format != XYZ_UV)
    {
        std::cout << "Vertex must be of same format type as buffer" << std::endl;
        return;
    }

    verts[vertPos++] = x;
    verts[vertPos++] = y;
    verts[vertPos++] = z;
    verts[vertPos++] = u;
    verts[vertPos++] = v;
}

void MeshRenderer::addVertex(const glm::vec3& v, const glm::vec2& u)
{
    addVertex(v.x, v.y, v.z, u.x, u.y);
}

void MeshRenderer::addVertex(float x, float y, float z, float r, float g, float b, float a)
{
    if (format != XYZ_COLOR)
    {
        std::cout << "Vertex must be of same format type as buffer" << std::endl;
        return;
    }

    verts[vertPos++] = x;
    verts[vertPos++] = y;
    verts[vertPos++] = z;
    verts[vertPos++] = r;
    verts[vertPos++] = g;
    verts[vertPos++] = b;
    verts[vertPos++] = a;
}

void MeshRenderer::addVertex(const glm::vec3& v, const glm::vec4& c)
{
    addVertex(v.x, v.y, v.z, c.r, c.g, c.b, c.a);
}

void MeshRenderer::addIndex(int ind)
{
    indices[indexPos++] = ind;
}

void MeshRenderer::addIndices(int* ind, int num)
{
    for (int i = 0; i < num; i++)
        indices[indexPos++] = ind[i];
}

void MeshRenderer::render()
{
    if (!loaded) return;

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    material->readyGL();
    glBindVertexArray(vao);

    glUniformMatrix4fv(material->getShader()->getUniformLocation("model"), 1, GL_FALSE,
        value_ptr(transform->getTransformation()));

    glDrawElements(drawMode, mesh->getNumIndices(), GL_UNSIGNED_INT, NULL);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MeshRenderer::setMaterial(Material* newMat)
{
    material = newMat;
}

void MeshRenderer::clearMaterial()
{
    material = defMat;
}

void MeshRenderer::setWireframe(bool wire)
{
    wireframe = wire;
}