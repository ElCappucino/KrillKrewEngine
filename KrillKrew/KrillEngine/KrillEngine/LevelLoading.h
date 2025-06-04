#pragma once
#include "Level.h"
#include "LevelUtilities.h"

/// @brief The class for setup object in the level
/// @brief It intent to inherit this class for creating any new unique scene.
class LevelLoading : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::vector<DrawableObject*> UIsList;
	std::map<std::string, SpritesheetInfo> spriteList;
	ImageObject* player;
	Camera camera;

	int windowWidth;
	int windowHeight;

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
