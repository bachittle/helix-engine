#include "opengl/buffer.hpp"

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace lwgle::buffer {

Buffer::Buffer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

Buffer::Buffer(std::vector<float> const& vertices,
               std::vector<unsigned int> const& attributes)
    : Buffer() {
    load(vertices, attributes);
}

Buffer::~Buffer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Buffer::load(std::vector<float> const& vertices,
                  std::vector<unsigned int> const& attributes) {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    unsigned int stride = 0;
    for (auto const& attribute : attributes) {
        stride += attribute;
    }

    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); i++) {
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE,
                              stride * sizeof(float),
                              (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += attributes[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    size = vertices.size() / stride;
}

void Buffer::set_EBO(std::vector<unsigned int> const& indices) {
    glBindVertexArray(VAO);

    EBO = 0;
    glGenBuffers(1, &EBO.value());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO.value());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    size = indices.size();
}

void Buffer::bind() {
    glBindVertexArray(VAO);
}

void Buffer::draw() {
    auto log_draw = [&](const char* name) {
        static bool first = true;
        if (!first)
            return;
        spdlog::trace("Drawing {} of size: {}", name, size);
        spdlog::trace("VAO: {}", VAO);
        first = false;
    };
    glBindVertexArray(VAO);
    if (EBO.has_value()) {
        log_draw("elements");
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    } else {
        log_draw("arrays");
        glDrawArrays(GL_TRIANGLES, 0, size);
    }
    glBindVertexArray(0);
}

} // namespace lwgle::buffer