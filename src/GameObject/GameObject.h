#pragma once
#include <glm/glm.hpp>

#include "../Dispose/IDisposable.h"
#include "../Shader/Shader.h"
#include "../Utils/Utils.h"

class GameObject : IDisposable {
protected:
    static constexpr glm::vec3 DEFAULT_POSITION {0.0f};
    static constexpr glm::vec3 DEFAULT_ROTATION {0.0f};
    static constexpr glm::vec3 DEFAULT_SCALE {1.0f};
    static constexpr glm::vec3 X_AXIS {1.0f, 0.0f, 0.0f};
    static constexpr glm::vec3 Y_AXIS {0.0f, 1.0f, 0.0f};
    static constexpr glm::vec3 Z_AXIS {0.0f, 0.0f, 1.0f};
    glm::mat4 model;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    virtual void UpdateTransform();
public:
    explicit GameObject(const glm::vec3 &position = DEFAULT_POSITION,
                        const glm::vec3 &rotation = DEFAULT_ROTATION,
                        const glm::vec3 &scale = DEFAULT_SCALE);
    virtual void SetModel(const glm::mat4 &model);
    void SetPosition(const glm::vec3 &position);
    void SetRotation(const glm::vec3 &rotation);
    void SetScale(const glm::vec3 &scale);
    NODISCARD glm::vec3 GetPosition() const;
    NODISCARD glm::vec3 GetRotation() const;
    NODISCARD glm::vec3 GetScale() const;
    NODISCARD glm::mat4 GetModel() const;
    virtual void Update();
    virtual void Render(Shader *shader) const;
    void Dispose() override;
};
