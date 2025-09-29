#pragma once
#include <glad/glad.h>

class Texture {
    static constexpr GLint DEFAULT_WRAP = GL_REPEAT;
    static constexpr GLint DEFAULT_FILTRATION = GL_LINEAR;
    GLuint id;
    int width;
    int height;
    GLvoid CreateTexture(GLint wrapS, GLint wrapT, GLint filtrationMin, GLint filtrationMag);
    GLvoid LoadTexture(const char *texturePath);
public:
    explicit Texture(const char *texturePath, GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT,
                     GLint filtrationMin = GL_LINEAR, GLint filtrationMag = GL_LINEAR);
    GLvoid Bind() const;
};
