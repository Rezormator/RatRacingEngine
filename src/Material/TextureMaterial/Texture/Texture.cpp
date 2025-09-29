#include "Texture.h"
#include <stb/stb_image.h>
#include "../../../Error/Error.h"

Texture::Texture(const char *texturePath, const GLint wrapS, const GLint wrapT, const GLint filtrationMin,
                 const GLint filtrationMag) : id(0), width(0), height(0) {
    CreateTexture(wrapS, wrapT, filtrationMin, filtrationMag);
    LoadTexture(texturePath);
}

GLvoid Texture::CreateTexture(const GLint wrapS, const GLint wrapT, const GLint filtrationMin,
                              const GLint filtrationMag) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtrationMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtrationMag);
}

GLvoid Texture::LoadTexture(const char *texturePath) {
    stbi_set_flip_vertically_on_load(true);
    GLint numChannels;
    const auto data = stbi_load(texturePath, &width, &height, &numChannels, 0);
    if (!data) {
        Error::LogError(std::vector<std::string>{"TEXTURE", "FAILED_TO_LOAD"});
    }
    const auto format = numChannels == 1 ? GL_RED : numChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLvoid Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}
