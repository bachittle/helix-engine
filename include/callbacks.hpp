#pragma once

#define GLFW_INCLUDE_NONE
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

namespace callbacks {
void error_callback(int error, const char* description) {
    spdlog::error("GLFW error {}: {}", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    spdlog::trace("GLFW window resized to {}x{}", width, height);
}

void set_callbacks(GLFWwindow* window) {
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

} // namespace callbacks
