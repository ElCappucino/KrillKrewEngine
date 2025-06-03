#pragma once
#include "Level.h"
#include "LevelUtilities.h"
#include "nlohmann/json.hpp"
#include <fstream>

/// @brief The class for level inherit test from P'tiam
class LevelSelectAbility : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::vector<ImageObject*> playerWindowList;
	std::vector<UiObject*> AbilityIconListTop;
	std::vector<UiObject*> AbilityIconListDown;
	std::vector<UiObject*> playerHoverList;
	std::vector<UiObject*> playerIconSmallList;
	std::vector<UiObject*> playerIconList;
	std::vector<UiObject*> playerRemainList;

	std::map<int, std::vector<UiObject*>*> playerAbilityList;
	std::map<std::string, SpritesheetInfo> spriteList;
	
	int playerSize = 0;
	int playerAbility[4][3] = {{8, 8, 8}, {8, 8, 8}, {8, 8, 8}, {8, 8, 8}};
	int character[4] = {-1};
	int playerHoverWhere[4] = { 0 };
	bool playerMove[4] = { false };
	int playerNumber = 4; // Change later
	bool ready[4] = { 0 };
	int helpHover = 0;

	int axisX = 0;
	int axisY = 0;
	int axisXplayerIconSmall = 0;
	int axisYplayerIconSmall = 0;
	int axisXplayerIcon = 0;
	int axisYplayerIcon = 0;
	int axisXAbilityIconSmall = 0;
	int axisYAbilityIconSmall = 0;

	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;
	int windowWidth;
	int windowHeight;

	int dt = 0;
	float time1s = 0;
	float time05s = 0;
	float previousWidth = 0, previousHeight = 0;
	int clicked[4] = { 0, 0, 0, 0 };
	std::ofstream abilityFile;

	// player
	float axisXOld;
	float axisYOld;
	float norAxisXOld;
	float norAxisYOld;
	bool isPositiveXOld;
	bool isPositiveYOld;

	struct config
	{
		int number;
		float posX;
		float posY;
		float offSetX;
		float offSetY;
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
	void abilityToFile(const std::string& fileName, int who);

	//Config
	void saveConfig(std::string& filename, config* con);
	void loadConfig(std::string filename);
};
