#pragma once

/// @brief The enum list of game state
enum GameState
{
	// list of all game states 
	GS_LEVEL1 = 0,
	GS_LEVELGAMEPLAY,
	GS_LEVELMAPTEST,
	GS_LEVELLOADING,
	GS_LEVELSHOWCASE,
	GS_LEVELIMGUI,
	GS_LEVELSELECTABILITY,
	GS_LEVELMAINMENU,
	GS_LEVELROUNDWIN,
	GS_LEVELMATCHWIN,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT,
	GS_NONE
};