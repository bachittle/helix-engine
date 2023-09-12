#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace lwgle::imgui {

class ImGuiManager {
public:
    ImGuiManager();
    ~ImGuiManager();

    void use_glfw(GLFWwindow* window);
    void use_opengl3(const char* glsl_version);

    void new_frame();
    void render();
};

} // namespace lwgle::imgui