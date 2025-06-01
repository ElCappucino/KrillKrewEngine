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
	std::vector<UiObject*> textList;
	std::map<std::string, SpritesheetInfo> spriteList;
	
	int playerNumber = 4; // Change later
	bool playerMove[4] = { false };
	int playerWhere[4] = { 0 };
	

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
		float posX;
		float posY;
		float height;
		float width;
	};

	std::vector<config*> configs;

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
	void saveConfig(std::string& filename, config* con);
	void loadConfig(std::string filename);
};
