#pragma once

#include "../../GameObject.h"

class Light : public GameObject {
protected:
    static constexpr glm::vec3 DEFAULT_AMBIENT {0.2f};
    static constexpr glm::vec3 DEFAULT_DIFFUSE {0.5f};
    static constexpr glm::vec3 DEFAULT_SPECULAR {1.0f};
    static constexpr int DEFAULT_INDEX = 0;
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
protected:
    std::string lightName;
public:
    Light(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
        const glm::vec3 &position = DEFAULT_POSITION, const glm::vec3 &rotation = DEFAULT_ROTATION);
    void SetAmbient(const glm::vec3 &ambient);
    void SetDiffuse(const glm::vec3 &diffuse);
    void SetSpecular(const glm::vec3 &specular);
    NODISCARD glm::vec3 GetAmbient() const;
    NODISCARD glm::vec3 GetDiffuse() const;
    NODISCARD glm::vec3 GetSpecular() const;
    virtual void SetIndex(int index) = 0;
    void Render(Shader *shader) const override = 0;
};
