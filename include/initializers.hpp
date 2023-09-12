#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace lwgle {

GLFWwindow* glfw_init(const char* name = "lwgle");
int glad_init();

} // namespace lwgle