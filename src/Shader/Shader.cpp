#include "Shader.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "../Error/Error.h"
#include "../Utils/Utils.h"

Shader::Shader(const char *vertPath, const char* fragPath) {
    const GLuint vertShader = CompileShader(vertPath, GL_VERTEX_SHADER, "VERTEX");
    const GLuint fragShader = CompileShader(fragPath, GL_FRAGMENT_SHADER, "FRAGMENT");

    const GLuint idTemp = glCreateProgram();
    glAttachShader(idTemp, vertShader);
    glAttachShader(idTemp, fragShader);
    glLinkProgram(idTemp);

    if (CheckCompileErrors(idTemp, "PROGRAM")) {
        id = idTemp;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

int Shader::CheckCompileErrors(const GLuint shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            Error::LogError(std::vector<std::string> {"Shader", type, "Compilation failed", infoLog}, true);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            Error::LogError(std::vector<std::string> {"Shader", type, "Linking failed",infoLog}, true);
        }
    }
    return success;
}

GLuint Shader::CompileShader(const std::string &shaderPath, const GLuint type, const std::string &name) {
    const std::string shaderSource = Utils::ReadTextFromFile(shaderPath);
    const char *shaderCode = shaderSource.c_str();
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    CheckCompileErrors(shader, name);
    return shader;
}

void Shader::Bind() const {
    glUseProgram(id);
}

void Shader::UnBind() {
    glUseProgram(0);
}

void Shader::Dispose() const {
    glDeleteProgram(id);
}

void Shader::SetInt(const std::string &name, const int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, const float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(value));
}
