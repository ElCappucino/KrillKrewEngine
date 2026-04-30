#include "LevelMainMenu.h"

void LevelMainMenu::LevelLoad() 
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	spriteList["BG"] = SpritesheetInfo("BG", "../Resource/Texture/Menu/UI_Menu_BG.png", 1920, 1080, 1920, 1080);
	spriteList["Text"] = SpritesheetInfo("Text", "../Resource/Texture/Menu/UI_Menu_Text.png", 289, 65, 2312, 65);
	spriteList["Name"] = SpritesheetInfo("Name", "../Resource/Texture/Menu/UI_Menu_KrillsKrew.png", 470, 55, 940, 55);
	spriteList["Credit"] = SpritesheetInfo("Credit", "../Resource/Texture/Menu/UI_Menu_Credit.png", 1920, 1080, 1920, 1080);
	spriteList["FadeBlack"] = SpritesheetInfo("FadeBlack", "../Resource/Texture/Menu/UI_Tutorial_BlackFade.png", 1920, 1080, 1920, 1080);

	spriteList["TutorialBG"] = SpritesheetInfo("TutorialBG", "../Resource/Texture/Menu/UI_Tutorial_BG.png", 1173, 696, 1173, 696);
	spriteList["TutorialInfo"] = SpritesheetInfo("TutorialInfo", "../Resource/Texture/Menu/UI_Tutorial_Info.png", 1173, 696, 3519, 696);

	spriteList["AreYouSure"] = SpritesheetInfo("AreYouSure", "../Resource/Texture/Are You Sure/UI_AreYouSure_BG.png", 676, 317, 2028, 317);
	spriteList["AreYouSureYN"] = SpritesheetInfo("AreYouSureYN", "../Resource/Texture/Are You Sure/UI_AreYouSure_YesNo.png", 235, 45, 940, 45);

	spriteList["OptionsBG"] = SpritesheetInfo("OptionsBG", "../Resource/Texture/Pause and Options/UI_Options_BG.png", 623, 671, 623, 671);
	spriteList["OptionsDisplay"] = SpritesheetInfo("OptionsDisplay", "../Resource/Texture/Pause and Options/UI_Options_Display_tab.png", 309, 50, 1236, 50);
	spriteList["OptionsDisplayDropdown"] = SpritesheetInfo("OptionsDisplayDropdown", "../Resource/Texture/Pause and Options/UI_Options_Display_tabdropdown.png", 300, 94, 600, 94);
	spriteList["OptionsText"] = SpritesheetInfo("OptionsText", "../Resource/Texture/Pause and Options/UI_Options_text.png", 183, 25, 1464, 25);
	spriteList["OptionsVolumeBox"] = SpritesheetInfo("OptionsVolumeBox", "../Resource/Texture/Pause and Options/UI_Options_Volume_box.png", 32, 32, 128, 32);
	spriteList["OptionsVolumeKnob"] = SpritesheetInfo("OptionsVolumeKnob", "../Resource/Texture/Pause and Options/UI_Options_Volume_knob.png", 21, 41, 42, 41);
	spriteList["OptionsVolumeTrack"] = SpritesheetInfo("OptionsVolumeTrack", "../Resource/Texture/Pause and Options/UI_Options_Volume_track.png", 406, 12, 812, 12);

	KrillSoundManager::SoundManager::GetInstance()->LoadMusic("Ability_Selection", "../Resource/Audio/BGMusic/Ability_Selection.mp3");

	KrillSoundManager::SoundManager::GetInstance()->PlayMusic("Ability_Selection", true);
}

UiObject* LevelMainMenu::InitUI(std::string name, SpritesheetInfo spriteInfo, glm::vec2 pos, glm::vec2 size, glm::vec2 spriteShiftPos)
{
	UiObject* ui = new UiObject();
	ui->SetSpriteInfo(spriteInfo);
	ui->SetPosition({ pos.x, pos.y, 0 });
	ui->SetSize(size.x, size.y);
	ui->ShiftSpriteTo(spriteShiftPos.x, spriteShiftPos.y);
	return ui;
}

UiObject* LevelMainMenu::InitButtonUI(std::string name, SpritesheetInfo spriteInfo, ButtonData* buttonData, glm::vec2 spriteShiftPos)
{
	UiObject* ui = new UiObject();
	ui->SetSpriteInfo(spriteInfo);
	ui->SetPosition({ buttonData->pos.x, buttonData->pos.y, 0 });
	ui->SetSize(buttonData->size.x, buttonData->size.y);
	ui->ShiftSpriteTo(spriteShiftPos.x, spriteShiftPos.y);
	return ui;
}
void LevelMainMenu::LevelInit() 
{
	soundManager = KrillSoundManager::SoundManager::GetInstance();
	renderer = GameEngine::GetInstance()->GetRenderer();
	gameEngine = GameEngine::GetInstance();

	renderer->SetOrthoProjection
	(
		-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2)
	);

	SDL_GetWindowSize(gameEngine->GetSDLWindow(), &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	glm::vec2 backgroundSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
	UiObject* BG = InitUI("BG", spriteList["BG"], glm::vec2(0, 0), backgroundSize, glm::vec2(0, 0));
	objectsList.push_back(BG);

	// game name
	InitButtonData("GameName", 0, { 100, 100 }, { 470, 55 }, { 0, 0 }, 0, "../Resource/SceneData/text0.json");

	UiObject* name = InitButtonUI("GameNameUI", spriteList["Name"], Buttons.at(0), glm::vec2(0, 0));
	objectsList.push_back(name);
	textList.push_back(name);

	//text button
	for (int i = 1; i < 5; i++) 
	{
		std::string fileName = "../Resource/SceneData/text" + std::to_string(i) + ".json";

		int buttonColumn = (i - 1) * 2;
		std::string buttonName = "Text" + std::to_string(i);
		glm::vec2 spriteshiftPos(0, Buttons.at(i)->column);

		InitButtonData(buttonName, i, { 100, 100 }, { 289, 65 }, { 0, 0 }, buttonColumn, fileName);

		UiObject* text = InitButtonUI(buttonName, spriteList["Text"], Buttons.at(i), spriteshiftPos);

		objectsList.push_back(text);
		textList.push_back(text);
	}
	
	//config yesno
	InitButtonData("YesNo", 6, { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/YesNoConfig.json");

	//config text option
	InitButtonData("TextOption", 6, { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/TextOptionConfig.json");

	//config display
	InitButtonData("Display", 7, { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/DisplayConfig.json");

	//config volume track
	InitButtonData("VolumeTrack", 8, { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/VolumeTrackConfig.json");

	soundManager->LoadVolumeConfig
	(
		"../Resource/SceneData/CurrentVolume.json",
		masterVolume,
		isToggleVolume[0],
		BGMVolume,
		isToggleVolume[2],
		SFXVolume,
		isToggleVolume[1]
	);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(gameEngine->GetSDLWindow(), gameEngine->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	KK_TRACE("Level Main Menu Loaded");
}

void LevelMainMenu::InitButtonData(std::string name, int number, glm::vec2 pos, glm::vec2 size, glm::vec2 offset, int column, std::string configPath)
{
	ButtonData* button = new ButtonData();
	button->name = name;
	button->number = number;
	button->pos = pos;
	button->size = size;
	button->offset = offset;
	button->column = column;
	Buttons.push_back(button);
	loadConfig(configPath);
}

void LevelMainMenu::LevelUpdate() 
{
	KrillSoundManager::SoundManager::GetInstance()->SetVolumeAllMusic((masterVolume / 100.0f) * BGMVolume * 0.01f * (128.f - 0));
	KrillSoundManager::SoundManager::GetInstance()->SetVolumeAllSFX((masterVolume / 100.0f) * SFXVolume * 0.01f * (128.f - 0));

	if (!isToggleVolume[0])
	{
		KrillSoundManager::SoundManager::GetInstance()->SetVolumeAllSFX(0);
		KrillSoundManager::SoundManager::GetInstance()->SetVolumeAllMusic(0);
	}

	if (!isToggleVolume[1])
	{
		KrillSoundManager::SoundManager::GetInstance()->SetVolumeAllSFX(0);
	}

	if (!isToggleVolume[2])
	{
		KrillSoundManager::SoundManager::GetInstance()->SetVolumeAllMusic(0);
	}

	

	UpdateInput();
	UpdateUi();

	// select box
	for (int i = 0; i < textList.size(); i++)
	{
		if (Buttons.at(i)->number == playerWhere)
		{
			Buttons.at(i)->playerHere = true;
		}
		else {
			Buttons.at(i)->playerHere = false;
		}
	}
}

void LevelMainMenu::LevelDraw() 
{
	GameEngine::GetInstance()->Render(objectsList);
	
	ShowImGuiConfig(true);

	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());

	// cout << "Draw Level" << endl;
}

void LevelMainMenu::ShowImGuiConfig(bool isShowing)
{
	if (!isShowing)
		return;

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (ImGui::Button("Go levelSelectAbility")) {
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSELECTABILITY;
	}
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
		if (ImGui::BeginTabItem("Text")) {
			if (ImGui::Button("Save config")) {
				for (int i = 0; i < Buttons.size(); i++) {
					std::string fileName = "text" + std::to_string(i) + ".json";
					saveConfig(fileName, Buttons.at(i));
				}
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				for (int i = 0; i < Buttons.size(); i++) {
					std::string fileName = "text" + std::to_string(i) + ".json";
					loadConfig(fileName);
					textList.at(i)->SetPosition(glm::vec3(Buttons.at(i)->pos.x, Buttons.at(i)->pos.y, 0));
					textList.at(i)->SetSize(Buttons.at(i)->size.x, -Buttons.at(i)->size.y);
				}
			}

			for (int i = 0; i < Buttons.size(); i++) {
				ImGui::PushID(i);
				ImGui::Text("Text%d", i);
				ImGui::InputFloat("PosX", &Buttons.at(i)->pos.x, 1.0f, 1.0f, "%.2f");
				ImGui::InputFloat("PosY", &Buttons.at(i)->pos.y, 1.0f, 1.0f, "%.2f");
				ImGui::InputFloat("Width", &Buttons.at(i)->size.x, 1.0f, 1.0f, "%.2f");
				ImGui::InputFloat("Height", &Buttons.at(i)->size.y, 1.0f, 1.0f, "%.2f");
				ImGui::PopID();
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("YesNo")) {
			configNum = 5;
			if (ImGui::Button("Save config")) {
				std::string fileName = "YesNoConfig.json";
				saveConfig(fileName, Buttons.at(configNum));
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
					std::string fileName = "YesNoConfig.json";
					loadConfig(fileName);
					for (int i = 0; i < yesNoList.size(); i++) {
						yesNoList.at(i)->SetPosition(glm::vec3(Buttons.at(configNum)->pos.x + (i * Buttons.at(configNum)->offset.x), Buttons.at(configNum)->pos.y, 0));
					}
			}
			ImGui::InputFloat("PosX", &Buttons.at(configNum)->pos.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &Buttons.at(configNum)->pos.y, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &Buttons.at(configNum)->offset.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &Buttons.at(configNum)->offset.y, 1.0f, 1.0f, "%.2f");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Text option")) {
			configNum = 6;
			if (ImGui::Button("Save config")) {
				std::string fileName = "TextOptionConfig.json";
				saveConfig(fileName, Buttons.at(configNum));
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				std::string fileName = "TextOptionConfig.json";
				loadConfig(fileName);
				for (int i = 0; i < textOptionList.size(); i++) {
					textOptionList.at(i)->SetPosition(glm::vec3(Buttons.at(configNum)->pos.x, Buttons.at(configNum)->pos.y + (i * Buttons.at(configNum)->offset.y), 0));
				}
			}
			ImGui::InputFloat("PosX", &Buttons.at(configNum)->pos.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &Buttons.at(configNum)->pos.y, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &Buttons.at(configNum)->offset.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &Buttons.at(configNum)->offset.y, 1.0f, 1.0f, "%.2f");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("display option")) {
			configNum = 7;
			if (ImGui::Button("Save config")) {
				std::string fileName = "DisplayConfig.json";
				saveConfig(fileName, Buttons.at(configNum));
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				std::string fileName = "DisplayConfig.json";
				loadConfig(fileName);
				for (int i = 0; i < textOptionList.size(); i++) {
					textOptionList.at(i)->SetPosition(glm::vec3(Buttons.at(configNum)->pos.x, Buttons.at(configNum)->pos.y + (i * Buttons.at(configNum)->offset.y), 0));
				}
			}
			ImGui::InputFloat("PosX", &Buttons.at(configNum)->pos.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &Buttons.at(configNum)->pos.y, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &Buttons.at(configNum)->offset.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &Buttons.at(configNum)->offset.y, 1.0f, 1.0f, "%.2f");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("volume track")) {
			configNum = 8;
			if (ImGui::Button("Save config")) {
				std::string fileName = "VolumeTrackConfig.json";
				saveConfig(fileName, Buttons.at(configNum));
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				std::string fileName = "VolumeTrackConfig.json";
				loadConfig(fileName);
				for (int i = 0; i < textOptionList.size(); i++) {
					volumeTrackList.at(i)->SetPosition(glm::vec3(Buttons.at(configNum)->pos.x, Buttons.at(configNum)->pos.y + (i * Buttons.at(configNum)->offset.y), 0));
				}
			}
			ImGui::InputFloat("PosX", &Buttons.at(configNum)->pos.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &Buttons.at(configNum)->pos.y, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &Buttons.at(configNum)->offset.x, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &Buttons.at(configNum)->offset.y, 1.0f, 1.0f, "%.2f");

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void LevelMainMenu::LevelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
}

void LevelMainMenu::LevelUnload() {
	GameEngine::GetInstance()->ClearMesh();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	KrillSoundManager::SoundManager::GetInstance()->SaveVolumeConfig
	(
		"../Resource/SceneData/CurrentVolume.json", 
		masterVolume, 
		isToggleVolume[0], 
		BGMVolume, 
		isToggleVolume[1],
		SFXVolume,
		isToggleVolume[2]
	);
}

void LevelMainMenu::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

}

void LevelMainMenu::HandleKey(char key) {

}

void LevelMainMenu::HandleMouse(int type, int x, int y) {

}

void LevelMainMenu::UpdateInput() 
{
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();
		for (int i = 0; i < 1/*SDL_NumJoysticks()*/; i++)
		{
			float axisX = Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal)/* / 32768.0f*/;
			/*std::cout << "axisX : " << axisX << std::endl;*/
			float axisY = Joystick::GetAxis(0, Joystick::Axis::LeftStickVertical)/* / 32768.0f*/;
			//std::cout << "axisY : " << axisY << std::endl;
			bool up = false;
			bool down = false;
			bool right = false;
			bool left = false;

			if (axisX > 0.8) {
				right = true;
			}

			else if (axisX < -0.8) {
				left = true;
			}

			else if (axisY > 0.8) {
				up = true;
			}

			else if (axisY < -0.8) {
				down = true;
			}

			if (isCredit == false && isTutorial == false && isStart == false && isExit == false && isOption == false) {
				//select button
				if (playerMove == false) {
					if (down || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Up))
					{
						playerWhere -= 1;
						if (playerWhere < 0) {
							playerWhere = 0;
						}
						playerMove = true;

					}
					else if (up || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Down))
					{
						playerWhere += 1;
						if (playerWhere > 4) {
							playerWhere = 4;
						}
						playerMove = true;
					}
				}

				if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
					playerMove = false;
				}

				//press x
				if (Joystick::GetButtonDown(0, Joystick::Button::Cross)) {
					//credit
					if (playerWhere == 0) {
						UiObject* credit = new UiObject();
						credit->SetSpriteInfo(spriteList.find("Credit")->second);
						credit->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
						objectsList.push_back(credit);
						isCredit = true;
					}

					//start game
					if (playerWhere == 1) {
						UiObject* fadeBlack = new UiObject();
						fadeBlack->SetSpriteInfo(spriteList.find("FadeBlack")->second);
						fadeBlack->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
						objectsList.push_back(fadeBlack);
						UiObject* areYouSure = new UiObject();
						areYouSure->SetSpriteInfo(spriteList.find("AreYouSure")->second);
						areYouSure->SetSize(areYouSure->GetSpriteRenderer()->GetSpriteWidth(), -areYouSure->GetSpriteRenderer()->GetSpriteHeight());
						objectsList.push_back(areYouSure);
						for (int j = 0; j < 2; j++) {
							UiObject* areYouSureYN = new UiObject();
							areYouSureYN->SetSpriteInfo(spriteList.find("AreYouSureYN")->second);
							areYouSureYN->SetSize(areYouSureYN->GetSpriteRenderer()->GetSpriteWidth(), -areYouSureYN->GetSpriteRenderer()->GetSpriteHeight());
							areYouSureYN->SetPosition(glm::vec3(Buttons.at(5)->pos.x + (j * Buttons.at(5)->offset.x), Buttons.at(5)->pos.y, 0));
							areYouSureYN->ShiftSpriteTo(areYouSureYN->GetSpriteRenderer()->GetRow(), j * 2);
							objectsList.push_back(areYouSureYN);
							yesNoList.push_back(areYouSureYN);
						}
						
						isStart = true;
					}

					//tutorial
					if (playerWhere == 2) {
						UiObject* fadeBlack = new UiObject();
						fadeBlack->SetSpriteInfo(spriteList.find("FadeBlack")->second);
						fadeBlack->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
						objectsList.push_back(fadeBlack);
						UiObject* tutorialBG = new UiObject();
						tutorialBG->SetSpriteInfo(spriteList.find("TutorialBG")->second);
						tutorialBG->SetSize(tutorialBG->GetSpriteRenderer()->GetSpriteWidth(), -tutorialBG->GetSpriteRenderer()->GetSpriteHeight());
						objectsList.push_back(tutorialBG);
						UiObject* tutorialInfo = new UiObject();
						tutorialInfo->SetSpriteInfo(spriteList.find("TutorialInfo")->second);
						tutorialInfo->SetSize(tutorialInfo->GetSpriteRenderer()->GetSpriteWidth(), -tutorialInfo->GetSpriteRenderer()->GetSpriteHeight());
						objectsList.push_back(tutorialInfo);
						tutorialInfoList.push_back(tutorialInfo);
						isTutorial = true;
					}

					//options
					if (playerWhere == 3) {
						UiObject* fadeBlack = new UiObject();
						fadeBlack->SetSpriteInfo(spriteList.find("FadeBlack")->second);
						fadeBlack->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
						objectsList.push_back(fadeBlack);
						UiObject* optionsBG = new UiObject();
						optionsBG->SetSpriteInfo(spriteList.find("OptionsBG")->second);
						optionsBG->SetSize(optionsBG->GetSpriteRenderer()->GetSpriteWidth(), -optionsBG->GetSpriteRenderer()->GetSpriteHeight());
						objectsList.push_back(optionsBG);
						for (int j = 0; j < 4; j++) {
							UiObject* textOption = new UiObject();
							textOption->SetSpriteInfo(spriteList.find("OptionsText")->second);
							textOption->SetSize(textOption->GetSpriteRenderer()->GetSpriteWidth(), -textOption->GetSpriteRenderer()->GetSpriteHeight());
							textOption->SetPosition(glm::vec3(Buttons.at(6)->pos.x, Buttons.at(6)->pos.y + (-j * Buttons.at(5)->offset.y), 0));
							textOption->ShiftSpriteTo(textOption->GetSpriteRenderer()->GetRow(), j * 2);
							objectsList.push_back(textOption);
							textOptionList.push_back(textOption);
						}

						UiObject* optionDisplay = new UiObject();
						optionDisplay->SetSpriteInfo(spriteList.find("OptionsDisplay")->second);
						optionDisplay->SetSize(optionDisplay->GetSpriteRenderer()->GetSpriteWidth(), -optionDisplay->GetSpriteRenderer()->GetSpriteHeight());
						optionDisplay->SetPosition(glm::vec3(Buttons.at(7)->pos.x, Buttons.at(7)->pos.y, 0));
						if (windowWidth == SCREEN_WIDTH) {
							optionDisplay->ShiftSpriteTo(optionDisplay->GetSpriteRenderer()->GetRow(), 3);
						}
						else {
							optionDisplay->ShiftSpriteTo(optionDisplay->GetSpriteRenderer()->GetRow(), 1);
						}
						
						objectsList.push_back(optionDisplay);
						displayList.push_back(optionDisplay);

						for (int j = 0; j < 3; j++) {
							UiObject* optionVolumeTrack = new UiObject();
							optionVolumeTrack->SetSpriteInfo(spriteList.find("OptionsVolumeTrack")->second);
							optionVolumeTrack->SetSize(optionVolumeTrack->GetSpriteRenderer()->GetSpriteWidth(), -optionVolumeTrack->GetSpriteRenderer()->GetSpriteHeight());
							optionVolumeTrack->SetPosition(glm::vec3(Buttons.at(8)->pos.x, Buttons.at(8)->pos.y - (j * Buttons.at(8)->offset.y), 0));
							objectsList.push_back(optionVolumeTrack);
							volumeTrackList.push_back(optionVolumeTrack);

							UiObject* optionVolumeKnob = new UiObject();
							optionVolumeKnob->SetSpriteInfo(spriteList.find("OptionsVolumeKnob")->second);
							optionVolumeKnob->SetSize(optionVolumeKnob->GetSpriteRenderer()->GetSpriteWidth(), -optionVolumeKnob->GetSpriteRenderer()->GetSpriteHeight());
							if (j == 0) {
								optionVolumeKnob->SetPosition(glm::vec3((masterVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y - (j * Buttons.at(8)->offset.y), 0));
							}
							else if (j == 1) {
								optionVolumeKnob->SetPosition(glm::vec3((SFXVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y - (j * Buttons.at(8)->offset.y), 0));
							}
							else if (j == 2) {
								optionVolumeKnob->SetPosition(glm::vec3((BGMVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y - (j * Buttons.at(8)->offset.y), 0));
							}
							objectsList.push_back(optionVolumeKnob);
							volumeKnobList.push_back(optionVolumeKnob);

							UiObject* optionVolumeBox = new UiObject();
							optionVolumeBox->SetSpriteInfo(spriteList.find("OptionsVolumeBox")->second);
							optionVolumeBox->SetSize(optionVolumeBox->GetSpriteRenderer()->GetSpriteWidth(), -optionVolumeBox->GetSpriteRenderer()->GetSpriteHeight());
							optionVolumeBox->SetPosition(glm::vec3(Buttons.at(8)->pos.x + Buttons.at(8)->offset.x, Buttons.at(8)->pos.y - (j * Buttons.at(8)->offset.y), 0));
							if (isToggleVolume[j] == true) {
								optionVolumeBox->ShiftSpriteTo(optionVolumeBox->GetSpriteRenderer()->GetRow(), 1);
							}
							else {
								optionVolumeBox->ShiftSpriteTo(optionVolumeBox->GetSpriteRenderer()->GetRow(), 3);
							}
							
							objectsList.push_back(optionVolumeBox);
							volumeBoxList.push_back(optionVolumeBox);
						}
						
						playerWhere = 0;
						isOption = true;
					}

					//exit
					if (playerWhere == 4) {
						UiObject* fadeBlack = new UiObject();
						fadeBlack->SetSpriteInfo(spriteList.find("FadeBlack")->second);
						fadeBlack->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
						objectsList.push_back(fadeBlack);
						UiObject* areYouSure = new UiObject();
						areYouSure->SetSpriteInfo(spriteList.find("AreYouSure")->second);
						areYouSure->SetSize(areYouSure->GetSpriteRenderer()->GetSpriteWidth(), -areYouSure->GetSpriteRenderer()->GetSpriteHeight());
						areYouSure->ShiftSpriteTo(areYouSure->GetSpriteRenderer()->GetRow(), 2);
						objectsList.push_back(areYouSure);
						for (int j = 0; j < 2; j++) {
							UiObject* areYouSureYN = new UiObject();
							areYouSureYN->SetSpriteInfo(spriteList.find("AreYouSureYN")->second);
							areYouSureYN->SetSize(areYouSureYN->GetSpriteRenderer()->GetSpriteWidth(), -areYouSureYN->GetSpriteRenderer()->GetSpriteHeight());
							areYouSureYN->SetPosition(glm::vec3(Buttons.at(5)->pos.x + (j * Buttons.at(5)->offset.x), Buttons.at(5)->pos.y, 0));
							areYouSureYN->ShiftSpriteTo(areYouSureYN->GetSpriteRenderer()->GetRow(), j * 2);
							objectsList.push_back(areYouSureYN);
							yesNoList.push_back(areYouSureYN);
						}

						isExit = true;
					}
				}
			}

			//tutorial next page
			else if (Joystick::GetButtonDown(0, Joystick::Button::Cross) && isTutorial == true) {
				tutorialInfoList.at(0)->GetSpriteRenderer()->ShiftColumn();
				InfoPage++;
				if (InfoPage == 3) {
					tutorialInfoList.erase(tutorialInfoList.end() - 1);
					for (int j = 0; j < 3; j++) {
						objectsList.erase(objectsList.end() - 1);
					}
					InfoPage = 0;
					isTutorial = false;
				}
			}

			//press o
			else if (Joystick::GetButtonDown(0, Joystick::Button::Circle) && isSelectDisplay == false && isSelectVolume == false) {
				std::cout << "close option" << std::endl;
				if (isCredit == true) {
					objectsList.erase(objectsList.end() - 1);
					isCredit = false;
				}

				if (isStart == true) {
					for (int j = 0; j < 2; j++) {
						yesNoList.erase(yesNoList.end() - 1);
					}
					
					for (int j = 0; j < 4; j++) {
						objectsList.erase(objectsList.end() - 1);
					}
					isStart = false;
					playerWhere = 1;
				}

				if (isTutorial == true) {
					tutorialInfoList.erase(tutorialInfoList.end() - 1);
					for (int j = 0; j < 3; j++) {
						objectsList.erase(objectsList.end() - 1);
					}
					isTutorial = false;
					playerWhere = 2;
					InfoPage = 0;
				}

				if (isOption == true) {

					displayList.erase(displayList.end() - 1);

					for (int j = 0; j < 3; j++) {
						volumeTrackList.erase(volumeTrackList.end() - 1);
						volumeKnobList.erase(volumeKnobList.end() - 1);
						volumeBoxList.erase(volumeBoxList.end() - 1);
					}

					for (int j = 0; j < 4; j++) {
						textOptionList.erase(textOptionList.end() - 1);
					}

					for (int j = 0; j < 16; j++) {
						objectsList.erase(objectsList.end() - 1);
					}

					isOption = false;
					playerWhere = 3;
				}

				if (isExit == true) {
					for (int j = 0; j < 2; j++) {
						yesNoList.erase(yesNoList.end() - 1);
					}

					for (int j = 0; j < 4; j++) {
						objectsList.erase(objectsList.end() - 1);
					}
					isExit = false;
					playerWhere = 4;
				}
			}

			//before start & exit
			else if (isStart == true || isExit == true) {
				//select button
				if (!playerMove) {
					if (left || right || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Left) || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Right))
					{
						playerWhere += 1;
						playerMove = true;
					}
				}

				if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
					playerMove = false;
				}

				if (Joystick::GetButtonDown(0, Joystick::Button::Cross) && isStart == true) {
					if (playerWhere % 2 == 1) {
						GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSELECTABILITY;
					}
					else {
						for (int j = 0; j < 2; j++) {
							yesNoList.erase(yesNoList.end() - 1);
						}

						for (int j = 0; j < 4; j++) {
							objectsList.erase(objectsList.end() - 1);
						}
						isStart = false;
						playerWhere = 1;
					}
				}

				if (Joystick::GetButtonDown(0, Joystick::Button::Cross) && isExit == true) {
					if (playerWhere % 2 == 1) {
						GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT;
					}
					else {
						for (int j = 0; j < 2; j++) {
							yesNoList.erase(yesNoList.end() - 1);
						}

						for (int j = 0; j < 4; j++) {
							objectsList.erase(objectsList.end() - 1);
						}
						isExit = false;
						playerWhere = 4;
					}
				}
			}

			//Option
			else if (isOption == true && isSelectDisplay == false && isSelectVolume == false) {
				//select button
				if (playerMove == false) {
					if (down || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Up))
					{
						playerWhere -= 1;
						if (playerWhere < 0) {
							playerWhere = 0;
						}
						playerMove = true;

					}
					else if (up || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Down))
					{
						playerWhere += 1;
						if (playerWhere > 3) {
							playerWhere = 3;
						}
						playerMove = true;
					}
				}
				if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
					playerMove = false;
				}

				//press X
				if (Joystick::GetButtonDown(0, Joystick::Button::Cross)) {
					if (playerWhere == 0 && isSelectVolume == false) {
						displayList.at(0)->ShiftSpriteTo(displayList.at(0)->GetSpriteRenderer()->GetRow(), displayList.at(0)->GetSpriteRenderer()->GetColumn() - 1);
						UiObject* optionDisplayDropdown = new UiObject();
						optionDisplayDropdown->SetSpriteInfo(spriteList.find("OptionsDisplayDropdown")->second);
						optionDisplayDropdown->SetSize(optionDisplayDropdown->GetSpriteRenderer()->GetSpriteWidth(), -optionDisplayDropdown->GetSpriteRenderer()->GetSpriteHeight());
						optionDisplayDropdown->SetPosition(glm::vec3(Buttons.at(7)->pos.x, Buttons.at(7)->pos.y + Buttons.at(7)->offset.y, 0));
						optionDisplayDropdown->ShiftSpriteTo(optionDisplayDropdown->GetSpriteRenderer()->GetRow(), 1);
						objectsList.push_back(optionDisplayDropdown);
						displayList.push_back(optionDisplayDropdown);
						playerWhere = displayList.at(0)->GetSpriteRenderer()->GetColumn();
						isSelectDisplay = true;
					}

					if (playerWhere == 1 && isSelectDisplay == false) {
						isSelectVolume = true;
						isMasterVolume = true;
						volumeKnobList.at(0)->ShiftSpriteTo(volumeKnobList.at(0)->GetSpriteRenderer()->GetRow(), 1);
						playerWhere = 0;
					}

					if (playerWhere == 2 && isSelectDisplay == false) {
						isSelectVolume = true;
						isSFXVolume = true;
						volumeKnobList.at(1)->ShiftSpriteTo(volumeKnobList.at(1)->GetSpriteRenderer()->GetRow(), 1);
						playerWhere = 0;
					}

					if (playerWhere == 3 && isSelectDisplay == false) {
						isSelectVolume = true;
						isBGMVolume = true;
						volumeKnobList.at(2)->ShiftSpriteTo(volumeKnobList.at(2)->GetSpriteRenderer()->GetRow(), 1);
						playerWhere = 0;
					}
				}
			}

			//display
			else if (isSelectDisplay == true) {
				//select option
				if (playerMove == false) {
					if (up || down || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Up) || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Down))
					{
						playerWhere += 1;
						playerMove = true;
					}
				}
				if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
					playerMove = false;
				}

				//display mode
				if (Joystick::GetButtonDown(0, Joystick::Button::Cross)) {
					if (playerWhere % 2 == 1) {
						SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
						SDL_GetWindowSize(GameEngine::GetInstance()->GetSDLWindow(), &windowWidth, &windowHeight);
						glViewport(0, 0, windowWidth, windowHeight);
						displayList.at(0)->ShiftSpriteTo(displayList.at(0)->GetSpriteRenderer()->GetRow(), 0);
					}
					else {
						SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), 0);
						windowWidth = SCREEN_WIDTH;
						windowHeight = SCREEN_HEIGHT;
						glViewport(0, 0, windowWidth, windowHeight);
						displayList.at(0)->ShiftSpriteTo(displayList.at(0)->GetSpriteRenderer()->GetRow(), 2);
					}
				}

				if (Joystick::GetButtonDown(0, Joystick::Button::Circle)) {
					playerWhere = 0;
					if (displayList.size() > 1) {
						displayList.erase(displayList.end() - 1);
						objectsList.erase(objectsList.end() - 1);
						displayList.at(0)->GetSpriteRenderer()->ShiftColumn();
						isSelectDisplay = false;
						isSelectVolume = false;
					}
				}
			}

			//volume
			else if (isSelectVolume == true) {
				//select option
				if (/*!playerMove[i]*/1) {
					if ((right || left || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Right) || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Left)) && (isSlider == false))
					{
						playerWhere += 1;
						playerMove = true;

						if (isMasterVolume == true) {
							if (playerWhere % 2 == 1) {
								volumeKnobList.at(0)->ShiftSpriteTo(volumeKnobList.at(0)->GetSpriteRenderer()->GetRow(), 0);
								volumeBoxList.at(0)->ShiftSpriteTo(volumeBoxList.at(0)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(0)->GetSpriteRenderer()->GetColumn() - 1);
							}
							else if (playerWhere % 2 == 0){
								volumeKnobList.at(0)->ShiftSpriteTo(volumeKnobList.at(0)->GetSpriteRenderer()->GetRow(), 1);
								volumeBoxList.at(0)->ShiftSpriteTo(volumeBoxList.at(0)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(0)->GetSpriteRenderer()->GetColumn() + 1);
							}
						}

						if (isSFXVolume == true) {
							if (playerWhere % 2 == 1) {
								volumeKnobList.at(1)->ShiftSpriteTo(volumeKnobList.at(1)->GetSpriteRenderer()->GetRow(), 0);
								volumeBoxList.at(1)->ShiftSpriteTo(volumeBoxList.at(1)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(1)->GetSpriteRenderer()->GetColumn() - 1);
							}
							else if (playerWhere % 2 == 0){
								volumeKnobList.at(1)->ShiftSpriteTo(volumeKnobList.at(1)->GetSpriteRenderer()->GetRow(), 1);
								volumeBoxList.at(1)->ShiftSpriteTo(volumeBoxList.at(1)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(1)->GetSpriteRenderer()->GetColumn() + 1);
							}
						}

						if (isBGMVolume == true) {
							if (playerWhere % 2 == 1) {
								volumeKnobList.at(2)->ShiftSpriteTo(volumeKnobList.at(2)->GetSpriteRenderer()->GetRow(), 0);
								volumeBoxList.at(2)->ShiftSpriteTo(volumeBoxList.at(2)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(2)->GetSpriteRenderer()->GetColumn() - 1);
							}
							else if (playerWhere % 2 == 0){
								volumeKnobList.at(2)->ShiftSpriteTo(volumeKnobList.at(2)->GetSpriteRenderer()->GetRow(), 1);
								volumeBoxList.at(2)->ShiftSpriteTo(volumeBoxList.at(2)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(2)->GetSpriteRenderer()->GetColumn() + 1);
							}
						}
					}
					if ((right || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Right)) && (isSlider == true)) {
						playerMove = true;
						if (isMasterVolume == true && masterVolume < 100) {
							std::cout << masterVolume << std::endl;
							masterVolume++;
							volumeKnobList.at(0)->SetPosition(glm::vec3((masterVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y, 0));
						}
						if (isSFXVolume == true && SFXVolume < 100) {
							SFXVolume++;
							volumeKnobList.at(1)->SetPosition(glm::vec3((SFXVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y + (-1 * Buttons.at(8)->offset.y), 0));
						}
						if (isBGMVolume == true && BGMVolume < 100) {
							BGMVolume++;
							volumeKnobList.at(2)->SetPosition(glm::vec3((BGMVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y + (-2 * Buttons.at(8)->offset.y), 0));
						}
						
					}
					else if ((left || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Left)) && (isSlider == true)){
						playerMove = true;
						if (isMasterVolume == true && masterVolume > 0) {
							masterVolume--;
							volumeKnobList.at(0)->SetPosition(glm::vec3((masterVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y, 0));
						}
						if (isSFXVolume == true && SFXVolume > 0) {
							SFXVolume--;
							volumeKnobList.at(1)->SetPosition(glm::vec3((SFXVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y + (-1 * Buttons.at(8)->offset.y), 0));
						}
						if (isBGMVolume == true && BGMVolume > 0) {
							BGMVolume--;
							volumeKnobList.at(2)->SetPosition(glm::vec3((BGMVolume * 4 - 57.5 / 0.25), Buttons.at(8)->pos.y + (-2 * Buttons.at(8)->offset.y), 0));
						}
					}
				}

				if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
					playerMove = false;
				}

				if (Joystick::GetButtonDown(0, Joystick::Button::Circle)) {
					if (isMasterVolume == true) {
						if (playerWhere % 2 == 1) {
							volumeKnobList.at(0)->ShiftSpriteTo(volumeKnobList.at(0)->GetSpriteRenderer()->GetRow(), volumeKnobList.at(0)->GetSpriteRenderer()->GetColumn());
							volumeBoxList.at(0)->ShiftSpriteTo(volumeBoxList.at(0)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(0)->GetSpriteRenderer()->GetColumn() + 1);
						}
						else {
							volumeKnobList.at(0)->ShiftSpriteTo(volumeKnobList.at(0)->GetSpriteRenderer()->GetRow(), volumeKnobList.at(0)->GetSpriteRenderer()->GetColumn() + 1);
							volumeBoxList.at(0)->ShiftSpriteTo(volumeBoxList.at(0)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(0)->GetSpriteRenderer()->GetColumn());
						}

						if (isSlider == true) {
							isSlider = false;
							volumeTrackList.at(0)->ShiftSpriteTo(volumeTrackList.at(0)->GetSpriteRenderer()->GetRow(), 0);
						}
						isSelectDisplay = false;
						isSelectVolume = false;
						isMasterVolume = false;
						playerWhere = 1;
					}
					
					else if (isSFXVolume == true) {
						
						if (playerWhere % 2 == 1) {
							volumeKnobList.at(1)->ShiftSpriteTo(volumeKnobList.at(1)->GetSpriteRenderer()->GetRow(), volumeKnobList.at(1)->GetSpriteRenderer()->GetColumn());
							volumeBoxList.at(1)->ShiftSpriteTo(volumeBoxList.at(1)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(1)->GetSpriteRenderer()->GetColumn() + 1);
						}
						else {
							volumeKnobList.at(1)->ShiftSpriteTo(volumeKnobList.at(1)->GetSpriteRenderer()->GetRow(), volumeKnobList.at(1)->GetSpriteRenderer()->GetColumn() + 1);
							volumeBoxList.at(1)->ShiftSpriteTo(volumeBoxList.at(1)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(1)->GetSpriteRenderer()->GetColumn());
						}

						if (isSlider == true) {
							isSlider = false;
							volumeTrackList.at(1)->ShiftSpriteTo(volumeTrackList.at(1)->GetSpriteRenderer()->GetRow(), 0);
						}
						isSelectDisplay = false;
						isSelectVolume = false;
						isSFXVolume = false;
						playerWhere = 2;
					}
					
					else if (isBGMVolume == true) {
						if (playerWhere % 2 == 1) {
							volumeKnobList.at(2)->ShiftSpriteTo(volumeKnobList.at(2)->GetSpriteRenderer()->GetRow(), volumeKnobList.at(2)->GetSpriteRenderer()->GetColumn());
							volumeBoxList.at(2)->ShiftSpriteTo(volumeBoxList.at(2)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(2)->GetSpriteRenderer()->GetColumn() + 1);
						}
						else {
							volumeKnobList.at(2)->ShiftSpriteTo(volumeKnobList.at(2)->GetSpriteRenderer()->GetRow(), volumeKnobList.at(2)->GetSpriteRenderer()->GetColumn() + 1);
							volumeBoxList.at(2)->ShiftSpriteTo(volumeBoxList.at(2)->GetSpriteRenderer()->GetRow(), volumeBoxList.at(2)->GetSpriteRenderer()->GetColumn());
						}
						if (isSlider == true) {
							isSlider = false;
							volumeTrackList.at(2)->ShiftSpriteTo(volumeTrackList.at(2)->GetSpriteRenderer()->GetRow(), 0);
						}
						isSelectDisplay = false;
						isSelectVolume = false;
						isBGMVolume = false;
						playerWhere = 3;
					}

					
				}

				if (Joystick::GetButtonDown(0, Joystick::Button::Cross)) {
					if (isMasterVolume == true) {
						if (playerWhere % 2 == 1) {
							if (isToggleVolume[0] == false) {
								volumeBoxList.at(0)->ShiftSpriteTo(volumeBoxList.at(0)->GetSpriteRenderer()->GetRow(), 0);
								isToggleVolume[0] = true;
							}
							else {
								volumeBoxList.at(0)->ShiftSpriteTo(volumeBoxList.at(0)->GetSpriteRenderer()->GetRow(), 2);
								isToggleVolume[0] = false;
							}
							
						}
						else {
							isSlider = true;
							volumeTrackList.at(0)->ShiftSpriteTo(volumeTrackList.at(0)->GetSpriteRenderer()->GetRow(), 1);
						}
					}

					if (isSFXVolume == true) {
						if (playerWhere % 2 == 1) {
							if (isToggleVolume[1] == false) {
								volumeBoxList.at(1)->ShiftSpriteTo(volumeBoxList.at(1)->GetSpriteRenderer()->GetRow(), 0);
								isToggleVolume[1] = true;
							}
							else {
								volumeBoxList.at(1)->ShiftSpriteTo(volumeBoxList.at(1)->GetSpriteRenderer()->GetRow(), 2);
								isToggleVolume[1] = false;
							}
						}
						else {
							isSlider = true;
							volumeTrackList.at(1)->ShiftSpriteTo(volumeTrackList.at(1)->GetSpriteRenderer()->GetRow(), 1);
						}
					}

					if (isBGMVolume == true) {
						if (playerWhere % 2 == 1) {
							if (isToggleVolume[2] == false) {
								volumeBoxList.at(2)->ShiftSpriteTo(volumeBoxList.at(2)->GetSpriteRenderer()->GetRow(), 0);
								isToggleVolume[2] = true;
							}
							else {
								volumeBoxList.at(2)->ShiftSpriteTo(volumeBoxList.at(2)->GetSpriteRenderer()->GetRow(), 2);
								isToggleVolume[2] = false;
							}
						}
						else {
							isSlider = true;
							volumeTrackList.at(2)->ShiftSpriteTo(volumeTrackList.at(2)->GetSpriteRenderer()->GetRow(), 1);
						}
					}
				}
				
			}
		}
	}
}

void LevelMainMenu::UpdateUi() {
	//select box
	if (isCredit == false && isTutorial == false && isStart == false && isExit == false && isOption == false) {
		for (int j = 0; j < textList.size(); j++)
		{
			if (Buttons.at(j)->playerHere == true)
			{
				textList.at(j)->ShiftSpriteTo(textList.at(j)->GetSpriteRenderer()->GetRow(), Buttons.at(j)->column + 1);
			}
			else {
				textList.at(j)->ShiftSpriteTo(textList.at(j)->GetSpriteRenderer()->GetRow(), Buttons.at(j)->column);
			}
		}
	}
	
	//select yes no
	if ((isStart == true) || (isExit == true)) {
		if (playerWhere % 2 == 1) {
			yesNoList.at(0)->ShiftSpriteTo(yesNoList.at(0)->GetSpriteRenderer()->GetRow(), 1);
			yesNoList.at(1)->ShiftSpriteTo(yesNoList.at(1)->GetSpriteRenderer()->GetRow(), 2);
		}
		else {
			yesNoList.at(0)->ShiftSpriteTo(yesNoList.at(0)->GetSpriteRenderer()->GetRow(), 0);
			yesNoList.at(1)->ShiftSpriteTo(yesNoList.at(1)->GetSpriteRenderer()->GetRow(), 3);
		}
	}
	
	//select text option
	if (isOption == true && isSelectDisplay == false && isSelectVolume == false) {
		for (int i = 0; i < textOptionList.size(); i++) {
			
			if (playerWhere == i) {
				textOptionList.at(i)->ShiftSpriteTo(textOptionList.at(i)->GetSpriteRenderer()->GetRow(), (i * 2) + 1);
			}
			else {
				textOptionList.at(i)->ShiftSpriteTo(textOptionList.at(i)->GetSpriteRenderer()->GetRow(), (i * 2));
			}
		}
	}

	//select option
	//display
	if (isSelectDisplay == true) {
		if (playerWhere % 2 == 0) {
			displayList.at(1)->ShiftSpriteTo(displayList.at(1)->GetSpriteRenderer()->GetRow(), 1);
		}
		else {
			displayList.at(1)->ShiftSpriteTo(displayList.at(1)->GetSpriteRenderer()->GetRow(), 0);
		}
	}

	//Updata by config
	//text
	for (int i = 0; i < textList.size(); i++) {
		textList.at(i)->SetPosition(glm::vec3(Buttons.at(i)->pos.x, Buttons.at(i)->pos.y, 0));
		textList.at(i)->SetSize(Buttons.at(i)->size.x, -Buttons.at(i)->size.y);
	}

	//yes no
	for (int i = 0; i < yesNoList.size(); i++) {
		yesNoList.at(i)->SetPosition(glm::vec3(Buttons.at(5)->pos.x + (i * Buttons.at(5)->offset.x), Buttons.at(5)->pos.y, 0));
	}

	//text option
	for (int i = 0; i < textOptionList.size(); i++) {
		textOptionList.at(i)->SetPosition(glm::vec3(Buttons.at(6)->pos.x, Buttons.at(6)->pos.y - (i * Buttons.at(6)->offset.y), 0));
	}

	//display option
	for (int i = 0; i < displayList.size(); i++) {
		displayList.at(i)->SetPosition(glm::vec3(Buttons.at(7)->pos.x, Buttons.at(7)->pos.y - (i * Buttons.at(7)->offset.y), 0));
	}

	//volume track
	for (int i = 0; i < volumeTrackList.size(); i++) {
		volumeTrackList.at(i)->SetPosition(glm::vec3(Buttons.at(8)->pos.x, Buttons.at(8)->pos.y - (i * Buttons.at(8)->offset.y), 0));
	}

	//volume box
	for (int i = 0; i < volumeBoxList.size(); i++) {
		volumeBoxList.at(i)->SetPosition(glm::vec3(Buttons.at(8)->pos.x + Buttons.at(8)->offset.x, Buttons.at(8)->pos.y - (i * Buttons.at(8)->offset.y), 0));
	}
}

void LevelMainMenu::saveConfig(std::string& filename, ButtonData* con) 
{
	nlohmann::json data;

	data["number"] = con->number;
	data["posX"] = con->pos.x;
	data["posY"] = con->pos.y;
	data["width"] = con->size.x;
	data["hight"] = con->size.y;
	data["offSetX"] = con->offset.x;
	data["offSetY"] = con->offset.y;

	std::ofstream file(filename);

	if (!file.is_open()) 
	{
		KK_CORE_WARN("LevelMainMenu::saveConfig : Cannot save configuration");
		return;
	}

	file << data;
	file.close();
	KK_CORE_INFO("LevelMainMenu::saveConfig : Successfully save configuration");

}

void LevelMainMenu::loadConfig(std::string filename) {
	std::ifstream file(filename);

	if (file.is_open()) {
		nlohmann::json data = nlohmann::json::parse(file);
		int id = -1;
		std::cout << "Opened" << std::endl;
		if (data.contains("number") && !data["number"].is_null()) {
			id = data["number"];
			for (int i = 0; i < Buttons.size(); i++) {
				if (Buttons.at(i)->number == id) {
					std::cout << "Loaded" << std::endl;
					//configs.at(i).text = data["text"];
					if (data.contains("posX") && !data["posX"].is_null()) {
						Buttons.at(i)->pos.x = data["posX"];
					}

					if (data.contains("posY") && !data["posY"].is_null()) {
						Buttons.at(i)->pos.y = data["posY"];
					}

					if (data.contains("width") && !data["width"].is_null()) {
						Buttons.at(i)->size.x = data["width"];
					}

					if (data.contains("hight") && !data["hight"].is_null()) {
						Buttons.at(i)->size.y = data["hight"];
					}

					if (data.contains("offSetX") && !data["offSetX"].is_null()) {
						Buttons.at(i)->offset.x = data["offSetX"];
					}

					if (data.contains("offSetY") && !data["offSetY"].is_null()) {
						Buttons.at(i)->offset.y = data["offSetY"];
					}
				}
			}
		}
	}

	else {
		std::cout << "Failed" << std::endl;
	}
}

