#pragma once
#include "Level.h"
#include "InfoStruct.h"
#include "PlayerObject.h"
#include "Joystick.h"

/// @brief The class for level inherit test from P'tiam
class LevelGameplay : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	DrawableObject* player[4]; // add up to 4 players
	int playerNum = 0;
	CameraZoomInfo zoomInfo; // to initialize the zoom property
	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;

	float dt = 0;

	float previousWidth = 0, previousHeight = 0;

public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);

	// void CameraLerp();
};
