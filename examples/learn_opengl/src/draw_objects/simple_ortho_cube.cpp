#include "draw_objects/simple_ortho_cube.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lwgle::draw_objects {

Solid_Simple_Ortho_Cube::Solid_Simple_Ortho_Cube() : program(vs, fs) {
    vs.load_from_file("../res/shaders/model/solid.vert");
    fs.load_from_file("../res/shaders/model/solid.frag");
    program.attachShaders();

    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, -0.5f}, // bottom left
        {0.5f, -0.5f, -0.5f},  // bottom right
        {0.5f, 0.5f, -0.5f},   // top right
        {-0.5f, 0.5f, -0.5f},  // top left

        {-0.5f, -0.5f, 0.5f}, // bottom left
        {0.5f, -0.5f, 0.5f},  // bottom right
        {0.5f, 0.5f, 0.5f},   // top right
        {-0.5f, 0.5f, 0.5f}   // top left
    };

    // clang-format off
    buf.load(
        {
            vertices[0].x, vertices[0].y, vertices[0].z,
            vertices[1].x, vertices[1].y, vertices[1].z,
            vertices[2].x, vertices[2].y, vertices[2].z,
            vertices[3].x, vertices[3].y, vertices[3].z,
            vertices[4].x, vertices[4].y, vertices[4].z,
            vertices[5].x, vertices[5].y, vertices[5].z,
            vertices[6].x, vertices[6].y, vertices[6].z,
            vertices[7].x, vertices[7].y, vertices[7].z
        },
        {3});
    
        buf.set_EBO({
            0, 1, 2, 0, 2, 3,   // front
            7, 6, 5, 5, 4, 7,   // back
            3, 2, 6, 6, 7, 3,   // top
            4, 5, 1, 1, 0, 4,   // bottom
            4, 0, 3, 3, 7, 4,   // left
            1, 5, 6, 6, 2, 1    // right
        });
    // clang-format on
}

void Solid_Simple_Ortho_Cube::draw() {
    program.use();
    float time = glfwGetTime();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));
    program.setMat4("model", model);
    buf.draw();
}

Textured_Simple_Ortho_Cube::Textured_Simple_Ortho_Cube() : program(vs, fs) {
    vs.load_from_file("../res/shaders/model/texture.vert");
    fs.load_from_file("../res/shaders/model/texture.frag");
    program.attachShaders();

    tex.load_from_file("../res/textures/container.jpg");

    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, -0.5f}, // bottom left
        {0.5f, -0.5f, -0.5f},  // bottom right
        {0.5f, 0.5f, -0.5f},   // top right
        {-0.5f, 0.5f, -0.5f},  // top left

        {-0.5f, -0.5f, 0.5f}, // bottom left
        {0.5f, -0.5f, 0.5f},  // bottom right
        {0.5f, 0.5f, 0.5f},   // top right
        {-0.5f, 0.5f, 0.5f}   // top left
    };

    std::vector<glm::vec2> tex_coords = {
        {0.0f, 0.0f}, // bottom left
        {1.0f, 0.0f}, // bottom right
        {1.0f, 1.0f}, // top right
        {0.0f, 1.0f}, // top left

        {0.0f, 0.0f}, // bottom left
        {1.0f, 0.0f}, // bottom right
        {1.0f, 1.0f}, // top right
        {0.0f, 1.0f}  // top left
    };

    // clang-format off

    // i need these vertices to have different TexCoords depending on the face side
    // so no EBO allowed here unfortunately
    buf.load(
        {
            // front
            vertices[0].x, vertices[0].y, vertices[0].z, tex_coords[0].x, tex_coords[0].y,
            vertices[1].x, vertices[1].y, vertices[1].z, tex_coords[1].x, tex_coords[1].y,
            vertices[2].x, vertices[2].y, vertices[2].z, tex_coords[2].x, tex_coords[2].y,
            vertices[2].x, vertices[2].y, vertices[2].z, tex_coords[2].x, tex_coords[2].y,
            vertices[3].x, vertices[3].y, vertices[3].z, tex_coords[3].x, tex_coords[3].y,
            vertices[0].x, vertices[0].y, vertices[0].z, tex_coords[0].x, tex_coords[0].y,

            // right
            vertices[1].x, vertices[1].y, vertices[1].z, tex_coords[0].x, tex_coords[0].y,
            vertices[5].x, vertices[5].y, vertices[5].z, tex_coords[1].x, tex_coords[1].y,
            vertices[6].x, vertices[6].y, vertices[6].z, tex_coords[2].x, tex_coords[2].y,
            vertices[6].x, vertices[6].y, vertices[6].z, tex_coords[2].x, tex_coords[2].y,
            vertices[2].x, vertices[2].y, vertices[2].z, tex_coords[3].x, tex_coords[3].y,
            vertices[1].x, vertices[1].y, vertices[1].z, tex_coords[0].x, tex_coords[0].y,

            // back
            vertices[7].x, vertices[7].y, vertices[7].z, tex_coords[0].x, tex_coords[0].y,
            vertices[6].x, vertices[6].y, vertices[6].z, tex_coords[1].x, tex_coords[1].y,
            vertices[5].x, vertices[5].y, vertices[5].z, tex_coords[2].x, tex_coords[2].y,
            vertices[5].x, vertices[5].y, vertices[5].z, tex_coords[2].x, tex_coords[2].y,
            vertices[4].x, vertices[4].y, vertices[4].z, tex_coords[3].x, tex_coords[3].y,
            vertices[7].x, vertices[7].y, vertices[7].z, tex_coords[0].x, tex_coords[0].y,

            // left
            vertices[4].x, vertices[4].y, vertices[4].z, tex_coords[0].x, tex_coords[0].y,
            vertices[0].x, vertices[0].y, vertices[0].z, tex_coords[1].x, tex_coords[1].y,
            vertices[3].x, vertices[3].y, vertices[3].z, tex_coords[2].x, tex_coords[2].y,
            vertices[3].x, vertices[3].y, vertices[3].z, tex_coords[2].x, tex_coords[2].y,
            vertices[7].x, vertices[7].y, vertices[7].z, tex_coords[3].x, tex_coords[3].y,
            vertices[4].x, vertices[4].y, vertices[4].z, tex_coords[0].x, tex_coords[0].y,

            // bottom
            vertices[4].x, vertices[4].y, vertices[4].z, tex_coords[0].x, tex_coords[0].y,
            vertices[5].x, vertices[5].y, vertices[5].z, tex_coords[1].x, tex_coords[1].y,
            vertices[1].x, vertices[1].y, vertices[1].z, tex_coords[2].x, tex_coords[2].y,
            vertices[1].x, vertices[1].y, vertices[1].z, tex_coords[2].x, tex_coords[2].y,
            vertices[0].x, vertices[0].y, vertices[0].z, tex_coords[3].x, tex_coords[3].y,
            vertices[4].x, vertices[4].y, vertices[4].z, tex_coords[0].x, tex_coords[0].y,

            // top
            vertices[3].x, vertices[3].y, vertices[3].z, tex_coords[0].x, tex_coords[0].y,
            vertices[2].x, vertices[2].y, vertices[2].z, tex_coords[1].x, tex_coords[1].y,
            vertices[6].x, vertices[6].y, vertices[6].z, tex_coords[2].x, tex_coords[2].y,
            vertices[6].x, vertices[6].y, vertices[6].z, tex_coords[2].x, tex_coords[2].y,
            vertices[7].x, vertices[7].y, vertices[7].z, tex_coords[3].x, tex_coords[3].y,
            vertices[3].x, vertices[3].y, vertices[3].z, tex_coords[0].x, tex_coords[0].y,

        },
        {3, 2});
}

void Textured_Simple_Ortho_Cube::draw() {
    program.use();
    float time = glfwGetTime();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));
    program.setMat4("model", model);
    tex.bind();
    buf.draw();
}

Rainbow_Simple_Ortho_Cube::Rainbow_Simple_Ortho_Cube() : program(vs, fs) {
    vs.load_from_file("../res/shaders/model/rainbow.vert");
    fs.load_from_file("../res/shaders/model/rainbow.frag");
    program.attachShaders();

    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, -0.5f}, // bottom left
        {0.5f, -0.5f, -0.5f},  // bottom right
        {0.5f, 0.5f, -0.5f},   // top right
        {-0.5f, 0.5f, -0.5f},  // top left

        {-0.5f, -0.5f, 0.5f}, // bottom left
        {0.5f, -0.5f, 0.5f},  // bottom right
        {0.5f, 0.5f, 0.5f},   // top right
        {-0.5f, 0.5f, 0.5f}   // top left
    };

    std::vector<glm::vec3> colors = {
        {1.0f, 0.0f, 0.0f}, // bottom left
        {0.0f, 1.0f, 0.0f}, // bottom right
        {0.0f, 0.0f, 1.0f}, // top right
        {1.0f, 1.0f, 0.0f}, // top left

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
            vertices[3].x, vertices[3].y, vertices[3].z, colors[3].x, colors[3].y, colors[3].z,
            vertices[4].x, vertices[4].y, vertices[4].z, colors[4].x, colors[4].y, colors[4].z,
            vertices[5].x, vertices[5].y, vertices[5].z, colors[5].x, colors[5].y, colors[5].z,
            vertices[6].x, vertices[6].y, vertices[6].z, colors[6].x, colors[6].y, colors[6].z,
            vertices[7].x, vertices[7].y, vertices[7].z, colors[7].x, colors[7].y, colors[7].z
        },
        {3, 3});

    buf.set_EBO({
        0, 1, 2, 0, 2, 3,   // front
        7, 6, 5, 5, 4, 7,   // back
        3, 2, 6, 6, 7, 3,   // top
        4, 5, 1, 1, 0, 4,   // bottom
        4, 0, 3, 3, 7, 4,   // left
        1, 5, 6, 6, 2, 1    // right
    });
    // clang-format on
}

void Rainbow_Simple_Ortho_Cube::draw() {
    program.use();
    float time = glfwGetTime();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));
    program.setMat4("model", model);
    buf.draw();
}

std::unique_ptr<Simple_Ortho_Cube> CubeFactory::create() {
    switch (type) {
    case CubeType::Solid:
        return std::make_unique<Solid_Simple_Ortho_Cube>();
    case CubeType::Textured:
        return std::make_unique<Textured_Simple_Ortho_Cube>();
    case CubeType::Rainbow:
        return std::make_unique<Rainbow_Simple_Ortho_Cube>();
    }
}

} // namespace lwgle::draw_objects