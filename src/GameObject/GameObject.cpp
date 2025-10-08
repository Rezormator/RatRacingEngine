#include "GameObject.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
    : model(glm::mat4(1.0f)), position(position), rotation(rotation), scale(scale) {
    GameObject::UpdateTransform();
}

void GameObject::SetModel(const glm::mat4 &model) {
    this->model = model;
    glm::quat rotationQuat;
    glm::vec3 skew;
    glm::vec4 perspective;
    decompose(model, scale, rotationQuat, position, skew, perspective);
    glm::vec3 rotation = glm::eulerAngles(rotationQuat);
    UpdateTransform();
}

void GameObject::SetPosition(const glm::vec3 &position) {
    this->position = position;
    UpdateTransform();
}

void GameObject::SetRotation(const glm::vec3 &rotation) {
    this->rotation = rotation;
}

void GameObject::SetScale(const glm::vec3 &scale) {
    this->scale = scale;
    UpdateTransform();
}

glm::mat4 GameObject::GetModel() const {
    return model;
}

glm::vec3 GameObject::GetPosition() const {
    return position;
}

glm::vec3 GameObject::GetRotation() const {
    return rotation;
}

glm::vec3 GameObject::GetScale() const {
    return scale;
}

void GameObject::Update() {
    UpdateTransform();
}

void GameObject::Render(Shader *shader) const {
}


void GameObject::UpdateTransform() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), X_AXIS);
    model = glm::rotate(model, glm::radians(rotation.y), Y_AXIS);
    model = glm::rotate(model, glm::radians(rotation.z), Z_AXIS);
    model = glm::scale(model, scale);
}

void GameObject::Dispose() {
}
