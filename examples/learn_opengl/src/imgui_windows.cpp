#include "imgui_windows.hpp"
#include "draw_objects/simple_ortho_cube.hpp"
#include "draw_objects/square.hpp"
#include "draw_objects/triangle.hpp"
#include "draw_objects/world.hpp"

#include <imgui.h>

#include <glad/gl.h>

namespace lwgle {

void triangle_window(std::unique_ptr<draw_objects::Triangle>& triangle,
                     bool* show_triangle_window) {
    if (ImGui::Begin("Triangle", show_triangle_window)) {
        static draw_objects::TriangleType type =
            draw_objects::TriangleType::Textured;
        static std::string type_str = "Textured";
        if (ImGui::BeginCombo("Type", type_str.c_str())) {
            if (ImGui::Selectable("Solid")) {
                type = draw_objects::TriangleType::Solid;
                triangle = draw_objects::TriangleFactory(type).create();
                type_str = "Solid";
            }
            if (ImGui::Selectable("Textured")) {
                type = draw_objects::TriangleType::Textured;
                triangle = draw_objects::TriangleFactory(type).create();

                type_str = "Textured";
            }
            if (ImGui::Selectable("Rainbow")) {
                type = draw_objects::TriangleType::Rainbow;
                triangle = draw_objects::TriangleFactory(type).create();
                type_str = "Rainbow";
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Toggle Triangle")) {
            if (triangle != nullptr) {
                triangle = nullptr;
            } else {
                triangle = draw_objects::TriangleFactory(type).create();
            }
        }
    }
    ImGui::End();
}

void square_window(std::unique_ptr<draw_objects::Square>& square,
                   bool* show_square_window) {
    if (ImGui::Begin("Square", show_square_window)) {
        static draw_objects::SquareType type = draw_objects::SquareType::Solid;
        static std::string type_str = "Solid";
        if (ImGui::BeginCombo("Type", type_str.c_str())) {
            if (ImGui::Selectable("Solid")) {
                type = draw_objects::SquareType::Solid;
                square = draw_objects::SquareFactory(type).create();
                type_str = "Solid";
            }
            if (ImGui::Selectable("Textured")) {
                type = draw_objects::SquareType::Textured;
                square = draw_objects::SquareFactory(type).create();

                type_str = "Textured";
            }
            if (ImGui::Selectable("Rainbow")) {
                type = draw_objects::SquareType::Rainbow;
                square = draw_objects::SquareFactory(type).create();
                type_str = "Rainbow";
            }

            ImGui::EndCombo();
        }

        if (ImGui::Button("Toggle Square")) {
            if (square != nullptr) {
                square = nullptr;
            } else {
                square = draw_objects::SquareFactory(type).create();
            }
        }
    }
    ImGui::End();
}

void cube_window(std::unique_ptr<draw_objects::Simple_Ortho_Cube>& cube,
                 bool* show_cube_window) {
    if (ImGui::Begin("Cube", show_cube_window)) {
        static draw_objects::CubeType type = draw_objects::CubeType::Solid;
        static std::string type_str = "Solid";
        if (ImGui::BeginCombo("Type", type_str.c_str())) {
            if (ImGui::Selectable("Solid")) {
                type = draw_objects::CubeType::Solid;
                cube = draw_objects::CubeFactory(type).create();
                type_str = "Solid";
            }
            if (ImGui::Selectable("Textured")) {
                type = draw_objects::CubeType::Textured;
                cube = draw_objects::CubeFactory(type).create();

                type_str = "Textured";
            }
            if (ImGui::Selectable("Rainbow")) {
                type = draw_objects::CubeType::Rainbow;
                cube = draw_objects::CubeFactory(type).create();
                type_str = "Rainbow";
            }

            ImGui::EndCombo();
        }

        if (ImGui::Button("Toggle Cube")) {
            if (cube != nullptr) {
                cube = nullptr;
            } else {
                cube = draw_objects::CubeFactory(type).create();
            }
        }
    }
    ImGui::End();
}

void world_window(std::unique_ptr<world::World>& world,
                  bool* show_world_window) {
    if (ImGui::Begin("World", show_world_window)) {
        static bool show_wireframe = false;

        if (ImGui::Checkbox("Wireframe", &show_wireframe)) {
            glPolygonMode(GL_FRONT_AND_BACK,
                          show_wireframe ? GL_LINE : GL_FILL);
        }

        if (ImGui::Button("Push Cube"))
            world->push_cube();
        if (ImGui::Button("Pop Cube"))
            world->pop_cube();

        if (ImGui::CollapsingHeader("Perspective")) {
            static float fovy = 45.0f;
            static float near = 0.1f;
            static float far = 100.0f;

            auto update = [&]() {
                world->update_projection_perspective(
                    glm::radians(fovy), 800.0f / 600.0f, near, far);
            };

            if (ImGui::SliderFloat("fovy", &fovy, 0.0f, 180.0f)) {
                update();
            }
            if (ImGui::SliderFloat("near", &near, 0.0f, 10.0f)) {
                update();
            }
            if (ImGui::SliderFloat("far", &far, 0.0f, 1000.0f)) {
                update();
            }
        }
    }
    ImGui::End();
}

} // namespace lwgle