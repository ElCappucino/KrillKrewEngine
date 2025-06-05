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

	SDL_GetWindowSize(GameEngine::GetInstance()->GetSDLWindow(), &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	timer = Timer::Instance();

	if (!LoadUIPositionConfig("../Resource/SceneData/MatchWin_UI_Config.json"))
	{
		KK_ERROR("Cannot Load UI Config");
	}

	if (!LoadWinnerInfo("../Resource/SceneData/RoundWin.json"))
	{
		KK_ERROR("Cannot Load Round Win");
		matchWinner = 0;
	}

	if (matchWinner == 3)
	{
		matchWinner = 2;
	}
	else if (matchWinner == 2)
	{
		matchWinner = 3;
	}

	Background_UI = new UiObject();
	std::string spriteName = "WinMatch_BG_Char" + std::to_string(matchWinner + 1);
	Background_UI->SetSpriteInfo(spriteList.find(spriteName)->second);
	Background_UI->SetIsRender(true);
	Background_UI->uiType = UiObject::UIType::PauseMenu;
	objectsList.push_back(Background_UI);
	
	PlayerNum_UI = new UiObject();
	PlayerNum_UI->SetSpriteInfo(spriteList.find("WinMatch_PlayerNum")->second);
	PlayerNum_UI->GetSpriteRenderer()->ShiftTo(0, matchWinner);
	PlayerNum_UI->SetIsRender(true);
	PlayerNum_UI->uiType = UiObject::UIType::PauseMenu;
	objectsList.push_back(PlayerNum_UI);

	//PlayerNum_size = glm::vec3(PlayerNum_UI->GetSpriteRenderer()->GetSpriteWidth(), PlayerNum_UI->GetSpriteRenderer()->GetSpriteHeight(), 0);

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
	glGetIntegerv(GL_VIEWPORT, currentViewport);

	windowWidth = currentViewport[2];
	windowHeight = currentViewport[3];



	if (isHold)
	{
		holdTime += 0.01f;
		//KK_TRACE("holdTime = {0}", holdTime);
		//KK_TRACE("timer->getDeltaTime() = {0}", timer->getDeltaTime());
	}
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

	/*ImGui::Text("UI Position");

	ImGui::DragFloat("PlayerNum_pos.x", &PlayerNum_pos.x, 2.0f, -1024.f, 1024.f, "%.3f");
	ImGui::DragFloat("PlayerNum_pos.y", &PlayerNum_pos.y, 2.0f, -1024.f, 1024.f, "%.3f");*/

	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());

	// cout << "Draw Level" << endl;
}

void LevelWinMatch::LevelFree() 
{
	for (DrawableObject* obj : objectsList) 
	{
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

	SaveUIPositionConfig("../Resource/SceneData/MatchWin_UI_Config.json");
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

		for (int i = 0; i < 4; i++)
		{
			if (Joystick::GetButtonDown(i, Joystick::Button::Circle))
			{
				isHold = true;
			}

			if (Joystick::GetButtonUp(i, Joystick::Button::Circle))
			{
				isHold = false;
				if (holdTime >= 1.5f)
				{
					GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELMAINMENU;
					GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
				}
				holdTime = 0.0f;
			}
		}
	}
}

void LevelWinMatch::UpdateUI() 
{
	Background_UI->SetPosition(glm::vec3(0, 0, 0));
	Background_UI->SetSize
	(
		Background_size.x * windowWidth / 1920.f,
		Background_size.y * windowHeight / 1080.f
	);

	PlayerNum_UI->SetPosition(PlayerNum_pos);
	PlayerNum_UI->SetSize
	(
		PlayerNum_size.x * windowWidth / 1920.f,
		PlayerNum_size.y * windowHeight / 1080.f
	);
}

bool LevelWinMatch::LoadWinnerInfo(const std::string filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		KK_ERROR("LevelWinRound: Cannot read info file!");

		return false;
	}
	else
	{
		nlohmann::json data = nlohmann::json::parse(file);

		std::string playerScore;

		for (int i = 0; i < 4; i++)
		{
			playerScore = "Score_Player" + std::to_string(i);

			if (!data.count(playerScore))
			{
				KK_ERROR("LevelWinRound: Cannot read player Score!");
			}
			else
			{
				playerScores[i] = data[playerScore];
			}
		}

		file.close();

		int maxPoint = -1;

		for (int i = 0; i < 4; i++)
		{
			if (playerScores[i] > maxPoint)
			{
				maxPoint = playerScores[i];
				matchWinner = i;
			}
		}
	}
}

void LevelWinMatch::SaveUIPositionConfig(std::string filename)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		KK_ERROR("LevelWinMatch: Cannot Write UI config file!");
	}
	else
	{
		KK_INFO("LevelWinMatch: Open file UI config Complete");
		nlohmann::json data;

		data["PlayerNum_pos"]["x"] = PlayerNum_pos.x;
		data["PlayerNum_pos"]["y"] = PlayerNum_pos.y;

		file << data;
		file.close();
	}
}
bool LevelWinMatch::LoadUIPositionConfig(std::string filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		KK_ERROR("LevelWinMatch: Cannot read config file!");

		return false;
	}
	else
	{
		nlohmann::json data = nlohmann::json::parse(file);

		if (!data.count("PlayerNum_pos"))
		{
			KK_ERROR("LevelWinMatch: Cannot read PlayerNum_pos!");
		}
		else
		{
			PlayerNum_pos.x = data["PlayerNum_pos"]["x"];
			PlayerNum_pos.y = data["PlayerNum_pos"]["y"];
		}

		file.close();
	}
}
