#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lwgle::scene {

class Camera {
public:
    Camera::Camera()
        : position(glm::vec3(0.0f, 0.0f, -3.0f)),
          front(glm::vec3(0.0f, 0.0f, 3.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {}

    glm::mat4 get_view_matrix() {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 get_projection_matrix() {
        return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
                                1000.0f);
    }

    bool process_keyboard(GLFWwindow* window, float deltaTime);
    void process_mouse(GLFWwindow* window, float deltaTime);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float yaw = 90.0f;
    float pitch = 0.0f;
};

} // namespace lwgle::scene