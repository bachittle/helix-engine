#pragma once

#include <optional>
#include <vector>

namespace lwgle::buffer {

class Buffer {
public:
    Buffer();
    Buffer(std::vector<float> const& vertices,
           std::vector<unsigned int> const& attributes);
    ~Buffer();

    void load(std::vector<float> const& vertices,
              std::vector<unsigned int> const& attributes);
    void set_EBO(std::vector<unsigned int> const& indices);
    void bind();

    // draws the elements in this buffer as triangles
    // requires shaders to be bound in OpenGL context
    void draw();

private:
    unsigned int id;

    unsigned int VAO;
    unsigned int VBO;
    std::optional<unsigned int> EBO;

    size_t size;
};

} // namespace lwgle::buffer