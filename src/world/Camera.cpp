#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspect, float near, float far) {
	this->fov = fov;
	this->aspect = aspect;
	this->nearClip = near;
	this->farClip = far;
}

glm::mat4 Camera::ProjectionMatrix() {
	return glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
}

glm::mat4 Camera::ViewMatrix() {
	return glm::lookAt(transform.position, transform.position + transform.Forward(), glm::vec3(0, 1, 0));
}

void Camera::Resize(float aspect) {
	this->aspect = aspect;
}