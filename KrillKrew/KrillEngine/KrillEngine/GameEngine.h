#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "GameStateController.h"


using namespace std;

/// @brief The class for creating game engine instance to control the renderer and game state.
class GameEngine
{
	static GameEngine* instance;
	int winWidth, winHeight;
	float left, right, bottom, top;
	
	GLRenderer *renderer;
	GameStateController* stateController;
	GameEngine();
public:
	static GameEngine* GetInstance();
	GLRenderer * GetRenderer();
	GameStateController* GetStateController();
	void Init(int width, int height);
	void SetDrawArea(float left, float right, float bottom, float top);
	void SetBackgroundColor(float r, float g, float b);
	void AddMesh(string name, MeshVbo* mesh);
	void ClearMesh();
	void Render(vector<DrawableObject*> renderObjects);
	int GetWindowWidth();
	int GetWindowHeight();
	float getLeft();
	float getRight();
	float getBottom();
	float getTop();
};