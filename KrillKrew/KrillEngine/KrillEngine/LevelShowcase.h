#pragma once
#include "Level.h"
#include "Utilities.h"

#define MAP_WIDTH  21
#define MAP_HEIGHT 16

/// @brief The class for level inherit test from P'tiam
class LevelShowcase : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::map<std::string, SpritesheetInfo> spriteList;

	typedef std::function<void(int, PlayerObject*, std::vector<DrawableObject*>&, SpritesheetInfo)> ability;
	std::map<std::string, ability> abilities;

	PlayerObject* players[4]; // add up to 4 players

	int groundTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	int propsTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	int colliderTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };

	int playerSize = 0;
	int playerNum = 0;
	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;

	int dt = 0;
	float time[4] = { 0 };
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
	void UpdateCollision();
	void UpdateProjectile();
	void UpdateCooldown();
	void UpdateMovement();
	void UpdateUI();

	void TileImport(int TileBuffer[][MAP_WIDTH], std::string fileName);

	// void CameraLerp();
};
