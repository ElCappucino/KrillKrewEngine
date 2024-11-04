#include "Camera.h"

Camera::Camera() 
{

}
void Camera::LerpCamera(glm::vec3 p_1, glm::vec3 p_2, glm::vec3 p_3, glm::vec3 p_4)
{
	glm::vec3 playerPos[4] = { p_1, p_2, p_3, p_4 };
	float current_top = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top;
	float current_bottom = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom;
	float current_left = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left;
	float current_right = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right;

	float currentWidth = current_right - current_left;
	float currentHeight = current_top - current_bottom;

	float currentRatio = std::round((currentWidth / currentHeight) * 100.f) / 100.f;

	float maxLeft = 0;
	float maxRight = 0;
	float maxTop = 0;
	float maxBottom = 0;

	for (int i = 0; i < 4; i++) {

		if (playerPos[i].x > maxRight) {

			maxRight = playerPos[i].x;
		}

		if (playerPos[i].x < maxLeft) {

			maxLeft = playerPos[i].x;

		}

		if (playerPos[i].y > maxTop) {

			maxTop = playerPos[i].y;

		}

		if (playerPos[i].y < maxBottom) {

			maxBottom = playerPos[i].y;

		}
	}

	float newWidth = maxRight - maxLeft;
	float newHeight = maxTop - maxBottom;

	if (newWidth == previousWidth && newHeight == previousHeight) {
		return;
	}
	else {
		float newRatio = std::round(newWidth / newHeight * 100.f) / 100.f;
		//std::cout << newRatio << std::endl;
		if (newRatio > SCREEN_RATIO_X)
		{
			current_left = maxLeft;
			current_right = maxRight;
			current_top = maxTop + (((newWidth / SCREEN_RATIO_X) - newHeight) / 2.f);
			current_bottom = maxBottom - (((newWidth / SCREEN_RATIO_X) - newHeight) / 2.f);

			previousWidth = newWidth;
			previousHeight = newHeight;

			// add padding
			current_left -= CAMERA_PADDING * SCREEN_RATIO_X;
			current_right += CAMERA_PADDING * SCREEN_RATIO_X;
			current_top += CAMERA_PADDING * SCREEN_RATIO_Y;
			current_bottom -= CAMERA_PADDING * SCREEN_RATIO_Y;

			GameEngine::GetInstance()->SetDrawArea(current_left, current_right, current_bottom, current_top);
		}
		else if (newRatio < SCREEN_RATIO_X)
		{
			current_top = maxTop;
			current_bottom = maxBottom;
			current_left = maxLeft - (((newHeight * SCREEN_RATIO_X) - newWidth) / 2.f);
			current_right = maxRight + (((newHeight * SCREEN_RATIO_X) - newWidth) / 2.f);

			previousWidth = newWidth;
			previousHeight = newHeight;

			// add padding
			current_left -= CAMERA_PADDING * SCREEN_RATIO_X;
			current_right += CAMERA_PADDING * SCREEN_RATIO_X;
			current_top += CAMERA_PADDING * SCREEN_RATIO_Y;
			current_bottom -= CAMERA_PADDING * SCREEN_RATIO_Y;

			GameEngine::GetInstance()->SetDrawArea(current_left, current_right, current_bottom, current_top);
		}
	}
}
float Camera::GetCameraWidth() 
{
	return GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right - 
		   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left;
}
float Camera::GetCameraHeight() 
{
	return GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top -
		   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom;
}
glm::vec3 Camera::ScreenToCameraPosition(glm::vec3 screenPos)
{
	float posX = ((cameraWidth / (float)GameEngine::GetInstance()->GetWindowWidth()) * screenPos.x) - (cameraWidth / 2.f);
	float posY = -1 * ((cameraHeight / (float)GameEngine::GetInstance()->GetWindowHeight()) * screenPos.y) - (cameraHeight / 2.f);
	return glm::vec3(posX, posY, 0);
}
glm::vec3 Camera::CameraToScreenPosition(glm::vec3 cameraPos)
{
	return glm::vec3(0, 0, 0);
}
glm::vec3 Camera::WorldToCameraPosition(glm::vec3 worldPos)
{
	return glm::vec3(0, 0, 0);
}
glm::vec3 Camera::CameraToWorldPosition(glm::vec3 cameraPos)
{
	return glm::vec3(0, 0, 0);
}
OrthographicValue Camera::getCameraOrthoValue()
{
	return GameEngine::GetInstance()->GetRenderer()->GetOrthovalue();
}