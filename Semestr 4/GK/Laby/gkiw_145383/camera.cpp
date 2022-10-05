#include "camera.h"


Camera::Camera(glm::vec3 position, 
               glm::vec3 front,
               glm::vec3 up,
               float yaw ,
               float pitch,
               float fov,
               float speed,
               float sensitivity){
    
    this->position = position;
    this->front = front;
    this->up = up;
    this->yaw = yaw;
    this->pitch = pitch;
    this->fov = fov;
    this->speed = speed;
    this->sensitivity = sensitivity;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position+front, up);
}

glm::vec3 Camera::GetPosition() {
    return position;
}

void Camera::ResetPosition() {
    this->position = glm::vec3(-8.0f, 8.0f, 0.0f);
}

void Camera::processKeyboardInput(CamDirections dir, float deltaTime) {
    float velocity = speed * deltaTime;

    if(dir == FORWARD) position += glm::normalize(glm::cross(up, glm::cross(front, up))) * velocity;
    if(dir == BACKWARD) position -= glm::normalize(glm::cross(up, glm::cross(front, up))) * velocity;
    if(dir == UP) position += up * velocity;
    if(dir == DOWN) position -= up * velocity;
    if(dir == LEFT) position -= glm::normalize(glm::cross(front, up)) * velocity;
    if(dir == RIGHT) position += glm::normalize(glm::cross(front, up)) * velocity;
}


void Camera::processMouseInput(float xoffset, float yoffset) {
    
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f) pitch = 89.0f;
	if(pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}


void Camera::updateCameraVectors(){
    glm::vec3 tmp_front;
    tmp_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tmp_front.y = sin(glm::radians(pitch));
    tmp_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(tmp_front);
}