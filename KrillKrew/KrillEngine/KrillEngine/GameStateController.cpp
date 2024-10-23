#include "GameStateController.h"
#include "Level.h"
#include "LevelGameplay.h"
#include "LevelMapTest.h"
#include "LevelLoading.h"

GameStateController::GameStateController()
{
	// set the initial game state
	gameStateCurr = gameStatePrev = gameStateNext = GameState::GS_NONE;

	currentLevel = nullptr;
}

void GameStateController::Init(GameState gameStateInit)
{
	// reset the current, previoud and next game
	gameStateCurr = gameStatePrev = gameStateNext = gameStateInit;
}

void GameStateController::LoadLevel()
{
	if ((gameStateCurr == GameState::GS_RESTART) || (gameStateCurr == GameState::GS_QUIT))
	{
		return;
	}

	switch (gameStateCurr)
	{
		case GameState::GS_LEVEL1:
			currentLevel = new Level();
			break;
		case GameState::GS_LEVELMAPTEST:
			currentLevel = new LevelMapTest();
			break;
		case GameState::GS_LEVELGAMEPLAY:
			currentLevel = new LevelGameplay();
			break;
		case GameState::GS_LEVELLOADING:
			currentLevel = new LevelLoading();
			break;
		
		default:
			std::cout << "gGameStateCurr : invalid state!!" << std::endl;
			exit(1);
	}

	currentLevel->LevelLoad();
}

void GameStateController::InitLevel()
{
	currentLevel->LevelInit();
}

void GameStateController::UpdateLevel()
{
	currentLevel->LevelUpdate();
}

void GameStateController::DrawLevel()
{
	currentLevel->LevelDraw();
}

void GameStateController::Freelevel()
{
	currentLevel->LevelFree();
}

void GameStateController::UnloadLevel()
{
	currentLevel->LevelUnload();
}

void GameStateController::HandleKeyLevel(char key)
{
	currentLevel->HandleKey(key);
}

void GameStateController::HandleMouseLevel(int type, int x, int y)
{
	currentLevel->HandleMouse(type, x, y);
}