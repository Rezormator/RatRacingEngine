#pragma once
#include <vector>

#include "../../../../Dispose/IDisposable.h"
#include "Vertex/Vertex.h"
#include "../../../../Utils/Utils.h"

class Mesh final : public IDisposable {
private:
    GLuint VBO{};
    GLuint EBO{};
    GLuint VAO{};
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    uint materialIndex;
    GLvoid CopyVertices(const aiMesh *mesh);
    GLvoid CopyIndices(const aiMesh *mesh);
    GLvoid SetupMesh();
public:
    Mesh(const aiMesh *mesh, uint materialIndex);
    void SetMaterialIndex(uint materialIndex);
    NODISCARD GLuint GetVAO() const;
    NODISCARD uint GetIndicesCount() const;
    NODISCARD uint GetMaterialIndex() const;
    void Dispose() override;
};
