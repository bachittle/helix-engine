project(lwgle_learn_opengl)

add_executable(${PROJECT_NAME} 
    src/draw_objects/triangle.cpp
    src/draw_objects/square.cpp
    src/draw_objects/simple_ortho_cube.cpp
    src/draw_objects/world.cpp

    src/imgui_windows.cpp
    src/main.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} lwgle)