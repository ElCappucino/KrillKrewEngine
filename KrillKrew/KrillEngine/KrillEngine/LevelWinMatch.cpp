#include "LevelWinMatch.h"

void LevelWinMatch::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	// Win Match
	
	spriteList["WinMatch_BG_Char1"] = SpritesheetInfo("WinMatch_BG_Char1", "../Resource/Texture/GameWin/UI_GW_Char1.png", 1920, 1080, 1920, 1080);
	spriteList["WinMatch_BG_Char2"] = SpritesheetInfo("WinMatch_BG_Char2", "../Resource/Texture/GameWin/UI_GW_Char2.png", 1920, 1080, 1920, 1080);
	spriteList["WinMatch_BG_Char3"] = SpritesheetInfo("WinMatch_BG_Char3", "../Resource/Texture/GameWin/UI_GW_Char3.png", 1920, 1080, 1920, 1080);
	spriteList["WinMatch_BG_Char4"] = SpritesheetInfo("WinMatch_BG_Char4", "../Resource/Texture/GameWin/UI_GW_Char4.png", 1920, 1080, 1920, 1080);

	spriteList["WinMatch_PlayerNum"] = SpritesheetInfo("WinMatch_PlayerNum", "../Resource/Texture/GameWin/UI_GW_PlayerNum.png", 820, 175, 3280, 175);

	

}

void LevelWinMatch::LevelInit() 
{
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(GameEngine::GetInstance()->GetSDLWindow(), GameEngine::GetInstance()->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	std::cout << GameEngine::GetInstance()->GetStateController()->loadingState << std::endl;
}
void LevelWinMatch::LevelUpdate() 
{
	UpdateInput();
	UpdateUI();
	
}

void LevelWinMatch::LevelDraw() 
{
	GameEngine::GetInstance()->Render(objectsList);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	

	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());

	// cout << "Draw Level" << endl;
}

void LevelWinMatch::LevelFree() 
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
}

void LevelWinMatch::LevelUnload() 
{
	GameEngine::GetInstance()->ClearMesh();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	
}

void LevelWinMatch::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

}

void LevelWinMatch::HandleKey(char key) {

}

void LevelWinMatch::HandleMouse(int type, int x, int y) {

}

void LevelWinMatch::UpdateInput() 
{
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();

		for (int i = 0; i < 1; i++)
		{
			
		}
	}
}

void LevelWinMatch::UpdateUI() 
{
	
}
