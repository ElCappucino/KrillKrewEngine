#pragma once
#include "Level.h"
#include "LevelUtilities.h"
#include "nlohmann/json.hpp"

#define MAP_WIDTH  20 // 29
#define MAP_HEIGHT 16 // 30

/// @brief The class for level inherit test from P'tiam
class LevelShowcase : public Level
{
private:
	std::vector<DrawableObject*> objectsList;
	std::vector<EntityObject*> entityObjects;
	std::set<std::pair<Collider*, Collider*>> currentCollisions;
	std::set<std::pair<Collider*, Collider*>> previousCollisions;
	std::map<std::string, SpritesheetInfo> spriteList;

	//std::map<std::string, SpritesheetInfo> spriteList;

	// typedef std::function<void(int, PlayerObject*, std::vector<DrawableObject*>&, SpritesheetInfo)> ability;
	// std::map<std::string, ability> abilities;

	std::array<PlayerObject*, 4> players; // add up to 4 players
	std::array<UiObject*, 4> playerUIs; // add up to 4 players

	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> currentGroundTile = { 0 };
	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> groundTile = { 0 };

	// 0 = no prop
	// 1 = prop A
	// 2 = prop B
	// 3 = prop C
	// 4 = Tree A
	// 5 = Tree B
	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> currentPropTile = { 0 };
	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> propsTile = { 0 };
	
	/*int groundTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	int propsTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };
	int colliderTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };*/

	std::array<std::array<TileObject*, MAP_WIDTH>, MAP_HEIGHT> tilesList;

	std::map<int, std::pair<int, int>> blob_lookup_table = {

	{666,	{1, 1}},
	{777,	{2, 1}},
	{888,	{3, 1}},
	{999,	{4, 1}},

	{16,	{1, 2}},
	{17,	{2, 2}},
	{1,		{3, 2}},
	{0,		{4, 2}},

	{20,	{1, 3}},
	{21,	{2, 3}},
	{5,		{3, 3}},
	{4,		{4, 3}},

	{84,	{1, 4}},
	{85,	{2, 4}},
	{69,	{3, 4}},
	{68,	{4, 4}},

	{80,	{1, 5}},
	{81,	{2, 5}},
	{65,	{3, 5}},
	{64,	{4, 5}},

	{213,	{1, 6}},
	{29,	{2, 6}},
	{23,	{3, 6}},
	{117,	{4, 6}},

	{92,	{1, 7}},
	{127,	{2, 7}},
	{223,	{3, 7}},
	{71,	{4, 7}},

	{116,	{1, 8}},
	{253,	{2, 8}},
	{247,	{3, 8}},
	{197,	{4, 8}},

	{87,	{1, 9}},
	{113,	{2, 9}},
	{209,	{3, 9}},
	{93,	{4, 9}},

	{28,	{1, 10}},
	{31,	{2, 10}},
	{95,	{3, 10}},
	{7,		{4, 10}},

	{125,	{1, 11}},
	{119,	{2, 11}},
	{255,	{3, 11}},
	{199,	{4, 11}},

	{124,	{1, 12}},
	{256,	{2, 12}}, // blank
	{221,	{3, 12}},
	{215,	{4, 12}},

	{112,	{1, 13}},
	{245,	{2, 13}},
	{241,	{3, 13}},
	{193,	{4, 13}},
	};

	std::map<int, std::pair<int, int>> blob_lookup_table_underground = {
		// 1
		{16,	{2, 12}},
		{17,	{2, 12}},
		{1,		{4, 1}},
		{0,		{4, 1}},
		// 2
		{20,	{2, 12}},
		{21,	{2, 12}},
		{5,		{3, 1}},
		{4,		{3, 1}},
		// 3
		{84,	{2, 12} },
		{ 85,	{2, 12} },
		{ 69,	{2, 1} },
		{68,	{2, 1}},
		// 4
		{80,	{2, 12}},
		{81,	{2, 12}},
		{65,	{1, 1}},
		{64,	{1, 1}},
		// 5
		{213,	{2, 12}},
		{29,	{2, 12}},
		{23,	{2, 12}},
		{117,	{2, 12}},
		// 6
		{92,	{2, 12}},
		{127,	{2, 12}},
		{223,	{2, 12}},
		{71,	{2, 1}},
		// 7
		{116,	{2, 12}},
		{253,	{2, 12}},
		{247,	{2, 12}},
		{197,	{2, 1}},
		// 8
		{87,	{2, 12}},
		{113,	{2, 12}},
		{209,	{2, 12}},
		{93,	{2, 12}},

		{28,	{2, 12}},
		{31,	{2, 12}},
		{95,	{2, 12}},
		{7,		{3, 1}},

		{125,	{2, 12}},
		{119,	{2, 12}},
		{255,	{2, 12}},
		{199,	{2, 1}},

		{124,	{2, 12}},
		{256,	{2, 12}}, // blank
		{221,	{2, 12}},
		{215,	{2, 12}},

		{112,	{2, 12}	},
		{245,	{2, 12}	},
		{241,	{2, 12}	},
		{193,	{1, 1}	},
	};

	// ImGUI
	float groundColX[4] = { 64.f, 64.f, 64.f, 64.f };
	float groundColY[4] = { 64.f, 64.f, 64.f, 64.f };
	float groundColOffsetX[4] = { 0.f, 0.f, 0.f, 0.f };
	float groundColOffsetY[4] = { -96.f, -96.f, -96.f, -96.f };
	int playersSkill[4][3];
	int isResetScene;
	int isFullScreen;
	int isWindowScreen;

	float MeleeCooldown = 2.f;
	float FireballCooldown = 3.f;
	float TrapCooldown = 3.f;
	float DashCooldown = 3.f;
	float TNTCooldown = 3.f;
	float TeleportCooldown = 3.f;
	float BolaCooldown = 3.f;
	float CleaveCooldown = 3.f;

	float FireballLifetime = 1.f;
	float TeleportLifetime = 2.f;
	float BolaLifetime = 2.f;
	float CleaveLifetime = 2.f;

	float DashDuration = 0.2f;

	int playerSize = 0;
	int playerNum = 0;
	int abilityId[3];
	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;

	int currentPlayer = 0;

	float dt = 0;
	int frame = 0;
	int framePerSecond = 0;
	float targetFrameDuration = 1.0f / 288.0f; // cap at 144 fps
	float time1s = 0;
	float time01s = 0;
	float previousWidth = 0, previousHeight = 0;

	float musicVolume = 1.f, sfxVolume = 1.f;

	// player
	float axisXOld;
	float axisYOld;
	float norAxisXOld;
	float norAxisYOld;
	bool isPositiveXOld;
	bool isPositiveYOld;

	KrillSoundManager::SoundManager* soundManager;

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

	void InitTile();
	void InitProp();

	void UpdateInput();
	void UpdateCollision();
	void UpdateProjectile();
	void UpdateCooldown();
	void UpdateMovement();
	void UpdateUI();
	// void UpdateKnockback(DrawableObject* obj1, DrawableObject* obj2);
	void UpdateTime();

	void GroundTileRefactor();
	void TileImport(std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> &TileBuffer, std::string fileName);

	virtual void AddEntityToScene(EntityObject* entity);
	virtual void AddObjectToScene(DrawableObject* object);

	void UsingAbilityKeyDown(int numPlayer, PlayerObject::AbilityButton button);
	void UsingAbilityKeyUp(int numPlayer, PlayerObject::AbilityButton button);
	void AimFireball(int numPlayer, PlayerObject::AbilityButton button);
	void ShootFireball(int numPlayer, PlayerObject::AbilityButton button);
	void Trap(int numPlayer, PlayerObject::AbilityButton button);
	void Dash(int numPlayer, PlayerObject::AbilityButton button);
	void TNT(int numPlayer, PlayerObject::AbilityButton button);
	void AimTeleport(int numPlayer, PlayerObject::AbilityButton button);
	void ShootTeleport(int numPlayer, PlayerObject::AbilityButton button);
	void AimBola(int numPlayer, PlayerObject::AbilityButton button);
	void ShootBola(int numPlayer, PlayerObject::AbilityButton button);
	void AimCleave(int numPlayer, PlayerObject::AbilityButton button);
	void ShootCleave(int numPlayer, PlayerObject::AbilityButton button);

	void loadAbility(std::string filename);
	void SaveConfigInfo(const std::string& fileName);
	void LoadConfigInfo(const std::string& fileName);
};
