#pragma once
#include "Level.h"
#include "LevelUtilities.h"
#include "nlohmann/json.hpp"
#include <fstream>


//using json = nlohmann::json;
class LevelMainMenu : public Level
{
private:

	enum class MenuState 
	{ 
		Main, 
		Credits, 
		StartConfirm, 
		Tutorial, 
		Options, 
		ExitConfirm
	};

	

	MenuState currentMenuState = MenuState::Main;

	std::vector<DrawableObject*> objectsList;
	std::vector<UiObject*> textList;
	std::vector<UiObject*> tutorialInfoList;
	std::vector<UiObject*> yesNoList;
	std::vector<UiObject*> yesNoList_Start;
	std::vector<UiObject*> yesNoList_Exit;
	std::vector<UiObject*> textOptionList;
	std::vector<UiObject*> displayList;
	std::vector<UiObject*> volumeTrackList;
	std::vector<UiObject*> volumeKnobList;
	std::vector<UiObject*> volumeBoxList;
	std::map<std::string, SpritesheetInfo> spriteList;
	
	int playerNumber = 4; // Change later
	bool playerMove = false;
	int playerWhere = 1;

	bool isCredit = false;

	bool isTutorial = false;
	int InfoPage = 0;

	bool isStart = false;
	bool isExit = false;

	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	bool isPressedCross = false;
	bool isPressedCircle = false;
	bool isPressedSquare = false;
	bool isPressedTriangle = false;

	bool isOption = false;
	bool isSelectDisplay = false;
	bool isSelectVolume = false;
	bool isMasterVolume = false;
	bool isSFXVolume = false;
	bool isBGMVolume = false;
	bool isToggleVolume[3] = { true, true, true };
	bool isSlider = false;
	float masterVolume = 100;
	float SFXVolume = 20;
	float BGMVolume = 20;

	int configNum = 0;
	int windowWidth = SCREEN_WIDTH;
	int windowHeight = SCREEN_HEIGHT;

	OrthographicValue targetSceneProjection; // use for lerping between the current projection and this (target projection).
	Camera camera;
	Timer* timer;
	KrillSoundManager::SoundManager* soundManager;
	GLRenderer* renderer;
	GameEngine* gameEngine;

	int dt = 0;
	float time1s = 0;
	float time05s = 0;
	float previousWidth = 0, previousHeight = 0;
	ImVec2 joystickVal;

	struct ButtonData
	{
		std::string name;
		int number;
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
	};

	std::map<std::string, ButtonData*> buttonList;
	std::vector<ButtonData*> Buttons;

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

	void UpdateInput();
	void NewUpdateInput();
	void UpdateUi();
	void UpdateAudio();

	void ShowImGuiConfig(bool isShowing);
	LevelMainMenu::ButtonData* InitButtonData(std::string name, glm::vec2 pos, glm::vec2 size, glm::vec2 offset, int column, std::string configPath);
	UiObject* InitUI(std::string name, SpritesheetInfo spriteInfo, glm::vec2 pos, glm::vec2 size, glm::vec2 spriteShiftPos);
	UiObject* InitButtonUI(std::string name, SpritesheetInfo spriteInfo, ButtonData* buttonData, glm::vec2 spriteShiftPos);
	void saveConfig(std::string& filename, ButtonData* con);
	void loadConfig(std::string filename);
	void loadConfigButtonData(std::string filename, ButtonData* buttonData);
	void DrawVirtualJoystick(const char* label, ImVec2& stickValue, float radius);
	void DrawControllerButtons();

	void TransitionTo(MenuState newState);
	void HandleMainMenuLogic();
	void HandleCreditsLogic();
	void HandleStartConfirmLogic();
	void HandleTutorialLogic();
	void HandleOptionsLogic();
	void HandleExitConfirmLogic();
};
