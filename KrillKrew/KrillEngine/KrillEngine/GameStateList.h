#pragma once

/// @brief The enum list of game state
enum GameState
{
	// list of all game states 
	GS_LEVEL1 = 0,
	GS_LEVEL2,
	GS_LEVELGAMEPLAY,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT,
	GS_NONE
};