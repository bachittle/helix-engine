#include "draw_objects/square.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace lwgle::draw_objects {

Solid_Square::Solid_Square() : program(vs, fs) {
    vs.load_from_file("../res/shaders/ndc_only/solid.vert");
    fs.load_from_file("../res/shaders/ndc_only/solid.frag");
    program.attachShaders();

    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, 0.0f}, // bottom left
        {0.5f, -0.5f, 0.0f},  // bottom right
        {0.5f, 0.5f, 0.0f},   // top right
        {-0.5f, 0.5f, 0.0f}   // top left
    };

    // clang-format off
        buf.load(
            {
                vertices[0].x, vertices[0].y, vertices[0].z, 
                vertices[1].x, vertices[1].y, vertices[1].z,
                vertices[2].x, vertices[2].y, vertices[2].z,
                vertices[3].x, vertices[3].y, vertices[3].z
            },
            {3});
        buf.set_EBO({0, 1, 2, 0, 2, 3});
    // clang-format on
}

void Solid_Square::draw() {
    program.use();
    buf.draw();
}

Textured_Square::Textured_Square() : program(vs, fs) {
    vs.load_from_file("../res/shaders/ndc_only/texture.vert");
    fs.load_from_file("../res/shaders/ndc_only/texture.frag");
    program.attachShaders();

    tex.load_from_file("../res/textures/container.jpg");

    std::vector<glm::vec3> positions = {
        {-0.5f, -0.5f, 0.0f}, // bottom left
        {0.5f, -0.5f, 0.0f},  // bottom right
        {0.5f, 0.5f, 0.0f},   // top right
        {-0.5f, 0.5f, 0.0f}   // top left
    };

    std::vector<glm::vec2> tex_coords = {
        {0.0f, 0.0f}, // bottom left
        {1.0f, 0.0f}, // bottom right
        {1.0f, 1.0f}, // top right
        {0.0f, 1.0f}  // top left
    };

    // clang-format off
        buf.load(
            {
                positions[0].x, positions[0].y, positions[0].z, tex_coords[0].x, tex_coords[0].y,
                positions[1].x, positions[1].y, positions[1].z, tex_coords[1].x, tex_coords[1].y,
                positions[2].x, positions[2].y, positions[2].z, tex_coords[2].x, tex_coords[2].y,
                positions[3].x, positions[3].y, positions[3].z, tex_coords[3].x, tex_coords[3].y
            },
            {3, 2});
    // clang-format on

    buf.set_EBO({0, 1, 2, 0, 2, 3});
}

void Textured_Square::draw() {
    program.use();
    tex.bind();
    buf.draw();
}

Rainbow_Square::Rainbow_Square() : program(vs, fs) {
    vs.load_from_file("../res/shaders/ndc_only/rainbow.vert");
    fs.load_from_file("../res/shaders/ndc_only/rainbow.frag");
    program.attachShaders();

    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, 0.0f}, // bottom left
        {0.5f, -0.5f, 0.0f},  // bottom right
        {0.5f, 0.5f, 0.0f},   // top right
        {-0.5f, 0.5f, 0.0f}   // top left
    };

    std::vector<glm::vec3> colors = {
        {1.0f, 0.0f, 0.0f}, // bottom left
        {0.0f, 1.0f, 0.0f}, // bottom right
        {0.0f, 0.0f, 1.0f}, // top right
        {1.0f, 1.0f, 0.0f}  // top left
    };

    // clang-format off
        buf.load(
            {
                vertices[0].x, vertices[0].y, vertices[0].z, colors[0].x, colors[0].y, colors[0].z,
                vertices[1].x, vertices[1].y, vertices[1].z, colors[1].x, colors[1].y, colors[1].z,
                vertices[2].x, vertices[2].y, vertices[2].z, colors[2].x, colors[2].y, colors[2].z,
                vertices[3].x, vertices[3].y, vertices[3].z, colors[3].x, colors[3].y, colors[3].z
            },
            {3, 3});
    // clang-format on

    buf.set_EBO({0, 1, 2, 0, 2, 3});
}

void Rainbow_Square::draw() {
    program.use();
    buf.draw();
}

std::unique_ptr<Square> SquareFactory::create() {
    switch (type) {
    case SquareType::Solid:
        return std::make_unique<Solid_Square>();
    case SquareType::Textured:
        return std::make_unique<Textured_Square>();
    case SquareType::Rainbow:
        return std::make_unique<Rainbow_Square>();
    default:
        return std::make_unique<Solid_Square>();
    }
}

} // namespace lwgle::draw_objects