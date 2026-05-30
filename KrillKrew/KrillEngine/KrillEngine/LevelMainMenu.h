#pragma once
#include "Level.h"
#include "LevelUtilities.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

class LevelMainMenu : public Level
{
    friend struct MenuTestBridge;

public:
	enum class MenuState
	{
		Main,
		Credits,
		StartConfirm,
		Tutorial,
		Options,
		ExitConfirm
	};

	struct ButtonData
	{
		MenuButtonName_ name;
		std::string stringName;
		glm::vec2 pos;
		glm::vec2 size;
		glm::vec2 offset;
		int column;

		UiObject* ButtonUI;

		ButtonData* UpperButton = nullptr;
		ButtonData* LowerButton = nullptr;
		ButtonData* LeftButton = nullptr;
		ButtonData* RightButton = nullptr;

		bool playerHere = false;

		std::function<void()> OnExecute = nullptr;
		std::vector<std::function<void()>> OnHoverListeners;

		// 2. Helper method to easily subscribe new functions
		void AddOnHover(std::function<void()> callback)
		{
			if (callback)
			{
				OnHoverListeners.push_back(callback);
			}
		}

		// 3. Helper method to fire all registered functions
		void InvokeHover()
		{
			for (const auto& callback : OnHoverListeners)
			{
				if (callback)
				{
					callback(); // Execute each registered function in order
				}
			}
		}
	};

private:
    const std::unordered_map<MenuButtonName_, int> volumeBoxIndexMap = {
        {MenuButtonName_MasterVolume_Box, 0}, {MenuButtonName_SFXVolume_Box, 1}, {MenuButtonName_BGMVolume_Box, 2}};

    const std::unordered_map<MenuButtonName_, int> volumeTextIndexMap = {{MenuButtonName_DisplayType_Text, 0},
                                                                         {MenuButtonName_MasterVolume_Text, 2},
                                                                         {MenuButtonName_SFXVolume_Text, 4},
                                                                         {MenuButtonName_BGMVolume_Text, 6}};

    MenuState currentMenuState = MenuState::Main;

    std::vector<DrawableObject*> objectsList;
    std::vector<UiObject*> textList;
    std::vector<UiObject*> tutorialInfoList;
    UiObject* tutorialInfoUI;
    std::vector<UiObject*> yesNoList;
    std::vector<UiObject*> yesNoList_Start;
    std::vector<UiObject*> yesNoList_Exit;
    std::vector<UiObject*> creditUIList;
    std::vector<UiObject*> OptionList;
    std::vector<UiObject*> textOptionList;
    std::vector<UiObject*> displayList;
    std::vector<UiObject*> volumeTrackList;
    std::vector<UiObject*> volumeKnobList;
    std::vector<UiObject*> volumeBoxList;
    std::map<std::string, SpritesheetInfo> spriteList;

    int playerNumber = 4; // Change later
    bool playerMove = false;

    bool isCredit = false;
    bool isFullscreen = false;

    bool isTutorial = false;
    int InfoPage = 0;
    int InfoPageLimit = 3;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool holdup = false;
    bool holddown = false;
    bool holdright = false;
    bool holdleft = false;

    bool isPressedCross = false;
    bool isPressedCircle = false;
    bool isPressedSquare = false;
    bool isPressedTriangle = false;

    bool isToggleVolume[3] = {true, true, true}; // Master, SFX, BGM
    float masterVolume = 0;
    float SFXVolume = 0;
    float BGMVolume = 0;

    int configNum = 0;
    int windowWidth = SCREEN_WIDTH;
    int windowHeight = SCREEN_HEIGHT;

    OrthographicValue targetSceneProjection;
    Camera camera;
    Timer* timer;

    ImVec2 joystickVal;

    std::map<MenuButtonName_, ButtonData*> buttonList;
    std::vector<ButtonData*> Buttons;

    KrillSoundManager::SoundManager* soundManager;
    GLRenderer* renderer;
    GameEngine* gameEngine;

    ButtonData* currentButton;

public:
    virtual void LevelLoad();
    virtual void LevelInit();
    virtual void LevelUpdate();
    virtual void LevelDraw();
    virtual void LevelFree();
    virtual void LevelUnload();
    virtual void Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
    virtual void HandleKey(char key);
    virtual void HandleMouse(int type, int x, int y);

    void InitializeMainMenuUI();
    void InitializeConfirmUI();
    void InitializeCreditUI();
    void InitializeTutorialUI();
    void InitializeOptionUI();
    void SetupButtonLinks();

    void InitializeButtonHoverActions();

    void InitializeImGui();

    void BackToMainMenu(const std::vector<UiObject*>& activeUiList, MenuButtonName_ fallbackButtonName);
    void TransitionToMenu(MenuState newState,
                          const std::vector<UiObject*>& hideList,
                          const std::vector<UiObject*>& showList,
                          MenuButtonName_ defaultButtonKey);
    void InitializeButtonsAction();
    void SwitchActiveButton(MenuButtonName_ targetKey, bool disableOldPlayerHere = true);

    // Options
    void HandleOptionsCancel();
    void UpdateVolumeSlider(float& volumeValue, MenuButtonName_ knobKey, int rowIndex);
    void HandleVolumeSliderAdjustment();

    void UpdateInput();
    void UpdateUi();
    void UpdateAudio();

    void ShowImGuiConfig(bool isShowing);
    LevelMainMenu::ButtonData* InitButtonData(
        MenuButtonName_ name, std::string stringName, glm::vec2 pos, glm::vec2 size, glm::vec2 offset, int column, std::string configPath);
    UiObject* InitUI(SpritesheetInfo spriteInfo, glm::vec2 pos, glm::vec2 size, glm::vec2 spriteShiftPos);
    UiObject* InitButtonUI(SpritesheetInfo spriteInfo, ButtonData* buttonData, glm::vec2 spriteShiftPos);
    void loadConfigButtonData(std::string filename, ButtonData* buttonData);
    void DrawVirtualJoystick(const char* label, ImVec2& stickValue, float radius);
    void DrawControllerButtons();

    void SaveAllButtonConfigs(const std::string& filename);
    void LoadAllButtonConfigs(const std::string& filename);

    void HandleMainMenuLogic();
    void HandleCreditsLogic();
    void HandleStartConfirmLogic();
    void HandleTutorialLogic();
    void HandleOptionsLogic();
    void HandleExitConfirmLogic();
};
