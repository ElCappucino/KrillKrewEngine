#pragma once
#include "Level.h"
#include "LevelUtilities.h"

#define MAP_WIDTH  20 // 29
#define MAP_HEIGHT 16 // 30

/// @brief The class for setup object in the level
/// @brief It intent to inherit this class for creating any new unique scene.
class LevelImGui : public Level
{
private:
	std::vector<DrawableObject*> objectsList;

	std::map<std::string, SpritesheetInfo> spriteList;

	std::set<std::pair<Collider*, Collider*>> currentCollisions;
	std::set<std::pair<Collider*, Collider*>> previousCollisions;

	Camera camera;

	std::array<PlayerObject*, 4> players; // add up to 4 players

	int groundTile[MAP_HEIGHT][MAP_WIDTH] = { 0 };

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

	int playerSize = 0;
	int playerNum = 0;
	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Timer* timer;

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
