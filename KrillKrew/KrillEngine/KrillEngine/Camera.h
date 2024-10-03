#pragma once
#include "glm.hpp"
#include "InfoStruct.h"
#include "GameEngine.h"

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_RATIO_X 1.78
#define SCREEN_RATIO_Y 1
#define CAMERA_PADDING 150
#define ZOOM_VELOCITY 0.05

class Camera 
{
private:
	glm::vec2 rightVector;
	glm::vec2 upVector;
	glm::vec2 center;

	float cameraWidth;
	float cameraHeight;

	float previousWidth = 0;
	float previousHeight = 0;

public:
	Camera();
	void LerpCamera(glm::vec3 p_1, glm::vec3 p_2, glm::vec3 p_3, glm::vec3 p_4);
	float GetCameraWidth();
	float GetCameraHeight();
	glm::vec3 ScreenToCameraPosition(glm::vec3 screenPos);
	glm::vec3 CameraToScreenPosition(glm::vec3 cameraPos);
	glm::vec3 WorldToCameraPosition(glm::vec3 screenPos);
	glm::vec3 CameraToWorldPosition(glm::vec3 cameraPos);
	OrthographicValue getCameraOrthoValue();
};