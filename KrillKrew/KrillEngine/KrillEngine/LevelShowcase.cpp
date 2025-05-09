#include "LevelShowcase.h"

bool compareLayer(const DrawableObject* a, const DrawableObject* b)
{
	return a->getOrderingLayer() < b->getOrderingLayer();
}

void LevelShowcase::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	LineMeshVbo* line = new LineMeshVbo();
	line->LoadData();
	GameEngine::GetInstance()->AddMesh(LineMeshVbo::MESH_NAME, line);

	spriteList["Prinny"] = SpritesheetInfo("Prinny", "../Resource/Texture/Prinny.png", 538, 538, 538, 538);
	
	// Shark ----------------------------------------------------------------------------------------------------------------------------
	//  ---------------------------------------------------------------------------------------------------------------------------------
	// Cast
	spriteList["P1_Cast"] = SpritesheetInfo("P1_Cast",						"../Resource/Texture/Ham/P1_Cast.png", 302, 302, 1208, 302, false);
	// Cleave
	spriteList["P1_Cleave_Down"] = SpritesheetInfo("P1_Cleave_Down",		"../Resource/Texture/Ham/P1_CleaveDown.png", 402, 402, 1608, 402, false);
	spriteList["P1_Cleave_Side"] = SpritesheetInfo("P1_Cleave_Side",		"../Resource/Texture/Ham/P1_CleaveSide.png", 402, 402, 1608, 402, false);
	spriteList["P1_Cleave_Up"] = SpritesheetInfo("P1_Cleave_Up",			"../Resource/Texture/Ham/P1_CleaveUp.png", 402, 402, 1608, 402, false);
	// Dash
	spriteList["P1_Dash_Back"] = SpritesheetInfo("P1_Dash_Back",			"../Resource/Texture/Ham/P1_DashBack.png", 302, 302, 906, 302, false);
	spriteList["P1_Dash_Front"] = SpritesheetInfo("P1_Dash_Front",			"../Resource/Texture/Ham/P1_DashFront.png", 302, 302, 906, 302, false);
	spriteList["P1_Dash_Side"] = SpritesheetInfo("P1_Dash_Side",			"../Resource/Texture/Ham/P1_DashSide.png", 302, 302, 906, 302, false);
	// Dead (Temp)
	spriteList["P1_Dead"] = SpritesheetInfo("P1_Dead",						"../Resource/Texture/Ham/P1_Dead.png", 302, 302, 302, 302, false);
	// Hit
	spriteList["P1_Hit"] = SpritesheetInfo("P1_Hit",						"../Resource/Texture/Ham/P1_Hit.png", 302, 302, 906, 302, false);
	// Idle
	spriteList["P1_Idle"] = SpritesheetInfo("P1_Idle",						"../Resource/Texture/Ham/P1_Idle.png", 302, 302, 1812, 302);
	// Move
	spriteList["P1_Move_Back"] = SpritesheetInfo("P1_Move_Back",			"../Resource/Texture/Ham/P1_MoveBack.png", 302, 302, 1208, 302);
	spriteList["P1_Move_Front"] = SpritesheetInfo("P1_Move_Front",			"../Resource/Texture/Ham/P1_MoveFront.png", 302, 302, 1208, 302);
	spriteList["P1_Move_Side"] = SpritesheetInfo("P1_Move_Side",			"../Resource/Texture/Ham/P1_MoveSide.png", 302, 302, 1208, 302);
	// Place Trap
	spriteList["P1_Place"] = SpritesheetInfo("P1_Place",					"../Resource/Texture/Ham/P1_Place.png", 302, 302, 1208, 302, false);
	// Smash
	spriteList["P1_Smash_DiagDown"] = SpritesheetInfo("P1_Smash_DiagDown",	"../Resource/Texture/Ham/P1_SmashDiagDown.png", 302, 302, 1208, 302, false);
	spriteList["P1_Smash_DiagUp"] = SpritesheetInfo("P1_Smash_DiagUp",		"../Resource/Texture/Ham/P1_SmashDiagUp.png", 302, 302, 1208, 302, false);
	spriteList["P1_Smash_Down"] = SpritesheetInfo("P1_SmashDown",			"../Resource/Texture/Ham/P1_SmashDown.png", 302, 302, 1208, 302, false);
	spriteList["P1_Smash_Side"] = SpritesheetInfo("P1_Smash_Side",			"../Resource/Texture/Ham/P1_SmashSide.png", 302, 302, 1208, 302, false);
	spriteList["P1_Smash_Up"] = SpritesheetInfo("P1_Smash_Up",				"../Resource/Texture/Ham/P1_SmashUp.png", 302, 302, 1208, 302, false);
	// Stun
	spriteList["P1_Stun"] = SpritesheetInfo("P1_Stun",						"../Resource/Texture/Ham/P1_Stun.png", 350, 350, 700, 350, false);

	// Squid ----------------------------------------------------------------------------------------------------------------------------
	//  ---------------------------------------------------------------------------------------------------------------------------------
	// Cast
	spriteList["P2_Cast"] = SpritesheetInfo("P2_Cast",						"../Resource/Texture/Byssa/P1_Cast.png", 302, 302, 1208, 302, false);
	// Cleave
	spriteList["P2_Cleave_Down"] = SpritesheetInfo("P2_Cleave_Down",		"../Resource/Texture/Byssa/P2_CleaveDown.png", 402, 402, 1608, 402, false);
	spriteList["P2_Cleave_Side"] = SpritesheetInfo("P2_Cleave_Side",		"../Resource/Texture/Byssa/P2_CleaveSide.png", 402, 402, 1608, 402, false);
	spriteList["P2_Cleave_Up"] = SpritesheetInfo("P2_Cleave_Up",			"../Resource/Texture/Byssa/P2_CleaveUp.png", 402, 402, 1608, 402, false);
	// Dash
	spriteList["P2_Dash_Back"] = SpritesheetInfo("P2_Dash_Back",			"../Resource/Texture/Byssa/P2_DashBack.png", 302, 302, 906, 302, false);
	spriteList["P2_Dash_Front"] = SpritesheetInfo("P2_Dash_Front",			"../Resource/Texture/Byssa/P2_DashFront.png", 302, 302, 906, 302, false);
	spriteList["P2_Dash_Side"] = SpritesheetInfo("P2_Dash_Side",			"../Resource/Texture/Byssa/P2_DashSide.png", 302, 302, 906, 302, false);
	// Dead (Temp)
	spriteList["P2_Dead"] = SpritesheetInfo("P2_Dead",						"../Resource/Texture/Byssa/P2_Dead.png", 302, 302, 302, 302, false);
	// Hit
	spriteList["P2_Hit"] = SpritesheetInfo("P2_Hit",						"../Resource/Texture/Byssa/P2_Hit.png", 302, 302, 906, 302, false);
	// Idle
	spriteList["P2_Idle"] = SpritesheetInfo("P2_Idle",						"../Resource/Texture/Byssa/P2_Idle.png", 302, 302, 1812, 302);
	// Move
	spriteList["P2_Move_Back"] = SpritesheetInfo("P2_Move_Back",			"../Resource/Texture/Byssa/P2_MoveBack.png", 302, 302, 1208, 302);
	spriteList["P2_Move_Front"] = SpritesheetInfo("P2_Move_Front",			"../Resource/Texture/Byssa/P2_MoveFront.png", 302, 302, 1208, 302);
	spriteList["P2_Move_Side"] = SpritesheetInfo("P2_Move_Side",			"../Resource/Texture/Byssa/P2_MoveSide.png", 302, 302, 1208, 302);
	// Place Trap
	spriteList["P2_Place"] = SpritesheetInfo("P2_Place",					"../Resource/Texture/Byssa/P2_Place.png", 302, 302, 1208, 302, false);
	// Smash
	spriteList["P2_Smash_DiagDown"] = SpritesheetInfo("P2_Smash_DiagDown",	"../Resource/Texture/Byssa/P2_SmashDiagDown.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_DiagUp"] = SpritesheetInfo("P2_Smash_DiagUp",		"../Resource/Texture/Byssa/P2_SmashDiagUp.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_Down"] = SpritesheetInfo("P2_SmashDown",			"../Resource/Texture/Byssa/P2_SmashDown.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_Side"] = SpritesheetInfo("P2_Smash_Side",			"../Resource/Texture/Byssa/P2_SmashSide.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_Up"] = SpritesheetInfo("P2_Smash_Up",				"../Resource/Texture/Byssa/P2_SmashUp.png", 302, 302, 1208, 302, false);
	// Stun
	spriteList["P2_Stun"] = SpritesheetInfo("P2_Stun",						"../Resource/Texture/Byssa/P2_Stun.png", 350, 350, 700, 350, false);

	// Squid ----------------------------------------------------------------------------------------------------------------------------
	//  ---------------------------------------------------------------------------------------------------------------------------------
	// Cast
	spriteList["P2_Cast"] =	SpritesheetInfo("P2_Cast",						"../Resource/Texture/Byssa/P2_Cast.png", 302, 302, 1208, 302, false);
	// Cleave
	spriteList["P2_Cleave_Down"] = SpritesheetInfo("P2_Cleave_Down",		"../Resource/Texture/Byssa/P2_CleaveDown.png", 402, 402, 1608, 402, false);
	spriteList["P2_Cleave_Side"] = SpritesheetInfo("P2_Cleave_Side",		"../Resource/Texture/Byssa/P2_CleaveSide.png", 402, 402, 1608, 402, false);
	spriteList["P2_Cleave_Up"] = SpritesheetInfo("P2_Cleave_Up",			"../Resource/Texture/Byssa/P2_CleaveUp.png", 402, 402, 1608, 402, false);
	// Dash
	spriteList["P2_Dash_Back"] = SpritesheetInfo("P2_Dash_Back",			"../Resource/Texture/Byssa/P2_DashBack.png", 302, 302, 906, 302, false);
	spriteList["P2_Dash_Front"] = SpritesheetInfo("P2_Dash_Front",			"../Resource/Texture/Byssa/P2_DashFront.png", 302, 302, 906, 302, false);
	spriteList["P2_Dash_Side"] = SpritesheetInfo("P2_Dash_Side",			"../Resource/Texture/Byssa/P2_DashSide.png", 302, 302, 906, 302, false);
	// Dead (Temp)
	spriteList["P2_Dead"] = SpritesheetInfo("P2_Dead",						"../Resource/Texture/Byssa/P2_Dead.png", 302, 302, 302, 302, false);
	// Hit
	spriteList["P2_Hit"] = SpritesheetInfo("P2_Hit",						"../Resource/Texture/Byssa/P2_Hit.png", 302, 302, 906, 302, false);
	// Idle
	spriteList["P2_Idle"] = SpritesheetInfo("P2_Idle",						"../Resource/Texture/Byssa/P2_Idle.png", 302, 302, 1812, 302);
	// Move
	spriteList["P2_Move_Back"] = SpritesheetInfo("P2_Move_Back",			"../Resource/Texture/Byssa/P2_MoveBack.png", 302, 302, 1208, 302);
	spriteList["P2_Move_Front"] = SpritesheetInfo("P2_Move_Front",			"../Resource/Texture/Byssa/P2_MoveFront.png", 302, 302, 1208, 302);
	spriteList["P2_Move_Side"] = SpritesheetInfo("P2_Move_Side",			"../Resource/Texture/Byssa/P2_MoveSide.png", 302, 302, 1208, 302);
	// Place Trap
	spriteList["P2_Place"] = SpritesheetInfo("P2_Place",					"../Resource/Texture/Byssa/P2_Place.png", 302, 302, 1208, 302, false);
	// Smash
	spriteList["P2_Smash_DiagDown"] = SpritesheetInfo("P2_Smash_DiagDown",	"../Resource/Texture/Byssa/P2_SmashDiagDown.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_DiagUp"] = SpritesheetInfo("P2_Smash_DiagUp",		"../Resource/Texture/Byssa/P2_SmashDiagUp.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_Down"] = SpritesheetInfo("P2_Smash_Down",			"../Resource/Texture/Byssa/P2_SmashDown.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_Side"] = SpritesheetInfo("P2_Smash_Side",			"../Resource/Texture/Byssa/P2_SmashSide.png", 302, 302, 1208, 302, false);
	spriteList["P2_Smash_Up"] = SpritesheetInfo("P2_Smash_Up",				"../Resource/Texture/Byssa/P2_SmashUp.png", 302, 302, 1208, 302, false);
	// Stun
	spriteList["P2_Stun"] = SpritesheetInfo("P2_Stun",						"../Resource/Texture/Byssa/P2_Stun.png", 350, 350, 700, 350, false);

	// Axolotl ----------------------------------------------------------------------------------------------------------------------------
	//  ---------------------------------------------------------------------------------------------------------------------------------
	// Cast
	spriteList["P3_Cast"] = SpritesheetInfo("P3_Cast",						"../Resource/Texture/Xoey/P3_Cast.png", 302, 302, 1208, 302, false);
	// Cleave
	spriteList["P3_Cleave_Down"] = SpritesheetInfo("P3_Cleave_Down",		"../Resource/Texture/Xoey/P3_CleaveDown.png", 402, 402, 1608, 402, false);
	spriteList["P3_Cleave_Side"] = SpritesheetInfo("P3_Cleave_Side",		"../Resource/Texture/Xoey/P3_CleaveSide.png", 402, 402, 1608, 402, false);
	spriteList["P3_Cleave_Up"] = SpritesheetInfo("P3_Cleave_Up",			"../Resource/Texture/Xoey/P3_CleaveUp.png", 402, 402, 1608, 402, false);
	// Dash																								
	spriteList["P3_Dash_Back"] = SpritesheetInfo("P3_Dash_Back",			"../Resource/Texture/Xoey/P3_DashBack.png", 302, 302, 906, 302, false);
	spriteList["P3_Dash_Front"] = SpritesheetInfo("P3_Dash_Front",			"../Resource/Texture/Xoey/P3_DashFront.png", 302, 302, 906, 302, false);
	spriteList["P3_Dash_Side"] = SpritesheetInfo("P3_Dash_Side",			"../Resource/Texture/Xoey/P3_DashSide.png", 302, 302, 906, 302, false);
	// Dead (Temp)																						
	spriteList["P3_Dead"] =	SpritesheetInfo("P3_Dead",						"../Resource/Texture/Xoey/P3_Dead.png", 302, 302, 302, 302, false);
	// Hit																								
	spriteList["P3_Hit"] = SpritesheetInfo("P3_Hit",						"../Resource/Texture/Xoey/P3_Hit.png", 302, 302, 906, 302, false);
	// Idle																								
	spriteList["P3_Idle"] =	SpritesheetInfo("P3_Idle",						"../Resource/Texture/Xoey/P3_Idle.png", 302, 302, 1812, 302);
	// Move																								
	spriteList["P3_Move_Back"] = SpritesheetInfo("P3_Move_Back",			"../Resource/Texture/Xoey/P3_MoveBack.png", 302, 302, 1208, 302);
	spriteList["P3_Move_Front"] = SpritesheetInfo("P3_Move_Front",			"../Resource/Texture/Xoey/P3_MoveFront.png", 302, 302, 1208, 302);
	spriteList["P3_Move_Side"] = SpritesheetInfo("P3_Move_Side",			"../Resource/Texture/Xoey/P3_MoveSide.png", 302, 302, 1208, 302);
	// Place Trap																						
	spriteList["P3_Place"] = SpritesheetInfo("P3_Place",					"../Resource/Texture/Xoey/P3_Place.png", 302, 302, 1208, 302, false);
	// Smash																							
	spriteList["P3_Smash_DiagDown"] = SpritesheetInfo("P3_Smash_DiagDown",	"../Resource/Texture/Xoey/P3_SmashDiagDown.png", 302, 302, 1208, 302, false);
	spriteList["P3_Smash_DiagUp"] = SpritesheetInfo("P3_Smash_DiagUp",		"../Resource/Texture/Xoey/P3_SmashDiagUp.png", 302, 302, 1208, 302, false);
	spriteList["P3_Smash_Down"] = SpritesheetInfo("P3_Smash_Down",			"../Resource/Texture/Xoey/P3_SmashDown.png", 302, 302, 1208, 302, false);
	spriteList["P3_Smash_Side"] = SpritesheetInfo("P3_Smash_Side",			"../Resource/Texture/Xoey/P3_SmashSide.png", 302, 302, 1208, 302, false);
	spriteList["P3_Smash_Up"] =	SpritesheetInfo("P3_Smash_Up",				"../Resource/Texture/Xoey/P3_SmashUp.png", 302, 302, 1208, 302, false);
	// Stun																								
	spriteList["P3_Stun"] = SpritesheetInfo("P3_Stun",						"../Resource/Texture/Xoey/P3_Stun.png", 350, 350, 700, 350, false);

	// Crocodile ----------------------------------------------------------------------------------------------------------------------------
	//  ---------------------------------------------------------------------------------------------------------------------------------
	// Cast
	spriteList["P4_Cast"] = SpritesheetInfo("P4_Cast",						"../Resource/Texture/Crunk/P4_Cast.png", 302, 302, 1208, 302, false);
	// Cleave	 																					   
	spriteList["P4_Cleave_Down"] = SpritesheetInfo("P4_Cleave_Down",		"../Resource/Texture/Crunk/P4_CleaveDown.png", 402, 402, 1608, 402, false);
	spriteList["P4_Cleave_Side"] = SpritesheetInfo("P4_Cleave_Side",		"../Resource/Texture/Crunk/P4_CleaveSide.png", 402, 402, 1608, 402, false);
	spriteList["P4_Cleave_Up"] = SpritesheetInfo("P4_Cleave_Up",			"../Resource/Texture/Crunk/P4_CleaveUp.png", 402, 402, 1608, 402, false);
	// Dash																							   
	spriteList["P4_Dash_Back"] = SpritesheetInfo("P4_Dash_Back",			"../Resource/Texture/Crunk/P4_DashBack.png", 302, 302, 906, 302, false);
	spriteList["P4_Dash_Front"] = SpritesheetInfo("P4_Dash_Front",			"../Resource/Texture/Crunk/P4_DashFront.png", 302, 302, 906, 302, false);
	spriteList["P4_Dash_Side"] = SpritesheetInfo("P4_Dash_Side",			"../Resource/Texture/Crunk/P4_DashSide.png", 302, 302, 906, 302, false);
	// Dead																							   
	spriteList["P4_Dead"] = SpritesheetInfo("P4_Dead",						"../Resource/Texture/Crunk/P4_Dead.png", 302, 302, 302, 302, false);
	// Hit																							   
	spriteList["P4_Hit"] = SpritesheetInfo("P4_Hit",						"../Resource/Texture/Crunk/P4_Hit.png", 302, 302, 906, 302, false);
	// Idle																							   
	spriteList["P4_Idle"] = SpritesheetInfo("P4_Idle",						"../Resource/Texture/Crunk/P4_Idle.png", 302, 302, 1812, 302);
	// Move																							   
	spriteList["P4_Move_Back"] = SpritesheetInfo("P4_Move_Back",			"../Resource/Texture/Crunk/P4_MoveBack.png", 302, 302, 1208, 302);
	spriteList["P4_Move_Front"] = SpritesheetInfo("P4_Move_Front",			"../Resource/Texture/Crunk/P4_MoveFront.png", 302, 302, 1208, 302);
	spriteList["P4_Move_Side"] = SpritesheetInfo("P4_Move_Side",			"../Resource/Texture/Crunk/P4_MoveSide.png", 302, 302, 1208, 302);
	// Place Trap																					   
	spriteList["P4_Place"] = SpritesheetInfo("P4_Place",					"../Resource/Texture/Crunk/P4_Place.png", 302, 302, 1208, 302, false);
	// Smash																						   
	spriteList["P4_Smash_DiagDown"] = SpritesheetInfo("P4_Smash_DiagDown",	"../Resource/Texture/Crunk/P4_SmashDiagDown.png", 302, 302, 1208, 302, false);
	spriteList["P4_Smash_DiagUp"] = SpritesheetInfo("P4_Smash_DiagUp",		"../Resource/Texture/Crunk/P4_SmashDiagUp.png", 302, 302, 1208, 302, false);
	spriteList["P4_Smash_Down"] = SpritesheetInfo("P4_Smash_Down",			"../Resource/Texture/Crunk/P4_SmashDown.png", 302, 302, 1208, 302, false);
	spriteList["P4_Smash_Side"] = SpritesheetInfo("P4_Smash_Side",			"../Resource/Texture/Crunk/P4_SmashSide.png", 302, 302, 1208, 302, false);
	spriteList["P4_Smash_Up"] = SpritesheetInfo("P4_Smash_Up",				"../Resource/Texture/Crunk/P4_SmashUp.png", 302, 302, 1208, 302, false);
	// Stun																							   
	spriteList["P4_Stun"] = SpritesheetInfo("P3_Stun",						"../Resource/Texture/Crunk/P4_Stun.png", 350, 350, 700, 350, false);

	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Ability/abi_spr_bomb_projecttile.png", 300, 300, 1800, 300, true);
	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Ability/abi_spr_jellyfish_putdown.png", 256, 256, 4096, 256, false);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/Ability/abi_spr_landmine_idle.png", 370, 370, 740, 370, true);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/Ability/abi_spr_teleport_projectile.png", 211, 97, 422, 97, true);
	spriteList["Bola"] = SpritesheetInfo("Bola", "../Resource/Texture/Ability/abi_spr_stun_projecttile.png", 400, 400, 1600, 400, true);
	spriteList["Cleave"] = SpritesheetInfo("Cleave", "../Resource/Texture/Ability/abi_spr_cleave_side.png", 358, 258, 1074, 258, true);
	
	spriteList["Xoey_UI"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	spriteList["Byssa_UI"] = SpritesheetInfo("Byssa_UI", "../Resource/Texture/byssa.png", 430, 220, 430, 220);
	spriteList["Crunk_UI"] = SpritesheetInfo("Crunk_UI", "../Resource/Texture/crunk.png", 430, 220, 430, 220);
	spriteList["Ham_UI"] = SpritesheetInfo("Ham_UI", "../Resource/Texture/Ham.png", 430, 220, 430, 220);

	spriteList["Blobtile"] = SpritesheetInfo("Blobtile", "../Resource/Texture/tileset_01.png", 128, 128, 1664, 512);

	soundManager = KrillSoundManager::SoundManager::GetInstance();

	soundManager->LoadMusic("bgm_test", "../Resource/Audio/bgm_test.mp3");
	soundManager->LoadSFX("hit_test", "../Resource/Audio/cute-pop-sfx.mp3");



	soundManager->PlayMusic("bgm_test", true);

	//cout << "Load Level" << endl;
}

void LevelShowcase::InitTile()
{
	float map_left = -1280.f;
	float map_top = 1080.f;

	int tileCount = 0;

	float totalLoadedTile = MAP_HEIGHT * MAP_WIDTH;
	float currentLoadedTile = 0;

	KK_TRACE("Generate Map-----------{0}", totalLoadedTile);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			currentLoadedTile++;
			KK_CORE_TRACE("Generate Map-----------{0}%", 100.f * currentLoadedTile / totalLoadedTile);

			int flag = groundTile[i][j];

			std::pair<int, int> pos;

			if (i == 0 ||
				i == MAP_HEIGHT - 1 ||
				j == 0 ||
				j == MAP_WIDTH - 1)
			{
				continue;
			}
			else
			{
				int checkPosRow;

				if (flag == 0)
				{
					checkPosRow = i - 1;
				}
				else if (flag == 1)
				{
					checkPosRow = i;
				}

				std::bitset<8> surround;
				surround[0] = groundTile[checkPosRow - 1][j];
				surround[1] = groundTile[checkPosRow - 1][j + 1];
				surround[2] = groundTile[checkPosRow][j + 1];
				surround[3] = groundTile[checkPosRow + 1][j + 1];
				surround[4] = groundTile[checkPosRow + 1][j];
				surround[5] = groundTile[checkPosRow + 1][j - 1];
				surround[6] = groundTile[checkPosRow][j - 1];
				surround[7] = groundTile[checkPosRow - 1][j - 1];

				if (!(surround[0] && surround[2])) { surround[1] = 0; }
				if (!(surround[2] && surround[4])) { surround[3] = 0; }
				if (!(surround[4] && surround[6])) { surround[5] = 0; }
				if (!(surround[6] && surround[0])) { surround[7] = 0; }

				if (flag == 0)
				{
					auto lookup_sheet = blob_lookup_table_underground.find((int)(surround.to_ulong()));

					if (lookup_sheet != blob_lookup_table_underground.end() && groundTile[checkPosRow][j] != 0)
					{
						pos = lookup_sheet->second;
					}
					else
					{
						pos = { 2, 12 };
					}
				}
				else if (flag == 1)
				{
					auto lookup_sheet = blob_lookup_table.find((int)(surround.to_ulong()));

					if (lookup_sheet != blob_lookup_table_underground.end())
					{
						pos = lookup_sheet->second;
					}
					else
					{
						pos = { 2, 12 };
					}
				}
			}

			if (pos.first == 2 && pos.second == 12)
			{
				// KK_TRACE("Pos.first = 2, pos.second = 12");
			}
			else
			{
				// KK_TRACE("Pos {0}, {1} pos.first = {2} pos.second = {3} ", i, j, pos.first, pos.second);
				TileObject* obj = new TileObject();
				obj->SetTextureWithID(spriteList.find("Blobtile")->second, spriteList.find("Blobtile")->second.textureid);
				//obj->SetSpriteInfo(spriteList.find("Blobtile")->second);
				obj->GetSpriteRenderer()->ShiftTo(pos.first - 1, pos.second - 1);
				//obj->SetTexture(spriteList.find("Blobtile")->second.texture);
				obj->SetSize(128.f, -128.f);
				obj->SetPosition(glm::vec3(map_left + (j * 126.f), map_top - (i * 126.f), 0));
				obj->SetTilePosition(i, j);
				obj->SetUpdateTileset(&currentGroundTile);

				if (flag == 0)
				{
					obj->SetIsBreakable(false);
					obj->SetIsBroke(true);
				}
				else if (flag == 1)
				{
					obj->SetIsBreakable(true);
					obj->SetIsBroke(false);
				}

				tilesList[i][j] = obj;

				entityObjects.push_back(obj);
				tileCount++;
				objectsList.push_back(obj);
				objectsList.push_back(obj->GetCollider()->GetGizmos());
				objectsList.push_back(obj->GetOverlaySprite());

				
			}
			
		}
	}
}

void LevelShowcase::LevelInit()
{
	std::cout << "Init Level" << std::endl;

	glClearColor(0.f, 180.f / 255.f, 171.f / 255.f, 1.f);

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(
		-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	timer = Timer::Instance();

	TileImport(groundTile, "../Resource/Texture/Tilemap0.txt");
	TileImport(currentGroundTile, "../Resource/Texture/Tilemap0.txt");

	// Create and Initialize 4 players object

	for (auto& info : spriteList)
	{
		unsigned int texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(info.second.texture);
		info.second.textureid = texture;
		KK_CORE_TRACE("Load Texture: {0}", texture);
	}

	InitTile();

	// Example Code
	int count = 0;
	std::string data[3];
	std::string line;
	int abilityId[3];

	KK_TRACE("Init Player-----------");
	PlayerObject* p1 = new PlayerObject();
	p1->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("P1_Idle")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::GetHit, spriteList.find("P1_Hit")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Stun, spriteList.find("P1_Stun")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::FellDown, spriteList.find("P1_Dead")->second);

	p1->SetAnimationSprite(PlayerObject::AnimationState::Move_Side, spriteList.find("P1_Move_Side")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Move_Back, spriteList.find("P1_Move_Back")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Move_Front, spriteList.find("P1_Move_Front")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Cast, spriteList.find("P1_Cast")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::PlaceItem, spriteList.find("P1_Place")->second);

	p1->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagDown, spriteList.find("P1_Smash_DiagDown")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagUp, spriteList.find("P1_Smash_DiagUp")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Smash_Down, spriteList.find("P1_Smash_Down")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Smash_Side, spriteList.find("P1_Smash_Side")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Smash_Up, spriteList.find("P1_Smash_Up")->second);

	std::ifstream readFile("Ability0.txt");
	while (std::getline(readFile, line)) {
		data[count] = line;
		abilityId[count] = stoi(data[count]);
		count++;
	}
	if (count < 3) {
		abilityId[0] = 0;
		abilityId[1] = 1;
		abilityId[2] = 2;
		count = 0;
	}
	else {
		count = 0;
	}
	readFile.close();

	p1->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p1->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p1->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));
	p1->SetTextureWithID(spriteList.find("P1_Idle")->second, spriteList.find("P1_Idle")->second.textureid);
	p1->SetPosition(glm::vec3(-400.f, -400.f, 0.f));
	p1->GetSpriteRenderer()->SetFrame(10);
	p1->SetPlayerNumber(0);
	entityObjects.push_back(p1);
	objectsList.push_back(p1);
	playerSize++;
	players[0] = p1;

	PlayerObject* p2 = new PlayerObject();
	p2->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("P2_Idle")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Stun, spriteList.find("P2_Stun")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::FellDown, spriteList.find("P2_Dead")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::GetHit, spriteList.find("P2_Hit")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Move_Side, spriteList.find("P2_Move_Side")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Move_Back, spriteList.find("P2_Move_Back")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Move_Front, spriteList.find("P2_Move_Front")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Cast, spriteList.find("P2_Cast")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::PlaceItem, spriteList.find("P2_Place")->second);

	p2->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagDown, spriteList.find("P2_Smash_DiagDown")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagUp, spriteList.find("P2_Smash_DiagUp")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Smash_Down, spriteList.find("P2_Smash_Down")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Smash_Side, spriteList.find("P2_Smash_Side")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Smash_Up, spriteList.find("P2_Smash_Up")->second);
	std::ifstream read2File("Ability1.txt");
	while (std::getline(read2File, line)) {
		data[count] = line;
		abilityId[count] = stoi(data[count]);
		count++;
	}
	if (count < 3) {
		abilityId[0] = 0;
		abilityId[1] = 1;
		abilityId[2] = 2;
		count = 0;
	}
	else {
		count = 0;
	}
	read2File.close();
	p2->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p2->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p2->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));

	p2->SetTextureWithID(spriteList.find("P2_Idle")->second, spriteList.find("P2_Idle")->second.textureid);
	p2->SetPosition(glm::vec3(400.f, -400.f, 0));
	p2->GetSpriteRenderer()->SetFrame(10);
	p2->SetPlayerNumber(1);
	entityObjects.push_back(p2);
	objectsList.push_back(p2);
	playerSize++;
	players[1] = p2;

	PlayerObject* p3 = new PlayerObject();
	p3->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("P3_Idle")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Stun, spriteList.find("P3_Stun")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::FellDown, spriteList.find("P3_Dead")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::GetHit, spriteList.find("P3_Hit")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Move_Side, spriteList.find("P3_Move_Side")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Move_Back, spriteList.find("P3_Move_Back")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Move_Front, spriteList.find("P3_Move_Front")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Cast, spriteList.find("P3_Cast")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::PlaceItem, spriteList.find("P3_Place")->second);

	p3->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagDown, spriteList.find("P3_Smash_DiagDown")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagUp, spriteList.find("P3_Smash_DiagUp")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Smash_Down, spriteList.find("P3_Smash_Down")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Smash_Side, spriteList.find("P3_Smash_Side")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Smash_Up, spriteList.find("P3_Smash_Up")->second);

	std::ifstream read3File("Ability2.txt");
	while (std::getline(read3File, line)) {
		data[count] = line;
		abilityId[count] = stoi(data[count]);
		count++;
	}
	if (count < 3) {
		abilityId[0] = 0;
		abilityId[1] = 1;
		abilityId[2] = 2;
		count = 0;
	}
	else {
		count = 0;
	}
	read3File.close();
	p3->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p3->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p3->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));
	p3->SetTextureWithID(spriteList.find("P3_Idle")->second, spriteList.find("P3_Idle")->second.textureid);
	p3->SetPosition(glm::vec3(400.f, 400.f, 0));
	p3->GetSpriteRenderer()->SetFrame(10);
	p3->SetPlayerNumber(2);
	entityObjects.push_back(p3);
	objectsList.push_back(p3);
	playerSize++;
	players[2] = p3;

	PlayerObject* p4 = new PlayerObject();
	p4->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("P4_Idle")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Stun, spriteList.find("P4_Stun")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::FellDown, spriteList.find("P4_Dead")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::GetHit, spriteList.find("P4_Hit")->second);
	
	p4->SetAnimationSprite(PlayerObject::AnimationState::Move_Side, spriteList.find("P4_Move_Side")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Move_Back, spriteList.find("P4_Move_Back")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Move_Front, spriteList.find("P4_Move_Front")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Cast, spriteList.find("P4_Cast")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::PlaceItem, spriteList.find("P4_Place")->second);

	p4->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagDown, spriteList.find("P4_Smash_DiagDown")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Smash_DiagUp, spriteList.find("P4_Smash_DiagUp")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Smash_Down, spriteList.find("P4_Smash_Down")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Smash_Side, spriteList.find("P4_Smash_Side")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Smash_Up, spriteList.find("P4_Smash_Up")->second);

	std::ifstream read4File("Ability3.txt");
	while (std::getline(read4File, line)) {
		data[count] = line;
		abilityId[count] = stoi(data[count]);
		count++;
	}
	if (count < 3) {
		abilityId[0] = 0;
		abilityId[1] = 1;
		abilityId[2] = 2;
		count = 0;
	}
	else {
		count = 0;
	}
	read4File.close();
	p4->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p4->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p4->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));
	p4->SetTextureWithID(spriteList.find("P4_Idle")->second, spriteList.find("P4_Idle")->second.textureid);
	p4->SetPosition(glm::vec3(-400.f, 400.f, 0));
	p4->GetSpriteRenderer()->SetFrame(10);
	p4->SetPlayerNumber(3);
	entityObjects.push_back(p4);
	objectsList.push_back(p4);
	playerSize++;
	players[3] = p4;

	for (int i = 0; i < playerSize; i++)
	{
		entityObjects.push_back(players[i]->GetAttackColliderObject());
		objectsList.push_back(players[i]->GetAttackColliderObject());
		objectsList.push_back(players[i]->GetAttackCollider()->GetGizmos());
		objectsList.push_back(players[i]->GetCollider()->GetGizmos());

		entityObjects.push_back(players[i]->GetGroundColliderObject());
		objectsList.push_back(players[i]->GetGroundCollider()->GetGizmos());
	}

	//create Ui by PlayerObject
	//int playerSize = playerSize;
	KK_TRACE("Init UI-----------");
	count = 0;

	if (playerSize >= 0) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Xoey_UI")->second);
		uiSkills->setNumOwner(0);
		objectsList.push_back(uiSkills);
		playerUIs[0] = uiSkills;
	}
	if (playerSize >= 1) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Ham_UI")->second);
		uiSkills->setNumOwner(1);
		objectsList.push_back(uiSkills);
		playerUIs[1] = uiSkills;
	}
	if (playerSize >= 2) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Byssa_UI")->second);
		uiSkills->setNumOwner(2);
		objectsList.push_back(uiSkills);
		playerUIs[2] = uiSkills;
	}
	if (playerSize >= 3) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Crunk_UI")->second);
		uiSkills->setNumOwner(3);
		objectsList.push_back(uiSkills);
		playerUIs[3] = uiSkills;
	}

	// sort with ordering layer
	std::sort(objectsList.begin(), objectsList.end(), compareLayer);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	const char* glsl_version = "#version 330";
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(GameEngine::GetInstance()->GetSDLWindow(), GameEngine::GetInstance()->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	std::cout << "Init Level" << std::endl;
}

void LevelShowcase::LevelUpdate()
{
	//dt++;
	// KK_TRACE("Update Per Frame");
		// Clear inactive object
	for (int i = 0; i < objectsList.size(); i++)
	{
		if (objectsList[i]->GetIsActive() == false)
		{
			objectsList.erase(objectsList.begin() + i);
		}
	}

	for (int i = 0; i < entityObjects.size(); i++)
	{
		if (entityObjects[i]->GetIsActive() == false)
		{
			entityObjects.erase(entityObjects.begin() + i);
		}
	}

	UpdateInput();

	for (int i = 0; i < playerSize; i++) {
		camera.setPlayerPos(i, players[i]->getPos());
	}
	camera.LerpCamera(playerSize); // update smooth camera here

	// Set Animation
	for (int i = 0; i < entityObjects.size(); i++)
	{
		EntityObject* entity = entityObjects[i];
		if (entity == nullptr)
		{
			continue;
		}
		else
		{
			if (entity->GetIsAnimated() && frame % entity->GetSpriteRenderer()->GetFrame() == 0)
			{
				entity->GetSpriteRenderer()->ShiftColumn();
				entity->UpdateCurrentAnimation();
			}
		}
	}

	// slowness
	UpdateMovement();

	// projectile collider player
	UpdateCollision();

	// delete projectile
	UpdateProjectile();

	// reduce cooldown skill
	UpdateCooldown();

	//Ui Skills
	UpdateUI();

	GroundTileRefactor();

	std::sort(objectsList.begin(), objectsList.end(), compareLayer);

	
}

void LevelShowcase::UpdateInput()
{
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();
		for (int i = 0; i < playerSize; i++)
		{
			if (players[i]->GetIsFell())
			{
				continue;
			}
			float axisX = Joystick::GetAxis(i, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
			float axisY = Joystick::GetAxis(i, Joystick::Axis::LeftStickVertical) / 32768.0f;
			float norAxisX = 0;
			float norAxisY = 0;

			bool isPositiveX = false;
			bool isPositiveY = false;

			if (abs(axisX) < 0.1)
			{
				norAxisX = 0;
			}
			else
			{
				float axis = atan2(axisY, axisX);
				norAxisX = cos(axis);
			}

			if (abs(axisY) < 0.1)
			{
				norAxisY = 0;
			}
			else
			{
				float axis = atan2(axisY, axisX);
				norAxisY = sin(axis);
			}

			if (axisX > 0)
			{
				isPositiveX = true;
			}
			else if (axisX <= 0)
			{
				isPositiveX = false;
			}

			if (axisY > 0)
			{
				isPositiveY = false;
			}
			else if (axisY < 0)
			{
				isPositiveY = true;
			}
			if (norAxisX != 0 || norAxisY != 0)
			{
				players[i]->SetCurrentDirection(glm::vec2(norAxisX, norAxisY));
			}

			if (players[i]->GetIsFell() == false)
			{
				// update facing
				if (abs(axisX) > 0.2f)
				{
					players[i]->UpdateFacingSide(isPositiveX);
				}

				// movement control
				if (players[i]->GetIsKnockback() == false)
				{
					if (players[i]->GetIsStun() == true)
					{
						// velo to zero if stun
						players[i]->SetVelocity(0, 0, isPositiveXOld, isPositiveYOld);
					}
					else if (players[i]->GetIsDashing() == true)
					{
						// use old velo during dash to disable control
						players[i]->SetVelocity(
							abs(norAxisXOld / 5.f),
							abs(norAxisYOld / 5.f),
							isPositiveXOld,
							isPositiveYOld
						);
					}
					else if (players[i]->GetIsAiming() == false)
					{
						// if not affecit by anything, use normaml velocity
						players[i]->SetVelocity(
							abs(norAxisX) / 5.f,
							abs(norAxisY) / 5.f,
							isPositiveX,
							isPositiveY
						);
					}
				}

				// update old velocity in case dashing

				if (players[i]->GetIsDashing())
				{
					norAxisXOld = norAxisX;
					norAxisYOld = norAxisY;
					isPositiveXOld = isPositiveX;
					isPositiveYOld = isPositiveY;
				}

				if (players[i]->GetIsAiming())
				{
					std::vector<ProjectileObject*> owningProjectile = players[i]->GetOwningProjectile();
					for (int j = 0; j < owningProjectile.size(); j++)
					{
						ProjectileObject* projectile = owningProjectile[j];
						if ((projectile != nullptr) &&
							(players[i]->GetPlayerNumber() == projectile->GetOwner()->GetPlayerNumber()) &&
							(projectile->GetIsShooting() == false))
						{
							PlayerObject* player = projectile->GetOwner();
							float veloX = player->GetCurrentDirection().x;
							float veloY = player->GetCurrentDirection().y;
							float angle = atan2(-player->GetCurrentDirection().y, player->GetCurrentDirection().x);

							float absSizeX = abs(projectile->getSize().x);

							if (angle < -3.14f / 2.f || angle > 3.14f / 2.f)
							{
								projectile->SetSize(-absSizeX, projectile->getSize().y);

								if (angle > 0)
								{
									angle = -(3.14f - angle);
								}
								else
								{
									angle = 3.14f + angle;
								}
							}
							else
							{
								projectile->SetSize(absSizeX, projectile->getSize().y);
							}

							bool PositiveX = veloX > 0.f ? true : false;
							bool PositiveY = veloY < 0.f ? true : false;

							projectile->SetPosition(players[i]->getPos() + (projectile->GetVelocity() * glm::vec3(15.f, 15.f, 0.f)));
							projectile->SetRotation(angle);
							projectile->SetVelocity(abs(veloX), abs(veloY), PositiveX, PositiveY);

							if (projectile->type == ProjectileObject::Cleave && projectile->GetLifetime() <= 9997) {
								players[i]->SetIsAiming(false);
								projectile->SetLifeTime(2);
								projectile->SetIsShooting(true);
								players[i]->SetHoldingProjectile(0);
							}
						}

						// cancel aim
						if ((projectile != nullptr) && (players[i]->GetIsKnockback() == true || players[i]->GetIsStun() == true)) {
							players[i]->SetHoldingProjectile(0);
							//players[i + playerNum]->SetIsShooting(false);
							projectile->SetLifeTime(0);
							players[i]->SetIsAiming(false);
							if (Joystick::GetButton(i, Joystick::Button::Circle))
							{
								players[i]->SetAbilityCooldown(PlayerObject::AbilityButton::Circle, 6);
							}
							if (Joystick::GetButton(i, Joystick::Button::Cross))
							{
								players[i]->SetAbilityCooldown(PlayerObject::AbilityButton::Cross, 6);
							}
							if (Joystick::GetButton(i, Joystick::Button::Triangle))
							{
								players[i]->SetAbilityCooldown(PlayerObject::AbilityButton::Triangle, 6);
							}
						}
					}


				}

			}	

			//Ability Triangle
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle))
			{
				if (players[i]->GetCooldown(PlayerObject::AbilityButton::Triangle) <= 0)
				{
					UsingAbilityKeyDown(i, PlayerObject::AbilityButton::Triangle);
				}
			}

			if (Joystick::GetButtonUp(i, Joystick::Button::Triangle)) {
				if (players[i]->GetCooldown(PlayerObject::AbilityButton::Triangle) <= 0)
				{
					UsingAbilityKeyUp(i, PlayerObject::AbilityButton::Triangle);
				}
			}

			//Ability Circle
			if (Joystick::GetButtonDown(i, Joystick::Button::Circle))
			{
				if (players[i]->GetCooldown(PlayerObject::AbilityButton::Circle) <= 0)
				{
					UsingAbilityKeyDown(i, PlayerObject::AbilityButton::Circle);
				}
			}

			if (Joystick::GetButtonUp(i, Joystick::Button::Circle)) {
				if (players[i]->GetCooldown(PlayerObject::AbilityButton::Circle) <= 0)
				{
					UsingAbilityKeyUp(i, PlayerObject::AbilityButton::Circle);
				}
			}

			//Ability Cross
			if (Joystick::GetButtonDown(i, Joystick::Button::Cross))
			{
				if (players[i]->GetCooldown(PlayerObject::AbilityButton::Cross) <= 0)
				{
					UsingAbilityKeyDown(i, PlayerObject::AbilityButton::Cross);
				}
			}

			if (Joystick::GetButtonUp(i, Joystick::Button::Cross))
			{
				if (players[i]->GetCooldown(PlayerObject::AbilityButton::Cross) <= 0)
				{
					UsingAbilityKeyUp(i, PlayerObject::AbilityButton::Cross);
				}
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{
				//players[i]->ChangeAnimationState(PlayerObject::AnimationState::Melee);
				players[i]->ChangeMeleeAnimation();
				players[i]->HitAimingTile();
				soundManager->PlaySFX("hit_test", false);
			}

			// Debug other player
			if (Joystick::GetButtonDown(i, Joystick::Button::R1))
			{

			}

			if (Joystick::GetButtonDown(i, Joystick::Button::P5Button))
			{
				GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELGAMEPLAY;
				GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
			}

			players[0]->Translate(players[0]->GetVelocity());
			players[1]->Translate(players[1]->GetVelocity());
			players[2]->Translate(players[2]->GetVelocity());
			players[3]->Translate(players[3]->GetVelocity());
		}

	}
}

void LevelShowcase::UpdateCollision()
{
	for (int i = 0; i < playerSize; i++)
	{
		players[i]->SetIsOnGround(false);
	}

	int entityCount = 0;
	for (int i = 0; i < entityObjects.size(); i++)
	{
		EntityObject* entity1 = entityObjects[i];
		TileObject* tile = dynamic_cast<TileObject*>(entityObjects[i]);

		if (entity1->GetCollider()->GetCollisionType() == Collider::Static ||
			tile != nullptr)
		{
			continue;
		}

		for (int j = 0; j < entityObjects.size(); j++)
		{
			entityCount++;
			
			if (i == j)
			{
				continue;
			}

			EntityObject* entity2 = entityObjects[j];

			Collider* col1 = entity1->GetCollider();
			Collider* col2 = entity2->GetCollider();

			float deltaX = entity1->getPos().x - entity2->getPos().x;
			float deltaY = entity1->getPos().y - entity2->getPos().y;
			glm::vec2 delta(abs(deltaX), abs(deltaY));

			float previousDeltaX = col1->GetPreviousPos().x - col2->GetPreviousPos().x;
			float previousDeltaY = col1->GetPreviousPos().y - col2->GetPreviousPos().y;
			glm::vec2 previousDelta(abs(previousDeltaX), abs(previousDeltaY));

			float halfSizeAbsX1 = abs(col1->GetHalfSize().x);
			float halfSizeAbsX2 = abs(col2->GetHalfSize().x);

			float halfSizeAbsY1 = abs(col1->GetHalfSize().y);
			float halfSizeAbsY2 = abs(col2->GetHalfSize().y);

			float overlapX = halfSizeAbsX1 + halfSizeAbsX2 - delta.x;

			float overlapY = halfSizeAbsY1 + halfSizeAbsY2 - delta.y;


			// for resolve collider
			float previousOverlapX = (abs(col1->GetHalfSize().x)) + (abs(col2->GetHalfSize().x)) - previousDelta.x;
			float previousOverlapY = (abs(col1->GetHalfSize().y)) + (abs(col2->GetHalfSize().y)) - previousDelta.y;

			if (overlapX > 0 && overlapY > 0)
			{

				if (previousCollisions.find({ col1, col2 }) == previousCollisions.end())
				{
					entity1->OnColliderEnter(entity2->GetCollider());
					// entity2->OnColliderEnter(entity1->GetCollider());
				}
				else
				{
					
					entity1->OnColliderStay(entity2->GetCollider());
					// entity2->OnColliderStay(entity1->GetCollider());
				}

				currentCollisions.insert({ col1, col2 });

				if (col1->GetCollisionType() == Collider::Kinematic &&
					col2->GetCollisionType() == Collider::Static)
				{
					glm::vec3 newPos(entity1->getPos().x, entity1->getPos().y, entity1->getPos().z);

					if (previousOverlapX > 0)
					{
						bool isTopSide = (col1->GetPreviousPos().y - col2->GetPreviousPos().y) > 0 ? true : false;

						newPos.y = entity1->getPos().y + (overlapY * (isTopSide ? 1 : -1));
					}
					if (previousOverlapY > 0)
					{
						bool isLeftSide = (col1->GetPreviousPos().x - col2->GetPreviousPos().x) < 0 ? true : false;
						newPos.x = entity1->getPos().x + (overlapX * (isLeftSide ? -1 : 1));
					}
					entity1->SetPosition(newPos);
				}
			}
			else if (overlapX <= 0 || overlapY <= 0)
			{
				if (previousCollisions.find({ col1, col2 }) != previousCollisions.end())
				{
					entity1->OnColliderExit(entity2->GetCollider());
					// entity2->OnColliderExit(entity1->GetCollider());
				}
			}

			entity2->GetCollider()->SetPreviousPos(entity2->getPos());
		}
		entity1->GetCollider()->SetPreviousPos(entity1->getPos());
	}

	// previousCollisions = currentCollisions;
	std::swap(previousCollisions, currentCollisions);
	currentCollisions.clear();


	if (frame > 10)
	{
		for (int i = 0; i < playerSize; i++)
		{
			players[i]->CheckIfOnGround();
			continue;
		}
	}
	
}

void LevelShowcase::UpdateProjectile()
{
	for (PlayerObject* player : players)
	{
		for (ProjectileObject* projectile : player->GetOwningProjectile())
		{
			//KK_TRACE("UpdateProjectile: Projectile check");
			projectile->ReduceLifeTime(timer->getDeltaTime());

			projectile->Translate(projectile->GetVelocity());

			
		}

		for (TrapObject* trap : player->GetOwningTrap())
		{
			//KK_TRACE("UpdateProjectile: trap check");
			if (trap->GetCanKnockback()) 
			{
				trap->SetIsActive(false);
				player->RemoveOwningTrap(trap);
			}
		}
	}
	
}

void LevelShowcase::UpdateCooldown()
{
	for (PlayerObject* player : players)
	{
		if (player->GetIsOnGround() == false)
		{
			continue;
		}

		player->UpdateAbilityCooldown(timer->getDeltaTime());
	}
}

void LevelShowcase::UpdateMovement()
{
	for (PlayerObject* player : players)
	{
		if (player->GetIsOnGround() == false)
		{
			continue;
		}

		if (player->GetIsKnockback() == true)
		{
			glm::vec3 knockbackVelo = player->GetVelocity();

			float knockbackVeloX = abs(knockbackVelo.x);
			float knockbackVeloY = abs(knockbackVelo.y);

			player->SetVelocity
			(
				knockbackVeloX / 1.01f,
				knockbackVeloY / 1.01f,
				player->GetXIsPositive(),
				player->GetYIsPositive()
			);

			KK_CORE_WARN("Set Velocity = {0}, {1}", knockbackVeloX, knockbackVeloY);
		}

		if (player->GetIsSlow() == true)
		{
			player->ReduceSlowDuration(timer->getDeltaTime());
		}

		if (player->GetIsKnockback() == true)
		{
			player->ReduceKnockbackDuration(timer->getDeltaTime());
		}

		if (player->GetIsStun() == true)
		{
			player->ReduceStunDuration(timer->getDeltaTime());

		}
		if (player->GetIsDashing() == true)
		{
			player->ReduceDashDuration(timer->getDeltaTime());
		}
	}
}


void LevelShowcase::UpdateTime() {

	timer->tick();
	//timer->reset();
	//KK_TRACE("timer->getDeltaTime() = {0}", timer->getDeltaTime());
	time1s += timer->getDeltaTime();
	time01s += timer->getDeltaTime();
	dt += timer->getDeltaTime();

	if (time1s >= 1.0f)
	{
		KK_INFO("UpdateTime() FPS: {0} time1s = {1}", framePerSecond, time1s);
		framePerSecond = 0;

		time1s = 0.0f;
	}

	if (time01s >= 0.1f)
	{
		time01s = 0.0f;
	}

}

void LevelShowcase::UpdateUI()
{
	int playerNumber = 4; // Change later
	float uiWidth = 215.f;
	float uiHeight = 100.f;
	
	float posX = camera.GetCenterX() - (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH / 2.f) * (playerNumber - 1);
	float posY = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + ((uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT) / 2.f);
	
	for (int i = 0; i < playerNumber; i++)
	{
		UiObject* ui = playerUIs[i];
		ui->SetPosition(glm::vec3(posX + (ui->getNumOwner() * uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH), posY, 0));
		ui->SetSize(uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);
	}
}

void LevelShowcase::LevelDraw()
{
	frame++;
	
	UpdateTime();

	// render image per frame cap
	if (dt >= targetFrameDuration)
	{
		framePerSecond++;

		// Collider position update
		for (int i = 0; i < entityObjects.size(); i++)
		{
			entityObjects[i]->UpdateCollider();
			
		}

		GameEngine::GetInstance()->Render(objectsList);

		dt = 0;
	}

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	if (ImGui::Button("Reset Scene", ImVec2(100, 50)))
		isResetScene++;
		
	if (isResetScene & 1)
	{
		GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELSHOWCASE;
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
	}
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	{
		for (int i = 0; i < playerSize; i++)
		{
			std::string tabname = "player " + std::to_string(i);
			ImGui::PushID(i);

			if (ImGui::BeginTabItem(tabname.c_str()))
			{
				ImGui::Text("Player %d", i);
				ImGui::SameLine();
				ImGui::SeparatorText("");
				ImGui::Text("Position: %f, %f, %f", players[i]->getPos().x, players[i]->getPos().y, players[i]->getPos().z);
				
				ImGui::Text("isShooting: %s", players[i]->GetIsShooting() ? "true" : "false");
				ImGui::Text("isAiming: %s", players[i]->GetIsAiming() ? "true" : "false");
				ImGui::Text("isSlow: %s", players[i]->GetIsSlow() ? "true" : "false");
				ImGui::Text("isDashing: %s", players[i]->GetIsDashing() ? "true" : "false");
				ImGui::Text("isKnockback: %s", players[i]->GetIsKnockback() ? "true" : "false");
				ImGui::Text("isStun: %s", players[i]->GetIsStun() ? "true" : "false");
				ImGui::Text("isOnGround: %s", players[i]->GetIsOnGround() ? "true" : "false");
				ImGui::Text("Current Velocity: %f, %f", players[i]->GetVelocity().x, players[i]->GetVelocity().y);

				ImGui::DragFloat("ColX Button", &groundColX[i], 2.0f, 0.0f, 1024.f, "%.3f");
				ImGui::DragFloat("ColY Button", &groundColY[i], 2.0f, 0.0f, 1024.f, "%.3f");
				ImGui::DragFloat("Col offset X", &groundColOffsetX[i], 2.0f, -1024.f, 1024.f, "%.3f");
				ImGui::DragFloat("Col offset Y", &groundColOffsetY[i], 2.0f, -1024.f, 1024.f, "%.3f");

				players[i]->GetGroundColliderObject()->SetCollisionOffset(glm::vec2(groundColOffsetX[i], groundColOffsetY[i]));
				/*Fireball = 0,
					Trap = 1,
					Dash = 2,
					TNT = 3,
					Teleport = 4,
					Bola = 5,
					Cleave = 6*/

				for (int j = 0; j < 3; j++)
				{
					ImGui::PushID(j);


					ImGui::Text("skill %d", j);
					ImGui::Text("ability %d cooldown: %.2f", i ,players[i]->GetCooldown(static_cast<PlayerObject::AbilityButton>(j)));
					ImGui::RadioButton("Fireball", &playersSkill[i][j], 0);
					ImGui::SameLine();
					ImGui::RadioButton("Trap", &playersSkill[i][j], 1);
					ImGui::SameLine();
					ImGui::RadioButton("Dash", &playersSkill[i][j], 2);
					//ImGui::SameLine();
					ImGui::RadioButton("TNT", &playersSkill[i][j], 3);
					ImGui::SameLine();
					ImGui::RadioButton("Teleport", &playersSkill[i][j], 4);
					ImGui::SameLine();
					ImGui::RadioButton("Bola", &playersSkill[i][j], 5);
					ImGui::SameLine();
					ImGui::RadioButton("Cleave", &playersSkill[i][j], 6);
					ImGui::SeparatorText("");

					ImGui::PopID();
				}
				ImGui::EndTabItem();
			}
			
			ImGui::PopID();
		}
		
		ImGui::EndTabBar();
	}
	
	for (int i = 0; i < playerSize; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			players[i]->SetAbility
			(
				static_cast<PlayerObject::AbilityButton>(j), 
				static_cast<PlayerObject::Ability>(playersSkill[i][j])
			);
		}
	}

	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());


	// cout << "Draw Level" << endl;
}

void LevelShowcase::LevelFree()
{
	// Clean up DrawableObjects
	for (auto obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	entityObjects.clear();
	currentCollisions.clear();
	previousCollisions.clear();
	spriteList.clear();

	//cout << "Free Level" << endl;
}

void LevelShowcase::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//cout << "Unload Level" << endl;
}

void LevelShowcase::HandleKey(char key)
{

}

void LevelShowcase::HandleMouse(int type, int x, int y)
{

}

void LevelShowcase::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY)
{

}

void LevelShowcase::GroundTileRefactor()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (i == 0 ||
				i == MAP_HEIGHT - 1 ||
				j == 0 ||
				j == MAP_WIDTH - 1)
			{
				continue;
			}

			if (tilesList[i][j] == nullptr)
			{
				continue;
			}

			// currentGroundTile[i][j] = tilesList[i][j]->GetIsBroke() ? 0 : 1;


			int flag = currentGroundTile[i][j];


			std::pair<int, int> pos;

			if (i == 0 ||
				i == MAP_HEIGHT - 1 ||
				j == 0 ||
				j == MAP_WIDTH - 1)
			{
				continue;
			}
			else if (flag == 0)
			{
				// tilesList[i][j]->GetCollider()->GetGizmos()->SetIsActive(false);
				tilesList[i][j]->DisableOverlaySprite();

				if (currentGroundTile[i - 1][j] == 0)
				{
					// blank
					pos = { 99, 99 };
				}
				else
				{
					
					int upperPos = i - 1;

					std::bitset<8> surround;
					surround[0] = currentGroundTile[upperPos - 1][j];
					surround[1] = currentGroundTile[upperPos - 1][j + 1];
					surround[2] = currentGroundTile[upperPos][j + 1];
					surround[3] = currentGroundTile[upperPos + 1][j + 1];
					surround[4] = currentGroundTile[upperPos + 1][j];
					surround[5] = currentGroundTile[upperPos + 1][j - 1];
					surround[6] = currentGroundTile[upperPos][j - 1];
					surround[7] = currentGroundTile[upperPos - 1][j - 1];

					if (!(surround[0] && surround[2])) { surround[1] = 0; }
					if (!(surround[2] && surround[4])) { surround[3] = 0; }
					if (!(surround[4] && surround[6])) { surround[5] = 0; }
					if (!(surround[6] && surround[0])) { surround[7] = 0; }

					auto it = blob_lookup_table_underground.find((int)(surround.to_ulong()));

					// std::cout << "Bitset = " << (int)surround.to_ulong() << std::endl;

					if (it != blob_lookup_table_underground.end())
					{
						pos = it->second;

						// std::cout << "pair = " << it->second.first << " " << it->second.second << std::endl;
					}
					else
					{
						pos = { 99, 99 };
						// std::cout << "blob_lookup_table.end()" << std::endl;
					}
				}

			}
			else
			{
				std::bitset<8> surround;
				surround[0] = currentGroundTile[i - 1][j];
				surround[1] = currentGroundTile[i - 1][j + 1];
				surround[2] = currentGroundTile[i][j + 1];
				surround[3] = currentGroundTile[i + 1][j + 1];
				surround[4] = currentGroundTile[i + 1][j];
				surround[5] = currentGroundTile[i + 1][j - 1];
				surround[6] = currentGroundTile[i][j - 1];
				surround[7] = currentGroundTile[i - 1][j - 1];

				if (!(surround[0] && surround[2])) { surround[1] = 0; }
				if (!(surround[2] && surround[4])) { surround[3] = 0; }
				if (!(surround[4] && surround[6])) { surround[5] = 0; }
				if (!(surround[6] && surround[0])) { surround[7] = 0; }

				auto it = blob_lookup_table.find((int)(surround.to_ulong()));
				// std::cout << "Bitset = " << (int)surround.to_ulong() << std::endl;
				if (it != blob_lookup_table.end())
				{
					pos = it->second;

					// std::cout << "pair = " << it->second.first << " " << it->second.second << std::endl;
				}
				else {
					pos = { 99, 99 };
					// std::cout << "blob_lookup_table.end()" << std::endl;
				}
			}

			// std::cout << flag << ",";

			if (pos.first != 99)
			{
				tilesList[i][j]->GetSpriteRenderer()->ShiftTo(pos.first - 1, pos.second - 1);
			}
			else
			{
				tilesList[i][j]->SetIsActive(false);
			}


			// std::cout << "posX = " << obj->getPos().x << " posY = " << obj->getPos().y << std::endl;
		}
		// std::cout << std::endl;
	}
}

void LevelShowcase::TileImport(std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> &TileBuffer, std::string fileName) 
{
	std::ifstream mapfile(fileName);
	std::string line;
	int row = 0;
	int column = 1;
	if (!mapfile.is_open()) {
		// error
		std::cout << "Error: reading tile information" << std::endl;
	}
	else {
		int counter = 0;
		while (!mapfile.eof()) {
			//string line;
			if (getline(mapfile, line, ',')) {

				TileBuffer[counter / MAP_WIDTH][counter % MAP_WIDTH] = std::stoi(line);

				counter++;
			}
		}
		mapfile.close();

	}
}

void LevelShowcase::UsingAbilityKeyDown(int numPlayer, PlayerObject::AbilityButton button) {

	PlayerObject::Ability idAbility = players[numPlayer]->GetAbilityByButton(button);
	// std::cout << "idAbility " << idAbility << std::endl;
	if (players[numPlayer]->GetCooldown(button) <= 0) 
	{
		switch (idAbility) 
		{

		case PlayerObject::Ability::Fireball:

			if (!players[numPlayer]->GetIsAiming()) 
			{
				AimFireball(numPlayer, button);
				
				break;
			}
			break;

		case PlayerObject::Ability::Trap:
			Trap(numPlayer, button);
			break;

		case PlayerObject::Ability::Dash:
			Dash(numPlayer, button);
			break;

		case PlayerObject::Ability::TNT:

			if (!players[numPlayer]->GetIsTNT()) 
			{
				TNT(numPlayer, button);
			}
			else if (players[numPlayer]->GetIsTNT()) 
			{
				for (TrapObject* trap : players[numPlayer]->GetOwningTrap()) // find tnt
				{
					if (trap->GetType() == TrapObject::TypeTrap::Tnt) 
					{
						trap->ExplodeTileInRange();
						KK_TRACE("Press Again");
						trap->isActivate = true;
						players[numPlayer]->SetAbilityCooldown(button, 3);
						players[numPlayer]->SetIsTNT(false);
					}
				}
			}
			break;

		case PlayerObject::Ability::Teleport:

			if (!players[numPlayer]->GetIsAiming()) 
			{
				if (players[numPlayer]->GetIsShooting())
				{
					for (ProjectileObject* projectile : players[numPlayer]->GetOwningProjectile())
					{
						if (projectile->GetType() == ProjectileObject::TypeProjectile::Teleport)
						{
								players[numPlayer]->SetPosition(projectile->getPos());
								players[numPlayer]->SetIsShooting(false);
								projectile->SetIsActive(false);
								players[numPlayer]->SetAbilityCooldown(button, 6);
								players[numPlayer]->RemoveOwningProjectile(projectile);
						}
					}
				}
				else
				{
					AimTeleport(numPlayer, button);
				}
			}
			break;

		case PlayerObject::Ability::Bola:

			if (!players[numPlayer]->GetIsAiming()) 
			{
				AimBola(numPlayer, button);
				break;
			}
			
			break;

		case PlayerObject::Ability::Cleave:

			if (!players[numPlayer]->GetIsAiming()) 
			{
				AimCleave(numPlayer, button);
				break;
			}
			break;
		}
	}
}

void LevelShowcase::UsingAbilityKeyUp(int numPlayer, PlayerObject::AbilityButton button) 
{
	PlayerObject::Ability idAbility = players[numPlayer]->GetAbilityByButton(button);
	// std::cout << "idAbility " << idAbility << std::endl;
	if (players[numPlayer]->GetCooldown(button) <= 0) {
		switch (idAbility) {

		case PlayerObject::Ability::Fireball:
			if (players[numPlayer]->GetIsAiming())
			{
				if (players[numPlayer]->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Fireball) {
					ShootFireball(numPlayer, button);
					break;
				}

			}
			break;

		case PlayerObject::Ability::Teleport:
			if (players[numPlayer]->GetIsAiming())
			{
				if (players[numPlayer]->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Teleport) {
					ShootTeleport(numPlayer, button);
					break;
				}

			}
			break;

		case PlayerObject::Ability::Bola:
			if (players[numPlayer]->GetIsAiming())
			{
				if (players[numPlayer]->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Bola) {
					ShootBola(numPlayer, button);
					break;
				}

			}
			break;
		}

	}
}

void LevelShowcase::AimFireball(int numPlayer, PlayerObject::AbilityButton button)
{
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Fireball);
	//players[numPlayer]->ChangeAnimationState(PlayerObject::AnimationState::Cast);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Bomb")->second);
	projectile->SetTexture(spriteList.find("Bomb")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Fireball);
	projectile->SetCanKnockback(true);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	//projectile->SetIsActive(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	entityObjects.push_back(projectile);
	objectsList.push_back(projectile);
	players[numPlayer]->AddOwningProjectile(projectile);
	//objectsList.push_back(projectile->GetCollider()->GetGizmos());
}

void LevelShowcase::ShootFireball(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsAiming(false);
	for (int j = 0; j < objectsList.size(); j++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
		if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Fireball) {
			projectile->SetLifeTime(1);
			projectile->SetIsShooting(true);
			//projectile->SetIsActive(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, 6);
}

void LevelShowcase::Trap(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->ChangeAnimationState(PlayerObject::AnimationState::PlaceItem);
	players[numPlayer]->SetAbilityCooldown(button, 3);
	TrapObject* Trap = new TrapObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->SetTexture(spriteList.find("Trap")->second.texture);
	Trap->SetPosition(players[numPlayer]->getPos());
	Trap->SetSize(128.f, -128.f);
	Trap->SetPlayerNumber(players[numPlayer]->GetPlayerNumber());
	Trap->SetType(TrapObject::TypeTrap::Trap);
	Trap->SetIsActive(true);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(Trap);
	entityObjects.push_back(Trap);
	players[numPlayer]->AddOwningTrap(Trap);
	//std::cout << "place trap" << std::endl;
}

void LevelShowcase::Dash(int num, PlayerObject::AbilityButton button) {
	players[num]->SetAbilityCooldown(button, 3);
	players[num]->SetIsDashing(true);
	players[num]->SetDashDuration(0.4f);
}

void LevelShowcase::TNT(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsTNT(true);
	players[numPlayer]->ChangeAnimationState(PlayerObject::AnimationState::PlaceItem);
	TrapObject* TNT = new TrapObject();
	TNT->SetSpriteInfo(spriteList.find("TNT")->second);
	TNT->SetTexture(spriteList.find("TNT")->second.texture);
	TNT->SetPosition(players[numPlayer]->getPos());
	TNT->SetSize(128.f, -128.f);
	TNT->GetCollider()->setColliderSize(glm::vec3(500.f, 500.f, 0));
	TNT->SetPlayerNumber(players[numPlayer]->GetPlayerNumber());
	TNT->SetType(TrapObject::TypeTrap::Tnt);
	//TNT->GetCollider()->Update(glm::vec3(0, 0, 0), TNT->getPos());
	//TNT->setIsCanKnockback(true);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(TNT);
	entityObjects.push_back(TNT);
	objectsList.push_back(TNT->GetCollider()->GetGizmos());
	players[numPlayer]->AddOwningTrap(TNT);
}

void LevelShowcase::AimTeleport(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Teleport);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Teleport")->second);
	projectile->SetTexture(spriteList.find("Teleport")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Teleport);
	projectile->SetCanKnockback(false);
	projectile->SetIsCanStun(false);
	projectile->SetIsShooting(false);
	//projectile->SetIsActive(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	entityObjects.push_back(projectile);
	players[numPlayer]->AddOwningProjectile(projectile);
}

void LevelShowcase::ShootTeleport(int numPlayer, PlayerObject::AbilityButton button) {
	if (players[numPlayer]->GetIsShooting() == false) {
		players[numPlayer]->SetIsShooting(true);
		players[numPlayer]->SetIsAiming(false);
		for (int j = 0; j < objectsList.size(); j++) {
			ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
			if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Teleport) {
				projectile->SetLifeTime(2);
				projectile->SetIsShooting(true);
				//projectile->SetIsActive(true);
				players[numPlayer]->SetHoldingProjectile(0);
			}
		}
	}
}

void LevelShowcase::AimBola(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Bola);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Bola")->second);
	projectile->SetTexture(spriteList.find("Bola")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Bola);
	projectile->SetCanKnockback(false);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	//projectile->SetIsActive(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	entityObjects.push_back(projectile);
	players[numPlayer]->AddOwningProjectile(projectile);
}

void LevelShowcase::ShootBola(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsAiming(false);
	for (int j = 0; j < objectsList.size(); j++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
		if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Bola) {
			projectile->SetLifeTime(2);
			projectile->SetIsShooting(true);
			//projectile->SetIsActive(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, 6);
}

void LevelShowcase::AimCleave(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Cleave);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Cleave")->second);
	projectile->SetTexture(spriteList.find("Cleave")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Cleave);
	projectile->SetCanKnockback(false);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	//projectile->SetIsActive(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	entityObjects.push_back(projectile);
	players[numPlayer]->SetAbilityCooldown(button, 6);
	players[numPlayer]->AddOwningProjectile(projectile);
}

void LevelShowcase::ShootCleave(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsAiming(false);
	for (int j = 0; j < objectsList.size(); j++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
		if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Cleave) {
			projectile->SetLifeTime(2);
			projectile->SetIsShooting(true);
			//projectile->SetIsActive(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, 6);
}