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
	std::vector<float> posX;
	std::vector<float> posY;
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
