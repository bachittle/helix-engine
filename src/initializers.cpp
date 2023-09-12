#include "initializers.hpp"

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace lwgle {

GLFWwindow* glfw_init(const char * name) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize glfw");
    }

    auto window = glfwCreateWindow(640, 480, name, NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(window);

    spdlog::info("GLFW version: {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);

    return window;
}

int glad_init() {
    int glad_status = gladLoadGL(glfwGetProcAddress);
    if (!glad_status) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize glad");
    }
    spdlog::info("OpenGL version: {}.{}", GLAD_VERSION_MAJOR(glad_status),
                 GLAD_VERSION_MINOR(glad_status));

    return glad_status;
}

} // namespace lwgle