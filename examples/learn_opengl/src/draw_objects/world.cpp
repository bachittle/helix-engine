#include "draw_objects/world.hpp"
#include "opengl/buffer.hpp"
#include "opengl/shader.hpp"
#include "opengl/texture.hpp"

#include <glad/gl.h>
#include <glm/gtx/string_cast.hpp>
#include <spdlog/spdlog.h>

namespace lwgle::world {

Cube::Cube() : program(vs, fs) {
    vs.load_from_file("../res/shaders/world/texture.vert");
    fs.load_from_file("../res/shaders/world/texture.frag");
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
    // clang-format on
}

void Cube::draw() {
    if (camera)
        view = camera->get_view_matrix();

    program.use();
    program.setMat4("model", model);
    program.setMat4("view", view);
    program.setMat4("projection", *projection);
    tex.bind();
    buf.draw();
}

World::World() {
    camera = std::make_shared<scene::Camera>();

    projection = std::make_shared<glm::mat4>(1.0f);
    for (int i = 0; i < 3; ++i) {
        push_cube();
    }
    update_projection_perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
                                  100.0f);

    // glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW);
}

void World::push_cube() {
    auto cube = std::make_unique<Cube>();
    cube->set_model(
        glm::translate(glm::mat4(1.0f), glm::vec3(cubes.size() * 2, 0, 0)));
    cube->add_camera(camera);
    cube->set_projection(projection);

    cubes.push_back(std::move(cube));
}

void World::pop_cube() {
    if (cubes.size() > 0)
        cubes.pop_back();
}

void World::process_input(GLFWwindow* window, float deltaTime) {
    auto res = camera->process_keyboard(window, deltaTime);
    if (res)
        camera->process_mouse(window, deltaTime);
}

void World::draw() {
    for (auto& cube : cubes)
        cube->draw();
}

} // namespace lwgle::world