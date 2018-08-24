#include "camera.h"

Camera::Camera(glm::vec3 position, float moveSpeed, float zoomSpeed)
{
	this->position = position;
	this->moveSpeed = moveSpeed;
	this->zoomSpeed = zoomSpeed;
	this->zoom = 1.0f;
	initAxis();
}

Camera::Camera(float posX, float posY, float posZ, float moveSpeed, float zoomSpeed)
{
	this->position = position;
	this->moveSpeed = moveSpeed;
	this->zoomSpeed = zoomSpeed;
	this->zoom = 1.0f;
	initAxis();
}

Camera::~Camera(){}

const glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + Z_axis, Y_axis);
}

void Camera::actMove(CameraDirection direction, float deltaTime)
{
	float velocity = moveSpeed * deltaTime;
	if (direction == DOWN)
		position -= Y_axis * velocity;
	if (direction == UP)
		position += Y_axis * velocity;
	if (direction == RIGHT)
		position += X_axis * velocity;
	if (direction == LEFT)
		position -= X_axis * velocity;
}

void Camera::actZoom(float yoffset)
{
	if (zoom >= 0.1f && zoom <= 3.0f)
		zoom -= yoffset * zoomSpeed;
	if (zoom <= 0.1f)
		zoom = 0.1f;
	if (zoom >= 3.0f)
		zoom = 3.0f;
}

void Camera::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Camera::setPosition(float x, float y, float z)
{
	this->position = glm::vec3(x, y, z);
}

void Camera::setPosX(float x)
{
	this->position.x = x;
}

void Camera::setPosY(float y)
{
	this->position.y = y;
}

void Camera::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void Camera::setZoomSpeed(float zoomSpeed)
{
	this->zoomSpeed = zoomSpeed;
}

void Camera::setZoom(float zoom)
{
	this->zoom = zoom;
}

void Camera::initAxis()
{
	this->X_axis = glm::vec3(1.0f, 0.0f, 0.0f);
	this->Y_axis = glm::vec3(0.0f, 1.0f, 0.0f);
	this->Z_axis = glm::vec3(0.0f, 0.0f, -1.0f);
}