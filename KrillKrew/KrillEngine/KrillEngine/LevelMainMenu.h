#pragma once
#include "Level.h"
#include "LevelUtilities.h"
class LevelMainMenu : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::map<std::string, SpritesheetInfo> spriteList;
	PlayerObject* players[4]; // add up to 4 players
	int playerSize = 0;

	int playerNumber = 4; // Change later
	float uiWidth = 215.f;
	float uiHeight = 100.f;
	float posX = camera.GetCenterX() - (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH / 2.f) * (playerNumber - 1);
	float posY = camera.GetCenterY() + ((uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT) / 2.f) * (playerNumber - 1);
	int ready[4] = { 0 };

	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;

	int dt = 0;
	float time1s = 0;
	float time05s = 0;
	float previousWidth = 0, previousHeight = 0;

public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();
	virtual void Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);

	void UpdateInput();
	void UpdateUi();
};
