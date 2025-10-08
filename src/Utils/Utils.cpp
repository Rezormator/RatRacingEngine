#include "Utils.h"
#include <fstream>
#include <sstream>
#include <stb/stb_image.h>
#include <filesystem>
#include "../Error/Error.h"

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

    std::string GetObjFileName(const std::string &fileDirectory) {
        for (const auto& entry : std::filesystem::directory_iterator(fileDirectory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".obj") {
                return entry.path().filename().string();
            }
        }
        Error::LogError(std::vector<std::string> {".obj dont found", fileDirectory});
        return "object";
    }

    std::string GetTwoLetters(const std::string& word) {
        std::string result;
        for (const char c : word) {
            if (std::isupper(static_cast<unsigned char>(c)) && result.size()<2) {
                result += c;
            }
        }
        for (const char c : word) {
            if (result.size()<2) {
                result += c;
            }
        }
        return result;
    }
}
