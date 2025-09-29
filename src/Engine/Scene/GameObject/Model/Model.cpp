#include "Model.h"
#include <iostream>
#include <ranges>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../../../../Error/Error.h"
#include "Material/DefaultMaterial/DefaultMaterial.h"
#include "Material/TextureMaterial/TextureMaterial.h"

Model::Model(const char *path) {
    directory = std::string(path).substr(0, std::string(path).find_last_of('/'));
    LoadModel(path);
}

Model::~Model() {
    for (const auto mesh: meshes) {
        delete mesh;
    }
    for (const auto* material : std::views::values(materials)) {
        delete material;
    }
    materials.clear();
}

void Model::LoadModel(const std::string &path) {
    Assimp::Importer importer;
    const auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Error::LogError(std::vector<std::string>{"Model failed to load", importer.GetErrorString()});
    }
    directory = path.substr(0, path.find_last_of('/'));
    LoadMaterials(scene);
}

void Model::LoadMaterials(const aiScene *scene) {
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const auto materialIndex = scene->mMeshes[i]->mMaterialIndex;

        if (materials[materialIndex] != nullptr) {
            continue;
        }

        const auto mat = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];

        if (mat->GetTextureCount(aiTextureType_DIFFUSE) == 0) {
            aiDefaultMaterial material;
            mat->Get(AI_MATKEY_COLOR_AMBIENT, material.ambient);
            mat->Get(AI_MATKEY_COLOR_DIFFUSE, material.diffuse);
            mat->Get(AI_MATKEY_COLOR_SPECULAR, material.specular);
            mat->Get(AI_MATKEY_COLOR_EMISSIVE, material.emission);
            mat->Get(AI_MATKEY_SHININESS, material.shininess);
            materials[materialIndex] = new DefaultMaterial(material);
        } else {
            aiTextureMaterial material{};
            material.diffuse = Utils::LoadMaterialTextures(mat, aiTextureType_DIFFUSE, directory);
            material.specular = Utils::LoadMaterialTextures(mat, aiTextureType_SPECULAR, directory);
            material.emission = Utils::LoadMaterialTextures(mat, aiTextureType_EMISSIVE, directory);
            mat->Get(AI_MATKEY_SHININESS, material.shininess);
            materials[materialIndex] = new TextureMaterial(material);
        }
    }
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(const aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        const auto mesh = scene->mMeshes[node->mMeshes[i]];
        const auto materialIndex = mesh->mMaterialIndex;
        meshes.push_back(new Mesh(mesh, materials[materialIndex]));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

void Model::UpdateTransform() {
    for (const auto& mesh : meshes) {
        mesh->SetModel(model);
    }
}

std::string Model::GetDirectory() const {
    return directory;
}

void Model::SetModel(const glm::mat4 &model) {
    this->model = model;
    this->UpdateTransform();
}


void Model::Render(Shader *shader) const {
    for (const auto mesh: meshes) {
        mesh->Render(shader);
    }
}
