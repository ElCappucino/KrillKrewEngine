#pragma once

#include <vector>
#include <cmath>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "GameStateController.h"
#include "Log.h"


/// @brief The class for creating game engine instance to control the renderer and game state.
class GameEngine
{
	static GameEngine* instance;
	int winWidth, winHeight;
	
	GLRenderer *renderer;
	GameStateController* stateController;
	SDL_Window* window;
	SDL_GLContext glContext;

	GameEngine();
public:
	static GameEngine* GetInstance();
	GLRenderer * GetRenderer();
	GameStateController* GetStateController();
	SDL_Window* GetSDLWindow();
	SDL_GLContext GetglContext();
	void SetSDLWindow(SDL_Window* window);
	void SetglContext(SDL_GLContext context);
	void Init(int width, int height);
	void SetDrawArea(float left, float right, float bottom, float top);
	void SetBackgroundColor(float r, float g, float b);
	void AddMesh(std::string name, MeshVbo* mesh);
	void ClearMesh();
	void Render(std::vector<DrawableObject*> renderObjects);
	int GetWindowWidth();
	int GetWindowHeight();
};