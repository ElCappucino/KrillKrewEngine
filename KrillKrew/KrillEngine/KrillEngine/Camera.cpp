#include "Camera.h"

Camera::Camera() 
{

}
void Camera::LerpCamera() 
{

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