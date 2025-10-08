#include "Scene.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "../../../Resources/Resources.h"

Scene::Scene(const std::string &path) {
    LoadFromJson(path);
}

void Scene::LoadFromJson(const std::string &path) {
    std::ifstream file(path);
    nlohmann::json json;
    file >> json;
    file.close();

    const auto& cameraJson = json["camera"];
    camera = new Camera(glm::vec3(cameraJson["position"][0], cameraJson["position"][1], cameraJson["position"][2]));

    for (const auto& gameObjectJson : json["gameObjects"]) {
        const auto gameObject = new GameObject();
        std::vector<float> transform = gameObjectJson["transform"];
        gameObject->SetModel(glm::make_mat4(transform.data()));
        gameObjects[gameObject] = gameObjectJson["model"];
    }
}

std::string Scene::GetName() const {
    return name;
}

Camera* Scene::GetCamera() const {
    return camera;
}

nlohmann::json Scene::GetJson() const {
    nlohmann::json json;
    // TODO : convert to json file
    return json;
}

void Scene::Render(Shader *shader) const {
    camera->Update();
    camera->Render(shader);

    for (const auto [gameObject, modelName] : gameObjects) {
        shader->SetMat4("model", gameObject->GetModel());
        const auto model = Resources::GetModelByIndex(Resources::GetModelIndexByName(modelName));
        for (const auto meshIndex : model->GetMeshes()) {
            const auto mesh = Resources::GetMeshByIndex(meshIndex);
            Resources::GetMaterialByIndex(mesh->GetMaterialIndex())->Apply(shader);
            glBindVertexArray(mesh->GetVAO());
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->GetIndicesCount()), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
    }
}

void Scene::Dispose() {
    delete camera;
}
