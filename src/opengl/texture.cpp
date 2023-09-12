#include "opengl/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <glad/gl.h>
#include <stb_image.h>

namespace lwgle::texture {

Texture::Texture() {
    glGenTextures(1, &id);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::load_from_file(fs::path path) {
    // stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data =
        stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);

    if (!data) {
        throw std::runtime_error("Failed to load image: " + path.string());
    }

    load_from_memory({data, width, height, nrChannels});
    stbi_image_free(data);
}

void Texture::load_from_memory(TextureData const& data) {
    GLenum format;
    switch (data.nrChannels) {
    case 1:
        format = GL_RED;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        throw std::runtime_error("Unsupported number of channels");
    }

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, data.width, data.height, 0, format,
                 GL_UNSIGNED_BYTE, data.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // makes textures less blurry
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

} // namespace lwgle::texture