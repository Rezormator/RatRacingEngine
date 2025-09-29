#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
    static constexpr int UNINITIALIZED = -1;
    GLuint id;
    static int CheckCompileErrors(GLuint shader, const std::string &type);
    static GLuint CompileShader(const std::string &shaderPath, GLuint type, const std::string &name);
public:
    Shader(const char *vertPath, const char* fragPath);
    void Bind() const;
    static void UnBind();
    void Dispose() const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVec3(const std::string &name, const glm::vec3& value) const;
    void SetVec4(const std::string &name, const glm::vec4& value) const;
    void SetMat4(const std::string &name, const glm::mat4& value) const;
};
