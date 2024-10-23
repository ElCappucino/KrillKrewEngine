#pragma once

#include "GameStateList.h"

class Level;

/// @brief The class for setup the game state and control during scene
class GameStateController
{
private:
	Level* currentLevel;

public:

	GameState gameStateCurr;
	GameState gameStatePrev;
	GameState gameStateNext;
	GameState loadingState;

	GameStateController();
	void Init(GameState gameStateInit);

	void LoadLevel();
	void InitLevel();
	void UpdateLevel();
	void DrawLevel();
	void Freelevel();
	void UnloadLevel();
	void HandleKeyLevel(char key);
	void HandleMouseLevel(int type, int x, int y);

};