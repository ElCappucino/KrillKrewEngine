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

	int matchWinner = 0;
	
	bool isHold = false;
	float holdTime = 0.0f;

	std::array<int, 4> playerScores = {0};

	GLint currentViewport[4];

	UiObject* Background_UI; // pos 0, 0 no config
	UiObject* PlayerNum_UI;

	glm::vec3 PlayerNum_pos = {0, 0, 0};

	glm::vec3 Background_size = { 1920, -1080, 0 };
	glm::vec3 PlayerNum_size = { 820, -175, 0 };

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

	bool LoadWinnerInfo(const std::string filename);

	void SaveUIPositionConfig(std::string filename);
	bool LoadUIPositionConfig(std::string filename);
};
