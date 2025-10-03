#include "Resources.h"
#include <filesystem>
#include <map>
#include <unordered_map>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "../Utils/Utils.h"
#include "../Error/Error.h"
#include "../GameObject/Components/Model/Model.h"
#include "../Material/DefaultMaterial/DefaultMaterial.h"
#include "../Material/TextureMaterial/TextureMaterial.h"

namespace Resources {
    std::vector<Model> models;
    std::vector<Mesh> meshes;
    std::vector<Material *> materials;
    std::unordered_map<std::string, uint> modelsIndexMap;
    // std::unordered_map<std::string, uint> meshesIndexMap;
    std::unordered_map<std::string, uint> materialIndexMap;

    void LoadMaterials(const aiScene *scene, const std::string &modelDirectory) {
        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            const auto aiMaterial = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
            const auto materialName = aiMaterial->GetName().C_Str();

            if (materialIndexMap.contains(materialName)) {
                continue;
            }

            if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE) == 0) {
                aiDefaultMaterial material;
                material.name = materialName;
                aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, material.ambient);
                aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, material.diffuse);
                aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, material.specular);
                aiMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, material.emission);
                aiMaterial->Get(AI_MATKEY_SHININESS, material.shininess);
                materials.push_back(new DefaultMaterial(material));
                materialIndexMap[materialName] = static_cast<int>(materials.size()) - 1;
            } else {
                aiTextureMaterial material{};
                material.name = materialName;
                material.diffuse = Utils::LoadMaterialTextures(aiMaterial, aiTextureType_DIFFUSE, modelDirectory);
                material.specular = Utils::LoadMaterialTextures(aiMaterial, aiTextureType_SPECULAR, modelDirectory);
                material.emission = Utils::LoadMaterialTextures(aiMaterial, aiTextureType_EMISSIVE, modelDirectory);
                aiMaterial->Get(AI_MATKEY_SHININESS, material.shininess);
                materials.push_back(new TextureMaterial(material));
                materialIndexMap[materialName] = static_cast<int>(materials.size()) - 1;
            }
        }
    }

    void ProcessNode(const aiNode *node, const aiScene *scene, std::vector<uint> *meshesIndex) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            meshesIndex->push_back(meshes.size());
            const auto mesh = scene->mMeshes[node->mMeshes[i]];
            const auto materialName =  scene->mMaterials[mesh->mMaterialIndex]->GetName().C_Str();
            meshes.push_back(Mesh(mesh, materialIndexMap[materialName]));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene, meshesIndex);
        }
    }

    void LoadModel(const std::string &modelDirectory) {
        const auto modelName = Utils::GetObjFileName(modelDirectory);
        const auto modelPath = modelDirectory + '/' + modelName + ".obj";
        Assimp::Importer importer;
        const auto scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Error::LogError(std::vector<std::string>{"Model failed to load", importer.GetErrorString()});
        }
        LoadMaterials(scene, modelDirectory);
        const auto meshesIndex = new std::vector<uint>();
        ProcessNode(scene->mRootNode, scene, meshesIndex);
        modelsIndexMap[modelName] = models.size();
        models.push_back(Model(std::filesystem::path(modelDirectory).filename().string(), *meshesIndex));
        delete meshesIndex;
    }

    Material *GetMaterialByIndex(const uint index) {
        return materials[index];
    }

    uint GetMaterialIndexByName(const std::string &name) {
        return materialIndexMap[name];
    }

    void Dispose() {
        for (const auto material : materials) {
            material->Dispose();
            delete material;
        }
    }

}
