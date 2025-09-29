#pragma once
#include "../../GameObject.h"

class Camera final : public GameObject {
protected:
    static constexpr glm::vec3 DEFAULT_CAMERA_POSITION {0.0f, 0.0f, 3.0f};
    // static constexpr glm::vec3 WORLD_UP {0.0f, 1.0f, 0.0f};
    static constexpr auto DEFAULT_NEAR_PLANE = 0.1f;
    static constexpr auto DEFAULT_FAR_PLANE = 100.0f;
    static constexpr auto DEFAULT_FOV = glm::radians(45.0f);
    float nearPlane;
    float farPlane;
    float fov;
    glm::vec3 front;
    glm::mat4 view;
    glm::mat4 projection;
    void InputMovement(const glm::vec3 &front, const glm::vec3 &up, const glm::vec3 &right);
    void UpdateTransform() override;
public:
    explicit Camera(const glm::vec3 &position = DEFAULT_CAMERA_POSITION);
    ~Camera() override = default;
    void SetNearPlane(float nearPlane);
    void SetFarPlane(float farPlane);
    void SetFov(float degrees);
    NODISCARD glm::vec3 GetFront() const;
    NODISCARD glm::mat4 GetViewMatrix() const;
    NODISCARD glm::mat4 GetProjectionMatrix() const;
    void Update() override;
    void Render(Shader *shader) const override;
};
