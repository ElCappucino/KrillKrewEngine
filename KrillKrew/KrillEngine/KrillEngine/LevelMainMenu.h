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
	std::vector<UiObject*> tutorialInfoList;
	std::vector<UiObject*> yesNoList;
	std::vector<UiObject*> textOptionList;
	std::vector<UiObject*> displayList;
	std::vector<UiObject*> volumeTrackList;
	std::vector<UiObject*> volumeKnobList;
	std::vector<UiObject*> volumeBoxList;
	std::map<std::string, SpritesheetInfo> spriteList;
	
	int playerNumber = 4; // Change later
	bool playerMove = false;
	int playerWhere = 1;

	bool isCredit = false;

	bool isTutorial = false;
	int InfoPage = 0;

	bool isStart = false;
	bool isExit = false;

	bool isOption = false;
	bool isSelectDisplay = false;
	bool isSelectVolume = false;
	bool isMasterVolume = false;
	bool isSFXVolume = false;
	bool isBGMVolume = false;
	bool isToggleVolume[3] = { true, true, true };
	bool isSlider = false;
	int masterVolume = 100;
	int SFXVolume = 20;
	int BGMVolume = 20;

	int configNum = 0;
	int windowWidth = SCREEN_WIDTH;
	int windowHeight = SCREEN_HEIGHT;

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
		float offSetX;
		float offSetY;
		bool playerHere = false;
		int column;
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
