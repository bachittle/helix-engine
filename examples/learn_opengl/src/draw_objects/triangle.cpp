#include "draw_objects/triangle.hpp"

#include <opengl/buffer.hpp>
#include <opengl/shader.hpp>

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace lwgle::draw_objects {

Solid_Triangle::Solid_Triangle() : program(vs, fs) {
    vs.load_from_file("../res/shaders/ndc_only/solid.vert");
    fs.load_from_file("../res/shaders/ndc_only/solid.frag");
    program.attachShaders();

    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, 0.0f}, // bottom left
        {0.5f, -0.5f, 0.0f},  // bottom right
        {0.0f, 0.5f, 0.0f}    // top
    };

    // clang-format off
    buf.load(
        {
            vertices[0].x, vertices[0].y, vertices[0].z, 
            vertices[1].x, vertices[1].y, vertices[1].z,
            vertices[2].x, vertices[2].y, vertices[2].z
        },
        {3});
    // clang-format on
}
void Solid_Triangle::draw() {
    program.use();
    buf.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Textured_Triangle::Textured_Triangle() : program(vs, fs) {
    vs.load_from_file("../res/shaders/ndc_only/texture.vert");
    fs.load_from_file("../res/shaders/ndc_only/texture.frag");
    program.attachShaders();

    tex.load_from_file("../res/textures/container.jpg");

    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f}, // bottom left
        {0.5f, -0.5f, 0.0f},  // bottom right
        {0.0f, 0.5f, 0.0f}    // top
    };

    std::vector<glm::vec2> tex_coords = {
        {0.0f, 0.0f}, // bottom left
        {1.0f, 0.0f}, // bottom right
        {0.5f, 1.0f}  // top
    };

    // clang-format off
    buf.load(
        {
            positions[0].x, positions[0].y, positions[0].z, tex_coords[0].x, tex_coords[0].y,
            positions[1].x, positions[1].y, positions[1].z, tex_coords[1].x, tex_coords[1].y,
            positions[2].x, positions[2].y, positions[2].z, tex_coords[2].x, tex_coords[2].y
        },
        {3, 2});
    // clang-format on
}

void Textured_Triangle::draw() {
    program.use();
    tex.bind();
    buf.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Rainbow_Triangle::Rainbow_Triangle() : program(vs, fs) {
    vs.load_from_file("../res/shaders/ndc_only/rainbow.vert");
    fs.load_from_file("../res/shaders/ndc_only/rainbow.frag");
    program.attachShaders();

    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f}, // bottom left
        {0.5f, -0.5f, 0.0f},  // bottom right
        {0.0f, 0.5f, 0.0f}    // top
    };

    std::vector<glm::vec3> colors = {
        {1.0f, 0.0f, 0.0f}, // bottom left
        {0.0f, 1.0f, 0.0f}, // bottom right
        {0.0f, 0.0f, 1.0f}  // top
    };

    // clang-format off
    buf.load(
        {
            positions[0].x, positions[0].y, positions[0].z, colors[0].x, colors[0].y, colors[0].z,
            positions[1].x, positions[1].y, positions[1].z, colors[1].x, colors[1].y, colors[1].z,
            positions[2].x, positions[2].y, positions[2].z, colors[2].x, colors[2].y, colors[2].z
        },
        {3, 3});
    // clang-format on
}

void Rainbow_Triangle::draw() {
    program.use();
    buf.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::unique_ptr<Triangle> TriangleFactory::create() {
    switch (type) {
    case TriangleType::Solid:
        return std::make_unique<Solid_Triangle>();
    case TriangleType::Textured:
        return std::make_unique<Textured_Triangle>();
    case TriangleType::Rainbow:
        return std::make_unique<Rainbow_Triangle>();
    default:
        return nullptr;
    }
}

} // namespace lwgle::draw_objects