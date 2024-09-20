#pragma once
#include "Level.h"
#include "InfoStruct.h"

/// @brief The class for level inherit test from P'tiam
class LevelGameplay : public Level
{
private:
	vector<DrawableObject*> objectsList;
	GameObject* player[4]; // add up to 4 players
	CameraZoomInfo zoomInfo;
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

	void CameraLerp();
};
