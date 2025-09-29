#include "Camera.h"
#include <iostream>
#include "../../../Core/Core.h"
#include "../../../Core/Time/Time.h"
#include "../../../Core/Input/Input.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(const glm::vec3 &position) : GameObject(position), nearPlane(DEFAULT_NEAR_PLANE),
                                            farPlane(DEFAULT_FAR_PLANE), fov(DEFAULT_FOV) {
}

void Camera::InputMovement(const glm::vec3 &front, const glm::vec3 &up, const glm::vec3 &right) {
    const auto speed = 5.0f * Time::GetDeltaTime();
    if (Input::GetKeyDown(GLFW_KEY_W)) {
        position += speed * front;
    }
    if (Input::GetKeyDown(GLFW_KEY_S)) {
        position -= speed * front;
    }
    if (Input::GetKeyDown(GLFW_KEY_A)) {
        position -= right * speed;
    }
    if (Input::GetKeyDown(GLFW_KEY_D)) {
        position += right * speed;
    }
    if (Input::GetKeyDown(GLFW_KEY_LEFT_CONTROL)) {
        position -= up * speed;
    }
    if (Input::GetKeyDown(GLFW_KEY_SPACE)) {
        position += up * speed;
    }

    rotation.x += Input::GetYOffset() * 0.3f;
    rotation.y -= Input::GetXOffset() * 0.3f;
    rotation.x = glm::clamp(rotation.x, -89.0f, 89.0f);
}

void Camera::UpdateTransform() {
    GameObject::UpdateTransform();

    front.x = glm::sin(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));
    front.y = glm::sin(glm::radians(rotation.x));
    front.z = glm::cos(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));
    front = glm::normalize(front);
    const glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    const  glm::vec3 up = glm::normalize(glm::cross(right, front));
    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(fov, Core::GetAspectRatio(), nearPlane, farPlane);
    InputMovement(front, up, right);
}

void Camera::SetNearPlane(const float nearPlane) {
    this->nearPlane = nearPlane;
}

void Camera::SetFarPlane(const float farPlane) {
    this->farPlane = farPlane;
}

void Camera::SetFov(const float degrees) {
    this->fov = glm::radians(degrees);
}

glm::vec3 Camera::GetFront() const {
    return front;
}

glm::mat4 Camera::GetViewMatrix() const {
    return view;
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return projection;
}

void Camera::Update() {
    UpdateTransform();
}

void Camera::Render(Shader *shader) const {
    shader->SetMat4("projection", projection);
    shader->SetMat4("view", view);
    shader->SetVec3("viewPos", position);
}