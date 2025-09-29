#pragma once
#include <vector>
#include "../../../GameObject.h"
#include "../../../../Shader/Shader.h"
#include "../../../../Material/Material.h"
#include "Vertex/Vertex.h"

class Mesh final : public GameObject {
private:
    GLuint VBO{};
    GLuint EBO{};
    GLuint VAO{};
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    Material *material;
    GLvoid CopyVertices(const aiMesh *mesh);
    GLvoid CopyIndices(const aiMesh *mesh);
    GLvoid SetupMesh();
public:
    Mesh(const aiMesh *mesh, Material *material);
    GLvoid Render(Shader *shader) const override;
};
