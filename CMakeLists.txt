cmake_minimum_required(VERSION 3.10.0)

project(lwgle)

# this has to be included for conan 1.0
# TODO: make optional in case user is using conan 2.0
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(glm REQUIRED)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    option(LWGLE_BUILD_EXAMPLES "Build examples" ON)
else()
    option(LWGLE_BUILD_EXAMPLES "Build examples" OFF)
endif()

add_subdirectory(external/glad)
add_subdirectory(external/imgui)
add_subdirectory(external/stb)

add_library(${PROJECT_NAME} 
    src/initializers.cpp

    src/opengl/shader.cpp
    src/opengl/buffer.cpp
    src/opengl/texture.cpp
    
    src/imgui/imgui_manager.cpp
    
    src/scene/camera.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} 
    glad
    imgui
    stb

    glfw
    spdlog::spdlog
    glm::glm
)
target_compile_definitions(${PROJECT_NAME} PUBLIC LWGLE_RES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/res/")

if (LWGLE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()