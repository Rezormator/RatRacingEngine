#pragma once
#include <string>
#include "../../../GameObject/Components/Camera/Camera.h"
#include "../../../GameObject/Components/Model/Model.h"
#include <map>
#include "../../../Dispose/IDisposable.h"
#include "nlohmann/json.hpp"

class Scene : IDisposable {
private:
    std::string name;
    Camera *camera;
    std::map<GameObject*, std::string> gameObjects;
    void LoadFromJson(const std::string &path);
public:
    explicit Scene(const std::string &path);
    NODISCARD std::string GetName() const;
    NODISCARD Camera *GetCamera() const;
    NODISCARD nlohmann::json GetJson() const;
    void Render(Shader *shader) const;
    void Dispose() override;
};
