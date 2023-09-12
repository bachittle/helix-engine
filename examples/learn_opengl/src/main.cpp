#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <imgui.h>

#include "draw_objects/simple_ortho_cube.hpp"
#include "draw_objects/square.hpp"
#include "draw_objects/triangle.hpp"
#include "draw_objects/world.hpp"

#include "imgui/imgui_manager.hpp"

#include "callbacks.hpp"
#include "imgui_windows.hpp"
#include "initializers.hpp"

#include <spdlog/spdlog.h>

using namespace lwgle;

void glfw_main() {
    spdlog::set_level(spdlog::level::trace);
    auto window = glfw_init();
    glad_init();

    glEnable(GL_DEPTH_TEST);

    imgui::ImGuiManager imgui_manager;
    imgui_manager.use_glfw(window);
    imgui_manager.use_opengl3("#version 460");

    callbacks::set_callbacks(window);

    std::unique_ptr<draw_objects::Triangle> triangle;
    std::unique_ptr<draw_objects::Square> square;
    std::unique_ptr<draw_objects::Simple_Ortho_Cube> cube;
    std::unique_ptr<world::World> world = std::make_unique<world::World>();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        imgui_manager.new_frame();

        static bool show_demo_window = false;
        static bool show_triangle_window = false;
        static bool show_square_window = false;
        static bool show_cube_window = false;
        static bool show_world_window = true;

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        if (show_triangle_window)
            triangle_window(triangle, &show_triangle_window);

        if (show_square_window)
            square_window(square, &show_square_window);

        if (show_cube_window)
            cube_window(cube, &show_cube_window);

        if (show_world_window)
            world_window(world, &show_world_window);

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Windows")) {
                ImGui::MenuItem("Demo Window", NULL, &show_demo_window);
                ImGui::MenuItem("Triangle Window", NULL, &show_triangle_window);
                ImGui::MenuItem("Square Window", NULL, &show_square_window);
                ImGui::MenuItem("Cube Window", NULL, &show_cube_window);
                ImGui::MenuItem("World Window", NULL, &show_world_window);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        if (world) {
            world->process_input(window, deltaTime);
            world->draw();
        }

        if (square)
            square->draw();

        if (triangle)
            triangle->draw();

        if (cube)
            cube->draw();

        imgui_manager.render();

        // swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

int main() {
    spdlog::info("START APPLICATION");
    try {
        glfw_main();
    } catch (std::exception& e) {
        spdlog::error("EXCEPTION: {}", e.what());
        return -1;
    }
    spdlog::info("END APPLICATION");

    return 0;
}