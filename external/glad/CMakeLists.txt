project(glad)

add_library(${PROJECT_NAME} src/gl.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)