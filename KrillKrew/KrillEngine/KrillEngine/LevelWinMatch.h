#pragma once
#include "Level.h"
#include "LevelUtilities.h"
#include "nlohmann/json.hpp"
#include <fstream>

class LevelWinMatch : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	
	std::map<std::string, SpritesheetInfo> spriteList;

	int winningPlayer;

	int playerNumber = 4; // Change later

	std::array<int, 4> playerScores;

	int windowWidth = SCREEN_WIDTH;
	int windowHeight = SCREEN_HEIGHT;

	OrthographicValue targetSceneProjection;
	Camera camera;
	Timer* timer;

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
	void UpdateUI();
};
