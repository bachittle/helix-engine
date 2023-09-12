#include "imgui/imgui_manager.hpp"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

namespace lwgle::imgui {

ImGuiManager::ImGuiManager() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
}

void ImGuiManager::use_glfw(GLFWwindow* window) {
    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void ImGuiManager::use_opengl3(const char* glsl_version) {
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImGuiManager::new_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiManager::~ImGuiManager() {
    ImGui::DestroyContext();
}

} // namespace lwgle::imgui