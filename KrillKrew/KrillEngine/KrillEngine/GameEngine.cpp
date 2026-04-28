
#include "GameEngine.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine()
{
	renderer = nullptr;
}

GameEngine * GameEngine::GetInstance()
{
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return instance;
}

GLRenderer * GameEngine::GetRenderer()
{
	return this->renderer;
}

GameStateController* GameEngine::GetStateController()
{
	return this->stateController;
}

SDL_Window* GameEngine::GetSDLWindow()
{
	return this->window;
}
SDL_GLContext GameEngine::GetglContext()
{
	return this->glContext;
}

void GameEngine::SetSDLWindow(SDL_Window* window)
{
	this->window = window;
}

void GameEngine::SetglContext(SDL_GLContext context)
{
	this->glContext = context;
}

void GameEngine::Init(int width, int height)
{
	winWidth = width;
	winHeight = height;
	renderer = new GLRenderer(width, height);
	renderer->InitGL("../Resource/Shader/vertext.shd", "../Resource/Shader/fragment.shd");
	SetDrawArea(-3, 3, -3, 3);
	SetBackgroundColor(1.0f, 1.0f, 200.0f / 255);

	// Init Logger
	Krill::Log::Init();

	std::string f = "First";
	std::string s = "Second";
	KK_TRACE("Initialized Logger! {0}", f);
	KK_INFO("Initialized Logger! {0} {1}", f, s);

	stateController = new GameStateController();
	//stateController->loadingState = GameState::GS_LEVELSHOWCASE;
	stateController->loadingState = GameState::GS_LEVELMAINMENU;
	stateController->Init(GameState::GS_LEVELLOADING);
}

void GameEngine::Render(std::vector<DrawableObject*> renderObjects)
{
	this->GetRenderer()->Render(renderObjects);
}

void GameEngine::SetDrawArea(float left, float right, float bottom, float top)
{

	//printf("Left = %f | Right = %f | Bottom = %f | Top = %f \n", left, right, bottom, top);
	renderer->SetOrthoProjection(left, right, bottom, top);
}

void GameEngine::SetBackgroundColor(float r, float g, float b)
{
	renderer->SetClearColor(1.0f, 1.0f, 200.0f / 255);
}

void GameEngine::AddMesh(std::string name, MeshVbo* mesh)
{
	renderer->AddMesh(name, mesh);
}

void GameEngine::ClearMesh()
{
	renderer->ClearMesh();
}

int GameEngine::GetWindowWidth()
{
	return winWidth;
}

int GameEngine::GetWindowHeight()
{
	return winHeight;
}
