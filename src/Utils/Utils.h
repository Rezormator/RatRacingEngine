#pragma once
#include <string>
#include <assimp/types.h>
#include <glm/glm.hpp>
#include "../Material/TextureMaterial/Texture/Texture.h"
#include <assimp/scene.h>

#define NODISCARD [[nodiscard]]
typedef unsigned int uint;
constexpr auto UNINITIALIZED = -1;

namespace Utils {
    std::string ReadTextFromFile(const std::string &filePath);
    glm::vec3 Color3DToVec3(const aiColor3D &aiColor3D);
    Texture *LoadMaterialTextures(const aiMaterial *mat, aiTextureType type, const std::string &directory);
    std::string GetObjFileName(const std::string &fileDirectory);
}
