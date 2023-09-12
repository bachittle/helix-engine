#pragma once

#include "draw_objects/simple_ortho_cube.hpp"
#include "draw_objects/square.hpp"
#include "draw_objects/triangle.hpp"
#include "draw_objects/world.hpp"

namespace lwgle {

// edit a triangle in this window
// set its type, color, etc.
void triangle_window(std::unique_ptr<draw_objects::Triangle>& triangle,
                     bool* show_triangle_window);

void square_window(std::unique_ptr<draw_objects::Square>& square,
                   bool* show_square_window);

void cube_window(std::unique_ptr<draw_objects::Simple_Ortho_Cube>& cube,
                 bool* show_cube_window);

void world_window(std::unique_ptr<world::World>& world,
                  bool* show_world_window);

} // namespace lwgle