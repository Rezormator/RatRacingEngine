#pragma once
#include <string>
#include "../../../GameObject/Components/Camera/Camera.h"
#include "../../../GameObject/Components/Model/Model.h"
#include <map>
#include "../../../Dispose/IDisposable.h"

class Scene : IDisposable {
private:
    Camera *camera;
    // std::map<GameObject*, uint>;
    void LoadModels(const std::string &models);
    void LoadModelsMatrices(const std::string &modelsMatrices);
public:
    explicit Scene(const std::string &path);
    NODISCARD Camera *GetCamera() const;
    void Render(Shader *shader) const;
    void Dispose() override;
};
