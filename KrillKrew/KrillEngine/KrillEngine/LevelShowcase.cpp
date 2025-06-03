#include "LevelShowcase.h"

bool compareLayer(const DrawableObject* a, const DrawableObject* b)
{
	return a->getOrderingLayer() > b->getOrderingLayer();
}

float SmoothStep(float t)
{
	float v1 = t * t;
	float v2 = 1.0 - ((1.0 - t) * (1.0 - t));
	return v1 + t * (v2);
}

float ElasticOut(float t)
{
	float output = std::sin(-13.0 * (t + 1.0) * 3.14 / 2) * std::pow(2.0, -10.0 * t) + 1.0;
	return output;
}

float Parabola(float t)
{
	float output = std::pow((t / 2.f) - 1.5f, 2) - 0.15f;
	return output;
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

	// Item
	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Ability/abi_spr_bomb_projecttile.png", 300, 300, 1800, 300, true);
	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Ability/abi_spr_jellyfish_putdown.png", 256, 256, 4096, 256, false);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/Ability/abi_spr_landmine_idle.png", 370, 370, 740, 370, true);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/Ability/abi_spr_teleport_projectile.png", 211, 97, 422, 97, true);
	spriteList["Bola"] = SpritesheetInfo("Bola", "../Resource/Texture/Ability/abi_spr_stun_projecttile.png", 400, 400, 1600, 400, true);
	spriteList["Cleave"] = SpritesheetInfo("Cleave", "../Resource/Texture/Ability/abi_spr_cleave_side.png", 358, 258, 1074, 258, true);

	spriteList["Bomb_Explode"] = SpritesheetInfo("Bomb_Explode",					"../Resource/Texture/Ability/abi_spr_bomb_explosion.png", 498, 498, 2490, 498, false);
	spriteList["Landmine_Explode"] = SpritesheetInfo("Landmine_Explode",			"../Resource/Texture/Ability/abi_spr_landmine_explosion.png", 370, 370, 2590, 370, false);
	spriteList["Teleport_Explode"] = SpritesheetInfo("Teleport_Explode",			"../Resource/Texture/Ability/abi_spr_teleport_explosion.png", 250, 250, 1000, 250, false);
	spriteList["Stun_Explode"] = SpritesheetInfo("Stun_Explode",					"../Resource/Texture/Ability/abi_spr_stun_explosion.png", 400, 400, 1600, 400, false);
	spriteList["Trap_Explode"] = SpritesheetInfo("Trap_Explode",					"../Resource/Texture/Ability/abi_spr_jellyfish_explosion.png", 332, 332, 4316, 332, false);
	
	spriteList["Xoey_UI"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	spriteList["Byssa_UI"] = SpritesheetInfo("Byssa_UI", "../Resource/Texture/byssa.png", 430, 220, 430, 220);
	spriteList["Crunk_UI"] = SpritesheetInfo("Crunk_UI", "../Resource/Texture/crunk.png", 430, 220, 430, 220);
	spriteList["Ham_UI"] = SpritesheetInfo("Ham_UI", "../Resource/Texture/Ham.png", 430, 220, 430, 220);

	spriteList["Player_UI"] = SpritesheetInfo("Player_UI", "../Resource/Texture/Gameplay/UI_GP_PlayerWindow.png", 420, 116, 1680, 116);
	spriteList["AbilityGameplay_UI"] = SpritesheetInfo("AbilityGameplay_UI", "../Resource/Texture/Gameplay/UI_GP_Abilityicon.png", 69, 69, 552, 69);
	spriteList["AbilityCover_UI"] = SpritesheetInfo("AbilityCover_UI", "../Resource/Texture/Gameplay/UI_GP_Abilityicon_black.png", 69, 69, 69, 69);

	spriteList["Blobtile"] = SpritesheetInfo("Blobtile", "../Resource/Texture/tileset_01.png", 128, 128, 1664, 512);

	// Prop
	spriteList["Prop_A"] = SpritesheetInfo("Prop_A", "../Resource/Texture/Props/prop_A.png", 170, 170, 1020, 170);
	spriteList["Prop_B"] = SpritesheetInfo("Prop_B", "../Resource/Texture/Props/prop_B.png", 123, 123, 369, 170);
	spriteList["Prop_C"] = SpritesheetInfo("Prop_C", "../Resource/Texture/Props/prop_C.png", 91, 91, 637, 91);

	spriteList["Tree_A"] = SpritesheetInfo("Tree_A", "../Resource/Texture/Props/prop_spr_CoconutTree_A.png", 300, 400, 900, 400, true);
	spriteList["Tree_B"] = SpritesheetInfo("Tree_B", "../Resource/Texture/Props/prop_spr_CoconutTree_B.png", 250, 370, 750, 370, true);

	spriteList["Leaf1_Collapse"] = SpritesheetInfo("Tree_B", "../Resource/Texture/Props/prop_spr_vfx_leaf.png", 200, 200, 800, 200);
	spriteList["Leaf2_Collapse"] = SpritesheetInfo("Tree_B", "../Resource/Texture/Props/prop_spr_vfx_smallleaf.png", 120, 120, 480, 120);

	spriteList["CollapseTile"] = SpritesheetInfo("CollapseTile", "../Resource/Texture/Props/prop_spr_vfx_smoke.png", 200, 200, 800, 200);

	spriteList["DangerSign"] = SpritesheetInfo("DangerSign", "../Resource/Texture/Gameplay/UI_GP_Event_DangerSign.png", 544, 215, 544, 215);

	spriteList["Pause_BG"] = SpritesheetInfo("Pause_BG", "../Resource/Texture/Menu/Pause/UI_Pause_BG.png", 623, 671, 623, 671);
	spriteList["Pause_text"] = SpritesheetInfo("Pause_text", "../Resource/Texture/Menu/Pause/UI_Pause_text.png", 300, 70, 1800, 70);

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

	//KK_TRACE("Generate Map-----------{0}", totalLoadedTile);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			currentLoadedTile++;
			//KK_CORE_TRACE("Generate Map-----------{0}%", 100.f * currentLoadedTile / totalLoadedTile);

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
				obj->LocateCurrentLevel(this);

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
				//objectsList.push_back(obj->GetCollider()->GetGizmos());
				objectsList.push_back(obj->GetOverlaySprite());

				
			}
			
		}
	}
}

void LevelShowcase::InitProp()
{
	srand(time(0));

	float map_left = -1280.f;
	float map_top = 1080.f;

	int tileCount = 0;

	float totalLoadedTile = MAP_HEIGHT * MAP_WIDTH;
	float currentLoadedTile = 0;

	//KK_TRACE("Generate Prop-----------{0}", totalLoadedTile);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			currentLoadedTile++;
			//KK_CORE_TRACE("Generate Prop-----------{0}%", 100.f * currentLoadedTile / totalLoadedTile);

			int flag = propsTile[i][j];

			//KK_CORE_TRACE("flag = {0}", flag);
			
			if (flag == 0)
			{
				continue;
			}

			PropObject* obj = new PropObject();
			//obj->SetTexture(spriteList.find("Blobtile")->second.texture);
			
			obj->SetPosition(glm::vec3(map_left + (j * 126.f), map_top - (i * 126.f), 0));
			obj->LocateCurrentLevel(this);
			propObjects.push_back(obj);

			int randnum = 0;

			switch (flag)
			{
			case 1:
				obj->SetTextureWithID(spriteList.find("Prop_A")->second, spriteList.find("Prop_A")->second.textureid);
				obj->SetSize(170.f, -170.f);
				randnum = rand() % 6;
				obj->GetSpriteRenderer()->ShiftTo(0, randnum);
				obj->propType = PropObject::PropType::Small;
				obj->propBreakSprite = spriteList.find("CollapseTile")->second;
				obj->SetIsBreakable(true);
				break;
			case 2:
				obj->SetTextureWithID(spriteList.find("Prop_B")->second, spriteList.find("Prop_B")->second.textureid);
				obj->SetSize(123.f, -123.f);
				randnum = rand() % 3;
				obj->GetSpriteRenderer()->ShiftTo(0, randnum);
				obj->propType = PropObject::PropType::Small;
				obj->propBreakSprite = spriteList.find("CollapseTile")->second;
				obj->SetIsBreakable(true);
				break;
			case 3:
				obj->SetTextureWithID(spriteList.find("Prop_C")->second, spriteList.find("Prop_C")->second.textureid);
				obj->SetSize(91.f, -91.f);
				randnum = rand() % 7;
				obj->GetSpriteRenderer()->ShiftTo(0, randnum);
				obj->propType = PropObject::PropType::Tiny;
				obj->propBreakSprite = spriteList.find("Leaf1_Collapse")->second;
				obj->SetIsBreakable(false);
				break;
			case 4:
				obj->SetTextureWithID(spriteList.find("Tree_A")->second, spriteList.find("Tree_A")->second.textureid);
				obj->SetSize(450.f, -600.f);
				obj->GetSpriteRenderer()->ShiftTo(0, 0);
				obj->propType = PropObject::PropType::Tree;
				obj->propBreakSprite = spriteList.find("Leaf2_Collapse")->second;
				obj->GetCollider()->SetOffset(0, -270.f, 0);
				obj->SetIsAnimated(true);
				obj->SetIsBreakable(true);
				break;
			case 5:
				obj->SetTextureWithID(spriteList.find("Tree_B")->second, spriteList.find("Tree_B")->second.textureid);
				obj->SetSize(375.f, -555.f);
				obj->GetSpriteRenderer()->ShiftTo(0, 0);
				obj->propType = PropObject::PropType::Tree;
				obj->propBreakSprite = spriteList.find("Leaf2_Collapse")->second;
				obj->GetCollider()->SetOffset(0, -250.5f, 0);
				obj->SetIsAnimated(true);
				obj->SetIsBreakable(true);
				break;
			}

			entityObjects.push_back(obj);
			tileCount++;
			objectsList.push_back(obj);

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

	TileImport(groundTile, "../Resource/MapFile/Tilemap0.txt");
	TileImport(currentGroundTile, "../Resource/MapFile/Tilemap0.txt");
	TileImport(propsTile, "../Resource/MapFile/Propmap0.txt");
	TileImport(currentPropTile, "../Resource/MapFile/Propmap0.txt");

	// Create and Initialize 4 players object

	for (auto& info : spriteList)
	{
		unsigned int texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(info.second.texture);
		info.second.textureid = texture;
		KK_CORE_TRACE("Load Texture: {0}", texture);
	}

	InitTile();
	InitProp();

	// Example Code

	//KK_TRACE("Init Player-----------");
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

	// std::ifstream readFile("Ability0.txt");
	// while (std::getline(readFile, line)) {
	// 	data[count] = line;
	// 	abilityId[count] = stoi(data[count]);
	// 	count++;
	// }
	// if (count < 3) {
	// 	abilityId[0] = 0;
	// 	abilityId[1] = 1;
	// 	abilityId[2] = 2;
	// 	count = 0;
	// }
	// else {
	// 	count = 0;
	// }

	std::ifstream readFile("Ability0.json");
	loadAbility("Ability0.json");
	readFile.close();

	KK_TRACE("abilityId[0] = {0}", abilityId[0]);
	KK_TRACE("abilityId[1] = {0}", abilityId[1]);
	KK_TRACE("abilityId[2] = {0}", abilityId[2]);

	playersSkill[0][0] = abilityId[0];
	playersSkill[0][1] = abilityId[1];
	playersSkill[0][2] = abilityId[2];

	p1->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p1->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p1->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));
	p1->SetTextureWithID(spriteList.find("P1_Idle")->second, spriteList.find("P1_Idle")->second.textureid);
	p1->SetPosition(glm::vec3(-400.f, -400.f, 0.f));
	p1->GetSpriteRenderer()->SetFrame(16);
	p1->SetPlayerNumber(0);
	p1->LocateCurrentLevel(this);
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
	// std::ifstream read2File("Ability1.txt");
	// while (std::getline(read2File, line)) {
	// 	data[count] = line;
	// 	abilityId[count] = stoi(data[count]);
	// 	count++;
	// }
	// if (count < 3) {
	// 	abilityId[0] = 0;
	// 	abilityId[1] = 1;
	// 	abilityId[2] = 2;
	// 	count = 0;
	// }
	// else {
	// 	count = 0;
	// }

	std::ifstream read2File("Ability1.json");
	loadAbility("Ability1.json");
	read2File.close();

	playersSkill[1][0] = abilityId[0];
	playersSkill[1][1] = abilityId[1];
	playersSkill[1][2] = abilityId[2];

	KK_TRACE("abilityId[0] = {0}", abilityId[0]);
	KK_TRACE("abilityId[1] = {0}", abilityId[1]);
	KK_TRACE("abilityId[2] = {0}", abilityId[2]);

	p2->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p2->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p2->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));

	p2->SetTextureWithID(spriteList.find("P2_Idle")->second, spriteList.find("P2_Idle")->second.textureid);
	p2->SetPosition(glm::vec3(400.f, -400.f, 0));
	p2->GetSpriteRenderer()->SetFrame(16);
	p2->SetPlayerNumber(1);
	p2->LocateCurrentLevel(this);
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

	// std::ifstream read3File("Ability2.txt");
	// while (std::getline(read3File, line)) {
	// 	data[count] = line;
	// 	abilityId[count] = stoi(data[count]);
	// 	count++;
	// }
	// if (count < 3) {
	// 	abilityId[0] = 0;
	// 	abilityId[1] = 1;
	// 	abilityId[2] = 2;
	// 	count = 0;
	// }
	// else {
	// 	count = 0;
	// }
	
	std::ifstream read3File("Ability2.json");
	loadAbility("Ability2.json");
	read3File.close();

	KK_TRACE("abilityId[0] = {0}", abilityId[0]);
	KK_TRACE("abilityId[1] = {0}", abilityId[1]);
	KK_TRACE("abilityId[2] = {0}", abilityId[2]);

	playersSkill[2][0] = abilityId[0];
	playersSkill[2][1] = abilityId[1];
	playersSkill[2][2] = abilityId[2];

	p3->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p3->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p3->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));
	p3->SetTextureWithID(spriteList.find("P3_Idle")->second, spriteList.find("P3_Idle")->second.textureid);
	p3->SetPosition(glm::vec3(400.f, 400.f, 0));
	p3->GetSpriteRenderer()->SetFrame(16);
	p3->SetPlayerNumber(2);
	p3->LocateCurrentLevel(this);
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

	// std::ifstream read4File("Ability3.txt");
	// while (std::getline(read4File, line)) {
	// 	data[count] = line;
	// 	abilityId[count] = stoi(data[count]);
	// 	count++;
	// }
	// if (count < 3) {
	// 	abilityId[0] = 0;
	// 	abilityId[1] = 1;
	// 	abilityId[2] = 2;
	// 	count = 0;
	// }
	// else {
	// 	count = 0;
	// }
	
	
	std::ifstream read4File("Ability3.json");
	loadAbility("Ability3.json");
	read4File.close();

	KK_TRACE("abilityId[0] = {0}", abilityId[0]);
	KK_TRACE("abilityId[1] = {0}", abilityId[1]);
	KK_TRACE("abilityId[2] = {0}", abilityId[2]);

	playersSkill[3][0] = abilityId[0];
	playersSkill[3][1] = abilityId[1];
	playersSkill[3][2] = abilityId[2];

	p4->SetAbility(PlayerObject::AbilityButton::Triangle, static_cast<PlayerObject::Ability>(abilityId[0]));
	p4->SetAbility(PlayerObject::AbilityButton::Circle, static_cast<PlayerObject::Ability>(abilityId[1]));
	p4->SetAbility(PlayerObject::AbilityButton::Cross, static_cast<PlayerObject::Ability>(abilityId[2]));
	p4->SetTextureWithID(spriteList.find("P4_Idle")->second, spriteList.find("P4_Idle")->second.textureid);
	p4->SetPosition(glm::vec3(-400.f, 400.f, 0));
	p4->GetSpriteRenderer()->SetFrame(16);
	p4->SetPlayerNumber(3);
	p4->LocateCurrentLevel(this);
	entityObjects.push_back(p4);
	objectsList.push_back(p4);
	playerSize++;
	players[3] = p4;

	for (int i = 0; i < playerSize; i++)
	{
		entityObjects.push_back(players[i]->GetAttackColliderObject());
		objectsList.push_back(players[i]->GetAttackColliderObject());
		//objectsList.push_back(players[i]->GetAttackCollider()->GetGizmos());
		//objectsList.push_back(players[i]->GetCollider()->GetGizmos());

		entityObjects.push_back(players[i]->GetGroundColliderObject());
		//objectsList.push_back(players[i]->GetGroundCollider()->GetGizmos());
	}

	//create Ui by PlayerObject
	//int playerSize = playerSize;
	//KK_TRACE("Init UI-----------");
	//count = 0;

	if (playerSize >= 0) {

		KK_TRACE("playersSkill[0][0] = {0}", playersSkill[0][0]);
		KK_TRACE("playersSkill[0][1] = {0}", playersSkill[0][1]);
		KK_TRACE("playersSkill[0][2] = {0}", playersSkill[0][2]);
		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Player_UI")->second);
		uiSkills->GetSpriteRenderer()->ShiftTo(0, 0);
		uiSkills->setNumOwner(0);
		objectsList.push_back(uiSkills);
		playerUIs[0] = uiSkills;

		//playerSkillUIs AbilityGameplay_UI
		UiObject* uiSkills1 = new UiObject();
		uiSkills1->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills1->GetSpriteRenderer()->ShiftTo(0, playersSkill[0][0]);
		uiSkills1->setNumOwner(0);
		objectsList.push_back(uiSkills1);
		playerSkillUIs[0][0] = uiSkills1;

		UiObject* uiSkills2 = new UiObject();
		uiSkills2->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills2->GetSpriteRenderer()->ShiftTo(0, playersSkill[0][1]);
		uiSkills2->setNumOwner(0);
		objectsList.push_back(uiSkills2);
		playerSkillUIs[0][1] = uiSkills2;

		UiObject* uiSkills3 = new UiObject();
		uiSkills3->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills3->GetSpriteRenderer()->ShiftTo(0, playersSkill[0][2]);
		uiSkills3->setNumOwner(0);
		objectsList.push_back(uiSkills3);
		playerSkillUIs[0][2] = uiSkills3;

		uiSkills1->uiType = UiObject::UIType::SkillIcon;
		uiSkills2->uiType = UiObject::UIType::SkillIcon;
		uiSkills3->uiType = UiObject::UIType::SkillIcon;

		

	}
	if (playerSize >= 1) {

		KK_TRACE("playersSkill[1][0] = {0}", playersSkill[1][0]);
		KK_TRACE("playersSkill[1][1] = {0}", playersSkill[1][1]);
		KK_TRACE("playersSkill[1][2] = {0}", playersSkill[1][2]);
		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Player_UI")->second);
		uiSkills->GetSpriteRenderer()->ShiftTo(0, 1);
		uiSkills->setNumOwner(1);
		objectsList.push_back(uiSkills);
		playerUIs[1] = uiSkills;

		//playerSkillUIs AbilityGameplay_UI
		UiObject* uiSkills1 = new UiObject();
		uiSkills1->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		
		uiSkills1->GetSpriteRenderer()->ShiftTo(0, playersSkill[1][0]);
		uiSkills1->setNumOwner(1);
		objectsList.push_back(uiSkills1);
		playerSkillUIs[1][0] = uiSkills1;

		UiObject* uiSkills2 = new UiObject();
		uiSkills2->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills2->GetSpriteRenderer()->ShiftTo(0, playersSkill[1][1]);
		uiSkills2->setNumOwner(1);
		objectsList.push_back(uiSkills2);
		playerSkillUIs[1][1] = uiSkills2;

		UiObject* uiSkills3 = new UiObject();
		uiSkills3->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills3->GetSpriteRenderer()->ShiftTo(0, playersSkill[1][2]);
		uiSkills3->setNumOwner(1);
		objectsList.push_back(uiSkills3);
		playerSkillUIs[1][2] = uiSkills3;

		uiSkills1->uiType = UiObject::UIType::SkillIcon;
		uiSkills2->uiType = UiObject::UIType::SkillIcon;
		uiSkills3->uiType = UiObject::UIType::SkillIcon;
	}
	if (playerSize >= 2) {

		KK_TRACE("playersSkill[2][0] = {0}", playersSkill[2][0]);
		KK_TRACE("playersSkill[2][1] = {0}", playersSkill[2][1]);
		KK_TRACE("playersSkill[2][2] = {0}", playersSkill[2][2]);

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Player_UI")->second);
		uiSkills->GetSpriteRenderer()->ShiftTo(0, 2);
		uiSkills->setNumOwner(2);
		objectsList.push_back(uiSkills);
		playerUIs[2] = uiSkills;

		//playerSkillUIs AbilityGameplay_UI
		UiObject* uiSkills1 = new UiObject();
		uiSkills1->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills1->GetSpriteRenderer()->ShiftTo(0, playersSkill[2][0]);
		uiSkills1->setNumOwner(2);
		objectsList.push_back(uiSkills1);
		playerSkillUIs[2][0] = uiSkills1;

		UiObject* uiSkills2 = new UiObject();
		uiSkills2->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills2->GetSpriteRenderer()->ShiftTo(0, playersSkill[2][1]);
		uiSkills2->setNumOwner(2);
		objectsList.push_back(uiSkills2);
		playerSkillUIs[2][1] = uiSkills2;

		UiObject* uiSkills3 = new UiObject();
		uiSkills3->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills3->GetSpriteRenderer()->ShiftTo(0, playersSkill[2][2]);
		uiSkills3->setNumOwner(2);
		objectsList.push_back(uiSkills3);
		playerSkillUIs[2][2] = uiSkills3;

		uiSkills1->uiType = UiObject::UIType::SkillIcon;
		uiSkills2->uiType = UiObject::UIType::SkillIcon;
		uiSkills3->uiType = UiObject::UIType::SkillIcon;
	}
	if (playerSize >= 3) {

		KK_TRACE("playersSkill[3][0] = {0}", playersSkill[3][0]);
		KK_TRACE("playersSkill[3][1] = {0}", playersSkill[3][1]);
		KK_TRACE("playersSkill[3][2] = {0}", playersSkill[3][2]);

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Player_UI")->second);
		uiSkills->GetSpriteRenderer()->ShiftTo(0, 3);
		uiSkills->setNumOwner(3);
		objectsList.push_back(uiSkills);
		playerUIs[3] = uiSkills;

		//playerSkillUIs AbilityGameplay_UI
		UiObject* uiSkills1 = new UiObject();
		uiSkills1->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills1->GetSpriteRenderer()->ShiftTo(0, playersSkill[3][0]);
		uiSkills1->setNumOwner(3);
		objectsList.push_back(uiSkills1);
		playerSkillUIs[3][0] = uiSkills1;

		UiObject* uiSkills2 = new UiObject();
		uiSkills2->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills2->GetSpriteRenderer()->ShiftTo(0, playersSkill[3][1]);
		uiSkills2->setNumOwner(3);
		objectsList.push_back(uiSkills2);
		playerSkillUIs[3][1] = uiSkills2;

		UiObject* uiSkills3 = new UiObject();
		uiSkills3->SetSpriteInfo(spriteList.find("AbilityGameplay_UI")->second);
		uiSkills3->GetSpriteRenderer()->ShiftTo(0, playersSkill[3][2]);
		uiSkills3->setNumOwner(3);
		objectsList.push_back(uiSkills3);
		playerSkillUIs[3][2] = uiSkills3;

		uiSkills1->uiType = UiObject::UIType::SkillIcon;
		uiSkills2->uiType = UiObject::UIType::SkillIcon;
		uiSkills3->uiType = UiObject::UIType::SkillIcon;
	}

	/*UiObject* uiSkills = new UiObject();
	uiSkills->SetSpriteInfo(spriteList.find("Player_UI")->second);
	uiSkills->GetSpriteRenderer()->ShiftTo(0, 3);
	uiSkills->setNumOwner(3);
	objectsList.push_back(uiSkills);
	playerUIs[3] = uiSkills;*/


	// Pause_BG. Pause_text
	PauseMenu = new UiObject();
	PauseMenu->SetSpriteInfo(spriteList.find("Pause_BG")->second);
	PauseMenu->SetIsRender(false);
	PauseMenu->uiType = UiObject::UIType::PauseMenu;
	objectsList.push_back(PauseMenu);

	ResumeButton = new UiObject();
	ResumeButton->SetSpriteInfo(spriteList.find("Pause_text")->second);
	ResumeButton->GetSpriteRenderer()->ShiftTo(0, 0);
	ResumeButton->SetIsRender(false);
	ResumeButton->uiType = UiObject::UIType::PauseText;
	objectsList.push_back(ResumeButton);

	OptionButton = new UiObject();
	OptionButton->SetSpriteInfo(spriteList.find("Pause_text")->second);
	OptionButton->GetSpriteRenderer()->ShiftTo(0, 2);
	OptionButton->SetIsRender(false);
	OptionButton->uiType = UiObject::UIType::PauseText;
	objectsList.push_back(OptionButton);

	MainMenuButton = new UiObject();
	MainMenuButton->SetSpriteInfo(spriteList.find("Pause_text")->second);
	MainMenuButton->GetSpriteRenderer()->ShiftTo(0, 4);
	MainMenuButton->SetIsRender(false);
	MainMenuButton->uiType = UiObject::UIType::PauseText;
	objectsList.push_back(MainMenuButton);


	for (int i = 0; i < playerSize; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			playerSkillCooldownTexts[i][j] = new TextObject();

			playerSkillCooldownTexts[i][j]->loadText(" ", SDL_Color{ 255, 255, 255 }, 64);
			//playerSkillCooldownTexts[i][j]->SetPosition(glm::vec3(0, 0, 0));

			objectsList.push_back(playerSkillCooldownTexts[i][j]);

			playerSkillCooldownCovers[i][j] = new UiObject();
			playerSkillCooldownCovers[i][j]->SetSpriteInfo(spriteList.find("AbilityCover_UI")->second);
			playerSkillCooldownCovers[i][j]->SetIsRender(false);
			playerSkillCooldownCovers[i][j]->uiType = UiObject::UIType::SkillCover;

			objectsList.push_back(playerSkillCooldownCovers[i][j]);
		}
	}

	TextObject* text = new TextObject();
	//text->InitSDL();
	text->loadText("3", SDL_Color{ 0, 0, 0 }, 256);
	text->SetPosition(glm::vec3(0, 0, 0));
	text_SizeX = text->getSize().x;
	text_SizeY = text->getSize().y;
	objectsList.push_back(text);
	
	
	textObjects.push_back(text);

	// sort with ordering layer
	std::sort(objectsList.begin(), objectsList.end(), compareLayer);

	// Read config file

	LoadConfigInfo("LevelShowcase.json");
	

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
		if (objectsList[i]->GetIsActive() == false || objectsList[i] == nullptr)
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

	for (int i = 0; i < propObjects.size(); i++)
	{
		if (propObjects[i]->GetIsActive() == false)
		{
			propObjects.erase(propObjects.begin() + i);
		}
	}

	

	/*for (TextObject* text : textObjects)
	{
		text->loadText("3", SDL_Color{ 255, 0, 0 }, 256);
		text->SetPosition(glm::vec3(0, 0, 0));
	}*/

	if (isPause)
	{
		if (!PauseMenu->GetIsRender())
		{
			PauseMenu->SetIsRender(true);
		}

		if (!ResumeButton->GetIsRender())
		{
			ResumeButton->SetIsRender(true);
		}

		if (!OptionButton->GetIsRender())
		{
			OptionButton->SetIsRender(true);
		}

		if (!MainMenuButton->GetIsRender())
		{
			MainMenuButton->SetIsRender(true);
		}

		switch (currentPauseButton)
		{
		case PauseMenuButton::Resume:
			ResumeButton->GetSpriteRenderer()->ShiftTo(0, 1);
			OptionButton->GetSpriteRenderer()->ShiftTo(0, 2);
			MainMenuButton->GetSpriteRenderer()->ShiftTo(0, 4);
			break;
		case PauseMenuButton::Option:
			ResumeButton->GetSpriteRenderer()->ShiftTo(0, 0);
			OptionButton->GetSpriteRenderer()->ShiftTo(0, 3);
			MainMenuButton->GetSpriteRenderer()->ShiftTo(0, 4);
			break;
		case PauseMenuButton::MainMenu:
			ResumeButton->GetSpriteRenderer()->ShiftTo(0, 0);
			OptionButton->GetSpriteRenderer()->ShiftTo(0, 2);
			MainMenuButton->GetSpriteRenderer()->ShiftTo(0, 5);
			break;

		}

		UpdateInput();

	}
	else
	{
		if (PauseMenu->GetIsRender())
		{
			PauseMenu->SetIsRender(false);
		}

		if (ResumeButton->GetIsRender())
		{
			ResumeButton->SetIsRender(false);
		}

		if (OptionButton->GetIsRender())
		{
			OptionButton->SetIsRender(false);
		}

		if (MainMenuButton->GetIsRender())
		{
			MainMenuButton->SetIsRender(false);
		}

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
					entity->UpdateSpriteSheetPosition();
					entity->UpdateCurrentAnimation();
					/*entity->GetSpriteRenderer()->ShiftColumn();
					entity->UpdateCurrentAnimation();*/
				}
			}
		}


		if (currentCountdownNum > -1)
		{
			UpdateCountdown();
		}
		else
		{
			UpdateInput();

			// slowness
			UpdateMovement();

			// projectile collider player
			UpdateCollision();

			// delete projectile
			UpdateProjectile();

			// reduce cooldown skill
			UpdateCooldown();

			// UpdateKrakenEvent()
			UpdateKrakenEvent();
		}

		//Ui Skills
		UpdateUI();

		playerRemain = 0;
		// Check Amount of player
		for (int i = 0; i < playerSize; i++)
		{
			if (!players[i]->GetIsFell())
			{
				playerRemain++;
			}
		}

		if (playerRemain <= 1)
		{
			SaveWinRoundInfo("../Resource/SceneData/RoundWin.json");
			GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELROUNDWIN;
			GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
		}

		GroundTileRefactor();

		std::sort(objectsList.begin(), objectsList.end(), compareLayer);
	}
}

void LevelShowcase::UpdateKrakenEvent()
{
	if (timeUntilKrakenCounter > timeUntilKrakenEvent && !isStartKrakenEvent)
	{
		isStartKrakenEvent = true;
		KK_INFO("Kraken Event Start!");

		UiObject* signUI = new UiObject();
		signUI->uiType = UiObject::UIType::Kraken;
		signUI->SetSpriteInfo(spriteList.find("DangerSign")->second);

		uiObjects.push_back(signUI);
		objectsList.push_back(signUI);
	}
	else
	{
		timeUntilKrakenCounter += timer->getDeltaTime();
		//KK_INFO("Kraken Event not yet start dt = {0}", dt);
	}

	// currently in kraken event
	if (isStartKrakenEvent)
	{
		if (KrakenEventOffset_bottom >= (MAP_HEIGHT / 2) + 1 ||
			KrakenEventOffset_top >= (MAP_HEIGHT / 2) + 1 ||
			KrakenEventOffset_left >= (MAP_WIDTH / 2) + 1 ||
			KrakenEventOffset_right >= (MAP_WIDTH / 2) + 1)
		{
			return;
		}

		timePerTileCounter += timer->getDeltaTime();

		if (timePerTileCounter > timePerTileKrakenEvent)
		{
			timePerTileCounter = 0.f;

			int x = currrentCollapsePosition.x;
			int y = currrentCollapsePosition.y;
			
			// break tile
			if (currentGroundTile[y][x] != 0)
			{
				tilesList[y][x]->ImmediatelyBreak();
			}

			// shift current collapse position
			switch (currentCollapseDirection)
			{

			case TileCollapseDirection::Down:

				currrentCollapsePosition.y = currrentCollapsePosition.y + 1;
				
				if (currrentCollapsePosition.y == MAP_HEIGHT - 1 - KrakenEventOffset_bottom)
				{
					currentCollapseDirection = TileCollapseDirection::Right;

					KrakenEventOffset_bottom++;
				}

				break;

			case TileCollapseDirection::Right:

				currrentCollapsePosition.x = currrentCollapsePosition.x + 1;

				if (currrentCollapsePosition.x == MAP_WIDTH - 1 - KrakenEventOffset_right)
				{
					currentCollapseDirection = TileCollapseDirection::Up;

					KrakenEventOffset_right++;
				}

				break;

			case TileCollapseDirection::Up:

				currrentCollapsePosition.y = currrentCollapsePosition.y - 1;

				if (currrentCollapsePosition.y == 0 + KrakenEventOffset_top)
				{
					currentCollapseDirection = TileCollapseDirection::Left;

					KrakenEventOffset_top++;
				}

				break;

			case TileCollapseDirection::Left:

				currrentCollapsePosition.x = currrentCollapsePosition.x - 1;

				if (currrentCollapsePosition.x == 0 + KrakenEventOffset_left)
				{
					currentCollapseDirection = TileCollapseDirection::Down;

					KrakenEventOffset_left++;
				}

				break;
			}
		}
	}
}

void LevelShowcase::UpdateCountdown()
{
	for (TextObject* text : textObjects)
	{
		if (text_t >= 1.0f) { break; }
		text_t += 0.01f;
		float maxSizeX = text_SizeX * 1.5f;
		float maxSizeY = text_SizeY * 1.5f;
		text->SetSize(text_SizeX + ElasticOut(text_t) * maxSizeX, text_SizeY + ElasticOut(text_t) * maxSizeY);
	}

	currentCountdownDelay += timer->getDeltaTime();

	if (currentCountdownDelay >= countdownDelay)
	{
		currentCountdownDelay = 0;
		currentCountdownNum--;

		KK_TRACE("LevelShowcase: currentCountdownNum = {0}", currentCountdownNum);

		if (currentCountdownNum < 0)
		{
			for (TextObject* text : textObjects)
			{
				text->SetIsActive(false);
			}
		}
		else
		{
			std::string displayString = std::to_string(currentCountdownNum);

			if (currentCountdownNum == 0)
			{
				displayString = "Start!";
			}

			for (TextObject* text : textObjects)
			{
				text->loadText(displayString, SDL_Color{ 0, 0, 0 }, 256);
				text_SizeX = text->getSize().x;
				text_SizeY = text->getSize().y;

				text->SetSize(text_SizeX, text_SizeY);
			}

			text_t = 0;
		}
	}
}

void LevelShowcase::UpdateInput()
{
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();

		if (isPause)
		{
			float axisX = Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
			float axisY = Joystick::GetAxis(0, Joystick::Axis::LeftStickVertical) / 32768.0f;

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
			KK_INFO("norAxisY == {0}", norAxisY);
			if (!isPressedInPause)
			{
				//KK_INFO("Pressed in pause!");

				if ((norAxisY > 0.0f && isPositiveY == false) || Joystick::GetButton(0, Joystick::Button::DPAD_Down)) // press down
				{
					if (currentPauseButton == PauseMenuButton::Resume)
					{
						currentPauseButton = PauseMenuButton::Option;
					}
					else if (currentPauseButton == PauseMenuButton::Option)
					{
						currentPauseButton = PauseMenuButton::MainMenu;
					}

					isPressedInPause = true;
				}

				if ((norAxisY < 0.0f && isPositiveY == true) || Joystick::GetButton(0, Joystick::Button::DPAD_Up)) // press up
				{
					
					if (currentPauseButton == PauseMenuButton::Option)
					{
						currentPauseButton = PauseMenuButton::Resume;
					}
					else if (currentPauseButton == PauseMenuButton::MainMenu)
					{
						currentPauseButton = PauseMenuButton::Option;
					}

					isPressedInPause = true;
				}
			}
			else
			{
				if (abs(norAxisY) < 0.3f && norAxisX < 0.3f && !Joystick::GetButton(0, Joystick::Button::DPAD_Up) && !Joystick::GetButton(0, Joystick::Button::DPAD_Down)) // press down
				{
					isPressedInPause = false;
				}
			}

			if (Joystick::GetButton(0, Joystick::Button::Cross))
			{
				if (currentPauseButton == PauseMenuButton::MainMenu)
				{
					GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELMAINMENU;
					GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
				}
				else if (currentPauseButton == PauseMenuButton::Resume)
				{
					isPause = false;
				}
				
			}

			if (Joystick::GetButtonDown(0, Joystick::Button::ShareButton))
			{
				isPause = false;
			}
		}
		else
		{
			for (int i = 0; i < playerSize; i++)
			{
				if (players[i + currentPlayer]->GetIsFell())
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
					players[i + currentPlayer]->SetCurrentDirection(glm::vec2(norAxisX, norAxisY));
				}

				if (players[i + currentPlayer]->GetIsFell() == false)
				{
					// update facing
					if (abs(axisX) > 0.2f)
					{
						players[i + currentPlayer]->UpdateFacingSide(isPositiveX);
					}

					// movement control
					if (players[i + currentPlayer]->GetIsKnockback() == false)
					{
						if (players[i + currentPlayer]->GetIsStun() == true)
						{
							// velo to zero if stun
							players[i + currentPlayer]->SetVelocity(0, 0, isPositiveXOld[i + currentPlayer], isPositiveYOld[i + currentPlayer]);
						}
						else if (players[i + currentPlayer]->GetIsDashing() == true)
						{
							// use old velo during dash to disable control
							players[i + currentPlayer]->SetVelocity(
								abs(norAxisXOld[i + currentPlayer]),
								abs(norAxisYOld[i + currentPlayer]),
								isPositiveXOld[i + currentPlayer],
								isPositiveYOld[i + currentPlayer]
							);
						}
						else if (players[i + currentPlayer]->GetIsAiming() == false)
						{
							// if not affecit by anything, use normaml velocity
							players[i + currentPlayer]->SetVelocity(
								abs(norAxisX),
								abs(norAxisY),
								isPositiveX,
								isPositiveY
							);
						}
					}

					// update old velocity in case dashing

					if (players[i + currentPlayer]->GetIsDashing())
					{
						norAxisXOld[i + currentPlayer] = norAxisX;
						norAxisYOld[i + currentPlayer] = norAxisY;
						isPositiveXOld[i + currentPlayer] = isPositiveX;
						isPositiveYOld[i + currentPlayer] = isPositiveY;
					}

					if (players[i + currentPlayer]->GetIsAiming())
					{

						if (players[i]->GetHoldingProjectile() == static_cast<int>(ProjectileObject::Cleave) && players[i]->projectileHoldDuration >= 3) {
							PlayerObject::Ability idAbility = players[i]->GetAbilityByButton(PlayerObject::AbilityButton::Circle);
							if (idAbility == PlayerObject::Ability::Cleave)
							{
								ShootCleave(i, PlayerObject::AbilityButton::Circle);
							}

							idAbility = players[i]->GetAbilityByButton(PlayerObject::AbilityButton::Cross);
							if (idAbility == PlayerObject::Ability::Cleave)
							{
								ShootCleave(i, PlayerObject::AbilityButton::Cross);
							}

							idAbility = players[i]->GetAbilityByButton(PlayerObject::AbilityButton::Triangle);
							if (idAbility == PlayerObject::Ability::Cleave)
							{
								ShootCleave(i, PlayerObject::AbilityButton::Triangle);
							}

							players[i]->SetIsAiming(false);
							players[i]->SetHoldingProjectile(0);
							players[i]->projectileHoldDuration = 0;
						}

						std::vector<ProjectileObject*> owningProjectile = players[i + currentPlayer]->GetOwningProjectile();
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

								//KK_TRACE("players[i]->GetHoldingProjectile() = {0}", players[i]->GetHoldingProjectile());

							}

							// cancel aim
							if ((projectile != nullptr) && (players[i]->GetIsKnockback() == true || players[i]->GetIsStun() == true)) {
								players[i]->SetHoldingProjectile(0);
								//players[i + playerNum]->SetIsShooting(false);
								projectile->SetLifeTime(0);
								players[i]->SetIsAiming(false);
								if (Joystick::GetButton(i, Joystick::Button::Circle))
								{
									players[i + currentPlayer]->SetAbilityCooldown(PlayerObject::AbilityButton::Circle, 6);
								}
								if (Joystick::GetButton(i, Joystick::Button::Cross))
								{
									players[i + currentPlayer]->SetAbilityCooldown(PlayerObject::AbilityButton::Cross, 6);
								}
								if (Joystick::GetButton(i, Joystick::Button::Triangle))
								{
									players[i + currentPlayer]->SetAbilityCooldown(PlayerObject::AbilityButton::Triangle, 6);
								}
							}
						}
					}

				}

				//Ability Triangle
				if (Joystick::GetButtonDown(i, Joystick::Button::Triangle))
				{
					if (players[i + currentPlayer]->GetCooldown(PlayerObject::AbilityButton::Triangle) <= 0)
					{
						UsingAbilityKeyDown(i + currentPlayer, PlayerObject::AbilityButton::Triangle);
					}
				}

				if (Joystick::GetButtonUp(i, Joystick::Button::Triangle)) {
					if (players[i + currentPlayer]->GetCooldown(PlayerObject::AbilityButton::Triangle) <= 0)
					{
						UsingAbilityKeyUp(i + currentPlayer, PlayerObject::AbilityButton::Triangle);
					}
				}

				//Ability Circle
				if (Joystick::GetButtonDown(i, Joystick::Button::Circle))
				{
					if (players[i + currentPlayer]->GetCooldown(PlayerObject::AbilityButton::Circle) <= 0)
					{
						UsingAbilityKeyDown(i + currentPlayer, PlayerObject::AbilityButton::Circle);
					}
				}

				if (Joystick::GetButtonUp(i, Joystick::Button::Circle)) {
					if (players[i + currentPlayer]->GetCooldown(PlayerObject::AbilityButton::Circle) <= 0)
					{
						UsingAbilityKeyUp(i + currentPlayer, PlayerObject::AbilityButton::Circle);
					}
				}

				//Ability Cross
				if (Joystick::GetButtonDown(i, Joystick::Button::Cross))
				{
					if (players[i + currentPlayer]->GetCooldown(PlayerObject::AbilityButton::Cross) <= 0)
					{
						UsingAbilityKeyDown(i + currentPlayer, PlayerObject::AbilityButton::Cross);
					}
				}

				if (Joystick::GetButtonUp(i, Joystick::Button::Cross))
				{
					if (players[i + currentPlayer]->GetCooldown(PlayerObject::AbilityButton::Cross) <= 0)
					{
						UsingAbilityKeyUp(i + currentPlayer, PlayerObject::AbilityButton::Cross);
					}
				}

				if (Joystick::GetButtonDown(i, Joystick::Button::Square))
				{
					//players[i]->ChangeAnimationState(PlayerObject::AnimationState::Melee);
					if (players[i + currentPlayer]->GetMeleeCooldown() <= 0.f)
					{
						players[i + currentPlayer]->ChangeMeleeAnimation();
						players[i + currentPlayer]->HitAimingTile();
						players[i + currentPlayer]->SetMeleeCooldown(MeleeCooldown);
						soundManager->PlaySFX("hit_test", false);
					}

				}

				// Debug other player
				if (Joystick::GetButtonDown(i, Joystick::Button::R1))
				{
					currentPlayer++;
					currentPlayer = currentPlayer % 4;
				}

				if (Joystick::GetButtonDown(i, Joystick::Button::ShareButton))
				{
					isPause = true;
				}

				if (Joystick::GetButtonDown(i, Joystick::Button::P5Button))
				{
					GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELSHOWCASE;
					GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
				}
			}

			players[0]->Translate(players[0]->GetVelocity() * playerMovementSpeed);
			players[1]->Translate(players[1]->GetVelocity() * playerMovementSpeed);
			players[2]->Translate(players[2]->GetVelocity() * playerMovementSpeed);
			players[3]->Translate(players[3]->GetVelocity() * playerMovementSpeed);
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

			glm::vec3 offsetEntity1 = entity1->GetCollider()->GetOffset();
			glm::vec3 offsetEntity2 = entity2->GetCollider()->GetOffset();

			glm::vec3 posAfterOffset1 = entity1->getPos() + offsetEntity1;
			glm::vec3 posAfterOffset2 = entity2->getPos() + offsetEntity2;

			float deltaX = posAfterOffset1.x - posAfterOffset2.x;
			float deltaY = posAfterOffset1.y - posAfterOffset2.y;

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

			entity2->GetCollider()->SetPreviousPos(entity2->getPos() + entity2->GetCollider()->GetOffset());
		}
		entity1->GetCollider()->SetPreviousPos(entity1->getPos() + entity1->GetCollider()->GetOffset());
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

		for (PropObject* prop : propObjects)
		{
			//KK_TRACE("----------------------------------------");
			prop->CheckIfNoTileSurround();
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
			//KK_INFO("Prpjectile Lifetime {0}", projectile->GetLifetime());
			projectile->Translate(projectile->GetVelocity());

			
		}

		for (TrapObject* trap : player->GetOwningTrap())
		{
			//KK_TRACE("UpdateProjectile: trap check");
			if (trap->GetCanKnockback()) 
			{
				//trap->SetIsActive(false);
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

			//KK_CORE_WARN("Set Velocity = {0}, {1}", knockbackVeloX, knockbackVeloY);
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

	float uiWidth = 420.f * 0.7f;
	float uiHeight = 116.f * 0.7f;
	
	float posX = camera.GetCenterX() - (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH / 2.f) * (playerNumber - 1);
	float posY = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + ((uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT) / 2.f);
	
	for (int i = 0; i < playerNumber; i++)
	{
		UiObject* ui = playerUIs[i];

		float posX_current = posX + (ui->getNumOwner() * uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH);

		ui->SetPosition(glm::vec3(posX_current, posY, 0));
		ui->SetSize(uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);

		for (int j = 0; j < 3; j++)
		{
			UiObject* uiSkill = playerSkillUIs[i][j];

			float offsetX = (57.f * j - 26.f) * camera.GetCameraWidth() / SCREEN_WIDTH;
			float posX_currentSkill = posX_current + offsetX;

			float skillWidth = 69.f * 0.7f;
			float skillHeight = 69.f * 0.7f;

			uiSkill->SetPosition(glm::vec3(posX_currentSkill, posY, 0));
			uiSkill->SetSize(skillWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -skillHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);

			TextObject* cooldownText = playerSkillCooldownTexts[i][j];
			cooldownText->SetPosition(glm::vec3(posX_currentSkill, posY, 0));

			UiObject* uiCover = playerSkillCooldownCovers[i][j];

			uiCover->SetPosition(glm::vec3(posX_currentSkill, posY, 0));
			uiCover->SetSize(skillWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -skillHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);

			float cooldown = players[i]->GetCooldown(static_cast<PlayerObject::AbilityButton>(j));
			
			if (cooldown > 0)
			{
				std::string cooldownString = std::to_string((int)std::roundf(cooldown));
				uiCover->SetIsRender(true);
				cooldownText->loadText(cooldownString, SDL_Color{ 255, 255, 255 }, 64);
			}
			else
			{
				if (uiCover->GetIsRender() == true)
				{
					std::string cooldownString = " ";
					uiCover->SetIsRender(false);
					cooldownText->loadText(cooldownString, SDL_Color{ 255, 255, 255 }, 64);
				}
				
			}

		}
		

	}

	for (UiObject* ui : uiObjects)
	{
		switch (ui->uiType)
		{
		case UiObject::Kraken:

			if (krakenSign_t >= 6.0f)
			{
				break;
			}

			krakenSign_t += 0.01f;
			
			float uiWidth = 544.f;
			float uiHeight = -215.f;

			// krakenSign_t
			float posY_start = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top - (uiHeight / 2.f);
			float posY_end = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top + (uiHeight / 2.f);

			float t = Parabola(krakenSign_t);

			float posX = camera.GetCenterX();
			float posY = posY_end + t * posY_start;

			ui->SetPosition(glm::vec3(posX, posY, 0));
			ui->SetSize(uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH, uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);

			
		}
		//ui->SetPosition(glm::vec3(posX + (ui->getNumOwner() * ui->getSize().x * camera.GetCameraWidth() / SCREEN_WIDTH), posY, 0));
		
	}

	if (isPause)
	{
		float uiWidth_PauseBG = 623.f;
		float uiHeight_PauseBG = 671.f;

		float uiWidth_PauseText = 300.f;
		float uiHeight_PauseText = 70.f;

		PauseMenu->SetPosition(glm::vec3(0, 0, 0));
		PauseMenu->SetSize(uiWidth_PauseBG * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight_PauseBG * camera.GetCameraHeight() / SCREEN_HEIGHT);

		ResumeButton->SetPosition(glm::vec3(0, 300, 0));
		ResumeButton->SetSize(uiWidth_PauseText * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight_PauseText * camera.GetCameraHeight() / SCREEN_HEIGHT);

		OptionButton->SetPosition(glm::vec3(0, 0, 0));
		OptionButton->SetSize(uiWidth_PauseText * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight_PauseText * camera.GetCameraHeight() / SCREEN_HEIGHT);

		MainMenuButton->SetPosition(glm::vec3(0, -300, 0));
		MainMenuButton->SetSize(uiWidth_PauseText * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight_PauseText * camera.GetCameraHeight() / SCREEN_HEIGHT);

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

	//if (ImGui::Button("Reset Scene", ImVec2(100, 50)))
	//	isResetScene++;

	//if (ImGui::Button("To FullScreen", ImVec2(100, 50)))
	//	isFullScreen++;

	//if (ImGui::Button("To WindowScreen", ImVec2(100, 50)))
	//	isWindowScreen++;

	//ImGui::SliderFloat("musicVolume", &musicVolume, 0.0f, 1.0f, "ratio = %.3f");
	//ImGui::SliderFloat("sfxVolume", &sfxVolume, 0.0f, 1.0f, "ratio = %.3f");

	//soundManager->SetVolumeAllMusic(0 + (musicVolume * (128.f - 0)));
	//soundManager->SetVolumeAllSFX(0 + (sfxVolume * (128.f - 0)));

	//if (isFullScreen & 1)
	//{
	//	SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	//	glViewport(0, 0, 1920, 1080);
	//	isFullScreen = 0;
	//}

	//if (isWindowScreen & 1)
	//{
	//	SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), 0);
	//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//	isWindowScreen = 0;
	//}
	//// Cooldown Stats
	///*float MeleeCooldown = 2.f;
	//float FireballCooldown = 3.f;
	//float TrapCooldown = 3.f;
	//float DashCooldown = 3.f;
	//float TNTCooldown = 3.f;
	//float TeleportCooldown = 3.f;
	//float BolaCooldown = 3.f;
	//float CleaveCooldown = 3.f;

	//float FireballLifetime = 3.f;
	//float TeleportLifetime = 2.f;
	//float BolaLifetime = 2.f;
	//float CleaveLifetime = 2.f;*/

	//ImGui::Text("Cooldown stats");
	//ImGui::InputFloat("Melee Cooldown", &MeleeCooldown, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Fireball Cooldown", &FireballCooldown, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Trap Cooldown", &TrapCooldown, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Dash Cooldown", &DashCooldown, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("TNT Cooldown", &TNTCooldown, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Teleport Cooldown", &TeleportCooldown, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Bola Cooldown", &BolaCooldown, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Cleave Cooldown", &CleaveCooldown, 0.1f, 1.0f, "%.2f");

	//ImGui::Text("Lifetime stats");
	//ImGui::InputFloat("Fireball Lifetime", &FireballLifetime, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Teleport Lifetime", &TeleportLifetime, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Bola Lifetime", &BolaLifetime, 0.1f, 1.0f, "%.2f");
	//ImGui::InputFloat("Cleave Lifetime", &CleaveLifetime, 0.1f, 1.0f, "%.2f");

	//ImGui::Text("Overall stats");
	//ImGui::InputFloat("Move Speed", &playerMovementSpeed, 0.1f, 1.0f, "%.2f");

	//if (isResetScene & 1)
	//{
	//	GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELSHOWCASE;
	//	GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
	//}
	//ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	//if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	//{
	//	for (int i = 0; i < playerSize; i++)
	//	{
	//		std::string tabname = "player " + std::to_string(i);
	//		ImGui::PushID(i);

	//		if (ImGui::BeginTabItem(tabname.c_str()))
	//		{
	//			ImGui::Text("Player %d", i);
	//			ImGui::SameLine();
	//			ImGui::SeparatorText("");
	//			ImGui::Text("Position: %f, %f, %f", players[i]->getPos().x, players[i]->getPos().y, players[i]->getPos().z);
	//			
	//			ImGui::Text("isShooting: %s", players[i]->GetIsShooting() ? "true" : "false");
	//			ImGui::Text("isAiming: %s", players[i]->GetIsAiming() ? "true" : "false");
	//			ImGui::Text("isSlow: %s", players[i]->GetIsSlow() ? "true" : "false");
	//			ImGui::Text("isDashing: %s", players[i]->GetIsDashing() ? "true" : "false");
	//			ImGui::Text("isKnockback: %s", players[i]->GetIsKnockback() ? "true" : "false");
	//			ImGui::Text("isStun: %s", players[i]->GetIsStun() ? "true" : "false");
	//			ImGui::Text("isOnGround: %s", players[i]->GetIsOnGround() ? "true" : "false");
	//			ImGui::Text("Current Velocity: %f, %f", players[i]->GetVelocity().x, players[i]->GetVelocity().y);

	//			/*ImGui::DragFloat("ColX Button", &groundColX[i], 2.0f, 0.0f, 1024.f, "%.3f");
	//			ImGui::DragFloat("ColY Button", &groundColY[i], 2.0f, 0.0f, 1024.f, "%.3f");*/
	//			ImGui::DragFloat("Col offset X", &groundColOffsetX[i], 2.0f, -1024.f, 1024.f, "%.3f");
	//			ImGui::DragFloat("Col offset Y", &groundColOffsetY[i], 2.0f, -1024.f, 1024.f, "%.3f");

	//			players[i]->GetGroundColliderObject()->SetCollisionOffset(glm::vec2(groundColOffsetX[i], groundColOffsetY[i]));
	//			/*Fireball = 0,
	//				Trap = 1,
	//				Dash = 2,
	//				TNT = 3,
	//				Teleport = 4,
	//				Bola = 5,
	//				Cleave = 6*/

	//			for (int j = 0; j < 3; j++)
	//			{
	//				ImGui::PushID(j);


	//				ImGui::Text("skill %d", j);
	//				ImGui::Text("ability %d cooldown: %.2f", i ,players[i]->GetCooldown(static_cast<PlayerObject::AbilityButton>(j)));
	//				ImGui::RadioButton("Fireball", &playersSkill[i][j], static_cast<int>(PlayerObject::Ability::Fireball));
	//				ImGui::SameLine();
	//				ImGui::RadioButton("Trap", &playersSkill[i][j], static_cast<int>(PlayerObject::Ability::Trap));
	//				ImGui::SameLine();
	//				ImGui::RadioButton("Dash", &playersSkill[i][j], static_cast<int>(PlayerObject::Ability::Dash));
	//				//ImGui::SameLine();
	//				ImGui::RadioButton("TNT", &playersSkill[i][j], static_cast<int>(PlayerObject::Ability::TNT));
	//				ImGui::SameLine();
	//				ImGui::RadioButton("Teleport", &playersSkill[i][j], static_cast<int>(PlayerObject::Ability::Teleport));
	//				ImGui::SameLine();
	//				ImGui::RadioButton("Bola", &playersSkill[i][j], static_cast<int>(PlayerObject::Ability::Bola));
	//				ImGui::SameLine();
	//				ImGui::RadioButton("Cleave", &playersSkill[i][j], static_cast<int>(PlayerObject::Ability::Cleave));
	//				ImGui::SeparatorText("");

	//				ImGui::PopID();
	//			}
	//			ImGui::EndTabItem();
	//		}
	//		
	//		ImGui::PopID();
	//	}
	//	
	//	ImGui::EndTabBar();
	//}
	//
	//for (int i = 0; i < playerSize; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		players[i]->SetAbility
	//		(
	//			static_cast<PlayerObject::AbilityButton>(j), 
	//			static_cast<PlayerObject::Ability>(playersSkill[i][j])
	//		);
	//	}
	//}

	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());


	// cout << "Draw Level" << endl;
}

void LevelShowcase::LevelFree()
{
	// Clean up DrawableObjects
	for (DrawableObject* obj: objectsList) 
	{
		if (obj == nullptr)
		{
			continue;
		}
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

	SaveConfigInfo("LevelShowcase.json");

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
			else if (tilesList[i][j]->currAnimState == TileObject::AnimationState::FinishBreaking)
			{
				//KK_TRACE("Refactor check: finish breaking");
				continue;
			}
			else if (flag == 2)
			{
				//KK_TRACE("Refactor check: if tile is breaking");
				//SpritesheetInfo collapseTileSprite = SpritesheetInfo("CollapseTile", "../Resource/Texture/Props/prop_spr_vfx_smoke.png", 200, 200, 800, 200);
				
				
				TileObject* collapseTile = new TileObject();
				collapseTile->SetIsAnimated(true);
				collapseTile->currAnimState = TileObject::AnimationState::Breaking;
				collapseTile->SetSize(256.f, -256.f);
				collapseTile->SetPosition(tilesList[i][j]->getPos());
				collapseTile->GetSpriteRenderer()->SetFrame(10);
				collapseTile->SetTextureWithID(spriteList.find("CollapseTile")->second, spriteList.find("CollapseTile")->second.textureid);
				collapseTile->GetSpriteRenderer()->ShiftTo(tilesList[i][j]->GetSpriteRenderer()->GetRow(), tilesList[i][j]->GetSpriteRenderer()->GetColumn());

				AddEntityToScene(collapseTile);
				tilesList[i][j]->currAnimState = TileObject::AnimationState::FinishBreaking;

				currentGroundTile[i][j] = 0;
			}

			flag = currentGroundTile[i][j];

			if (flag == 0)
			{
				if (tilesList[i - 1][j] == 0)
				{
					tilesList[i][j]->currAnimState = TileObject::AnimationState::Breaking;
				}
				
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
						trap->ChangeAnimationState(TrapObject::AnimationState::Collide);
						KK_TRACE("Press Again");
						trap->isActivate = true;
						players[numPlayer]->SetAbilityCooldown(button, TNTCooldown);
						players[numPlayer]->SetIsTNT(false);
						players[numPlayer]->RemoveOwningTrap(trap);
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
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetAnimationSprite(ProjectileObject::Collide, spriteList.find("Bomb_Explode")->second);
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

void LevelShowcase::ShootFireball(int numPlayer, PlayerObject::AbilityButton button) 
{
	players[numPlayer]->SetIsAiming(false);
	for (ProjectileObject* projectile : players[numPlayer]->GetOwningProjectile()) 
	{
		if (projectile->GetType() == ProjectileObject::TypeProjectile::Fireball) 
		{
			projectile->SetLifeTime(FireballLifetime);
			projectile->SetIsShooting(true);
			//projectile->SetIsActive(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, FireballCooldown);
}

void LevelShowcase::Trap(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->ChangeAnimationState(PlayerObject::AnimationState::PlaceItem);
	players[numPlayer]->SetAbilityCooldown(button, TrapCooldown);
	TrapObject* Trap = new TrapObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->SetTexture(spriteList.find("Trap")->second.texture);
	Trap->SetPosition(players[numPlayer]->getPos());
	Trap->SetSize(128.f, -128.f);
	Trap->SetPlayerNumber(players[numPlayer]->GetPlayerNumber());
	Trap->SetType(TrapObject::TypeTrap::Trap);
	Trap->SetIsActive(true);
	Trap->SetAnimationSprite(TrapObject::AnimationState::Idle, spriteList.find("Trap")->second);
	Trap->SetAnimationSprite(TrapObject::AnimationState::Collide, spriteList.find("Trap_Explode")->second);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(Trap);
	entityObjects.push_back(Trap);
	players[numPlayer]->AddOwningTrap(Trap);
	//std::cout << "place trap" << std::endl;
}

void LevelShowcase::Dash(int num, PlayerObject::AbilityButton button) {
	players[num]->SetAbilityCooldown(button, DashCooldown);
	players[num]->SetIsDashing(true);
	players[num]->SetDashDuration(DashDuration);
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
	TNT->SetAnimationSprite(TrapObject::AnimationState::Idle, spriteList.find("TNT")->second);
	TNT->SetAnimationSprite(TrapObject::AnimationState::Collide, spriteList.find("Landmine_Explode")->second);
	//TNT->GetCollider()->Update(glm::vec3(0, 0, 0), TNT->getPos());
	//TNT->setIsCanKnockback(true);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(TNT);
	entityObjects.push_back(TNT);
	//objectsList.push_back(TNT->GetCollider()->GetGizmos());
	players[numPlayer]->AddOwningTrap(TNT);
}

void LevelShowcase::AimTeleport(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Teleport);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetAnimationSprite(ProjectileObject::Collide, spriteList.find("Teleport_Explode")->second);
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

void LevelShowcase::ShootTeleport(int numPlayer, PlayerObject::AbilityButton button) 
{
	if (players[numPlayer]->GetIsShooting() == false) 
	{
		players[numPlayer]->SetIsShooting(true);
		players[numPlayer]->SetIsAiming(false);

		for (ProjectileObject* projectile : players[numPlayer]->GetOwningProjectile()) 
		{
			if (projectile->GetType() == ProjectileObject::TypeProjectile::Teleport) 
			{
				projectile->SetLifeTime(TeleportLifetime);
				projectile->SetIsShooting(true);
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
	projectile->SetAnimationSprite(ProjectileObject::Collide, spriteList.find("Stun_Explode")->second);
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

void LevelShowcase::ShootBola(int numPlayer, PlayerObject::AbilityButton button) 
{
	players[numPlayer]->SetIsAiming(false);
	for (ProjectileObject* projectile : players[numPlayer]->GetOwningProjectile()) 
	{
		if (projectile->GetType() == ProjectileObject::TypeProjectile::Bola) 
		{
			projectile->SetLifeTime(BolaLifetime);
			projectile->SetIsShooting(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, BolaCooldown);
}

void LevelShowcase::AimCleave(int numPlayer, PlayerObject::AbilityButton button) 
{
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Cleave);
	//ProjectileObject* projectile = new ProjectileObject();
	//
	//projectile->SetSpriteInfo(spriteList.find("Cleave")->second);
	//projectile->SetTexture(spriteList.find("Cleave")->second.texture);
	//projectile->SetPosition(players[numPlayer]->getPos());
	//projectile->SetSize(256.f, -256.f);
	//projectile->SetLifeTime(9999);
	//projectile->SetOwner(players[numPlayer]);
	//projectile->SetType(ProjectileObject::TypeProjectile::Cleave);
	//projectile->SetCanKnockback(false);
	//projectile->SetIsCanStun(true);
	//projectile->SetIsShooting(false);
	////projectile->SetIsActive(false);
	//std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	//objectsList.push_back(projectile);
	//entityObjects.push_back(projectile);
	////players[numPlayer]->SetAbilityCooldown(button, CleaveCooldown);
	//players[numPlayer]->AddOwningProjectile(projectile);
}

void LevelShowcase::ShootCleave(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsAiming(false);

	ProjectileObject* projectile = new ProjectileObject();

	projectile->SetSpriteInfo(spriteList.find("Cleave")->second);
	projectile->SetTexture(spriteList.find("Cleave")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Cleave);
	projectile->SetCanKnockback(false);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	//projectile->SetIsActive(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	entityObjects.push_back(projectile);
	//players[numPlayer]->SetAbilityCooldown(button, CleaveCooldown);
	players[numPlayer]->AddOwningProjectile(projectile);

	projectile->SetLifeTime(CleaveLifetime);
	projectile->SetIsShooting(true);
	players[numPlayer]->SetHoldingProjectile(0);
	projectile->SetLifeTime(1);

	PlayerObject* player = players[numPlayer];
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

	projectile->SetPosition(player->getPos() + (projectile->GetVelocity() * glm::vec3(15.f, 15.f, 0.f)));
	projectile->SetRotation(angle);
	projectile->SetVelocity(abs(veloX), abs(veloY), PositiveX, PositiveY);
	players[numPlayer]->SetAbilityCooldown(button, CleaveCooldown);
}

void LevelShowcase::AddEntityToScene(EntityObject* entity)
{
	entityObjects.push_back(entity);
	objectsList.push_back(entity);
	//objectsList.push_back(entity->GetCollider()->GetGizmos());
	//players[numPlayer]->SetAbilityCooldown(button, 6);
}
void LevelShowcase::AddObjectToScene(DrawableObject* object)
{
	objectsList.push_back(object);
}
void LevelShowcase::loadAbility(std::string filename) {
	std::ifstream file(filename);
	nlohmann::json data = nlohmann::json::parse(file);

	if (file.is_open()) {
		std::cout << "Opened" << std::endl;
		std::string selectStr;
		for (int i = 0; i < 3; i++) {
			selectStr = "ability" + std::to_string(i);
			if (data.count(selectStr)) {
				abilityId[i] = data[selectStr];

			}
			else {
				std::cout << selectStr << "Not found" << std::endl;
				abilityId[i] = i;
			}
		}
	}

	else {
		std::cout << "Failed" << std::endl;
	}
}

void LevelShowcase::SaveConfigInfo(const std::string& fileName) {

	std::ofstream file(fileName);
	nlohmann::json data;

	//// ImGUI
	//float groundColX[4] = { 64.f, 64.f, 64.f, 64.f };
	//float groundColY[4] = { 64.f, 64.f, 64.f, 64.f };
	//float groundColOffsetX[4] = { 0.f, 0.f, 0.f, 0.f };
	//float groundColOffsetY[4] = { -96.f, -96.f, -96.f, -96.f };
	//int playersSkill[4][3];

	data["groundColOffsetY"] = 
	{ 
		{ "0", groundColOffsetY[0] },
		{ "1", groundColOffsetY[1] },
		{ "2", groundColOffsetY[2] },
		{ "3", groundColOffsetY[3] }
	};

	/*for (int i = 0; i < 4; i++)
	{
		std::string playerName = "Player " + std::to_string(i) + " Skill";
		data[playerName] =
		{
			playersSkill[i][0],
			playersSkill[i][1],
			playersSkill[i][2]
		};
	}*/

	data["MeleeCooldown"] = MeleeCooldown;
	data["FireballCooldown"] = FireballCooldown;
	data["TrapCooldown"] = TrapCooldown;
	data["DashCooldown"] = DashCooldown;
	data["TNTCooldown"] = MeleeCooldown;
	data["TeleportCooldown"] = MeleeCooldown;
	data["BolaCooldown"] = BolaCooldown;
	data["CleaveCooldown"] = CleaveCooldown;

	//float MeleeCooldown = 2.f;
	//float FireballCooldown = 3.f;
	//float TrapCooldown = 3.f;
	//float DashCooldown = 3.f;
	//float TNTCooldown = 3.f;
	//float TeleportCooldown = 3.f;
	//float BolaCooldown = 3.f;
	//float CleaveCooldown = 3.f;

	data["FireballLifetime"] = FireballLifetime;
	data["TeleportLifetime"] = TeleportLifetime;
	data["BolaLifetime"] = BolaLifetime;
	data["CleaveLifetime"] = CleaveLifetime;
	data["DashDuration"] = DashDuration;
	data["playerMovementSpeed"] = playerMovementSpeed;
	//float FireballLifetime = 1.f;
	//float TeleportLifetime = 2.f;
	//float BolaLifetime = 2.f;
	//float CleaveLifetime = 2.f;

	//float DashDuration = 0.2f;

	if (!file.is_open())
	{
		KK_ERROR("LevelShowcase: Fail to save config");
	}
	else
	{
		file << data;
		file.close();
		KK_INFO("LevelShowcase: Save config Complete");
	}

	
}

void LevelShowcase::LoadConfigInfo(const std::string& fileName)
{
	std::ifstream file(fileName);
	nlohmann::json data = nlohmann::json::parse(file);

	groundColOffsetY[0] = data["groundColOffsetY"]["0"];
	groundColOffsetY[1] = data["groundColOffsetY"]["1"];
	groundColOffsetY[2] = data["groundColOffsetY"]["2"];
	groundColOffsetY[3] = data["groundColOffsetY"]["3"];

	/*for (int i = 0; i < 4; i++)
	{
		std::string playerName = "Player " + std::to_string(i) + " Skill";

		for (int j = 0; j < 3; j++)
		{
			playersSkill[i][j] = data[playerName][j].get<int>();
		}
	}*/

	MeleeCooldown = data["MeleeCooldown"];
	FireballCooldown = data["FireballCooldown"];
	TrapCooldown = data["TrapCooldown"];
	DashCooldown = data["DashCooldown"];
	TNTCooldown = data["TNTCooldown"];
	TeleportCooldown = data["TeleportCooldown"];
	BolaCooldown = data["BolaCooldown"];
	CleaveCooldown = data["CleaveCooldown"];

	FireballLifetime = data["FireballLifetime"];
	TeleportLifetime = data["TeleportLifetime"];
	BolaLifetime = data["BolaLifetime"];
	CleaveLifetime = data["CleaveLifetime"];
	DashDuration = data["DashDuration"];

	playerMovementSpeed = data["playerMovementSpeed"];

}

void LevelShowcase::SaveWinRoundInfo(const std::string& fileName)
{
	int playerRoundWin[4] = { 0 };
	int currentRoundWinner = 0;
	int currentRound;

	std::ifstream readfile(fileName);

	// read file
	if (!readfile.is_open())
	{
		KK_ERROR("LevelShowcase: Cannot read round win file!");
	}
	else
	{
		nlohmann::json data = nlohmann::json::parse(readfile);

		std::string playerScore;

		for (int i = 0; i < 4; i++)
		{
			playerScore = "Score_Player" + std::to_string(i);

			if (!data.count(playerScore))
			{
				KK_ERROR("LevelShowcase: Cannot read player Score!");
			}
			else
			{
				playerRoundWin[i] = data[playerScore];

				KK_ERROR("playerRoundWin[{0}] = {1}", i, playerRoundWin[i]);
			}
		}

		std::string roundNumber = "roundNumber";

		if (!data.count(roundNumber))
		{
			KK_ERROR("LevelShowcase: Cannot read round Number!");
		}
		else
		{
			currentRound = data[roundNumber];
		}

		readfile.close();
	}
	
	// save value + new round win
	for (int i = 0; i < playerSize; i++)
	{
		if (!players[i]->GetIsFell())
		{
			int winner = i;

			if (winner == 3)
			{
				winner = 2;
			}
			else if (winner == 2)
			{
				winner = 3;
			}
			currentRoundWinner = winner;
			playerRoundWin[winner]++;
			break;
		}
	}

	currentRound++;
	
	// save value to file

	std::ofstream writefile(fileName);

	if (!writefile.is_open())
	{
		KK_ERROR("LevelShowcase: Cannot write Ui Position config file!");
	}
	else
	{
		KK_INFO("LevelShowcase: Open file Round Win Complete");

		nlohmann::json data;

		std::string playerScore;

		for (int i = 0; i < 4; i++)
		{
			playerScore = "Score_Player" + std::to_string(i);

			data[playerScore] = playerRoundWin[i];
		}

		std::string roundWinner = "RoundWinner";

		data[roundWinner] = currentRoundWinner;

		std::string roundNumber = "roundNumber";

		data[roundNumber] = currentRound;

		writefile << data;

		KK_INFO("LevelShowcase: Save Round Win Complete");

		writefile.close();
	}
}