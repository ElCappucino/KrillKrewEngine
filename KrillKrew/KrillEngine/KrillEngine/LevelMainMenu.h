#pragma once
#include "Level.h"
#include "LevelUtilities.h"
#include "nlohmann/json.hpp"
#include <fstream>
//using json = nlohmann::json;
class LevelMainMenu : public Level
{



private:
	std::vector<DrawableObject*> objectsList;
	std::vector<TextObject*> textList;
	std::map<std::string, SpritesheetInfo> spriteList;
	PlayerObject* players[4]; // add up to 4 players
	int playerSize = 0;

	int playerNumber = 4; // Change later
	int ready[4] = { 0 };
	

	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;

	int dt = 0;
	float time1s = 0;
	float time05s = 0;
	float previousWidth = 0, previousHeight = 0;

	struct config
	{
		int number;
		std::string text;
		float textPosX;
		float textPosY;
		int textSize;
	};

	std::vector<config> configs;

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
	void saveConfig(std::string& filename, config con);
	void loadConfig(std::string filename);
};
