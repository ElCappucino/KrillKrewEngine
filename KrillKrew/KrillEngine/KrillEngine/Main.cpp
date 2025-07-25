

// OpenGL headers
#include <GL/glew.h>

// SDL headers
#include <SDL_main.h>
#include <SDL.h>
#include <SDL_opengl.h>

// ImGui
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include "GameEngine.h"
#include "Joystick.h"

using namespace std;
bool quit;
const GLint WIDTH = 1280, HEIGHT = 720;

SDL_Window* window;
SDL_GLContext glContext;
SDL_Event sdlEvent;

GameEngine * engine = nullptr;

int main(int argc, char *argv[])
{
	quit = false;

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Initialize video subsystem
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
		// Display error message
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		// Create window
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);

		window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			// Display error message
			cout << "Window could not be created! SDL_Error" << SDL_GetError() << endl;
			return false;
		}
		else
		{
			// Create OpenGL context
			glContext = SDL_GL_CreateContext(window);

			if (glContext == NULL)
			{
				// Display error message
				cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
				return false;
			}
			else
			{
				// Initialize glew
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << endl;
					return false;
				}
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
				}


				engine = GameEngine::GetInstance();
				engine->SetSDLWindow(window);
				engine->SetglContext(glContext);
				engine->Init(WIDTH, HEIGHT);
			}
		}
	}

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

	// Game loop
	while (engine->GetStateController()->gameStateCurr != GameState::GS_QUIT)
	{

		if (engine->GetStateController()->gameStateCurr != GS_RESTART)
		{
			engine->GetStateController()->LoadLevel();
		}
		else
		{
			engine->GetStateController()->gameStateNext =
			engine->GetStateController()->gameStateCurr = engine->GetStateController()->gameStatePrev;
		}
			
		

		// Initialize the gamestate
		engine->GetStateController()->InitLevel();

		while (engine->GetStateController()->gameStateCurr == engine->GetStateController()->gameStateNext)
		{

			while (SDL_PollEvent(&sdlEvent) != 0)
			{
				ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

				// std::cout << "Event not 0" << endl;
				if (sdlEvent.type == SDL_JOYDEVICEADDED) // Joystick code
				{
					std::cout << "Connected" << endl;
					Joystick::OnJoystickConnected(sdlEvent.cdevice);
				}
				if (sdlEvent.type == SDL_JOYDEVICEREMOVED)
				{
					std::cout << "Disconnected" << endl;
					Joystick::OnJoystickDisconnected(sdlEvent.cdevice);
				}

				// Esc button is pressed
				if (sdlEvent.type == SDL_QUIT)
				{
					std::cout << "Quit" << endl;
					engine->GetStateController()->gameStateNext = GameState::GS_QUIT;
				}
				else if (sdlEvent.type == SDL_KEYDOWN)
				{
					switch (sdlEvent.key.keysym.sym)
					{
					case SDLK_LEFT:
					case SDLK_a:	engine->GetStateController()->HandleKeyLevel('a'); break;
					case SDLK_RIGHT:
					case SDLK_d:	engine->GetStateController()->HandleKeyLevel('d'); break;
					case SDLK_UP:
					case SDLK_w:	engine->GetStateController()->HandleKeyLevel('w'); break;
					case SDLK_DOWN:
					case SDLK_s:	engine->GetStateController()->HandleKeyLevel('s'); break;
					case SDLK_ESCAPE: engine->GetStateController()->HandleKeyLevel('q'); break;
					case SDLK_r: engine->GetStateController()->HandleKeyLevel('r'); break;
					case SDLK_e: engine->GetStateController()->HandleKeyLevel('e'); break;
					case SDLK_i: engine->GetStateController()->HandleKeyLevel('i'); break;
					case SDLK_o: engine->GetStateController()->HandleKeyLevel('o'); break;
					case SDLK_1: engine->GetStateController()->HandleKeyLevel('1'); break;
					case SDLK_2: engine->GetStateController()->HandleKeyLevel('2'); break;
					case SDLK_3: engine->GetStateController()->HandleKeyLevel('3'); break;
					case SDLK_4: engine->GetStateController()->HandleKeyLevel('4'); break;
					}
				}
				else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
				{
					if (sdlEvent.button.button == SDL_BUTTON_LEFT)
					{
						engine->GetStateController()->HandleMouseLevel(0, sdlEvent.button.x, sdlEvent.button.y);
					}
				}
				
			}

			engine->GetStateController()->UpdateLevel();

			engine->GetStateController()->DrawLevel();
		}

		engine->GetStateController()->Freelevel();

		if (engine->GetStateController()->gameStateNext != GS_RESTART)
		{
			engine->GetStateController()->UnloadLevel();
		}

		

		engine->GetStateController()->gameStatePrev = engine->GetStateController()->gameStateCurr;
		engine->GetStateController()->gameStateCurr = engine->GetStateController()->gameStateNext;
	}

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}


