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
	ui->SetSize(size.x, -size.y);
	ui->ShiftSpriteTo(spriteShiftPos.x, spriteShiftPos.y);
	return ui;
}

UiObject* LevelMainMenu::InitButtonUI(std::string name, SpritesheetInfo spriteInfo, ButtonData* buttonData, glm::vec2 spriteShiftPos)
{
	UiObject* ui = new UiObject();
	ui->SetSpriteInfo(spriteInfo);
	ui->SetPosition({ buttonData->pos.x, buttonData->pos.y, 0 });
	ui->SetSize(buttonData->size.x, -buttonData->size.y);
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

	glm::vec2 backgroundSize(camera.GetCameraWidth(), camera.GetCameraHeight());
	UiObject* BG = InitUI("BG", spriteList["BG"], glm::vec2(0, 0), backgroundSize, glm::vec2(0, 0));
	objectsList.push_back(BG);

	// game name
	buttonList["GameName"] = InitButtonData("GameName", {100, 100}, {470, 55}, {0, 0}, 0, "../Resource/SceneData/text0.json");
	buttonList["GameName"]->ButtonUI = InitButtonUI("GameName", spriteList["Name"], buttonList["GameName"], glm::vec2(0, 0));

	objectsList.push_back(buttonList["GameName"]->ButtonUI);
	textList.push_back(buttonList["GameName"]->ButtonUI);

	//Main button
	for (int i = 1; i < 5; i++) 
	{
		// position file data
		std::string fileName = "../Resource/SceneData/text" + std::to_string(i) + ".json";
		std::string buttonName = "Text" + std::to_string(i);
		int buttonUIShiftColumn = (i - 1) * 2;
		 
		buttonList[buttonName] = InitButtonData(buttonName, { 100, 100 }, { 289, 65 }, { 0, 0 }, buttonUIShiftColumn, fileName);
		buttonList[buttonName]->ButtonUI = InitButtonUI(buttonName, spriteList["Text"], buttonList[buttonName], glm::vec2(0, buttonUIShiftColumn));

		objectsList.push_back(buttonList[buttonName]->ButtonUI);
		textList.push_back(buttonList[buttonName]->ButtonUI);
	}

	// Background Image for start confirm
	UiObject* areYouSureStart = new UiObject();
	areYouSureStart->SetSpriteInfo(spriteList.find("AreYouSure")->second);
	areYouSureStart->SetSize(areYouSureStart->GetSpriteRenderer()->GetSpriteWidth(), -areYouSureStart->GetSpriteRenderer()->GetSpriteHeight());
	areYouSureStart->ShiftSpriteTo(areYouSureStart->GetSpriteRenderer()->GetRow(), 0);
	areYouSureStart->SetIsRender(false);
	objectsList.push_back(areYouSureStart);
	yesNoList_Start.push_back(areYouSureStart);

	UiObject* areYouSureExit = new UiObject();
	areYouSureExit->SetSpriteInfo(spriteList.find("AreYouSure")->second);
	areYouSureExit->SetSize(areYouSureExit->GetSpriteRenderer()->GetSpriteWidth(), -areYouSureExit->GetSpriteRenderer()->GetSpriteHeight());
	areYouSureExit->ShiftSpriteTo(areYouSureExit->GetSpriteRenderer()->GetRow(), 2);
	areYouSureExit->SetIsRender(false);
	objectsList.push_back(areYouSureExit);
	yesNoList_Exit.push_back(areYouSureExit);

	UiObject* credit = new UiObject();
	credit->SetSpriteInfo(spriteList.find("Credit")->second);
	credit->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
	credit->SetIsRender(false);
	objectsList.push_back(credit);
	creditUIList.push_back(credit);

	UiObject* tutorialBG = new UiObject();
	tutorialBG->SetSpriteInfo(spriteList.find("TutorialBG")->second);
	tutorialBG->SetSize(tutorialBG->GetSpriteRenderer()->GetSpriteWidth(), -tutorialBG->GetSpriteRenderer()->GetSpriteHeight());
	tutorialBG->SetIsRender(false);
	objectsList.push_back(tutorialBG);
	tutorialInfoList.push_back(tutorialBG);

	UiObject* tutorialInfo = new UiObject();
	tutorialInfo->SetSpriteInfo(spriteList.find("TutorialInfo")->second);
	tutorialInfo->SetSize(tutorialInfo->GetSpriteRenderer()->GetSpriteWidth(), -tutorialInfo->GetSpriteRenderer()->GetSpriteHeight());
	tutorialInfo->SetIsRender(false);
	tutorialInfoUI = tutorialInfo;
	objectsList.push_back(tutorialInfo);
	tutorialInfoList.push_back(tutorialInfo);

	UiObject* fadeBlack = new UiObject();
	fadeBlack->SetSpriteInfo(spriteList.find("FadeBlack")->second);
	fadeBlack->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
	fadeBlack->SetIsRender(false);
	OptionList.push_back(fadeBlack);
	objectsList.push_back(fadeBlack);

	UiObject* optionsBG = new UiObject();
	optionsBG->SetSpriteInfo(spriteList.find("OptionsBG")->second);
	optionsBG->SetSize(optionsBG->GetSpriteRenderer()->GetSpriteWidth(), -optionsBG->GetSpriteRenderer()->GetSpriteHeight());
	optionsBG->SetIsRender(false);
	OptionList.push_back(optionsBG);
	objectsList.push_back(optionsBG);

	for (int j = 0; j < 4; j++) {

		std::string buttonName;

		switch (j)
		{
		case 0:
			buttonName = "DisplayType_Text";
			break;
		case 1:
			buttonName = "MasterVolume_Text";
			break;
		case 2:
			buttonName = "SFXVolume_Text";
			break;
		case 3:
			buttonName = "BGMVolume_Text";
			break;
		}

		buttonList[buttonName] = InitButtonData(buttonName, { 100, 100 }, { 289, 65 }, { 0, 0 }, j * 2, "../Resource/SceneData/TextOptionConfig.json");
		

		UiObject* textOption = new UiObject();
		textOption->SetSpriteInfo(spriteList.find("OptionsText")->second);
		textOption->SetSize(textOption->GetSpriteRenderer()->GetSpriteWidth(), -textOption->GetSpriteRenderer()->GetSpriteHeight());
		textOption->SetPosition(glm::vec3(buttonList[buttonName]->pos.x, buttonList[buttonName]->pos.y + (-j * buttonList[buttonName]->offset.y), 0));
		textOption->ShiftSpriteTo(textOption->GetSpriteRenderer()->GetRow(), j * 2);
		textOption->SetIsRender(false);
		buttonList[buttonName]->ButtonUI = textOption;
		OptionList.push_back(textOption);
		objectsList.push_back(textOption);
	}

	buttonList["DisplayType"] = InitButtonData("DisplayType", {100, 100}, {289, 65}, {0, 0}, 0, "../Resource/SceneData/DisplayConfig.json");
	UiObject* optionDisplay = new UiObject();
	optionDisplay->SetSpriteInfo(spriteList.find("OptionsDisplay")->second);
	optionDisplay->SetSize(optionDisplay->GetSpriteRenderer()->GetSpriteWidth(), -optionDisplay->GetSpriteRenderer()->GetSpriteHeight());
	optionDisplay->SetPosition(glm::vec3(buttonList["DisplayType"]->pos.x, buttonList["DisplayType"]->pos.y, 0));
	optionDisplay->SetIsRender(false);
	buttonList["DisplayType"]->ButtonUI = optionDisplay;
	if (windowWidth == SCREEN_WIDTH) {
		optionDisplay->ShiftSpriteTo(optionDisplay->GetSpriteRenderer()->GetRow(), 3);
	}
	else {
		optionDisplay->ShiftSpriteTo(optionDisplay->GetSpriteRenderer()->GetRow(), 1);
	}
	OptionList.push_back(optionDisplay);
	objectsList.push_back(optionDisplay);
	
	buttonList["DisplayDropdown"] = InitButtonData("DisplayDropdown", { 100, 100 }, { 289, 65 }, { 0, 0 }, 0, "../Resource/SceneData/DisplayConfig.json");
	float displayDropdownOffsetY = -70.0f;
	UiObject* optionDisplayDropdown = new UiObject();
	optionDisplayDropdown->SetSpriteInfo(spriteList.find("OptionsDisplayDropdown")->second);
	optionDisplayDropdown->SetSize(optionDisplayDropdown->GetSpriteRenderer()->GetSpriteWidth(), -optionDisplayDropdown->GetSpriteRenderer()->GetSpriteHeight());
	optionDisplayDropdown->SetPosition(glm::vec3(buttonList["DisplayDropdown"]->pos.x, buttonList["DisplayDropdown"]->pos.y + displayDropdownOffsetY, 0));
	//optionDisplayDropdown->ShiftSpriteTo(0, 1);
	optionDisplayDropdown->SetIsRender(false);
	buttonList["DisplayDropdown"]->ButtonUI = optionDisplayDropdown;
	objectsList.push_back(optionDisplayDropdown);
	//OptionList.push_back(optionDisplayDropdown);

	for (int j = 0; j < 3; j++) 
	{
		std::string buttonName;

		switch (j)
		{
		case 0:
			buttonName = "MasterVolume_Track";
			break;
		case 1:
			buttonName = "SFXVolume_Track";
			break;
		case 2:
			buttonName = "BGMVolume_Track";
			break;
		}

		buttonList[buttonName] = InitButtonData(buttonName, { 100, 100 }, { 289, 65 }, { 0, 0 }, 0, "../Resource/SceneData/VolumeTrackConfig.json");

		UiObject* optionVolumeTrack = new UiObject();
		optionVolumeTrack->SetSpriteInfo(spriteList.find("OptionsVolumeTrack")->second);
		optionVolumeTrack->SetSize(optionVolumeTrack->GetSpriteRenderer()->GetSpriteWidth(), -optionVolumeTrack->GetSpriteRenderer()->GetSpriteHeight());
		optionVolumeTrack->SetPosition(glm::vec3(buttonList[buttonName]->pos.x, buttonList[buttonName]->pos.y - (j * buttonList[buttonName]->offset.y), 0));
		optionVolumeTrack->SetIsRender(false);
		buttonList[buttonName]->ButtonUI = optionVolumeTrack;

		objectsList.push_back(optionVolumeTrack);
		OptionList.push_back(optionVolumeTrack);

		switch (j)
		{
		case 0:
			buttonName = "MasterVolume_Knob";
			break;
		case 1:
			buttonName = "SFXVolume_Knob";
			break;
		case 2:
			buttonName = "BGMVolume_Knob";
			break;
		}

		buttonList[buttonName] = InitButtonData(buttonName, { 100, 100 }, { 289, 65 }, { 0, 0 }, 0, "../Resource/SceneData/VolumeTrackConfig.json");

		UiObject* optionVolumeKnob = new UiObject();
		optionVolumeKnob->SetSpriteInfo(spriteList.find("OptionsVolumeKnob")->second);
		optionVolumeKnob->SetSize(optionVolumeKnob->GetSpriteRenderer()->GetSpriteWidth(), -optionVolumeKnob->GetSpriteRenderer()->GetSpriteHeight());
		optionVolumeKnob->SetIsRender(false);
		buttonList[buttonName]->ButtonUI = optionVolumeKnob;
		if (j == 0) {
			optionVolumeKnob->SetPosition(glm::vec3((masterVolume * 4 - 57.5 / 0.25), buttonList[buttonName]->pos.y - (j * buttonList[buttonName]->offset.y), 0));
		}
		else if (j == 1) {
			optionVolumeKnob->SetPosition(glm::vec3((SFXVolume * 4 - 57.5 / 0.25), buttonList[buttonName]->pos.y - (j * buttonList[buttonName]->offset.y), 0));
		}
		else if (j == 2) {
			optionVolumeKnob->SetPosition(glm::vec3((BGMVolume * 4 - 57.5 / 0.25), buttonList[buttonName]->pos.y - (j * buttonList[buttonName]->offset.y), 0));
		}
		objectsList.push_back(optionVolumeKnob);
		OptionList.push_back(optionVolumeKnob);

		switch (j)
		{
		case 0:
			buttonName = "MasterVolume_Box";
			break;
		case 1:
			buttonName = "SFXVolume_Box";
			break;
		case 2:
			buttonName = "BGMVolume_Box";
			break;
		}
		
		buttonList[buttonName] = InitButtonData(buttonName, { 100, 100 }, { 289, 65 }, { 0, 0 }, 0, "../Resource/SceneData/VolumeTrackConfig.json");
		
		UiObject* optionVolumeBox = new UiObject();
		optionVolumeBox->SetSpriteInfo(spriteList.find("OptionsVolumeBox")->second);
		optionVolumeBox->SetSize(optionVolumeBox->GetSpriteRenderer()->GetSpriteWidth(), -optionVolumeBox->GetSpriteRenderer()->GetSpriteHeight());
		optionVolumeBox->SetPosition(glm::vec3(buttonList[buttonName]->pos.x + buttonList[buttonName]->offset.x, buttonList[buttonName]->pos.y - (j * buttonList[buttonName]->offset.y), 0));
		optionVolumeBox->SetIsRender(false);
		buttonList[buttonName]->ButtonUI = optionVolumeBox;
		if (isToggleVolume[j] == true) {
			optionVolumeBox->ShiftSpriteTo(optionVolumeBox->GetSpriteRenderer()->GetRow(), 1);
		}
		else {
			optionVolumeBox->ShiftSpriteTo(optionVolumeBox->GetSpriteRenderer()->GetRow(), 3);
		}

		OptionList.push_back(optionVolumeBox);
		objectsList.push_back(optionVolumeBox);

	}
	// DisplayText
	buttonList["DisplayType_Text"]->LowerButton = buttonList["MasterVolume_Text"];

	buttonList["MasterVolume_Text"]->UpperButton = buttonList["DisplayType_Text"];
	buttonList["MasterVolume_Text"]->LowerButton = buttonList["SFXVolume_Text"];
	buttonList["MasterVolume_Knob"]->RightButton = buttonList["MasterVolume_Box"];
	buttonList["MasterVolume_Box"]->LeftButton = buttonList["MasterVolume_Knob"];


	buttonList["SFXVolume_Text"]->UpperButton = buttonList["MasterVolume_Text"];
	buttonList["SFXVolume_Text"]->LowerButton = buttonList["BGMVolume_Text"];
	buttonList["SFXVolume_Knob"]->RightButton = buttonList["SFXVolume_Box"];
	buttonList["SFXVolume_Box"]->LeftButton = buttonList["SFXVolume_Knob"];

	buttonList["BGMVolume_Text"]->UpperButton = buttonList["SFXVolume_Text"];
	buttonList["BGMVolume_Knob"]->RightButton = buttonList["BGMVolume_Box"];
	buttonList["BGMVolume_Box"]->LeftButton = buttonList["BGMVolume_Knob"];
	
	buttonList["AreYouSureStart_Yes"] = InitButtonData("AreYouSureStart_Yes", { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/YesNoConfig.json");
	buttonList["AreYouSureStart_Yes"]->ButtonUI = InitButtonUI("AreYouSureStart_Yes", spriteList["AreYouSureYN"], buttonList["AreYouSureStart_Yes"], glm::vec2(0, 1));
	buttonList["AreYouSureStart_Yes"]->ButtonUI->SetIsRender(false);
	objectsList.push_back(buttonList["AreYouSureStart_Yes"]->ButtonUI);
	yesNoList_Start.push_back(buttonList["AreYouSureStart_Yes"]->ButtonUI);

	buttonList["AreYouSureStart_No"] = InitButtonData("AreYouSureStart_No", { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/YesNoConfig.json");
	buttonList["AreYouSureStart_No"]->ButtonUI = InitButtonUI("AreYouSureStart_No", spriteList["AreYouSureYN"], buttonList["AreYouSureStart_No"], glm::vec2(0, 3));
	buttonList["AreYouSureStart_No"]->ButtonUI->SetIsRender(false);
	objectsList.push_back(buttonList["AreYouSureStart_No"]->ButtonUI);
	yesNoList_Start.push_back(buttonList["AreYouSureStart_No"]->ButtonUI);

	buttonList["AreYouSureExit_Yes"] = InitButtonData("AreYouSureExit_Yes", { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/YesNoConfig.json");
	buttonList["AreYouSureExit_Yes"]->ButtonUI = InitButtonUI("AreYouSureExit_Yes", spriteList["AreYouSureYN"], buttonList["AreYouSureExit_Yes"], glm::vec2(0, 1));
	buttonList["AreYouSureExit_Yes"]->ButtonUI->SetIsRender(false);
	objectsList.push_back(buttonList["AreYouSureExit_Yes"]->ButtonUI);
	yesNoList_Exit.push_back(buttonList["AreYouSureExit_Yes"]->ButtonUI);

	buttonList["AreYouSureExit_No"] = InitButtonData("AreYouSureExit_No", { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/YesNoConfig.json");
	buttonList["AreYouSureExit_No"]->ButtonUI = InitButtonUI("AreYouSureExit_No", spriteList["AreYouSureYN"], buttonList["AreYouSureExit_No"], glm::vec2(0, 3));
	buttonList["AreYouSureExit_No"]->ButtonUI->SetIsRender(false);
	objectsList.push_back(buttonList["AreYouSureExit_No"]->ButtonUI);
	yesNoList_Exit.push_back(buttonList["AreYouSureExit_No"]->ButtonUI);

	glm::vec3 AreYouSure_No_ButtonPos = buttonList["AreYouSureStart_No"]->ButtonUI->getPos();
	AreYouSure_No_ButtonPos.x = buttonList["AreYouSureStart_No"]->pos.x + buttonList["AreYouSureStart_No"]->offset.x;
	buttonList["AreYouSureStart_No"]->ButtonUI->SetPosition(AreYouSure_No_ButtonPos);
	buttonList["AreYouSureExit_No"]->ButtonUI->SetPosition(AreYouSure_No_ButtonPos);


	buttonList["TextOption"] = InitButtonData("TextOption", { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/TextOptionConfig.json");
	
	buttonList["Display"] = InitButtonData("Display", { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/DisplayConfig.json");
	
	buttonList["VolumeTrack"] = InitButtonData("VolumeTrack", { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, "../Resource/SceneData/VolumeTrackConfig.json");


	// Setup Button Links
	buttonList["GameName"]->LowerButton = buttonList["Text1"];

	buttonList["Text1"]->UpperButton = buttonList["GameName"];
	buttonList["Text1"]->LowerButton = buttonList["Text2"];

	buttonList["Text2"]->UpperButton = buttonList["Text1"];
	buttonList["Text2"]->LowerButton = buttonList["Text3"];

	buttonList["Text3"]->UpperButton = buttonList["Text2"];
	buttonList["Text3"]->LowerButton = buttonList["Text4"];

	buttonList["Text4"]->UpperButton = buttonList["Text3"];

	buttonList["AreYouSureStart_Yes"]->RightButton = buttonList["AreYouSureStart_No"];
	buttonList["AreYouSureStart_No"]->LeftButton = buttonList["AreYouSureStart_Yes"];

	buttonList["AreYouSureExit_Yes"]->RightButton = buttonList["AreYouSureExit_No"];
	buttonList["AreYouSureExit_No"]->LeftButton = buttonList["AreYouSureExit_Yes"];

	currentButton = buttonList["Text1"];
	buttonList["Text1"]->playerHere = true;

	

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(gameEngine->GetSDLWindow(), gameEngine->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	KK_TRACE("Level Main Menu Loaded");
}

LevelMainMenu::ButtonData* LevelMainMenu::InitButtonData(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec2 offset, int column, std::string configPath)
{
	ButtonData* button = new ButtonData();
	button->name = name;
	button->pos = pos;
	button->size = size;
	button->offset = offset;
	button->column = column;
	Buttons.push_back(button);
	loadConfigButtonData(configPath, button);

	return button;
}

void LevelMainMenu::UpdateAudio()
{
	soundManager->SetVolumeAllMusic((masterVolume / 100.0f) * BGMVolume * 0.01f * (128.f - 0));
	soundManager->SetVolumeAllSFX((masterVolume / 100.0f) * SFXVolume * 0.01f * (128.f - 0));

	if (!isToggleVolume[0])
	{
		soundManager->SetVolumeAllSFX(0);
		soundManager->SetVolumeAllMusic(0);
	}

	if (!isToggleVolume[1])
	{
		soundManager->SetVolumeAllSFX(0);
	}

	if (!isToggleVolume[2])
	{
		soundManager->SetVolumeAllMusic(0);
	}
}

void LevelMainMenu::LevelUpdate() 
{
	UpdateAudio();
	UpdateUi();

	NewUpdateInput();

	//UpdateInput();
}

void LevelMainMenu::LevelDraw() 
{
	gameEngine->Render(objectsList);
	
	ShowImGuiConfig(true);

	SDL_GL_SwapWindow(gameEngine->GetSDLWindow());

	// cout << "Draw Level" << endl;
}
void LevelMainMenu::DrawControllerButtons() {
	ImGui::BeginGroup();

	float buttonSize = 40.0f;
	float spacing = 10.0f;
	ImVec2 startPos = ImGui::GetCursorPos();

	// Helper to draw a button at a specific grid coordinate
	auto DrawButton = [&](const char* label, float x_offset, float y_offset, ImVec4 color) {
		ImGui::SetCursorPos(ImVec2(startPos.x + x_offset, startPos.y + y_offset));
		ImGui::PushStyleColor(ImGuiCol_Button, color);
		if (ImGui::Button(label, ImVec2(buttonSize, buttonSize))) {
			// Button Logic Here
			if (label == "Cross")
			{
				KK_TRACE("Pressed virtual Cross");
				isPressedCross = true;
			}
			if (label == "Circle")
			{
				KK_TRACE("Pressed virtual Circle");
				isPressedCircle = true;
			}
			if (label == "Square")
			{
				KK_TRACE("Pressed virtual Square");
				isPressedSquare = true;
			}
			if (label == "Triangle")
			{
				KK_TRACE("Pressed virtual Triangle");
				isPressedTriangle = true;
			}
		}
		else
		{
			/*isPressedCross = false;
			isPressedCircle = false;
			isPressedSquare = false;
			isPressedTriangle = false;*/
		}
		ImGui::PopStyleColor();
	};



	// Calculate offsets for the diamond shape
	float center = buttonSize + spacing;

	// Y - Top (Yellow-ish)
	DrawButton("Cross", center, 0, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	// X - Left (Blue-ish)
	DrawButton("Circle", 0, center, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	// B - Right (Red-ish)
	DrawButton("Square", center * 2, center, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	// A - Bottom (Green-ish)
	DrawButton("Triangle", center, center * 2, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	ImGui::EndGroup();
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
		gameEngine->GetStateController()->gameStateNext = GameState::GS_LEVELSELECTABILITY;
	}
	
	DrawVirtualJoystick("Joystick", joystickVal, 50);
	DrawControllerButtons();

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

void LevelMainMenu::DrawVirtualJoystick(const char* label, ImVec2& stickValue, float radius) {
	ImGui::Text("%s: %.2f, %.2f", label, stickValue.x, stickValue.y);

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 center = ImGui::GetCursorScreenPos();
	center.x += radius; center.y += radius;

	// Draw the outer boundary
	drawList->AddCircle(center, radius, IM_COL32(200, 200, 200, 255), 32, 2.0f);

	// Interaction Logic
	ImGui::InvisibleButton(label, ImVec2(radius * 2, radius * 2));
	if (ImGui::IsItemActive()) {
		ImVec2 mousePos = ImGui::GetIO().MousePos;
		stickValue.x = (mousePos.x - center.x) / radius;
		stickValue.y = (mousePos.y - center.y) / radius;

		// Clamp the vector to a length of 1.0 (circular clamping)
		float len = sqrtf(stickValue.x * stickValue.x + stickValue.y * stickValue.y);
		if (len > 1.0f) {
			stickValue.x /= len;
			stickValue.y /= len;
		}
	}
	else {
		// Optional: Auto-center (snap back to zero)
		stickValue = ImVec2(0, 0);
	}

	// Draw the knob
	ImVec2 knobPos = ImVec2(center.x + stickValue.x * radius, center.y + stickValue.y * radius);
	drawList->AddCircleFilled(knobPos, radius * 0.3f, IM_COL32(66, 150, 250, 255));

	stickValue.y *= -1;
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

void LevelMainMenu::HandleMainMenuLogic() {

	if (isPressedCross)
	{
		if (currentButton->name == "GameName")
		{
			for (UiObject* ui : creditUIList)
			{
				ui->SetIsRender(true);
			}
			currentMenuState = MenuState::Credits;
		}

		else if (currentButton->name == "Text1")
		{
			for (UiObject* ui : yesNoList_Start)
			{
				ui->SetIsRender(true);
			}
			currentMenuState = MenuState::StartConfirm;
			currentButton->playerHere = false;
			currentButton = buttonList["AreYouSureStart_No"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "Text2")
		{
			for (UiObject* ui : tutorialInfoList)
			{
				ui->SetIsRender(true);
			}
			InfoPage = 0;
			currentMenuState = MenuState::Tutorial;
		}

		//text3

		else if (currentButton->name == "Text3")
		{
			for (UiObject* ui : OptionList)
			{
				ui->SetIsRender(true);
			}
			currentMenuState = MenuState::Options;
			currentButton->playerHere = false;
			currentButton = buttonList["DisplayType_Text"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "Text4")
		{
			for (UiObject* ui : yesNoList_Exit)
			{
				ui->SetIsRender(true);
			}
			currentMenuState = MenuState::ExitConfirm;
			currentButton->playerHere = false;
			currentButton = buttonList["AreYouSureExit_No"];
			currentButton->playerHere = true;
		}
	}
}
void LevelMainMenu::HandleCreditsLogic() 
{
	if (isPressedCross || isPressedCircle)
	{
		for (UiObject* ui : creditUIList)
		{
			ui->SetIsRender(false);
		}
		currentMenuState = MenuState::Main;
		currentButton->playerHere = false;
		currentButton = buttonList["Text1"];
		currentButton->playerHere = true;
	}
}

void LevelMainMenu::HandleStartConfirmLogic() 
{
	KK_TRACE("currentButton->name = " + currentButton->name);
	if (isPressedCross)
	{
		if (currentButton->name == "AreYouSureStart_Yes")
		{
			gameEngine->GetStateController()->gameStateNext = GameState::GS_LEVELSELECTABILITY;
		}

		if (currentButton->name == "AreYouSureStart_No")
		{
			for (UiObject* ui : yesNoList_Start)
			{
				ui->SetIsRender(false);
			}
			currentMenuState = MenuState::Main;
			currentButton->playerHere = false;
			currentButton = buttonList["Text1"];
			currentButton->playerHere = true;
		}
	}

	if (isPressedCircle)
	{
		if (currentButton->name == "AreYouSureStart_No")
		{
			for (UiObject* ui : yesNoList_Start)
			{
				ui->SetIsRender(false);
			}
			currentMenuState = MenuState::Main;
			currentButton->playerHere = false;
			currentButton = buttonList["Text1"];
			currentButton->playerHere = true;
		}
	}
}

void LevelMainMenu::HandleTutorialLogic() {

	if (isPressedCross)
	{
		tutorialInfoUI->GetSpriteRenderer()->ShiftColumn();
		InfoPage++;
		if (InfoPage >= InfoPageLimit)
		{
			for (UiObject* ui : tutorialInfoList)
			{
				ui->SetIsRender(false);
			}
			currentMenuState = MenuState::Main;
			currentButton = buttonList["Text2"];
			currentButton->playerHere = true;
		}
	}
}

void LevelMainMenu::HandleOptionsLogic() {

	//KK_TRACE("currentButton = " + currentButton->name);
	if (isPressedCross)
	{
		if (currentButton->name == "DisplayType_Text")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["DisplayType"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "DisplayType")
		{
			currentButton = buttonList["DisplayDropdown"];
			currentButton->playerHere = true;
			buttonList["DisplayDropdown"]->ButtonUI->SetIsRender(true);
		}

		else if (currentButton->name == "DisplayDropdown")
		{
			int currentShift = buttonList["DisplayDropdown"]->ButtonUI->GetSpriteRenderer()->GetColumn();
			
			if (isFullscreen && currentShift == 1)
			{
				SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), 0);
				windowWidth = SCREEN_WIDTH;
				windowHeight = SCREEN_HEIGHT;
				glViewport(0, 0, windowWidth, windowHeight);
				buttonList["DisplayType"]->ButtonUI->ShiftSpriteTo(0, 2);
				isFullscreen = false;
			}
			else if (!isFullscreen && currentShift == 0)
			{
				SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
				SDL_GetWindowSize(GameEngine::GetInstance()->GetSDLWindow(), &windowWidth, &windowHeight);
				glViewport(0, 0, windowWidth, windowHeight);
				buttonList["DisplayType"]->ButtonUI->ShiftSpriteTo(0, 0);
				isFullscreen = true;
			}
		}

		else if (currentButton->name == "MasterVolume_Text")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["MasterVolume_Knob"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "SFXVolume_Text")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["SFXVolume_Knob"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "BGMVolume_Text")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["BGMVolume_Knob"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "MasterVolume_Knob")
		{
			currentButton = buttonList["MasterVolume_Track"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "SFXVolume_Knob")
		{
			currentButton = buttonList["SFXVolume_Track"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "BGMVolume_Knob")
		{
			currentButton = buttonList["BGMVolume_Track"];
			currentButton->playerHere = true;
		}


		else if (currentButton->name == "MasterVolume_Box" ||
			currentButton->name == "SFXVolume_Box" ||
			currentButton->name == "BGMVolume_Box")
		{
			int boxIndex = volumeBoxIndexMap.find(currentButton->name)->second;
			isToggleVolume[boxIndex] = !isToggleVolume[boxIndex];
		}

	}

	if (isPressedCircle)
	{
		if (currentButton->name == "DisplayType_Text" ||
			currentButton->name == "MasterVolume_Text" ||
			currentButton->name == "SFXVolume_Text" ||
			currentButton->name == "BGMVolume_Text")
		{
			for (UiObject* ui : OptionList)
			{
				ui->SetIsRender(false);
			}
			currentMenuState = MenuState::Main;
			currentButton->playerHere = false;
			currentButton = buttonList["Text3"];
			currentButton->playerHere = true;
		}
		else if (currentButton->name == "DisplayType")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["DisplayType_Text"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "MasterVolume_Knob" ||
			currentButton->name == "MasterVolume_Box")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["MasterVolume_Text"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "SFXVolume_Knob" ||
			currentButton->name == "SFXVolume_Box")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["SFXVolume_Text"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "BGMVolume_Knob" ||
			currentButton->name == "BGMVolume_Box")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["BGMVolume_Text"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "MasterVolume_Track")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["MasterVolume_Knob"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "SFXVolume_Track")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["SFXVolume_Knob"];
			currentButton->playerHere = true;
		}

		else if (currentButton->name == "BGMVolume_Track")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["BGMVolume_Knob"];
			currentButton->playerHere = true;
		}
		else if (currentButton->name == "DisplayDropdown")
		{
			currentButton->playerHere = false;
			currentButton = buttonList["DisplayType"];
			currentButton->playerHere = true;
			buttonList["DisplayDropdown"]->ButtonUI->SetIsRender(false);
		}
	}

	if (currentButton->name == "DisplayDropdown")
	{
		//KK_TRACE("currentButton->name == DisplayDropdown");
		if (playerMove) KK_TRACE("playerMove");

		if ((up || down) && !playerMove)
		{
			currentButton->ButtonUI->GetSpriteRenderer()->ShiftColumn();
		}
	}

	if (currentButton == buttonList["MasterVolume_Track"]) {
		std::cout << masterVolume << std::endl;
		if (holdright)
			masterVolume++;
		else if (holdleft)
			masterVolume--;
		masterVolume = std::min(100.0f, std::max(masterVolume, 0.0f));
		buttonList["MasterVolume_Knob"]->ButtonUI->SetPosition(
			glm::vec3((masterVolume * 4 - 57.5 / 0.25), 
			buttonList["MasterVolume_Knob"]->pos.y - (0 * buttonList["MasterVolume_Knob"]->offset.y), 
			0));
	}
	if (currentButton == buttonList["SFXVolume_Track"]) {
		std::cout << masterVolume << std::endl;
		if (holdright)
			SFXVolume++;
		else if (holdleft)
			SFXVolume--;
		SFXVolume = std::min(100.0f, std::max(SFXVolume, 0.0f));
		buttonList["SFXVolume_Knob"]->ButtonUI->SetPosition(
			glm::vec3((SFXVolume * 4 - 57.5 / 0.25),
				buttonList["SFXVolume_Knob"]->pos.y - (1 * buttonList["SFXVolume_Knob"]->offset.y),
				0));
	}
	if (currentButton == buttonList["BGMVolume_Track"]) {
		std::cout << masterVolume << std::endl;
		if (holdright)
			BGMVolume++;
		else if (holdleft)
			BGMVolume--;
		BGMVolume = std::min(100.0f, std::max(BGMVolume, 0.0f));
		buttonList["BGMVolume_Knob"]->ButtonUI->SetPosition(
			glm::vec3((BGMVolume * 4 - 57.5 / 0.25), 
			buttonList["BGMVolume_Knob"]->pos.y - (2 * buttonList["BGMVolume_Knob"]->offset.y), 
			0));
	}
	
}
void LevelMainMenu::HandleExitConfirmLogic() {

	KK_TRACE("currentButton->name = " + currentButton->name);
	if (isPressedCross)
	{
		if (currentButton->name == "AreYouSureExit_Yes")
		{
			GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT;
		}

		if (currentButton->name == "AreYouSureExit_No")
		{
			for (UiObject* ui : yesNoList_Exit)
			{
				ui->SetIsRender(false);
			}
			currentMenuState = MenuState::Main;
			currentButton->playerHere = false;
			currentButton = buttonList["Text4"];
			currentButton->playerHere = true;
		}
	}

	if (isPressedCircle)
	{
		if (currentButton->name == "AreYouSureExit_No")
		{
			for (UiObject* ui : yesNoList_Exit)
			{
				ui->SetIsRender(false);
			}
			currentMenuState = MenuState::Main;
			currentButton->playerHere = false;
			currentButton = buttonList["Text4"];
			currentButton->playerHere = true;
		}
	}
}
void LevelMainMenu::NewUpdateInput()
{
	// change this to test the joystick
	bool isUsingJoystick = true;

	
	up = false;
	down = false;
	right = false;
	left = false;

	if (isUsingJoystick)
	{
		if (SDL_NumJoysticks() > 0)
		{
			Joystick::Update();
			for (int i = 0; i < 1; i++)
			{
				float axisX = Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal);
				float axisY = Joystick::GetAxis(0, Joystick::Axis::LeftStickVertical);

				up = false;
				down = false;
				right = false;
				left = false;

				if (axisX > 0.8 || joystickVal.x > 0.8 || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Right)) {
					right = true;
					holdright = true;
				}
				else if (axisX < -0.8 || joystickVal.x < -0.8 || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Left)) {
					left = true;
					holdleft = true;
				}
				else if (axisY > 0.8 || joystickVal.y < -0.8 || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Down)) {
					
					down = true;
					holddown = true;
				}
				else if (axisY < -0.8 || joystickVal.y > 0.8 || Joystick::GetButtonDown(0, Joystick::Button::DPAD_Up)) {
					up = true;
					holdup = true;
					
				}
				else
				{
					holdright = false;
					holdleft = false;
					holddown = false;
					holdup = false;

					playerMove = false;
				}

				if (Joystick::GetButtonDown(i, Joystick::Button::Cross)) isPressedCross = true;
				if (Joystick::GetButtonDown(i, Joystick::Button::Circle)) isPressedCircle = true;
				if (Joystick::GetButtonDown(i, Joystick::Button::Square)) isPressedSquare = true;
				if (Joystick::GetButtonDown(i, Joystick::Button::Triangle)) isPressedTriangle = true;
			}
		}
	}
	else
	{
		if (joystickVal.x > 0.8) {
			right = true;
			holdright = true;
		}
		else if (joystickVal.x < -0.8) {
			left = true;
			holdleft = true;
		}
		else if (joystickVal.y > 0.8) {
			up = true;
			holdup = true;
		}
		else if (joystickVal.y < -0.8) {
			
			down = true;
			holddown = true;
		}
		else
		{
			holdright = false;
			holdleft = false;
			holddown = false;
			holdup = false;

			playerMove = false;
		}
	}
	

	switch (currentMenuState) {
	case MenuState::Main:        HandleMainMenuLogic(); break;
	case MenuState::Credits:     HandleCreditsLogic();  break;
	case MenuState::StartConfirm:    HandleStartConfirmLogic(); break;
	case MenuState::Tutorial:    HandleTutorialLogic(); break;
	case MenuState::Options:    HandleOptionsLogic(); break;
	case MenuState::ExitConfirm:    HandleExitConfirmLogic(); break;
	}

	// update joystick inputs
	if (!playerMove && (up || down || left || right))
	{
		playerMove = true;
		currentButton->playerHere = false;

		if (up && currentButton->UpperButton != nullptr)
			currentButton = currentButton->UpperButton;

		if (down && currentButton->LowerButton != nullptr)
			currentButton = currentButton->LowerButton;

		if (left && currentButton->LeftButton != nullptr)
			currentButton = currentButton->LeftButton;

		if (right && currentButton->RightButton != nullptr)
			currentButton = currentButton->RightButton;

		currentButton->playerHere = true;
	}

	


	// Reset button to prevent infinite Click
	isPressedCross = false;
	isPressedCircle = false;
	isPressedSquare = false;
	isPressedTriangle = false;
}
void LevelMainMenu::UpdateInput() 
{
	
}

void LevelMainMenu::UpdateUi() 
{
	if (currentMenuState == MenuState::Main)
	{
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
	else if (currentMenuState == MenuState::StartConfirm)
	{
		for (const auto& buttonData : buttonList)
		{
			if (buttonData.first == "AreYouSureStart_Yes")
			{
				if (buttonData.second->playerHere)
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 1);
				else
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 0);
			}

			if (buttonData.first == "AreYouSureStart_No")
			{
				if (buttonData.second->playerHere)
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 3);
				else
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 2);
			}
		}
	}
	else if (currentMenuState == MenuState::ExitConfirm)
	{
		for (const auto& buttonData : buttonList)
		{
			if (buttonData.first == "AreYouSureExit_Yes")
			{
				if (buttonData.second->playerHere)
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 1);
				else
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 0);
			}

			if (buttonData.first == "AreYouSureExit_No")
			{
				if (buttonData.second->playerHere)
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 3);
				else
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 2);
			}
		}
	}
	else if (currentMenuState == MenuState::Options)
	{
		for (const auto& buttonData : buttonList)
		{
			if (buttonData.first == "DisplayType")
			{
				int baseOffset = !isFullscreen ? 2 : 0;
				int playerOffset = buttonData.second->playerHere ? 0 : 1;

				buttonData.second->ButtonUI->ShiftSpriteTo(0, baseOffset + playerOffset);
			}

			if (buttonData.first == "MasterVolume_Track" ||
				buttonData.first == "SFXVolume_Track" || 
				buttonData.first == "BGMVolume_Track")
			{
				if (buttonData.second->playerHere)
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 1);
				else
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 0);
			}

			if (buttonData.first == "MasterVolume_Knob" || 
				buttonData.first == "SFXVolume_Knob" || 
				buttonData.first == "BGMVolume_Knob")
			{
				//KK_TRACE("KNOB");
				//KK_TRACE("buttonData.first = " + buttonData.first);

				if (buttonData.second->playerHere)
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 1);
				else
					buttonData.second->ButtonUI->ShiftSpriteTo(0, 0);
			}

			if (buttonData.first == "DisplayType_Text" || 
				buttonData.first == "MasterVolume_Text" ||
				buttonData.first == "SFXVolume_Text" ||
				buttonData.first == "BGMVolume_Text")
			{
				int isPlayer = buttonData.second->playerHere ? 1 : 0;

				int yIndex = isPlayer + volumeTextIndexMap.find(buttonData.first)->second;

				buttonData.second->ButtonUI->ShiftSpriteTo(0, yIndex);
			}

			if (buttonData.first == "MasterVolume_Box" || 
				buttonData.first == "SFXVolume_Box" || 
				buttonData.first == "BGMVolume_Box")
			{
				bool isToggled = isToggleVolume[volumeBoxIndexMap.find(buttonData.first)->second];
				bool isPlayer = buttonData.second->playerHere;

				int yIndex = isPlayer ? (isToggled ? 0 : 2) : (isToggled ? 1 : 3);

				buttonData.second->ButtonUI->ShiftSpriteTo(0, yIndex);
			}
		}
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

void LevelMainMenu::loadConfig(std::string filename) 
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		KK_ERROR("LevelMainMenu: Cannot Load Configuration file!");
		return;
	}

	nlohmann::json data = nlohmann::json::parse(file);
	int id = -1;
	std::cout << "Opened" << std::endl;

	if (data.contains("number") && !data["number"].is_null()) 
	{
		id = data["number"];

		for (int i = 0; i < Buttons.size(); i++) 
		{
			if (Buttons.at(i)->number == id) 
			{
				std::cout << "Loaded" << std::endl;

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

void LevelMainMenu::loadConfigButtonData(std::string filename, ButtonData* buttonData)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		KK_ERROR("LevelMainMenu: Cannot Load Configuration file!");
		return;
	}

	nlohmann::json data = nlohmann::json::parse(file);
	std::cout << "Opened" << std::endl;

	if (data.contains("posX") && !data["posX"].is_null()) {
		buttonData->pos.x = data["posX"];
	}

	if (data.contains("posY") && !data["posY"].is_null()) {
		buttonData->pos.y = data["posY"];
	}

	if (data.contains("width") && !data["width"].is_null()) {
		buttonData->size.x = data["width"];
	}

	if (data.contains("hight") && !data["hight"].is_null()) {
		buttonData->size.y = data["hight"];
	}

	if (data.contains("offSetX") && !data["offSetX"].is_null()) {
		buttonData->offset.x = data["offSetX"];
	}

	if (data.contains("offSetY") && !data["offSetY"].is_null()) {
		buttonData->offset.y = data["offSetY"];
	}
}

