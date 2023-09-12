#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "opengl/buffer.hpp"
#include "opengl/shader.hpp"
#include "opengl/texture.hpp"
#include "scene/camera.hpp"

using namespace lwgle;

namespace lwgle::world {

class Cube {
public:
    Cube();
    void draw();

    void add_camera(std::shared_ptr<scene::Camera> _camera) {
        camera = _camera;
    }

    void set_model(glm::mat4 _model) {
        model = _model;
    }

    void set_projection(std::shared_ptr<glm::mat4> _projection) {
        projection = _projection;
    }

private:
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    std::shared_ptr<glm::mat4> projection;

    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;
    texture::Texture tex;

    buffer::Buffer buf;

    std::shared_ptr<scene::Camera> camera;
};

class World {
public:
    World();
    void process_input(GLFWwindow* window, float deltaTime);
    void draw();

    void push_cube();
    void pop_cube();

    void update_projection_perspective(float fovy, float aspect, float near,
                                       float far) {
        if (!projection)
            throw std::runtime_error("projection is not initialized");
        *projection = glm::perspective(fovy, aspect, near, far);
    }

    void update_projection_ortho(float left, float right, float bottom,
                                 float top, float near, float far) {
        if (!projection)
            throw std::runtime_error("projection is not initialized");
        *projection = glm::ortho(left, right, bottom, top, near, far);
    }

private:
    std::shared_ptr<scene::Camera> camera;

    std::vector<std::unique_ptr<Cube>> cubes;

    std::shared_ptr<glm::mat4> projection;
};

} // namespace lwgle::world