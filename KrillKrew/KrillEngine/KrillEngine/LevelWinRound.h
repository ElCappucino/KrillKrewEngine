#pragma once
#include "Level.h"
#include "LevelUtilities.h"
#include "nlohmann/json.hpp"
#include <fstream>

class LevelWinRound : public Level
{
private:
	std::vector<DrawableObject*> objectsList;

	std::map<std::string, SpritesheetInfo> spriteList;

	int roundWinner;
	int playerNumber = 4;
	int roundNum;
	std::array<int, 4> playerScores;

	GLint currentViewport[4];

	UiObject* Background_UI; // pos 0, 0 no config
	UiObject* RoundNum_UI;
	UiObject* RoundWinCharacter_UI;
	UiObject* PlayerProfile_UI;
	std::array<UiObject*, 4> PlayerScore_UI;

	glm::vec3 RoundNum_pos;
	glm::vec3 RoundWinCharacter_pos;
	glm::vec3 PlayerProfile_pos;
	std::array<glm::vec3, 4> PlayerScore_pos;

	glm::vec3 Background_size = {1920, -1080, 0};
	glm::vec3 RoundNum_size = { 330, -125, 0 };
	glm::vec3 RoundWinCharacter_size = { 919, -950, 0 };
	glm::vec3 PlayerProfile_size = { 600, -150, 0 };
	glm::vec3 PlayerScore_size = { 36, -46, 0 };

	float windowWidth = SCREEN_WIDTH;
	float windowHeight = SCREEN_HEIGHT;

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

	void SaveInfo(std::string filename);
	bool LoadInfo(std::string filename);

	void SaveUIPositionConfig(std::string filename);
	bool LoadUIPositionConfig(std::string filename);
};
