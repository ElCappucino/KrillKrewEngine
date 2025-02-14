#pragma once
#include "Level.h"
#include "InfoStruct.h"
#include "EntityObject.h"
#include "PlayerObject.h"
#include "ProjectileObject.h"
#include "TrapObject.h"
#include "GizmosObject.h"
#include "TrapObject.h"
#include <map>
#include "Timer.h"
#include "UiObject.h"
#include "Ability.h"



/// @brief The class for level inherit test from P'tiam
class LevelGameplay : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::map<std::string, SpritesheetInfo> spriteList;
	PlayerObject* players[4]; // add up to 4 players
	int playerSize = 0;
	int playerNum = 0;
	CameraZoomInfo zoomInfo; // to initialize the zoom property
	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;

	int dt = 0;
	float time1s = 0;
	float time05s = 0;
	float previousWidth = 0, previousHeight = 0;

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
	void UpdateCollision();
	void UpdateProjectile();
	void UpdateCooldown();
	void UpdateMovement();
	void UpdateUI();
	void UpdateKnockback(DrawableObject* obj1, DrawableObject* obj2);
	void UpdateTime();
	
	// void CameraLerp();
	

	//ability function
	void usingAbility(int numberPlayer, int numberAbility);
	void aimFireball(int num, int numAbility);
	void shootFireball(int num, int numAbility);
	void trap(int num, int numAbility);
	void dash(int num, int numAbility);
	void TNT(int num, int numAbility);
	void Teleport(int num, int numAbility);
	
};
