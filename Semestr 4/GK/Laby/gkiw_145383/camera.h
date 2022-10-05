#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum CamDirections {
    UP, DOWN,
    FORWARD, BACKWARD,
    LEFT, RIGHT
};


class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float fov;

    float speed;
    float sensitivity;

    Camera(glm::vec3 position = glm::vec3(8.0f, 8.0f, 0.0f), 
               glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = 180.0f,
               float pitch = -45.0f,
               float fov = 45.0f,
               float speed = 5.0f,
               float sensitivity = 0.1f);
    glm::mat4 GetViewMatrix();
    glm::vec3 GetPosition();
    void ResetPosition();
    void processKeyboardInput(CamDirections dir, float deltaTime);
    void processMouseInput(float xoffset, float yoffset);

private:
    void updateCameraVectors();

};