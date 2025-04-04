#pragma once
#include "Level.h"
#include "LevelUtilities.h"

/// @brief The class for level inherit test from P'tiam
class LevelSelectAbility : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::vector<DrawableObject*> playerHoverList;
	std::vector<DrawableObject*> SkillBoxList;
	std::vector<UiObject*> playerIconList;
	std::map<int, std::vector<UiObject*>> playerIconSkillList;
	std::map<std::string, SpritesheetInfo> spriteList;
	PlayerObject* players[4]; // add up to 4 players
	int playerSize = 0;
	int playerNum = 0;
	int playerAbility[4][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};

	int playerNumber = 4; // Change later
	float uiWidth = 215.f;
	float uiHeight = 100.f;
	float posX = camera.GetCenterX() - (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH / 2.f) * (playerNumber - 1);
	float posY = camera.GetCenterY() + ((uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT) / 2.f) * (playerNumber - 1);
	bool playerMove[4] = { false };
	int playerWhere[4] = { 0 };
	int playerHoverPosX = 60;
	int playerHoverPosY = 35;
	int ready[4] = { 0 };

	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;

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
	void abilityToFile(const std::string& fileName, PlayerObject::Ability abilityId, int who);
};
