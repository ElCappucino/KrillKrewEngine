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

UiObject* LevelMainMenu::InitUI(SpritesheetInfo spriteInfo, glm::vec2 pos, glm::vec2 size, glm::vec2 spriteShiftPos)
{
	UiObject* ui = new UiObject();
	ui->SetSpriteInfo(spriteInfo);
	ui->SetPosition({ pos.x, pos.y, 0 });
	ui->SetSize(size.x, -size.y);
	ui->ShiftSpriteTo(spriteShiftPos.x, spriteShiftPos.y);
	return ui;
}

UiObject* LevelMainMenu::InitButtonUI(SpritesheetInfo spriteInfo, ButtonData* buttonData, glm::vec2 spriteShiftPos)
{
	UiObject* ui = new UiObject();
	ui->SetSpriteInfo(spriteInfo);
	ui->SetPosition({ buttonData->pos.x, buttonData->pos.y, 0 });
	ui->SetSize(buttonData->size.x, -buttonData->size.y);
	ui->ShiftSpriteTo(spriteShiftPos.x, spriteShiftPos.y);
	return ui;
}

LevelMainMenu::ButtonData* LevelMainMenu::InitButtonData(MenuButtonName_ name, std::string stringName, glm::vec2 pos, glm::vec2 size, glm::vec2 offset, int column, std::string configPath)
{
	ButtonData* button = new ButtonData();
	button->name = name;
	button->stringName = stringName;
	button->pos = pos;
	button->size = size;
	button->offset = offset;
	button->column = column;
	Buttons.push_back(button);
	loadConfigButtonData(configPath, button);

	return button;
}

void LevelMainMenu::SetupButtonLinks()
{
	// DisplayText
	buttonList[MenuButtonName_DisplayType_Text]->LowerButton = buttonList[MenuButtonName_MasterVolume_Text];

	buttonList[MenuButtonName_MasterVolume_Text]->UpperButton = buttonList[MenuButtonName_DisplayType_Text];
	buttonList[MenuButtonName_MasterVolume_Text]->LowerButton = buttonList[MenuButtonName_SFXVolume_Text];
	buttonList[MenuButtonName_MasterVolume_Knob]->RightButton = buttonList[MenuButtonName_MasterVolume_Box];
	buttonList[MenuButtonName_MasterVolume_Box]->LeftButton = buttonList[MenuButtonName_MasterVolume_Knob];


	buttonList[MenuButtonName_SFXVolume_Text]->UpperButton = buttonList[MenuButtonName_MasterVolume_Text];
	buttonList[MenuButtonName_SFXVolume_Text]->LowerButton = buttonList[MenuButtonName_BGMVolume_Text];
	buttonList[MenuButtonName_SFXVolume_Knob]->RightButton = buttonList[MenuButtonName_SFXVolume_Box];
	buttonList[MenuButtonName_SFXVolume_Box]->LeftButton = buttonList[MenuButtonName_SFXVolume_Knob];

	buttonList[MenuButtonName_BGMVolume_Text]->UpperButton = buttonList[MenuButtonName_SFXVolume_Text];
	buttonList[MenuButtonName_BGMVolume_Knob]->RightButton = buttonList[MenuButtonName_BGMVolume_Box];
	buttonList[MenuButtonName_BGMVolume_Box]->LeftButton = buttonList[MenuButtonName_BGMVolume_Knob];

	// Setup Button Links
	buttonList[MenuButtonName_GameName]->LowerButton = buttonList[MenuButtonName_StartButton];

	buttonList[MenuButtonName_StartButton]->UpperButton = buttonList[MenuButtonName_GameName];
	buttonList[MenuButtonName_StartButton]->LowerButton = buttonList[MenuButtonName_TutorialButton];

	buttonList[MenuButtonName_TutorialButton]->UpperButton = buttonList[MenuButtonName_StartButton];
	buttonList[MenuButtonName_TutorialButton]->LowerButton = buttonList[MenuButtonName_OptionButton];

	buttonList[MenuButtonName_OptionButton]->UpperButton = buttonList[MenuButtonName_TutorialButton];
	buttonList[MenuButtonName_OptionButton]->LowerButton = buttonList[MenuButtonName_ExitButton];

	buttonList[MenuButtonName_ExitButton]->UpperButton = buttonList[MenuButtonName_OptionButton];

	buttonList[MenuButtonName_AreYouSureStart_Yes]->RightButton = buttonList[MenuButtonName_AreYouSureStart_No];
	buttonList[MenuButtonName_AreYouSureStart_No]->LeftButton = buttonList[MenuButtonName_AreYouSureStart_Yes];

	buttonList[MenuButtonName_AreYouSureExit_Yes]->RightButton = buttonList[MenuButtonName_AreYouSureExit_No];
	buttonList[MenuButtonName_AreYouSureExit_No]->LeftButton = buttonList[MenuButtonName_AreYouSureExit_Yes];

	currentButton = buttonList[MenuButtonName_StartButton];
	buttonList[MenuButtonName_StartButton]->playerHere = true;
}

void LevelMainMenu::InitializeMainMenuUI()
{
	glm::vec2 backgroundSize(camera.GetCameraWidth(), camera.GetCameraHeight());
	UiObject* BG = InitUI(spriteList["BG"], glm::vec2(0, 0), backgroundSize, glm::vec2(0, 0));
	objectsList.push_back(BG);

	// game name
	buttonList[MenuButtonName_GameName] = InitButtonData(MenuButtonName_GameName, "MenuButtonName_GameName", { 100, 100 }, {470, 55}, {0, 0}, 0, "../Resource/SceneData/MainMenu/MenuButtonName_GameName.json");
	buttonList[MenuButtonName_GameName]->ButtonUI = InitButtonUI(spriteList["Name"], buttonList[MenuButtonName_GameName], glm::vec2(0, 0));

	objectsList.push_back(buttonList[MenuButtonName_GameName]->ButtonUI);
	textList.push_back(buttonList[MenuButtonName_GameName]->ButtonUI);

	// Main button
	for (int i = 1; i < 5; i++)
	{
		// position file data
		
		MenuButtonName_ buttonName;
		std::string buttonStringName;

		switch (i)
		{
		case 1:
			buttonName = MenuButtonName_StartButton;
			buttonStringName = "MenuButtonName_StartButton";
			break;
		case 2:
			buttonName = MenuButtonName_TutorialButton;
			buttonStringName = "MenuButtonName_TutorialButton";
			break;
		case 3:
			buttonName = MenuButtonName_OptionButton;
			buttonStringName = "MenuButtonName_OptionButton";
			break;
		case 4:
			buttonName = MenuButtonName_ExitButton;
			buttonStringName = "MenuButtonName_ExitButton";
			break;
		}

		std::string fileName = "../Resource/SceneData/MainMenu/" + buttonStringName + ".json";

		int buttonUIShiftColumn = (i - 1) * 2;

		buttonList[buttonName] = InitButtonData(buttonName, buttonStringName, { 100, 100 }, { 289, 65 }, { 0, 0 }, buttonUIShiftColumn, fileName);
		buttonList[buttonName]->ButtonUI = InitButtonUI(spriteList["Text"], buttonList[buttonName], glm::vec2(0, buttonUIShiftColumn));

		objectsList.push_back(buttonList[buttonName]->ButtonUI);
		textList.push_back(buttonList[buttonName]->ButtonUI);
	}
}

void LevelMainMenu::InitializeConfirmUI()
{
	// 1. Get a reference to the sprites to avoid repetitive map lookups
	auto& areYouSureSprite = spriteList["AreYouSure"];
	auto& ynsprite = spriteList["AreYouSureYN"];

	// 2. Setup Background for Start Confirm
	UiObject* areYouSureStart = InitUI(areYouSureSprite, { 0, 0 }, { areYouSureSprite.spritewidth, areYouSureSprite.spriteheight }, { 0, 0 });
	areYouSureStart->SetIsRender(false);
	objectsList.push_back(areYouSureStart);
	yesNoList_Start.push_back(areYouSureStart);

	// 3. Setup Background for Exit Confirm
	UiObject* areYouSureExit = InitUI(areYouSureSprite, { 0, 0 }, { areYouSureSprite.spritewidth, areYouSureSprite.spriteheight }, { 0, 2 });
	areYouSureExit->SetIsRender(false);
	objectsList.push_back(areYouSureExit);
	yesNoList_Exit.push_back(areYouSureExit);

	// 4. Helper Lambda for confirmation button creation
	auto SetupConfirmButton = [this, &ynsprite](MenuButtonName_ name, std::string stringName, glm::vec2 shift, std::vector<UiObject*>& targetList)
		{
			std::string filename = "../Resource/SceneData/MainMenu/" + stringName + ".json";
			buttonList[name] = InitButtonData(name, stringName, { 0, 0 }, { 0, 0 }, { 100, 0 }, 0, filename);
			buttonList[name]->ButtonUI = InitButtonUI(ynsprite, buttonList[name], shift);
			buttonList[name]->ButtonUI->SetIsRender(false);

			objectsList.push_back(buttonList[name]->ButtonUI);
			targetList.push_back(buttonList[name]->ButtonUI);
		};

	// 5. Create the buttons cleanly
	SetupConfirmButton(MenuButtonName_AreYouSureStart_Yes, "MenuButtonName_AreYouSureStart_Yes", { 0, 1 }, yesNoList_Start);
	SetupConfirmButton(MenuButtonName_AreYouSureStart_No, "MenuButtonName_AreYouSureStart_No", { 0, 3 }, yesNoList_Start);

	SetupConfirmButton(MenuButtonName_AreYouSureExit_Yes, "MenuButtonName_AreYouSureExit_Yes", { 0, 1 }, yesNoList_Exit);
	SetupConfirmButton(MenuButtonName_AreYouSureExit_No, "MenuButtonName_AreYouSureExit_No", { 0, 3 }, yesNoList_Exit);

	// 6. Adjust positions for 'No' buttons
	glm::vec3 AreYouSure_No_ButtonPos = buttonList[MenuButtonName_AreYouSureStart_No]->ButtonUI->getPos();
	AreYouSure_No_ButtonPos.x = buttonList[MenuButtonName_AreYouSureStart_No]->pos.x + buttonList[MenuButtonName_AreYouSureStart_No]->offset.x;

	buttonList[MenuButtonName_AreYouSureStart_No]->ButtonUI->SetPosition(AreYouSure_No_ButtonPos);
	buttonList[MenuButtonName_AreYouSureExit_No]->ButtonUI->SetPosition(AreYouSure_No_ButtonPos);
}

void LevelMainMenu::InitializeCreditUI()
{
	UiObject* credit = InitUI(spriteList["Credit"], {0, 0}, { camera.GetCameraWidth(), camera.GetCameraHeight() }, {0, 0});
	credit->SetIsRender(false);
	objectsList.push_back(credit);
	creditUIList.push_back(credit);
}

void LevelMainMenu::InitializeTutorialUI()
{
	auto& tutorialBGSprite = spriteList["TutorialBG"];
	UiObject* tutorialBG = InitUI(tutorialBGSprite, { 0, 0 }, { tutorialBGSprite.spritewidth, tutorialBGSprite.spriteheight }, { 0, 0 });
	tutorialBG->SetIsRender(false);
	objectsList.push_back(tutorialBG);
	tutorialInfoList.push_back(tutorialBG);

	auto& tutorialInfoSprite = spriteList["TutorialInfo"];
	UiObject* tutorialInfo = InitUI(tutorialInfoSprite, { 0, 0 }, { tutorialInfoSprite.spritewidth, tutorialInfoSprite.spriteheight }, { 0, 0 });
	tutorialInfo->SetIsRender(false);
	tutorialInfoUI = tutorialInfo;
	objectsList.push_back(tutorialInfo);
	tutorialInfoList.push_back(tutorialInfo);
}

void LevelMainMenu::InitializeOptionUI()
{
	// Setup Options Background
	auto& bgSprite = spriteList["OptionsBG"];
	UiObject* optionsBG = InitUI(bgSprite, { 0, 0 }, { bgSprite.spritewidth, bgSprite.spriteheight }, { 0, 0 });
	optionsBG->SetIsRender(false);
	OptionList.push_back(optionsBG);
	objectsList.push_back(optionsBG);

	// Setup Option Texts
	// Button Name Mapping
	MenuButtonName_ textButtons[] = 
	{
		MenuButtonName_DisplayType_Text,
		MenuButtonName_MasterVolume_Text,
		MenuButtonName_SFXVolume_Text,
		MenuButtonName_BGMVolume_Text
	};

	std::string textButtonsName[] =
	{
		"MenuButtonName_DisplayType_Text",
		"MenuButtonName_MasterVolume_Text",
		"MenuButtonName_SFXVolume_Text",
		"MenuButtonName_BGMVolume_Text"
	};

	std::string configFileName;

	for (int j = 0; j < 4; j++) {

		MenuButtonName_ buttonName = textButtons[j];
		std::string buttonStringName = textButtonsName[j];
		auto& textSprite = spriteList["OptionsText"];
		glm::vec2 spriteColumn = glm::vec2(0, j * 2);
		configFileName = "../Resource/SceneData/MainMenu/" + buttonStringName + ".json";

		buttonList[buttonName] = InitButtonData(buttonName, buttonStringName, { 100, 100 }, { 289, 65 }, { 0, 0 }, j * 2, configFileName);
		float buttonPosX = buttonList[buttonName]->pos.x;
		float buttonPosY = buttonList[buttonName]->pos.y + (-j * buttonList[buttonName]->offset.y);

		UiObject* textOption = InitUI(textSprite, { 0, 0 }, { textSprite.spritewidth, textSprite.spriteheight }, spriteColumn);
		textOption->SetPosition(glm::vec3(buttonPosX, buttonPosY, 0));
		textOption->SetIsRender(false);

		buttonList[buttonName]->ButtonUI = textOption;

		OptionList.push_back(textOption);
		objectsList.push_back(textOption);
	}

	// Display Type Button Setup
	auto& optionDisplaySprite = spriteList["OptionsDisplay"];

	configFileName = "../Resource/SceneData/MainMenu/MenuButtonName_DisplayType.json";

	buttonList[MenuButtonName_DisplayType] = InitButtonData(MenuButtonName_DisplayType, "MenuButtonName_DisplayType", { 100, 100 }, {289, 65}, {0, 0}, 0, configFileName);

	float displayTypePosX = buttonList[MenuButtonName_DisplayType]->pos.x;
	float displayTypePosY = buttonList[MenuButtonName_DisplayType]->pos.y;

	UiObject* optionDisplay = InitUI(optionDisplaySprite, { displayTypePosX, displayTypePosY }, { optionDisplaySprite.spritewidth, optionDisplaySprite.spriteheight }, { 0, 0 });
	optionDisplay->SetIsRender(false);
	optionDisplay->ShiftSpriteTo(optionDisplay->GetSpriteRenderer()->GetRow(), (windowWidth == SCREEN_WIDTH) ? 3 : 1);

	buttonList[MenuButtonName_DisplayType]->ButtonUI = optionDisplay;

	OptionList.push_back(optionDisplay);
	objectsList.push_back(optionDisplay);

	// Display Dropdown

	auto& displayDropdownSprite = spriteList["OptionsDisplayDropdown"];
	buttonList[MenuButtonName_DisplayDropdown] = InitButtonData(MenuButtonName_DisplayDropdown, "MenuButtonName_DisplayDropdown", { 100, 100 }, {289, 65}, {0, 0}, 0, configFileName);
	
	float displayDropdownOffsetY = -70.0f;
	float displayDropdownButtonPosX = buttonList[MenuButtonName_DisplayDropdown]->pos.x;
	float displayDropdownButtonPosY = buttonList[MenuButtonName_DisplayDropdown]->pos.y + displayDropdownOffsetY;

	UiObject* displayDropdownUI = InitUI(displayDropdownSprite, { displayDropdownButtonPosX, displayDropdownButtonPosY }, { displayDropdownSprite.spritewidth, displayDropdownSprite.spriteheight }, { 0, 0 });
	displayDropdownUI->SetIsRender(false);

	buttonList[MenuButtonName_DisplayDropdown]->ButtonUI = displayDropdownUI;

	objectsList.push_back(displayDropdownUI);

	// Volume Controls
	MenuButtonName_ trackButtons[] = { MenuButtonName_MasterVolume_Track, MenuButtonName_SFXVolume_Track, MenuButtonName_BGMVolume_Track };
	MenuButtonName_ knobButtons[] = { MenuButtonName_MasterVolume_Knob,  MenuButtonName_SFXVolume_Knob,  MenuButtonName_BGMVolume_Knob };
	MenuButtonName_ boxButtons[] = { MenuButtonName_MasterVolume_Box,   MenuButtonName_SFXVolume_Box,   MenuButtonName_BGMVolume_Box };

	std::string trackButtonsString[] = { "MenuButtonName_MasterVolume_Track", "MenuButtonName_SFXVolume_Track", "MenuButtonName_BGMVolume_Track" };
	std::string knobButtonsString[] = { "MenuButtonName_MasterVolume_Knob",  "MenuButtonName_SFXVolume_Knob",  "MenuButtonName_BGMVolume_Knob" };
	std::string boxButtonsString[] = { "MenuButtonName_MasterVolume_Box",   "MenuButtonName_SFXVolume_Box",   "MenuButtonName_BGMVolume_Box" };

	float volumeValues[] = { masterVolume, SFXVolume, BGMVolume };

	auto& trackSprite = spriteList["OptionsVolumeTrack"];
	auto& knobSprite = spriteList["OptionsVolumeKnob"];
	auto& boxSprite = spriteList["OptionsVolumeBox"];

	for (int j = 0; j < 3; j++)
	{
		MenuButtonName_ trackName = trackButtons[j];
		MenuButtonName_ knobName = knobButtons[j];
		MenuButtonName_ boxName = boxButtons[j];

		std::string trackNameString = trackButtonsString[j];
		std::string knobNameString = knobButtonsString[j];
		std::string boxNameString = boxButtonsString[j];

		// Track UI
		configFileName = "../Resource/SceneData/MainMenu/" + trackNameString + ".json";
		
		buttonList[trackName] = InitButtonData(trackName, trackNameString, { 100, 100 }, { 289, 65 }, { 0, 0 }, 0, configFileName);

		float volumeButtonPosX = buttonList[trackName]->pos.x;
		float volumeButtonPosY = buttonList[trackName]->pos.y - (j * buttonList[trackName]->offset.y);

		UiObject* optionVolumeTrack = InitUI(trackSprite, { volumeButtonPosX, volumeButtonPosY }, { trackSprite.spritewidth, trackSprite.spriteheight }, { 0, 0 });
		optionVolumeTrack->SetIsRender(false);

		buttonList[trackName]->ButtonUI = optionVolumeTrack;

		objectsList.push_back(optionVolumeTrack);
		OptionList.push_back(optionVolumeTrack);

		// Knob UI
		configFileName = "../Resource/SceneData/MainMenu/" + knobNameString + ".json";
		float knobX = (volumeValues[j] * 4 - 57.5 / 0.25);

		buttonList[knobName] = InitButtonData(knobName, knobNameString, { 100, 100 }, { 289, 65 }, { 0, 0 }, 0, configFileName);

		UiObject* optionVolumeKnob = InitUI(knobSprite, { 0, 0 }, { knobSprite.spritewidth, knobSprite.spriteheight }, { 0, 0 });
		optionVolumeKnob->SetIsRender(false);
		optionVolumeKnob->SetPosition(glm::vec3(knobX, buttonList[knobName]->pos.y - (j * buttonList[knobName]->offset.y), 0));

		buttonList[knobName]->ButtonUI = optionVolumeKnob;

		objectsList.push_back(optionVolumeKnob);
		OptionList.push_back(optionVolumeKnob);

		// Box UI
		configFileName = "../Resource/SceneData/MainMenu/" + boxNameString + ".json";

		buttonList[boxName] = InitButtonData(boxName, boxNameString, { 100, 100 }, { 289, 65 }, { 0, 0 }, 0, configFileName);

		float BoxButtonPosX = buttonList[boxName]->pos.x + buttonList[boxName]->offset.x;
		float BoxButtonPosY = buttonList[boxName]->pos.y - (j * buttonList[boxName]->offset.y);

		UiObject* optionVolumeBox = InitUI(spriteList["OptionsVolumeBox"], { BoxButtonPosX, BoxButtonPosY }, { spriteList["OptionsVolumeBox"].spritewidth, spriteList["OptionsVolumeBox"].spriteheight }, { 0, 0 });
		optionVolumeBox->SetIsRender(false);
		optionVolumeBox->ShiftSpriteTo(optionVolumeBox->GetSpriteRenderer()->GetRow(), isToggleVolume[j] ? 1 : 3);

		buttonList[boxName]->ButtonUI = optionVolumeBox;

		OptionList.push_back(optionVolumeBox);
		objectsList.push_back(optionVolumeBox);
	}
}

void LevelMainMenu::InitializeImGui()
{
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
}

void LevelMainMenu::InitializeButtonsAction()
{
	buttonList[MenuButtonName_GameName]->OnExecute = [this]() {
		TransitionToMenu(MenuState::Credits, {}, creditUIList, MenuButtonName_StartButton);
		};

	buttonList[MenuButtonName_StartButton]->OnExecute = [this]() {
		TransitionToMenu(MenuState::StartConfirm, {}, yesNoList_Start, MenuButtonName_AreYouSureStart_No);
		};

	buttonList[MenuButtonName_TutorialButton]->OnExecute = [this]() {
		InfoPage = 0;
		TransitionToMenu(MenuState::Tutorial, {}, tutorialInfoList, MenuButtonName_TutorialButton);
		};

	buttonList[MenuButtonName_OptionButton]->OnExecute = [this]() {
		TransitionToMenu(MenuState::Options, {}, OptionList, MenuButtonName_DisplayType_Text);
		};

	buttonList[MenuButtonName_ExitButton]->OnExecute = [this]() {
		TransitionToMenu(MenuState::ExitConfirm, {}, yesNoList_Exit, MenuButtonName_AreYouSureExit_No);
		};

	buttonList[MenuButtonName_AreYouSureStart_Yes]->OnExecute = [this]() {
		gameEngine->GetStateController()->gameStateNext = GameState::GS_LEVELSELECTABILITY;
		};

	buttonList[MenuButtonName_AreYouSureStart_No]->OnExecute = [this]() {
		BackToMainMenu(yesNoList_Start, MenuButtonName_StartButton);
		};

	buttonList[MenuButtonName_AreYouSureExit_Yes]->OnExecute = [this]() {
		gameEngine->GetStateController()->gameStateNext = GameState::GS_QUIT;
		};

	buttonList[MenuButtonName_AreYouSureExit_No]->OnExecute = [this]() {
		BackToMainMenu(yesNoList_Exit, MenuButtonName_ExitButton);
		};

	// Options
	// Text Links -> Sub Controls
	buttonList[MenuButtonName_DisplayType_Text]->OnExecute = [this]() { SwitchActiveButton(MenuButtonName_DisplayType); };
	buttonList[MenuButtonName_MasterVolume_Text]->OnExecute = [this]() { SwitchActiveButton(MenuButtonName_MasterVolume_Knob); };
	buttonList[MenuButtonName_SFXVolume_Text]->OnExecute = [this]() { SwitchActiveButton(MenuButtonName_SFXVolume_Knob); };
	buttonList[MenuButtonName_BGMVolume_Text]->OnExecute = [this]() { SwitchActiveButton(MenuButtonName_BGMVolume_Knob); };

	// Knobs -> Sliders
	buttonList[MenuButtonName_MasterVolume_Knob]->OnExecute = [this]() { SwitchActiveButton(MenuButtonName_MasterVolume_Track, false); };
	buttonList[MenuButtonName_SFXVolume_Knob]->OnExecute = [this]() { SwitchActiveButton(MenuButtonName_SFXVolume_Track, false); };
	buttonList[MenuButtonName_BGMVolume_Knob]->OnExecute = [this]() { SwitchActiveButton(MenuButtonName_BGMVolume_Track, false); };

	// Checkboxes / Mute Toggles
	auto handleBoxToggle = [this]() {
		auto it = volumeBoxIndexMap.find(currentButton->name);
		if (it != volumeBoxIndexMap.end()) {
			isToggleVolume[it->second] = !isToggleVolume[it->second];
		}
		};
	buttonList[MenuButtonName_MasterVolume_Box]->OnExecute = handleBoxToggle;
	buttonList[MenuButtonName_SFXVolume_Box]->OnExecute = handleBoxToggle;
	buttonList[MenuButtonName_BGMVolume_Box]->OnExecute = handleBoxToggle;

	// Dropdown Toggles
	buttonList[MenuButtonName_DisplayType]->OnExecute = [this]() {
		currentButton = buttonList[MenuButtonName_DisplayDropdown];
		currentButton->playerHere = true;
		buttonList[MenuButtonName_DisplayDropdown]->ButtonUI->SetIsRender(true);
		};

	// Hardware Window Resolution Execution
	buttonList[MenuButtonName_DisplayDropdown]->OnExecute = [this]() {
		int currentShift = buttonList[MenuButtonName_DisplayDropdown]->ButtonUI->GetSpriteRenderer()->GetColumn();

		if (isFullscreen && currentShift == 1) {
			SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), 0);
			windowWidth = SCREEN_WIDTH;
			windowHeight = SCREEN_HEIGHT;
			glViewport(0, 0, windowWidth, windowHeight);
			buttonList[MenuButtonName_DisplayType]->ButtonUI->ShiftSpriteTo(0, 2);
			isFullscreen = false;
		}
		else if (!isFullscreen && currentShift == 0) {
			SDL_SetWindowFullscreen(GameEngine::GetInstance()->GetSDLWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
			SDL_GetWindowSize(GameEngine::GetInstance()->GetSDLWindow(), &windowWidth, &windowHeight);
			glViewport(0, 0, windowWidth, windowHeight);
			buttonList[MenuButtonName_DisplayType]->ButtonUI->ShiftSpriteTo(0, 0);
			isFullscreen = true;
		}
		};
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
void LevelMainMenu::InitializeButtonHoverActions()
{
	// Assign hover function
	// Lambda function for main menu text hover
	auto BindNormalHoverFunction = [this](MenuButtonName_ enumName, int activeCol, int inactiveCol) {

		if (!buttonList[enumName])
		{ 
			KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() : No button in buttonList that matches the name!");
			return;
		}

		buttonList[enumName]->OnHover = [this, enumName, activeCol, inactiveCol]() {

			ButtonData* btn = buttonList[enumName];
			if (!btn)
			{
				KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() : No button data!");
				return;
			}

			if (!btn->ButtonUI)
			{
				KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() : button isn't initialize UI yet!");
				return;
			}

			btn->ButtonUI->ShiftSpriteTo(0, btn->playerHere ? activeCol : inactiveCol);
		};
	};

	BindNormalHoverFunction(MenuButtonName_GameName, 1, 0);
	BindNormalHoverFunction(MenuButtonName_StartButton, 1, 0);
	BindNormalHoverFunction(MenuButtonName_TutorialButton, 3, 2);
	BindNormalHoverFunction(MenuButtonName_OptionButton, 5, 4);
	BindNormalHoverFunction(MenuButtonName_ExitButton, 7, 6);

	BindNormalHoverFunction(MenuButtonName_AreYouSureStart_Yes, 1, 0);
	BindNormalHoverFunction(MenuButtonName_AreYouSureStart_No, 3, 2);
	BindNormalHoverFunction(MenuButtonName_AreYouSureExit_Yes, 1, 0);
	BindNormalHoverFunction(MenuButtonName_AreYouSureExit_No, 3, 2);

	BindNormalHoverFunction(MenuButtonName_DisplayType_Text, 1, 0);
	BindNormalHoverFunction(MenuButtonName_MasterVolume_Text, 3, 2);
	BindNormalHoverFunction(MenuButtonName_SFXVolume_Text, 5, 4);
	BindNormalHoverFunction(MenuButtonName_BGMVolume_Text, 7, 6);

	BindNormalHoverFunction(MenuButtonName_MasterVolume_Track, 1, 0);
	BindNormalHoverFunction(MenuButtonName_SFXVolume_Track, 1, 0);
	BindNormalHoverFunction(MenuButtonName_BGMVolume_Track, 1, 0);

	BindNormalHoverFunction(MenuButtonName_MasterVolume_Knob, 1, 0);
	BindNormalHoverFunction(MenuButtonName_SFXVolume_Knob, 1, 0);
	BindNormalHoverFunction(MenuButtonName_BGMVolume_Knob, 1, 0);

	// Lambda function for main menu text hover
	if (!buttonList[MenuButtonName_DisplayType])
	{
		KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() : No MenuButtonName_DisplayType button data!");
	}
	else
	{
		buttonList[MenuButtonName_DisplayType]->OnHover = [this]() {
			ButtonData* btn = buttonList[MenuButtonName_DisplayType];
			if (!btn)
			{
				KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() : No button data!");
				return;
			}

			if (!btn->ButtonUI)
			{
				KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() : button isn't initialize UI yet!");
				return;
			}

			int baseOffset = !this->isFullscreen ? 2 : 0;
			int playerOffset = btn->playerHere ? 0 : 1;
			btn->ButtonUI->ShiftSpriteTo(0, baseOffset + playerOffset);
			};
	}

	// Lambda function for volume mute checkbox
	auto BindVolumeBoxHoverFunction = [this](MenuButtonName_ enumName, int mapIndex) {

		if (!buttonList[enumName])
		{
			KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() at BindVolumeBoxHoverFunction() : No button in buttonList that matches the name!");
			return;
		}

		buttonList[enumName]->OnHover = [this, enumName, mapIndex]() {

			ButtonData* btn = buttonList[enumName];
			if (!btn)
			{
				KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() at BindVolumeBoxHoverFunction() : No button data!");
				return;
			}

			if (!btn->ButtonUI)
			{
				KK_CORE_ERROR("LevelMainMenu::InitializeButtonHoverActions() at BindVolumeBoxHoverFunction() : button isn't initialize UI yet!");
				return;
			}

			bool isToggled = this->isToggleVolume[mapIndex];
			int yIndex = btn->playerHere ? (isToggled ? 0 : 2) : (isToggled ? 1 : 3);
			btn->ButtonUI->ShiftSpriteTo(0, yIndex);
			};
		};

	BindVolumeBoxHoverFunction(MenuButtonName_MasterVolume_Box, 0);
	BindVolumeBoxHoverFunction(MenuButtonName_SFXVolume_Box, 1);
	BindVolumeBoxHoverFunction(MenuButtonName_BGMVolume_Box, 2);
}
void LevelMainMenu::UpdateUi()
{
	for (auto& pair : buttonList)
	{
		ButtonData* buttonData = pair.second;

		if (buttonData == nullptr)
		{
			KK_ERROR("LevelMainMenu::UpdateUi() : buttonData == nullptr!");
			continue;
		}

		if (buttonData->OnHover)
		{
			buttonData->OnHover();
		}
	}
}

void LevelMainMenu::TransitionToMenu(MenuState newState, const std::vector<UiObject*>& hideList, const std::vector<UiObject*>& showList, MenuButtonName_ defaultButtonKey)
{
	// Check if current button isn't null
	if (currentButton == nullptr)
	{
		KK_ERROR("LevelMainMenu::TransitionToMenu() : currentButton == nullptr!");
	}
	for (UiObject* ui : hideList) ui->SetIsRender(false);
	for (UiObject* ui : showList) ui->SetIsRender(true);

	currentButton->playerHere = false;
	currentMenuState = newState;
	currentButton = buttonList[defaultButtonKey];

	// Check if new current button isn't null
	if (currentButton == nullptr)
	{
		KK_ERROR("LevelMainMenu::TransitionToMenu() : new currentButton == nullptr!");
	}

	currentButton->playerHere = true;
}

void LevelMainMenu::BackToMainMenu(const std::vector<UiObject*>& activeUiList, MenuButtonName_ fallbackButtonName) {
	TransitionToMenu(MenuState::Main, activeUiList, {}, fallbackButtonName);
}

void LevelMainMenu::HandleMainMenuLogic() {

	if (isPressedCross)
	{
		if (currentButton == nullptr)
		{
			KK_ERROR("LevelMainMenu::HandleMainMenuLogic() : currentButton == nullptr!");
			return;
		}

		if (!currentButton->OnExecute)
		{
			KK_ERROR("LevelMainMenu::HandleMainMenuLogic() : No OnExecute function in current button!");
		}
		else 
		{
			currentButton->OnExecute();
		}
	}
}

void LevelMainMenu::HandleCreditsLogic()
{
	if (isPressedCross || isPressedCircle) {
		BackToMainMenu(creditUIList, MenuButtonName_StartButton);
	}
}

void LevelMainMenu::HandleStartConfirmLogic()
{
	if (isPressedCross) {

		if (currentButton == nullptr)
		{
			KK_ERROR("LevelMainMenu::HandleStartConfirmLogic() : currentButton == nullptr!");
			return;
		}

		if (!currentButton->OnExecute)
		{
			KK_ERROR("LevelMainMenu::HandleStartConfirmLogic() : No OnExecute function in current button!");
		}
		else
		{
			currentButton->OnExecute();
		}
	}
	else if (isPressedCircle) {
		BackToMainMenu(yesNoList_Start, MenuButtonName_StartButton);
	}
}

void LevelMainMenu::HandleTutorialLogic() {

	if (isPressedCross)
	{
		tutorialInfoUI->GetSpriteRenderer()->ShiftColumn();
		InfoPage++;

		if (InfoPage >= InfoPageLimit) {
			TransitionToMenu(MenuState::Main, tutorialInfoList, {}, MenuButtonName_TutorialButton);
		}
	}
}

void LevelMainMenu::HandleOptionsCancel() 
{
	MenuButtonName_ name = currentButton->name;

	// If backing out of root options, hide options menu entirely and go back to main menu
	if (name == MenuButtonName_DisplayType_Text || 
		name == MenuButtonName_MasterVolume_Text ||
		name == MenuButtonName_SFXVolume_Text || 
		name == MenuButtonName_BGMVolume_Text) 
	{
		TransitionToMenu(MenuState::Main, OptionList, {}, MenuButtonName_OptionButton);
		return;
	}

	// Map sub-buttons directly back to their parent elements
	MenuButtonName_ targetDestination = MenuButtonName_None;

	if (name == MenuButtonName_DisplayType)
		targetDestination = MenuButtonName_DisplayType_Text;
	
	else if (
		name == MenuButtonName_MasterVolume_Knob || 
		name == MenuButtonName_MasterVolume_Box)
		targetDestination = MenuButtonName_MasterVolume_Text;

	else if (
		name == MenuButtonName_SFXVolume_Knob || 
		name == MenuButtonName_SFXVolume_Box)
		targetDestination = MenuButtonName_SFXVolume_Text;

	else if (
		name == MenuButtonName_BGMVolume_Knob || 
		name == MenuButtonName_BGMVolume_Box)
		targetDestination = MenuButtonName_BGMVolume_Text;

	else if (name == MenuButtonName_MasterVolume_Track)
		targetDestination = MenuButtonName_MasterVolume_Knob;

	else if (name == MenuButtonName_SFXVolume_Track)
		targetDestination = MenuButtonName_SFXVolume_Knob;

	else if (name == MenuButtonName_BGMVolume_Track)
		targetDestination = MenuButtonName_BGMVolume_Knob;

	else if (name == MenuButtonName_DisplayDropdown) {
		targetDestination = MenuButtonName_DisplayType;
		buttonList[MenuButtonName_DisplayDropdown]->ButtonUI->SetIsRender(false);
	}

	if (targetDestination != MenuButtonName_None) {
		currentButton->playerHere = false;
		currentButton = buttonList[targetDestination];
		currentButton->playerHere = true;
	}
}

void LevelMainMenu::UpdateVolumeSlider(float& volumeValue, MenuButtonName_ knobKey, int rowIndex) {
	std::cout << masterVolume << std::endl; // Match your original debug trace

	if (holdright)      volumeValue++;
	else if (holdleft)  volumeValue--;

	volumeValue = std::min(100.0f, std::max(volumeValue, 0.0f));

	float newX = (volumeValue * 4.0f) - (57.5f / 0.25f);
	float newY = buttonList[knobKey]->pos.y - (rowIndex * buttonList[knobKey]->offset.y);

	buttonList[knobKey]->ButtonUI->SetPosition(glm::vec3(newX, newY, 0.0f));
}

void LevelMainMenu::HandleVolumeSliderAdjustment() 
{
	if (currentButton == nullptr) return;

	if (currentButton == buttonList[MenuButtonName_MasterVolume_Track]) {
		UpdateVolumeSlider(masterVolume, MenuButtonName_MasterVolume_Knob, 0);
	}
	else if (currentButton == buttonList[MenuButtonName_SFXVolume_Track]) {
		UpdateVolumeSlider(SFXVolume, MenuButtonName_SFXVolume_Knob, 1);
	}
	else if (currentButton == buttonList[MenuButtonName_BGMVolume_Track]) {
		UpdateVolumeSlider(BGMVolume, MenuButtonName_BGMVolume_Knob, 2);
	}
}

void LevelMainMenu::SwitchActiveButton(MenuButtonName_ targetKey, bool disableOldPlayerHere) {
	if (disableOldPlayerHere) currentButton->playerHere = false;
	currentButton = buttonList[targetKey];
	currentButton->playerHere = true;
}

void LevelMainMenu::HandleOptionsLogic() 
{
	if (isPressedCross) 
	{
		if (currentButton == nullptr)
		{
			KK_ERROR("LevelMainMenu::HandleOptionsLogic() : currentButton == nullptr!");
			return;
		}

		if (!currentButton->OnExecute)
		{
			KK_ERROR("LevelMainMenu::HandleOptionsLogic() : No OnExecute function in current button!");
		}
		else
		{
			currentButton->OnExecute();
		}
	}
	else if (isPressedCircle) 
	{
		HandleOptionsCancel();
	}

	// Handle Up/Down Navigation while in display setting drop down
	if (currentButton->name == MenuButtonName_DisplayDropdown && (up || down) && !playerMove) {
		currentButton->ButtonUI->GetSpriteRenderer()->ShiftColumn();
	}

	// Handle slider hold logic
	HandleVolumeSliderAdjustment();
}

void LevelMainMenu::HandleExitConfirmLogic() {

	if (isPressedCross) {
		if (currentButton == nullptr)
		{
			KK_ERROR("LevelMainMenu::HandleExitConfirmLogic() : currentButton == nullptr!");
			return;
		}

		if (!currentButton->OnExecute)
		{
			KK_ERROR("LevelMainMenu::HandleExitConfirmLogic() : No OnExecute function in current button!");
		}
		else
		{
			currentButton->OnExecute();
		}
	}
	else if (isPressedCircle) {
		BackToMainMenu(yesNoList_Exit, MenuButtonName_ExitButton);
	}
}

void LevelMainMenu::LevelInit() 
{
	soundManager = KrillSoundManager::SoundManager::GetInstance();
	renderer		= GameEngine::GetInstance()->GetRenderer();
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

	InitializeMainMenuUI();
	
	// Fade black background for pop up UI
	UiObject* fadeBlack = InitUI(spriteList["FadeBlack"], {0, 0}, { camera.GetCameraWidth() , camera.GetCameraHeight() }, {0, 0});
	fadeBlack->SetIsRender(false);
	OptionList.push_back(fadeBlack);
	yesNoList_Start.push_back(fadeBlack);
	yesNoList_Exit.push_back(fadeBlack);
	creditUIList.push_back(fadeBlack);
	tutorialInfoList.push_back(fadeBlack);
	objectsList.push_back(fadeBlack);

	InitializeConfirmUI();
	InitializeCreditUI();
	InitializeTutorialUI();
	InitializeOptionUI();
	
	SetupButtonLinks();
	InitializeButtonsAction();

	InitializeImGui();

	InitializeButtonHoverActions();

	KK_TRACE("Level Main Menu Loaded");
}

void LevelMainMenu::DrawControllerButtons()
{
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
		
		ImGui::PopStyleColor();
		};



	// Calculate offsets for the diamond shape
	float center = buttonSize + spacing;

	// Y - Top (Yellow-ish)
	DrawButton("Triangle", center, 0, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	// X - Left (Blue-ish)
	DrawButton("Square", 0, center, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	// B - Right (Red-ish)
	DrawButton("Circle", center * 2, center, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	// A - Bottom (Green-ish)
	DrawButton("Cross", center, center * 2, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	ImGui::EndGroup();
}

void LevelMainMenu::DrawVirtualJoystick(const char* label, ImVec2& stickValue, float radius)
{
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

void LevelMainMenu::ShowImGuiConfig(bool isShowing)
{
	if (!isShowing)
		return;

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	static MenuButtonName_ selectedKey = MenuButtonName_None;

	if (ImGui::Button("Go levelSelectAbility")) {
		gameEngine->GetStateController()->gameStateNext = GameState::GS_LEVELSELECTABILITY;
	}

	ImGui::SameLine();
	if (ImGui::Button("Save Entire Layout")) {
		SaveAllButtonConfigs("../Resource/SceneData/MenuLayoutConfig.json");
	}

	ImGui::SameLine();
	if (ImGui::Button("Load Entire Layout")) {
		LoadAllButtonConfigs("../Resource/SceneData/MenuLayoutConfig.json");
	}


	DrawVirtualJoystick("Joystick", joystickVal, 50);
	DrawControllerButtons();

	auto DrawButtonEditor = [](const char* label, ButtonData* data) {
		if (!data) return;
		ImGui::PushID(label);

		bool changed = false;
		changed |= ImGui::InputFloat("PosX", &data->pos.x, 1.0f, 1.0f, "%.2f");
		changed |= ImGui::InputFloat("PosY", &data->pos.y, 1.0f, 1.0f, "%.2f");
		changed |= ImGui::InputFloat("Width", &data->size.x, 1.0f, 1.0f, "%.2f");
		changed |= ImGui::InputFloat("Height", &data->size.y, 1.0f, 1.0f, "%.2f");
		changed |= ImGui::InputFloat("OffsetX", &data->offset.x, 1.0f, 1.0f, "%.2f");
		changed |= ImGui::InputFloat("OffsetY", &data->offset.y, 1.0f, 1.0f, "%.2f");
		ImGui::InputInt("Column ID", &data->column);

		if (changed && data->ButtonUI) {
			data->ButtonUI->SetPosition(glm::vec3(data->pos.x, data->pos.y, 0));
			data->ButtonUI->SetSize(data->size.x, -data->size.y);
		}

		ImGui::PopID();
	};

	ImGui::BeginChild("left_pane", ImVec2(300, 0), true);
	ImGui::TextColored(ImVec4(0.3f, 0.6f, 0.9f, 1.0f), "UI Object List");
	ImGui::Separator();

	for (auto& pair : buttonList) {
		MenuButtonName_ enumKey = pair.first;
		ButtonData* buttonData = pair.second;

		if (!buttonData) continue;

		// Determine a display title string
		std::string displayName = buttonData->stringName.empty() ?
			"ID: " + std::to_string(enumKey) : buttonData->stringName;

		// Fallback safety selection initializing if nothing is selected yet
		if (selectedKey == MenuButtonName_None) {
			selectedKey = enumKey;
		}

		// Render an interactive list item
		if (ImGui::Selectable(displayName.c_str(), selectedKey == enumKey)) {
			selectedKey = enumKey;
		}
	}
	ImGui::EndChild();

	ImGui::SameLine(); // Places panel 2 immediately to the right of panel 1

	// Pane 2: Right-side properties inspector context matching our selection
	ImGui::BeginChild("right_pane", ImVec2(0, 0), true);

	// Safety verification check that the selected entry exists
	if (buttonList.find(selectedKey) != buttonList.end() && buttonList[selectedKey] != nullptr) {
		ButtonData* currentData = buttonList[selectedKey];

		std::string inspectorTitle = currentData->stringName.empty() ?
			"Object Inspector" : currentData->stringName;

		ImGui::Text("Editing Entity: %s", inspectorTitle.c_str());
		ImGui::Text("System Enum Identifier: %d", selectedKey);
		ImGui::Checkbox("Active Hover State Focus", &currentData->playerHere);
		ImGui::Separator();

		// Pass selection pointer over into our drawing logic blocks
		DrawButtonEditor(inspectorTitle.c_str(), currentData);
	}
	else {
		ImGui::Text("Please choose a UI configuration target from the sidebar.");
	}
	ImGui::EndChild();
	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void LevelMainMenu::UpdateInput()
{
	// change this to test the joystick
	bool isUsingJoystick = false;

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

void LevelMainMenu::LevelUpdate() 
{
	UpdateAudio();
	UpdateUi();
	UpdateInput();
}

void LevelMainMenu::LevelDraw() 
{
	gameEngine->Render(objectsList);
	
	ShowImGuiConfig(true);

	SDL_GL_SwapWindow(gameEngine->GetSDLWindow());

	// cout << "Draw Level" << endl;
}

void LevelMainMenu::LevelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
}

void LevelMainMenu::LevelUnload() 
{
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

void LevelMainMenu::SaveAllButtonConfigs(const std::string& filename)
{
	nlohmann::json rootJson;

	for (const auto& pair : buttonList)
	{
		MenuButtonName_ enumName = pair.first;
		ButtonData* buttonData = pair.second;

		if (!buttonData) continue;

		std::string key = buttonData->stringName.empty() ? std::to_string(enumName) : buttonData->stringName;

		nlohmann::json buttonJson;

		buttonJson["posX"] = buttonData->pos.x;
		buttonJson["posY"] = buttonData->pos.y;
		buttonJson["width"] = buttonData->size.x;
		buttonJson["height"] = buttonData->size.y;
		buttonJson["offsetX"] = buttonData->offset.x;
		buttonJson["offsetY"] = buttonData->offset.y;
		buttonJson["column"] = buttonData->column;

		rootJson[key] = buttonJson;
	}

	std::ofstream file(filename);
	if (!file.is_open()) return;

	file << rootJson.dump(4);
	file.close();
}

void LevelMainMenu::LoadAllButtonConfigs(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) return;

	nlohmann::json rootJson = nlohmann::json::parse(file);
	file.close();

	for (auto& pair : buttonList)
	{
		MenuButtonName_ enumName = pair.first;
		ButtonData* buttonData = pair.second;

		if (!buttonData) continue;

		std::string key = buttonData->stringName.empty() ? std::to_string(enumName) : buttonData->stringName;

		if (rootJson.contains(key))
		{
			const auto& buttonJson = rootJson[key];

			if (buttonJson.contains("posX"))    buttonData->pos.x = buttonJson["posX"];
			if (buttonJson.contains("posY"))    buttonData->pos.y = buttonJson["posY"];
			if (buttonJson.contains("width"))   buttonData->size.x = buttonJson["width"];
			if (buttonJson.contains("height"))   buttonData->size.y = buttonJson["height"];
			if (buttonJson.contains("offsetX")) buttonData->offset.x = buttonJson["offsetX"];
			if (buttonJson.contains("offsetY")) buttonData->offset.y = buttonJson["offsetY"];
			if (buttonJson.contains("column"))  buttonData->column = buttonJson["column"];

			if (buttonData->ButtonUI)
			{
				buttonData->ButtonUI->SetPosition(glm::vec3(buttonData->pos.x, buttonData->pos.y, 0));
				buttonData->ButtonUI->SetSize(buttonData->size.x, -buttonData->size.y);
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

	if (data.contains("height") && !data["height"].is_null()) {
		buttonData->size.y = data["height"];
	}

	if (data.contains("offsetX") && !data["offsetX"].is_null()) {
		buttonData->offset.x = data["offsetX"];
	}

	if (data.contains("offsetY") && !data["offsetY"].is_null()) {
		buttonData->offset.y = data["offsetY"];
	}
}

