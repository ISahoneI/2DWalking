#pragma once
#include "../utilities/mathmanager.h"
#include "../utilities/global.h"

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

	//Position ecran
	glm::vec3 position;

	//Position sur la map
	glm::vec2 positionRef;

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
	const glm::mat4 getProjectionMatrix() const;

	void actionMove(CameraDirection direction, float deltaTime);
	void actionZoom(float yoffset);
	void centerOn(float x, float y);

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

	const float getPosRefX() const { return this->positionRef.x; }
	const float getPosRefY() const { return this->positionRef.y; }

	const float getBordXmin() const;
	const float getBordXmax() const;
	const float getBordYmin() const;
	const float getBordYmax() const;

private:
	void initAxis();

	void setPositionRef(glm::vec2 positionRef);
};