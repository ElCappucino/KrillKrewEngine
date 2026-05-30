#include "LevelWinRound.h"

void LevelWinRound::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	// Win Round

	spriteList["WinRound_BG"] = SpritesheetInfo("WinRound_BG", "../Resource/Texture/GameWin/UI_RW_BG.png", 1920, 1080, 1920, 1080);

	spriteList["WinRound_RoundNum"] = SpritesheetInfo("WinRound_RoundNum", "../Resource/Texture/GameWin/UI_RW_RoundNum.png", 330, 125, 990, 125);

	spriteList["WinRound_AllChar"] = SpritesheetInfo("WinRound_AllChar", "../Resource/Texture/GameWin/UI_RW_PlayerWinner.png", 919, 950, 3676, 950);

	spriteList["WinRound_Profile"] = SpritesheetInfo("WinRound_Profile", "../Resource/Texture/GameWin/UI_RW_PlayerProfile.png", 600, 150, 600, 150);

	spriteList["WinRound_PointNum"] = SpritesheetInfo("WinRound_PointNum", "../Resource/Texture/GameWin/UI_RW_Number.png", 36, 46, 144, 46);

}

void LevelWinRound::LevelInit()
{
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	SDL_GetWindowSize(GameEngine::GetInstance()->GetSDLWindow(), &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	/*KK_INFO("LevelWinRound: Fail to load RoundWin.json. Use test data");
	roundWinner = 0;
	roundNum = 1;

	playerScores[0] = 0;
	playerScores[1] = 0;
	playerScores[2] = 0;
	playerScores[3] = 0;*/

	if (!LoadInfo("../Resource/SceneData/RoundWin.json"))
	{
		// fail to load info, use test data
		KK_INFO("LevelWinRound: Fail to load RoundWin.json. Use test data");
		roundWinner = 0;
		roundNum = 1;

		playerScores[0] = 0;
		playerScores[1] = 0;
		playerScores[2] = 0;
		playerScores[3] = 0;
	}

	// fail to load config, use test data
	/*KK_INFO("LevelWinRound: Fail to load RoundWin_UI_Config.json. Use test data");
	RoundNum_pos = { 0, 0, 0 };
	RoundWinCharacter_pos = { 0, 0, 0 };
	PlayerProfile_pos = { 0, 0, 0 };

	for (glm::vec3& pos : PlayerScore_pos)
	{
		pos = { 0, 0, 0 };
	}*/

	if (!LoadUIPositionConfig("../Resource/SceneData/RoundWin_UI_Config.json"))
	{
		// fail to load config, use test data
		KK_INFO("LevelWinRound: Fail to load RoundWin_UI_Config.json. Use test data");
		RoundNum_pos = { 0, 0, 0 };
		RoundWinCharacter_pos = { 0, 0, 0 };
		PlayerProfile_pos = { 0, 0, 0 };

		for (glm::vec3& pos : PlayerScore_pos)
		{
			pos = { 0, 0, 0 };
		}
	}

	Background_UI = new UiObject();
	Background_UI->SetSpriteInfo(spriteList.find("WinRound_BG")->second);
	Background_UI->SetIsRender(true);
	Background_UI->uiType = UiObject::UIType::PauseMenu;
	objectsList.push_back(Background_UI);

	RoundNum_UI = new UiObject();
	RoundNum_UI->SetSpriteInfo(spriteList.find("WinRound_RoundNum")->second);
	RoundNum_UI->GetSpriteRenderer()->ShiftTo(0, roundNum - 1);
	RoundNum_UI->SetIsRender(true);
	RoundNum_UI->uiType = UiObject::UIType::PauseMenu;
	objectsList.push_back(RoundNum_UI);

	/*if (roundWinner == 2)
	{
		roundWinner = 3;
	}
	else if (roundWinner == 3)
	{
		roundWinner = 2;
	}*/

	RoundWinCharacter_UI = new UiObject();
	RoundWinCharacter_UI->SetSpriteInfo(spriteList.find("WinRound_AllChar")->second);
	RoundWinCharacter_UI->GetSpriteRenderer()->ShiftTo(0, roundWinner);
	RoundWinCharacter_UI->SetIsRender(true);
	RoundWinCharacter_UI->uiType = UiObject::UIType::PauseMenu;
	objectsList.push_back(RoundWinCharacter_UI);

	PlayerProfile_UI = new UiObject();
	PlayerProfile_UI->SetSpriteInfo(spriteList.find("WinRound_Profile")->second);
	PlayerProfile_UI->SetIsRender(true);
	PlayerProfile_UI->uiType = UiObject::UIType::PauseMenu;
	objectsList.push_back(PlayerProfile_UI);

	for (int i = 0; i < 4; i++)
	{
		PlayerScore_UI[i] = new UiObject();
		PlayerScore_UI[i]->SetSpriteInfo(spriteList.find("WinRound_PointNum")->second);
		PlayerScore_UI[i]->GetSpriteRenderer()->ShiftTo(0, playerScores[i]);
		PlayerScore_UI[i]->SetIsRender(true);
		PlayerScore_UI[i]->uiType = UiObject::UIType::PauseMenu;
		objectsList.push_back(PlayerScore_UI[i]);
	}

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
void LevelWinRound::LevelUpdate() 
{

	glGetIntegerv(GL_VIEWPORT, currentViewport);

	windowWidth = currentViewport[2];
	windowHeight = currentViewport[3];

	//KK_TRACE("Current viewport width = {0}, height = {1}", windowWidth, windowHeight);

	UpdateInput();
	UpdateUI();

}

void LevelWinRound::LevelDraw()
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

	ImGui::DragFloat("RoundNum.x", &RoundNum_pos.x, 2.0f, -1024.f, 1024.f, "%.3f");
	ImGui::DragFloat("RoundNum.y", &RoundNum_pos.y, 2.0f, -1024.f, 1024.f, "%.3f");

	ImGui::DragFloat("RoundWinCharacter.x", &RoundWinCharacter_pos.x, 2.0f, -1024.f, 1024.f, "%.3f");
	ImGui::DragFloat("RoundWinCharacter.y", &RoundWinCharacter_pos.y, 2.0f, -1024.f, 1024.f, "%.3f");

	ImGui::DragFloat("PlayerProfile.x", &PlayerProfile_pos.x, 2.0f, -1024.f, 1024.f, "%.3f");
	ImGui::DragFloat("PlayerProfile.y", &PlayerProfile_pos.y, 2.0f, -1024.f, 1024.f, "%.3f");

	for (int i = 0; i < 4; i++)
	{
		ImGui::PushID(i);
		ImGui::DragFloat("PlayerScore.x", &PlayerScore_pos[i].x, 2.0f, -1024.f, 1024.f, "%.3f");
		ImGui::DragFloat("PlayerScore.y", &PlayerScore_pos[i].y, 2.0f, -1024.f, 1024.f, "%.3f");
		ImGui::PopID();
	}*/
	

	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());

	// cout << "Draw Level" << endl;
}

void LevelWinRound::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
}

void LevelWinRound::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SaveUIPositionConfig("../Resource/SceneData/RoundWin_UI_Config.json");
	SaveInfo("../Resource/SceneData/RoundWin.json");
}

void LevelWinRound::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

}

void LevelWinRound::HandleKey(char key) {

}

void LevelWinRound::HandleMouse(int type, int x, int y) {

}

void LevelWinRound::UpdateInput()
{
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();

		for (int i = 0; i < 4; i++)
		{
			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{
				int maxPoint = -1;

				for (int i = 0; i < 4; i++)
				{
					if (playerScores[i] > maxPoint)
					{
						maxPoint = playerScores[i];
					}
				}

				if (maxPoint >= 3)
				{
					GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELMATCHWIN;
					GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
				}
				else
				{
					GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELSHOWCASE;
					GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
				}
				
			}
		}
	}
}

void LevelWinRound::UpdateUI()
{
	Background_UI->SetPosition(glm::vec3(0, 0, 0));
	Background_UI->SetSize
	(
		Background_size.x,
		Background_size.y
	);

	RoundNum_UI->SetPosition(RoundNum_pos);
	RoundNum_UI->SetSize
	(
		RoundNum_size.x,
		RoundNum_size.y
	);

	RoundWinCharacter_UI->SetPosition(RoundWinCharacter_pos);
	RoundWinCharacter_UI->SetSize
	(
		RoundWinCharacter_size.x,
		RoundWinCharacter_size.y
	);

	PlayerProfile_UI->SetPosition(PlayerProfile_pos);
	PlayerProfile_UI->SetSize
	(
		PlayerProfile_size.x,
		PlayerProfile_size.y
	);

	for (int i = 0; i < 4; i++)
	{
		PlayerScore_UI[i]->SetPosition(PlayerScore_pos[i]);
		PlayerScore_UI[i]->SetSize
		(
			PlayerScore_size.x,
			PlayerScore_size.y
		);
	}
}

void LevelWinRound::SaveInfo(std::string filename)
{
	// just for testing

	std::ofstream file(filename);

	if (!file.is_open())
	{
		KK_ERROR("LevelWinRound: Cannot write Ui Position config file!");
	}
	else
	{
		KK_INFO("LevelWinRound: Open file Round Win Complete");

		nlohmann::json data;

		std::string playerScore;

		for (int i = 0; i < 4; i++)
		{
			playerScore = "Score_Player" + std::to_string(i);

			data[playerScore] = playerScores[i];
		}

		std::string roundWinner = "RoundWinner";

		data[roundWinner] = this->roundWinner;

		std::string roundNumber = "roundNumber";

		data[roundNumber] = this->roundNum;

		file << data;

		KK_INFO("LevelWinRound: Save Round Win Complete");

		file.close();
	}

}

bool LevelWinRound::LoadInfo(std::string filename)
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

		std::string roundWinner = "RoundWinner";

		if (!data.count(roundWinner))
		{
			KK_ERROR("LevelWinRound: Cannot read round Winner!");
		}
		else
		{
			this->roundWinner = data[roundWinner];
		}

		std::string roundNumber = "roundNumber";

		if (!data.count(roundNumber))
		{
			KK_ERROR("LevelWinRound: Cannot read round Number!");
		}
		else
		{
			this->roundNum = data[roundNumber];
		}

		file.close();

		return true;
	}

}

bool LevelWinRound::LoadUIPositionConfig(std::string filename)
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

		if (!data.count("RoundNum_Pos"))
		{
			KK_ERROR("LevelWinRound: Cannot read RoundNum_Pos!");
		}
		else
		{
			RoundNum_pos.x = data["RoundNum_Pos"]["x"];
			RoundNum_pos.y = data["RoundNum_Pos"]["y"];
		}

		if (!data.count("RoundWinCharacter_Pos"))
		{
			KK_ERROR("LevelWinRound: Cannot read RoundWinCharacter_pos!");
		}
		else
		{
			RoundWinCharacter_pos.x = data["RoundWinCharacter_Pos"]["x"];
			RoundWinCharacter_pos.y = data["RoundWinCharacter_Pos"]["y"];
		}

		if (!data.count("PlayerProfile_Pos"))
		{
			KK_ERROR("LevelWinRound: Cannot read RoundNum_Pos!");
		}
		else
		{
			PlayerProfile_pos.x = data["PlayerProfile_Pos"]["x"];
			PlayerProfile_pos.y = data["PlayerProfile_Pos"]["y"];
		}

		std::string playerScorePos;

		for (int i = 0; i < 4; i++)
		{
			playerScorePos = "PlayerScorePos_P" + std::to_string(i + 1);
			if (!data.count(playerScorePos))
			{
				KK_ERROR("LevelWinRound: Cannot read {0}!", playerScorePos);
			}
			else
			{
				PlayerScore_pos[i].x = data[playerScorePos]["x"];
				PlayerScore_pos[i].y = data[playerScorePos]["y"];
			}
		}

		file.close();
	}
}

void LevelWinRound::SaveUIPositionConfig(std::string filename)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		KK_ERROR("LevelWinRound: Cannot write Ui Position config file!");
	}
	else
	{
		KK_INFO("LevelWinRound: Open file UI config Complete");
		nlohmann::json data;

		data["RoundNum_Pos"]["x"] = RoundNum_pos.x;
		data["RoundNum_Pos"]["y"] = RoundNum_pos.y;

		data["RoundWinCharacter_Pos"]["x"] = RoundWinCharacter_pos.x;
		data["RoundWinCharacter_Pos"]["y"] = RoundWinCharacter_pos.y;

		data["PlayerProfile_Pos"]["x"] = PlayerProfile_pos.x;
		data["PlayerProfile_Pos"]["y"] = PlayerProfile_pos.y;

		std::string playerScorePos;
		for (int i = 0; i < 4; i++)
		{
			playerScorePos = "PlayerScorePos_P" + std::to_string(i + 1);
			data[playerScorePos]["x"] = PlayerScore_pos[i].x;
			data[playerScorePos]["y"] = PlayerScore_pos[i].y;
		}

		file << data;
		KK_INFO("LevelWinRound: Save UI config Complete");

		file.close();
	}
}