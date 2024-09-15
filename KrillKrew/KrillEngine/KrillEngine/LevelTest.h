#pragma once
#include "Level.h"

/// @brief The class for level inherit test from P'tiam
class LevelTest : public Level
{
private:
	vector<DrawableObject*> objectsList;
	GameObject * player;

public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);
};
