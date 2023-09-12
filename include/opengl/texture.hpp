#pragma once

#include <filesystem>

namespace lwgle::texture {

namespace fs = std::filesystem;

struct TextureData {
    unsigned char* data;
    int width;
    int height;
    int nrChannels;
};

class Texture {
public:
    Texture();
    ~Texture();

    // load an image from a file
    // use that image as a texture
    // image can be png, jpg, bmp, etc.
    // uses stb_image internally
    void load_from_file(fs::path path);

    // load an image from memory
    // must be loaded in the specified TextureData format
    void load_from_memory(TextureData const& data);

    void bind();

private:
    unsigned int id;
};

} // namespace lwgle::texture