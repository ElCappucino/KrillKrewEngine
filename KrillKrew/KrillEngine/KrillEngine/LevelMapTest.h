#pragma once
#include "Level.h"
#include "LevelUtilities.h"

#define MAP_WIDTH  21
#define MAP_HEIGHT 15

/// @brief The class for level inherit test from P'tiam
class LevelMapTest : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::map<std::string, SpritesheetInfo> spriteList;
	DrawableObject* player[4]; // add up to 4 players

	int groundTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	int propsTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	int colliderTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };

	Camera camera;
	
	// struct SheetPosition { int row, column; };

	float dt = 0;
	
public:

	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);
	virtual void Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY);

	void CameraLerp();
	void TileImport(int TileBuffer[][MAP_WIDTH], std::string fileName);
};
