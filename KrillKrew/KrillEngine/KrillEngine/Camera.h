#pragma once
#include "glm.hpp"
#include "InfoStruct.h"
#include "GameEngine.h"

using namespace std;

class Camera 
{
private:
	glm::vec2 rightVector;
	glm::vec2 upVector;
	glm::vec2 center;

	float cameraWidth;
	float cameraHeight;

public:
	Camera();
	void LerpCamera();
	float GetCameraWidth();
	float GetCameraHeight();
	glm::vec3 ScreenToCameraPosition(glm::vec3 screenPos);
	glm::vec3 CameraToScreenPosition(glm::vec3 cameraPos);
	glm::vec3 WorldToCameraPosition(glm::vec3 screenPos);
	glm::vec3 CameraToWorldPosition(glm::vec3 cameraPos);
	OrthographicValue getCameraOrthoValue();
};