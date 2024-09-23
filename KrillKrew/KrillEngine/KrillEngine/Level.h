#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "ImageObject.h"

#define SCREEN_RATIO_X 1.78
#define SCREEN_RATIO_Y 1
#define ZOOM_VELOCITY 0.2
/// @brief The class for setup object in the level
/// @brief It intent to inherit this class for creating any new unique scene.
class Level
{
private:
	vector<DrawableObject*> objectsList;
	vector<DrawableObject*> UIsList;
	ImageObject * player;

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
};
