#pragma once
#include "../utilities/mathmanager.h"

#include <vector>


enum class CameraDirection {
	DOWN,
	UP,
	RIGHT,
	LEFT
};

class Camera
{
private:

	glm::vec3 position;

	glm::vec3 X_axis;
	glm::vec3 Y_axis;
	glm::vec3 Z_axis;

	float moveSpeed;
	float zoom;
	float zoomSpeed;

public:

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float moveSpeed = 2.0f, float zoomSpeed = 0.05f);
	Camera(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float moveSpeed = 2.0f, float zoomSpeed = 0.05f);
	~Camera();

	const glm::mat4 getViewMatrix() const;

	void actionMove(CameraDirection direction, float deltaTime);
	void actionZoom(float yoffset);

	void setPosition(glm::vec3 position);
	void setPosition(float x, float y, float z = 0.0f);
	void setPosX(float x);
	void setPosY(float y);
	void setMoveSpeed(float moveSpeed);
	void setZoomSpeed(float zoomSpeed);
	void setZoom(float zoom);

	const float getPosX() const { return this->position.x; }
	const float getPosY() const { return this->position.y; }
	const float getZoom() const { return this->zoom; }

private:
	void initAxis();
};