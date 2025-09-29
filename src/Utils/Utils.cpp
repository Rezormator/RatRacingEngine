#include "Utils.h"
#include <fstream>
#include <sstream>
#include <stb/stb_image.h>

namespace Utils {
    std::string ReadTextFromFile(const std::string &filePath) {
        std::ifstream file(filePath);
        std::stringstream fileContentStream;
        fileContentStream << file.rdbuf();
        std::string fileContent = fileContentStream.str();
        file.close();
        return fileContent;
    }

    glm::vec3 Color3DToVec3(const aiColor3D &aiColor3D) {
        return {aiColor3D.r, aiColor3D.g, aiColor3D.b};
    }

    Texture *LoadMaterialTextures(const aiMaterial *mat, const aiTextureType type, const std::string &directory) {
        stbi_set_flip_vertically_on_load(true);
        aiString texName;
        mat->GetTexture(type, 0, &texName);
        const auto texPath = directory + "/" + texName.C_Str();
        return new Texture(texPath.c_str());
    }
}
