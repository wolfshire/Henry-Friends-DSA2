#pragma once
#include "gamec.h"
#include "model.h"
#include "mesh.h"
#include "material.h"
#include "vertexformat.h"
#include <GLFW\glfw3.h>

class Transform;
class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(EVertexFormat, Model*, Material*);
	~MeshRenderer();

    void clear();
    void setFormat(EVertexFormat);
    void load();
    void reload();
    void addVertex(float, float, float);
    void addVertex(const glm::vec3&);
    void addVertex(float, float, float, float, float);
    void addVertex(const glm::vec3&, const glm::vec2&);
    void addVertex(float, float, float, float, float, float, float);
    void addVertex(const glm::vec3&, const glm::vec4&);
    void addIndex(int);
    void addIndices(int*, int);
    void init() override;
	void render() override;
    void setMaterial(Material*);
    void clearMaterial();
private:
    void loadData();
    void setStride();
    void createBuffers();
    void deleteBuffers();

    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    float verts[1024];
    int indices[1024];
    int vertPos = 0;
    int indexPos = 0;

    EVertexFormat format;
    int stride;
    int attributeCount;
    bool loaded = false;
    int bufferUsageHint;
    int drawMode;

	Mesh* mesh;
	Material* material;
    Material* defMat;
};