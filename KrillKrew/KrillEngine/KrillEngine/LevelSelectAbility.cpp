#include "LevelSelectAbility.h"

void LevelSelectAbility::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	spriteList["BG"] = SpritesheetInfo("BG", "../Resource/Texture/CharacterSelection/UI_CS_Background.png", 1920, 1080, 1920, 1080);

	spriteList["Player_Window1"] = SpritesheetInfo("Player_Window1", "../Resource/Texture/CharacterSelection/UI_CS_PlayerWindow_1.png", 284, 373, 1988, 373);
	spriteList["Player_Window2"] = SpritesheetInfo("Player_Window2", "../Resource/Texture/CharacterSelection/UI_CS_PlayerWindow_2.png", 284, 373, 1988, 373);
	spriteList["Player_Window3"] = SpritesheetInfo("Player_Window3", "../Resource/Texture/CharacterSelection/UI_CS_PlayerWindow_3.png", 284, 373, 1988, 373);
	spriteList["Player_Window4"] = SpritesheetInfo("Player_Window4", "../Resource/Texture/CharacterSelection/UI_CS_PlayerWindow_4.png", 284, 373, 1988, 373);

	spriteList["Player_Icon"] = SpritesheetInfo("Player_Icon", "../Resource/Texture/CharacterSelection/UI_CS_PlayerProfile.png", 175, 152, 700, 152);
	spriteList["Player_Icon_Small"] = SpritesheetInfo("Player_Icon_Small", "../Resource/Texture/CharacterSelection/UI_CS_PlayerProfile_Small.png", 127, 120, 508, 120);
	
	spriteList["Ability_Icon"] = SpritesheetInfo("Ability_Icon", "../Resource/Texture/CharacterSelection/UI_CS_Abilityicon_Big.png", 160, 160, 1280, 160);
	spriteList["Ability_Icon_Small"] = SpritesheetInfo("Ability_Icon_Small", "../Resource/Texture/CharacterSelection/UI_CS_Abilityicon_Small.png", 72, 72, 648, 72);

	spriteList["Player_Remain"] = SpritesheetInfo("Player_Remain", "../Resource/Texture/CharacterSelection/UI_CS_PlayerRemain.png", 292, 133, 2044, 133);
	spriteList["Player_Hover"] = SpritesheetInfo("Player_Hover", "../Resource/Texture/CharacterSelection/PlayerAbilityHover.png", 450, 283, 1800, 283);
}

void LevelSelectAbility::LevelInit()
{
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	SDL_GetWindowSize(GameEngine::GetInstance()->GetSDLWindow(), &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	//BG
	UiObject* BG = new UiObject();
	BG->SetSpriteInfo(spriteList.find("BG")->second);
	BG->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
	objectsList.push_back(BG);

	//Player window
	axisX = 1;
	axisY = 2;

	config* PlayerWindowConfig = new config();
	PlayerWindowConfig->number = 0;
	PlayerWindowConfig->posX = 0;
	PlayerWindowConfig->posY = 0;
	PlayerWindowConfig->offSetX = 284;
	PlayerWindowConfig->offSetY = 373;
	PlayerWindowConfig->width = 284;
	PlayerWindowConfig->height = 373;
	configs.push_back(PlayerWindowConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility0.json");

	for (int i = 0; i < 4; i++) {
		std::string spriteName = "Player_Window" + std::to_string(i + 1);
		UiObject* PlayerWindow = new UiObject();
		PlayerWindow->SetSpriteInfo(spriteList.find(spriteName)->second);
		PlayerWindow->GetSpriteRenderer()->ShiftTo(PlayerWindow->GetSpriteRenderer()->GetRow(), 0);
		PlayerWindow->SetSize(configs.at(0)->width, -configs.at(0)->height);
		if (i == 2) {
			axisX = 1;
			axisY = 1;
		}
		PlayerWindow->SetPosition(glm::vec3(configs.at(0)->posX + (configs.at(0)->offSetX * axisX), configs.at(0)->posY + (configs.at(0)->offSetY * axisY), 0));
		axisX++;
		PlayerWindow->setNumOwner(i);
		objectsList.push_back(PlayerWindow);
		playerWindowList.push_back(PlayerWindow);
	}

	//Player remain
	config* PlayerRemainConfig = new config();
	PlayerRemainConfig->number = 1;
	PlayerRemainConfig->posX = 0;
	PlayerRemainConfig->posY = 0;
	PlayerRemainConfig->offSetX = 0;
	PlayerRemainConfig->offSetY = 0;
	PlayerRemainConfig->width = 292;
	PlayerRemainConfig->height = 133;
	configs.push_back(PlayerRemainConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility1.json");

	UiObject* PlayerRemain = new UiObject();
	PlayerRemain->SetSpriteInfo(spriteList.find("Player_Remain")->second);
	PlayerRemain->GetSpriteRenderer()->ShiftTo(PlayerRemain->GetSpriteRenderer()->GetRow(), 3);
	PlayerRemain->SetSize(configs.at(1)->width, -configs.at(1)->height);
	PlayerRemain->SetPosition(glm::vec3(configs.at(1)->posX, configs.at(1)->posY, 0));
	PlayerRemain->setNumOwner(-1);
	objectsList.push_back(PlayerRemain);
	playerRemainList.push_back(PlayerRemain);

	//Ability icon
	//Top
	config* AbilityIconTopConfig = new config();
	AbilityIconTopConfig->number = 2;
	AbilityIconTopConfig->posX = 0;
	AbilityIconTopConfig->posY = 0;
	AbilityIconTopConfig->offSetX = 160;
	AbilityIconTopConfig->offSetY = 0;
	AbilityIconTopConfig->width = 160;
	AbilityIconTopConfig->height = 160;
	configs.push_back(AbilityIconTopConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility2.json");

	//Down
	config* AbilityIconDownConfig = new config();
	AbilityIconDownConfig->number = 3;
	AbilityIconDownConfig->posX = 0;
	AbilityIconDownConfig->posY = 0;
	AbilityIconDownConfig->offSetX = 160;
	AbilityIconDownConfig->offSetY = 0;
	AbilityIconDownConfig->width = 160;
	AbilityIconDownConfig->height = 160;
	configs.push_back(AbilityIconDownConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility3.json");

	for (int i = 0; i < 7; i++) {
		if (i < 3){
			UiObject* AbilityIconTop = new UiObject();
			AbilityIconTop->SetSpriteInfo(spriteList.find("Ability_Icon")->second);
			AbilityIconTop->SetSize(configs.at(2)->width, -configs.at(2)->height);
			AbilityIconTop->SetPosition(glm::vec3(configs.at(2)->posX + (configs.at(2)->offSetX * axisX), configs.at(2)->posY, 0));
			AbilityIconTop->GetSpriteRenderer()->ShiftTo(AbilityIconTop->GetSpriteRenderer()->GetRow(), i);
			AbilityIconTop->setNumOwner(-1);
			objectsList.push_back(AbilityIconTop);
			AbilityIconListTop.push_back(AbilityIconTop);
		}
		else {
			UiObject* AbilityIconDown = new UiObject();
			AbilityIconDown->SetSpriteInfo(spriteList.find("Ability_Icon")->second);
			AbilityIconDown->SetSize(configs.at(3)->width, -configs.at(3)->height);
			AbilityIconDown->SetPosition(glm::vec3(configs.at(3)->posX + (configs.at(0)->offSetX * axisX), configs.at(3)->posY, 0));
			AbilityIconDown->GetSpriteRenderer()->ShiftTo(AbilityIconDown->GetSpriteRenderer()->GetRow(), i);
			AbilityIconDown->setNumOwner(-1);
			objectsList.push_back(AbilityIconDown);
			AbilityIconListDown.push_back(AbilityIconDown);
		}
	}
	

	//Player hover
	config* playerHoverConfig = new config();
	playerHoverConfig->number = 4;
	playerHoverConfig->posX = 0;
	playerHoverConfig->posY = 0;
	playerHoverConfig->offSetX = 0;
	playerHoverConfig->offSetY = 0;
	playerHoverConfig->width = 450;
	playerHoverConfig->height = 283;
	configs.push_back(playerHoverConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility4.json");
	/*for (int i = 0; i < 4; i++) {
		UiObject* playerHover = new UiObject();
		playerHover->SetSpriteInfo(spriteList.find("Player_Hover")->second);
		playerHover->SetSize(configs.at(4)->width, -configs.at(4)->height);
		playerHover->SetPosition(glm::vec3(configs.at(4)->posX, configs.at(4)->posY, 0));
		playerHover->GetSpriteRenderer()->ShiftTo(playerHover->GetSpriteRenderer()->GetRow(), i);
		playerHover->setNumOwner(i);
		objectsList.push_back(playerHover);
		playerHoverList.push_back(playerHover);
	}*/

	//Player icon
	config* playerIconConfig = new config();
	playerIconConfig->number = 5;
	playerIconConfig->posX = 0;
	playerIconConfig->posY = 0;
	playerIconConfig->offSetX = 0;
	playerIconConfig->offSetY = 0;
	playerIconConfig->width = 175;
	playerIconConfig->height = 152;
	configs.push_back(playerIconConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility5.json");
	/*axisX = 0;
	axisY = 0;
	for (int i = 0; i < 4; i++) {
		UiObject* PlayerIcon = new UiObject();
		PlayerIcon->SetSpriteInfo(spriteList.find("Player_Icon")->second);
		PlayerIcon->SetSize(configs.at(5)->width, -configs.at(5)->height);
		if (i == 2) {
			axisX = 0;
			axisY = -1;
		}
		PlayerIcon->SetPosition(glm::vec3(configs.at(5)->posX + (configs.at(5)->offSetX * axisX), configs.at(5)->posY + (configs.at(5)->offSetY * axisY), 0));
		axisX++;
		PlayerIcon->setNumOwner(i);
		objectsList.push_back(PlayerIcon);
		playerIconList.push_back(PlayerIcon);
	}*/

	//Player icon(small)
	config* playerIconSmallConfig = new config();
	playerIconSmallConfig->number = 6;
	playerIconSmallConfig->posX = 0;
	playerIconSmallConfig->posY = 0;
	playerIconSmallConfig->offSetX = 120;
	playerIconSmallConfig->offSetY = 120;
	playerIconSmallConfig->width = 127;
	playerIconSmallConfig->height = 120;
	configs.push_back(playerIconSmallConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility6.json");
	/*axisX = 0;
	axisY = 0;
	for (int i = 0; i < 4; i++) {
		UiObject* PlayerIconSmall = new UiObject();
		PlayerIconSmall->SetSpriteInfo(spriteList.find("Player_Icon_Small")->second);
		PlayerIconSmall->SetSize(configs.at(6)->width, -configs.at(6)->height);
		if (i == 2) {
			axisX = 0;
			axisY = -1;
		}
		PlayerIconSmall->SetPosition(glm::vec3(configs.at(6)->posX + (configs.at(6)->offSetX * axisX), configs.at(6)->posY + (configs.at(6)->offSetY * axisY), 0));
		axisX++;
		PlayerIconSmall->setNumOwner(i);
		objectsList.push_back(PlayerIconSmall);
		playerIconSmallList.push_back(PlayerIconSmall);
	}*/

	//Ability icon(small)
	config* abilityIconSmallConfig = new config();
	abilityIconSmallConfig->number = 7;
	abilityIconSmallConfig->posX = 0;
	abilityIconSmallConfig->posY = 0;
	abilityIconSmallConfig->offSetX = 100;
	abilityIconSmallConfig->offSetY = 100;
	abilityIconSmallConfig->width = 72;
	abilityIconSmallConfig->height = 72;
	configs.push_back(abilityIconSmallConfig);
	loadConfig("../Resource/SceneData/ConfigLevelSelectAbility7.json");
	/*axisX = 0;
	axisY = 0;
	for (int i = 0; i < 4; i++) {
		std::vector<UiObject*>* abilityIconSmallList = new std::vector<UiObject*>;
		for (int j = 0; j < 3; j++) {
			UiObject* abilityIconSmall = new UiObject();
			abilityIconSmall->SetSpriteInfo(spriteList.find("Ability_Icon_Small")->second);
			abilityIconSmall->GetSpriteRenderer()->ShiftTo(abilityIconSmall->GetSpriteRenderer()->GetRow(), 8);
			if (axisX < 3) {
				abilityIconSmall->SetSize(configs.at(7)->width, -configs.at(7)->height);
				abilityIconSmall->SetPosition(glm::vec3(configs.at(7)->posX + (configs.at(7)->offSetX * axisX),
														configs.at(7)->posY + (configs.at(7)->offSetY * axisY), 0));
			}
			else {
				abilityIconSmall->SetSize(configs.at(7)->width, -configs.at(7)->height);
				abilityIconSmall->SetPosition(glm::vec3(configs.at(7)->posX + (configs.at(7)->offSetX * (axisX - 3)) + configs.at(0)->offSetX,
																   configs.at(7)->posY + (configs.at(7)->offSetY * axisY), 0));
			}
			
			abilityIconSmall->setNumOwner(i);
			objectsList.push_back(abilityIconSmall);
			abilityIconSmallList->push_back(abilityIconSmall);
			axisX++;
		}
		if (axisX >= 6) {
			axisX = 0;
			axisY = -1;
		}
		playerAbilityList[i] = abilityIconSmallList;
	}*/


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(GameEngine::GetInstance()->GetSDLWindow(), GameEngine::GetInstance()->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	std::cout << GameEngine::GetInstance()->GetStateController()->loadingState << std::endl;
	//std::ofstream MyFile("Ability.txt");
	//std::ofstream abilityFile("Ability.txt");
	/*for (int i = 0; i < 4; i++)
	{
		std::string fileName = "Ability" + std::to_string(i) + ".txt";
		std::ofstream abilityFile(fileName);
		abilityFile.close();
	}*/
}

void LevelSelectAbility::LevelUpdate()
{
	UpdateInput();
	UpdateUi();

	//check ready
	int check = 0;
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (ready[i] == true) {
			check++;
		}
	}
	if (check == SDL_NumJoysticks()) {
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			std::string fileName = "../Resource/SceneData/Ability" + std::to_string(i) + ".json";
			abilityToFile(fileName, i);
		}
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
	}
}

void LevelSelectAbility::UpdateInput()
{
	if (SDL_NumJoysticks() > 0) {
		Joystick::Update();
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			//join
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle) && playerWindowList[i]->GetSpriteRenderer()->GetColumn() == 0) {
				ready[i] = 0;

				//player window
				playerWindowList[i]->GetSpriteRenderer()->ShiftColumn();

				//player hover
				UiObject* playerHover = new UiObject();
				playerHover->SetSpriteInfo(spriteList.find("Player_Hover")->second);
				playerHover->SetSize(configs.at(4)->width, -configs.at(4)->height);
				playerHover->SetPosition(glm::vec3(configs.at(4)->posX, configs.at(4)->posY, 0));
				playerHover->GetSpriteRenderer()->ShiftTo(playerHover->GetSpriteRenderer()->GetRow(), i);
				playerHover->setNumOwner(i);
				objectsList.push_back(playerHover);
				playerHoverList.push_back(playerHover);

				//Player icon(small)
				UiObject* PlayerIconSmall = new UiObject();
				PlayerIconSmall->SetSpriteInfo(spriteList.find("Player_Icon_Small")->second);
				PlayerIconSmall->SetSize(configs.at(6)->width, -configs.at(6)->height);
				if (i == 0) {
					axisXplayerIconSmall = 0;
					axisYplayerIconSmall = 0;
				}
				if (i == 1) {
					axisXplayerIconSmall = 1;
					axisYplayerIconSmall = 0;
				}
				if (i == 2) {
					axisXplayerIconSmall = 0;
					axisYplayerIconSmall = -1;
				}
				if (i == 3) {
					axisXplayerIconSmall = 1;
					axisYplayerIconSmall = -1;
				}
				PlayerIconSmall->SetPosition(glm::vec3(configs.at(6)->posX + (configs.at(6)->offSetX * axisXplayerIconSmall), configs.at(6)->posY + (configs.at(6)->offSetY * axisYplayerIconSmall), 0));
				PlayerIconSmall->setNumOwner(i);
				objectsList.push_back(PlayerIconSmall);
				playerIconSmallList.push_back(PlayerIconSmall);

				//player ability
				std::vector<UiObject*>* abilityIconSmallList = new std::vector<UiObject*>;
				for (int j = 0; j < 3; j++) {
					UiObject* abilityIconSmall = new UiObject();
					abilityIconSmall->SetSpriteInfo(spriteList.find("Ability_Icon_Small")->second);
					abilityIconSmall->GetSpriteRenderer()->ShiftTo(abilityIconSmall->GetSpriteRenderer()->GetRow(), 8);
					if (axisXAbilityIconSmall == 6) {
						axisXAbilityIconSmall = 0;
						axisYAbilityIconSmall = -1;
					}
					if (axisXAbilityIconSmall < 3) {
						abilityIconSmall->SetSize(configs.at(7)->width, -configs.at(7)->height);
						abilityIconSmall->SetPosition(glm::vec3(configs.at(7)->posX + (configs.at(7)->offSetX * axisXAbilityIconSmall),
							configs.at(7)->posY + (configs.at(7)->offSetY * axisYAbilityIconSmall), 0));
					}
					else {
						abilityIconSmall->SetSize(configs.at(7)->width, -configs.at(7)->height);
						abilityIconSmall->SetPosition(glm::vec3(configs.at(7)->posX + (configs.at(7)->offSetX * (axisXAbilityIconSmall - 3)) + configs.at(0)->offSetX,
							configs.at(7)->posY + (configs.at(7)->offSetY * axisYAbilityIconSmall), 0));
					}

					abilityIconSmall->setNumOwner(i);
					objectsList.push_back(abilityIconSmall);
					abilityIconSmallList->push_back(abilityIconSmall);
					axisXAbilityIconSmall++;
				}
				playerAbilityList[i] = abilityIconSmallList;
			}

			float axisX = Joystick::GetAxis(i, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
			float axisY = Joystick::GetAxis(i, Joystick::Axis::LeftStickVertical) / 32768.0f;
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

			if (playerWindowList.at(i)->GetSpriteRenderer()->GetColumn() != 0 && ready[i] == false) {
				//move hover
				if (playerMove[i] == false) {
					if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Right) || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Up) || right || up) {
						playerHoverWhere[i]++;
						helpHover++;
						if (playerHoverWhere[i] > 6) {
							playerHoverWhere[i] = 0;
							helpHover = 0;
						}
						if (playerHoverWhere[i] == 3) {
							helpHover = 0;
						}
						playerMove[i] = true;
					}

					if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Left) || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Down) || left || down) {
						playerHoverWhere[i]--;
						helpHover--;
						if (playerHoverWhere[i] <= -1) {
							playerHoverWhere[i] = 6;
							helpHover = 3;
						}
						if (playerHoverWhere[i] == 2) {
							helpHover = 2;
						}
						playerMove[i] = true;
					}

					if (playerHoverWhere[i] > 2) {
						playerHoverList.at(i)->SetPosition(glm::vec3(configs.at(4)->posX + (configs.at(4)->offSetX * (playerHoverWhere[i] - 4 + helpHover)),
							configs.at(4)->posY + AbilityIconListDown.at(0)->getPos().y + configs.at(4)->offSetY, 0));
					}
					else {
						playerHoverList.at(i)->SetPosition(glm::vec3(configs.at(4)->posX + (configs.at(4)->offSetX * (playerHoverWhere[i] + helpHover)),
							configs.at(4)->posY, 0));
					}
					
				}

				//select character
				if (Joystick::GetButtonDown(i, Joystick::Button::R1)) {
					playerIconSmallList.at(i)->GetSpriteRenderer()->ShiftColumn();
				}

				if (Joystick::GetButtonDown(i, Joystick::Button::L1)) {
					playerIconSmallList.at(i)->GetSpriteRenderer()->ShiftTo(playerIconSmallList.at(i)->GetSpriteRenderer()->GetRow(), playerIconSmallList.at(i)->GetSpriteRenderer()->GetColumn() - 1);
				}

				//select ability
				if (Joystick::GetButtonDown(i, Joystick::Button::Cross)) {
					bool press = false;
					for (int j = 0; j < 3; j++) {
						if (playerHoverWhere[i] == playerAbility[i][j]) {
							playerAbility[i][j] = 8;
							press = true;
						}
					}

					for (int j = 0; j < 3; j++) {
						if (press == false && playerAbility[i][j] == 8) {
							playerAbility[i][j] = playerHoverWhere[i];
							press = true;
						}
					}
				}

				//ready
				if (Joystick::GetButtonDown(i, Joystick::Button::Square)) {
					bool canReady = true;
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == 8) {
							canReady = false;
						}
					}
						
					for (int j = 0; j < playerIconSmallList.size(); j++) {
						for (int k = 0; k < SDL_NumJoysticks(); k++) {
							if (playerIconSmallList.at(j)->getNumOwner() == i && playerIconSmallList.at(j)->GetSpriteRenderer()->GetColumn() == character[k]) {
								canReady = false;
							}
						}
					}
					
					if (canReady == true) {
						playerWindowList.at(i)->GetSpriteRenderer()->ShiftTo(playerWindowList.at(i)->GetSpriteRenderer()->GetRow(), playerIconSmallList.at(i)->GetSpriteRenderer()->GetColumn() + 2);
						playerRemainList.at(0)->GetSpriteRenderer()->ShiftTo(playerRemainList.at(0)->GetSpriteRenderer()->GetRow(), playerRemainList.at(0)->GetSpriteRenderer()->GetColumn() + 1);
						
						for (int j = 0; j < 3; j++) {
							playerAbilityList[i]->at(j)->SetPosition(glm::vec3(playerAbilityList[i]->at(j)->getPos().x,
								playerAbilityList[i]->at(j)->getPos().y - 25, 0));
						}

						//character = playerIconSmallList.at(i).;
						UiObject* PlayerIcon = new UiObject();
						PlayerIcon->SetSpriteInfo(spriteList.find("Player_Icon")->second);
						PlayerIcon->SetSize(configs.at(5)->width, -configs.at(5)->height);
						PlayerIcon->GetSpriteRenderer()->ShiftTo(PlayerIcon->GetSpriteRenderer()->GetRow(), playerIconSmallList.at(i)->GetSpriteRenderer()->GetColumn());
						if (i == 0) {
							axisXplayerIcon = 0;
							axisYplayerIcon = 0;
						}
						if (i == 1) {
							axisXplayerIcon = 1;
							axisYplayerIcon = 0;
						}
						if (i == 2) {
							axisXplayerIcon = 0;
							axisYplayerIcon = -1;
						}
						if (i == 3) {
							axisXplayerIcon = 1;
							axisYplayerIcon = -1;
						}
						PlayerIcon->SetPosition(glm::vec3(configs.at(5)->posX + (configs.at(5)->offSetX * axisXplayerIcon), configs.at(5)->posY + (configs.at(5)->offSetY * axisYplayerIcon), 0));
						PlayerIcon->setNumOwner(i);
						objectsList.push_back(PlayerIcon);
						playerIconList.push_back(PlayerIcon);
						ready[i] = true;

						for (int j = 0; j < playerIconSmallList.size(); j++) {
							if (playerIconSmallList.at(j)->getNumOwner() == i) {
								character[i] = playerIconSmallList.at(j)->GetSpriteRenderer()->GetColumn();
								PlayerIcon->GetSpriteRenderer()->ShiftTo(PlayerIcon->GetSpriteRenderer()->GetRow(), playerIconSmallList.at(j)->GetSpriteRenderer()->GetColumn());
								playerIconSmallList.at(j)->SetIsActive(false);
								playerIconSmallList.erase(playerIconSmallList.begin() + j);
							}
						}

						for (int i = 0; i < objectsList.size(); i++)
						{
							if (objectsList[i]->GetIsActive() == false)
							{
								objectsList.erase(objectsList.begin() + i);
							}
						}
					}
					
					else {
						playerWindowList.at(i)->GetSpriteRenderer()->ShiftTo(playerWindowList.at(i)->GetSpriteRenderer()->GetRow(), 6);
					}
				}
			}
			
			else if (Joystick::GetButtonDown(i, Joystick::Button::Square) && ready[i] == true) {
				playerWindowList.at(i)->GetSpriteRenderer()->ShiftTo(playerWindowList.at(i)->GetSpriteRenderer()->GetRow(), 1);
				playerRemainList.at(0)->GetSpriteRenderer()->ShiftTo(playerRemainList.at(0)->GetSpriteRenderer()->GetRow(), playerRemainList.at(0)->GetSpriteRenderer()->GetColumn() - 1);
				character[i] = -1;
				UiObject* PlayerIconSmall = new UiObject();
				PlayerIconSmall->SetSpriteInfo(spriteList.find("Player_Icon_Small")->second);
				PlayerIconSmall->SetSize(configs.at(6)->width, -configs.at(6)->height);
				if (i == 0) {
					axisXplayerIconSmall = 0;
					axisYplayerIconSmall = 0;
				}
				if (i == 1) {
					axisXplayerIconSmall = 1;
					axisYplayerIconSmall = 0;
				}
				if (i == 2) {
					axisXplayerIconSmall = 0;
					axisYplayerIconSmall = -1;
				}
				if (i == 3) {
					axisXplayerIconSmall = 1;
					axisYplayerIconSmall = -1;
				}
				PlayerIconSmall->SetPosition(glm::vec3(configs.at(6)->posX + (configs.at(6)->offSetX * axisXplayerIconSmall), configs.at(6)->posY + (configs.at(6)->offSetY * axisYplayerIconSmall), 0));
				PlayerIconSmall->setNumOwner(i);
				objectsList.push_back(PlayerIconSmall);
				playerIconSmallList.push_back(PlayerIconSmall);

				for (int j = 0; j < 3; j++) {
					playerAbilityList[i]->at(j)->SetPosition(glm::vec3(playerAbilityList[i]->at(j)->getPos().x,
						playerAbilityList[i]->at(j)->getPos().y + 25, 0));
				}
				for (int j = 0; j < playerIconList.size(); j++) {
					if (playerIconList.at(j)->getNumOwner() == i) {
						PlayerIconSmall->GetSpriteRenderer()->ShiftTo(PlayerIconSmall->GetSpriteRenderer()->GetRow(), playerIconList.at(j)->GetSpriteRenderer()->GetColumn());
						playerIconList.at(j)->SetIsActive(false);
						playerIconList.erase(playerIconList.begin() + j);
					}
				}

				for (int i = 0; i < objectsList.size(); i++)
				{
					if (objectsList[i]->GetIsActive() == false)
					{
						objectsList.erase(objectsList.begin() + i);
					}
				}
				ready[i] = false;
			}

			if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
				playerMove[i] = false;
			}
		}


	}
}

void LevelSelectAbility::UpdateUi() {

	//player hover
	for (int i = 0; i < 4; i++) {
		int count = 0;
		for (int j = 0; j < playerHoverList.size(); j++) {
			if (playerHoverWhere[i] == playerHoverWhere[j] && i != j && playerHoverList.size() > 1) {
				playerHoverList.at(j)->SetPosition(glm::vec3(configs.at(4)->posX, configs.at(4)->posY + (configs.at(4)->offSetY * count), 0));
				count++;
				if (playerHoverList.at(i)->getPos() == playerHoverList.at(j)->getPos()) {
					playerHoverList.at(j)->SetPosition(glm::vec3(configs.at(4)->posX, configs.at(4)->posY + (configs.at(4)->offSetY * count), 0));
				}
			}
		}
	}

	// player ability icon
	for (int i = 0; i < playerAbilityList.size(); i++) {
		for (int j = 0; j < 3; j++) {
			playerAbilityList[i]->at(j)->GetSpriteRenderer()->ShiftTo(playerAbilityList[i]->at(j)->GetSpriteRenderer()->GetRow(), playerAbility[i][j]); 
		}
	}

	//update by config *Replace this in LevelInit instead old code when build it.
	//Player window
	axisX = 1;
	axisY = 2;
	for (int i = 0; i < playerWindowList.size(); i++) {
		if (i == 2) {
			axisX = 1;
			axisY = 1;
		}
		playerWindowList.at(i)->SetPosition(glm::vec3(configs.at(0)->posX + (configs.at(0)->offSetX * axisX), configs.at(0)->posY + (configs.at(0)->offSetY * axisY), 0));
		playerWindowList.at(i)->SetSize(configs.at(0)->width, -configs.at(0)->height);
		axisX++;
	}

	//Player remain
	objectsList.at(5)->SetPosition(glm::vec3(configs.at(1)->posX, configs.at(1)->posY, 0));
	objectsList.at(5)->SetSize(configs.at(1)->width, -configs.at(1)->height);

	//Ability icon
	//Top
	axisX = 1;
	for (int i = 0; i < AbilityIconListTop.size(); i++) {
		AbilityIconListTop.at(i)->SetPosition(glm::vec3(configs.at(2)->posX + (configs.at(2)->offSetX * axisX), configs.at(2)->posY, 0));
		AbilityIconListTop.at(i)->SetSize(configs.at(2)->width, -configs.at(2)->height);
		axisX++;
	}
	//Down
	axisX = 1;
	for (int i = 0; i < AbilityIconListDown.size(); i++) {
		AbilityIconListDown.at(i)->SetPosition(glm::vec3(configs.at(3)->posX + (configs.at(3)->offSetX * axisX), configs.at(3)->posY, 0));
		AbilityIconListDown.at(i)->SetSize(configs.at(3)->width, -configs.at(3)->height);
		axisX++;
	}

	//Player hover
	/*for (int i = 0; i < playerHoverList.size(); i++) {
		playerHoverList.at(i)->SetPosition(glm::vec3(configs.at(4)->posX + (configs.at(4)->offSetX * i), configs.at(4)->posY + (configs.at(4)->offSetY * i), 0));
		playerHoverList.at(i)->SetSize(configs.at(4)->width, -configs.at(4)->height);
		axisX++;
	}*/

	//Player icon 
	/*axisX = 0;
	axisY = 0;
	for (int i = 0; i < playerIconList.size(); i++) {
		playerIconList.at(i)->SetSize(configs.at(5)->width, -configs.at(5)->height);
		if (i == 2) {
			axisX = 0;
			axisY = -1;
		}
		playerIconList.at(i)->SetPosition(glm::vec3(configs.at(5)->posX + (configs.at(5)->offSetX * axisX), configs.at(5)->posY + (configs.at(5)->offSetY * axisY), 0));
		axisX++;
	}*/

	//Player icon small
	/*axisX = 0;
	axisY = 0;
	for (int i = 0; i < playerIconSmallList.size(); i++) {
		if (i == 2) {
			axisX = 0;
			axisY = -1;
		}
		playerIconSmallList.at(i)->SetPosition(glm::vec3(configs.at(6)->posX + (configs.at(6)->offSetX * axisX), configs.at(6)->posY + (configs.at(6)->offSetY * axisY), 0));
		axisX++;
		playerIconSmallList.at(i)->SetSize(configs.at(6)->width, -configs.at(6)->height);
	}*/

	//Ability icon small
	/*axisX = 0;
	axisY = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (axisX < 3) {
				playerAbilityList[i]->at(j)->SetSize(configs.at(7)->width, -configs.at(7)->height);
				playerAbilityList[i]->at(j)->SetPosition(glm::vec3(configs.at(7)->posX + (configs.at(7)->offSetX * axisX), 
																   configs.at(7)->posY + (configs.at(7)->offSetY * axisY), 0));
			}
			else{
				playerAbilityList[i]->at(j)->SetSize(configs.at(7)->width, -configs.at(7)->height);
				playerAbilityList[i]->at(j)->SetPosition(glm::vec3(configs.at(7)->posX + (configs.at(7)->offSetX * (axisX - 3)) + configs.at(0)->offSetX,
																   configs.at(7)->posY + (configs.at(7)->offSetY * axisY), 0));
			}
			axisX++;
		}

		
		if (axisX >= 6) {
			axisX = 0;
			axisY = -1;
		}
	}*/
}

void LevelSelectAbility::LevelDraw()
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

	////ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
	//int configNum = -1;
	//if (ImGui::Button("Go levelShowcase")) {
	//	for (int i = 0; i < 4; i++)
	//	{
	//		std::string fileName = "Ability" + std::to_string(i) + ".json";
	//		abilityToFile(fileName, i);
	//	}
	//	GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
	//}

	//ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	//if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
	//	if (ImGui::BeginTabItem("Player ability")) {
	//		for (int i = 0; i < 4; i++)
	//		{
	//			std::string fileName = "Ability" + std::to_string(i) + ".txt";
	//			std::string buttonName;
	//			ImGui::SeparatorText("");
	//			ImGui::Text("Ability Player %d", i);

	//			for (int j = 0; j < 3; j++) {
	//				ImGui::Text("Ability%d: ", j);
	//				if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Fireball)) {
	//					ImGui::SameLine();
	//					ImGui::Text("Fireball");
	//				}
	//				if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Trap)) {
	//					ImGui::SameLine();
	//					ImGui::Text("Trap");
	//				}
	//				if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Dash)) {
	//					ImGui::SameLine();
	//					ImGui::Text("Dash");
	//				}
	//				if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::TNT)) {
	//					ImGui::SameLine();
	//					ImGui::Text("TNT");
	//				}
	//				if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Teleport)) {
	//					ImGui::SameLine();
	//					ImGui::Text("Teleport");
	//				}
	//				if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Bola)) {
	//					ImGui::SameLine();
	//					ImGui::Text("Bola");
	//				}
	//				if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Cleave)) {
	//					ImGui::SameLine();
	//					ImGui::Text("Cleave");
	//				}
	//			}
	//		}
	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Config Player Window")) {
	//		configNum = 0;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility0.json";
	//			saveConfig(fileName, configs.at(configNum));
	//		}
	//		
	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			
	//			std::string fileName = "ConfigLevelSelectAbility0.json";
	//			loadConfig(fileName);
	//			int axisX = 1;
	//			int axisY = 2;
	//			for (int i = 0; i < playerWindowList.size(); i++) {
	//				if (i == 2) {
	//					axisX = 1;
	//					axisY = 1;
	//				}
	//				playerWindowList.at(i)->SetPosition(glm::vec3(configs.at(configNum)->posX + (configs.at(configNum)->offSetX * axisX), configs.at(configNum)->posY + (configs.at(configNum)->offSetY * axisY), 0));
	//				playerWindowList.at(i)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//				axisX++;
	//			}
	//			
	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Config Player remain")) {
	//		configNum = 1;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility1.json";
	//			std::cout << "save config1" << std::endl;
	//			saveConfig(fileName, configs.at(configNum));
	//		}

	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			std::string fileName = "ConfigLevelSelectAbility1.json";
	//			loadConfig(fileName);
	//			objectsList.at(5)->SetPosition(glm::vec3(configs.at(configNum)->posX, configs.at(configNum)->posY, 0));
	//			objectsList.at(5)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//			
	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}
	//	
	//	if (ImGui::BeginTabItem("Config Ability top")) {
	//		configNum = 2;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility2.json";
	//			std::cout << "save config1" << std::endl;
	//			saveConfig(fileName, configs.at(configNum));
	//		}

	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			std::string fileName = "ConfigLevelSelectAbility2.json";
	//			loadConfig(fileName);
	//			int axisX = 1;
	//			for (int i = 0; i < AbilityIconListTop.size(); i++) {
	//				AbilityIconListTop.at(i)->SetPosition(glm::vec3(configs.at(configNum)->posX + (configs.at(configNum)->offSetX * axisX), configs.at(configNum)->posY, 0));
	//				AbilityIconListTop.at(i)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//				axisX++;
	//			}

	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Config Ability Down")) {
	//		configNum = 3;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility3.json";
	//			std::cout << "save config1" << std::endl;
	//			saveConfig(fileName, configs.at(configNum));
	//		}

	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			std::string fileName = "ConfigLevelSelectAbility3.json";
	//			loadConfig(fileName);
	//			int axisX = 1;
	//			for (int i = 0; i < AbilityIconListDown.size(); i++) {
	//				AbilityIconListDown.at(i)->SetPosition(glm::vec3(configs.at(configNum)->posX + (configs.at(configNum)->offSetX * axisX), configs.at(configNum)->posY, 0));
	//				AbilityIconListDown.at(i)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//				axisX++;
	//			}

	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Config Player Hover")) {
	//		configNum = 4;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility4.json";
	//			std::cout << "save config1" << std::endl;
	//			saveConfig(fileName, configs.at(configNum));
	//		}

	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			std::string fileName = "ConfigLevelSelectAbility4.json";
	//			loadConfig(fileName);
	//			int axisX = 1;
	//			for (int i = 0; i < AbilityIconListDown.size(); i++) {
	//				AbilityIconListDown.at(i)->SetPosition(glm::vec3(configs.at(configNum)->posX + (configs.at(configNum)->offSetX * axisX), configs.at(configNum)->posY, 0));
	//				AbilityIconListDown.at(i)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//				axisX++;
	//			}

	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Config Player Icon")) {
	//		configNum = 5;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility5.json";
	//			std::cout << "save config1" << std::endl;
	//			saveConfig(fileName, configs.at(configNum));
	//		}

	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			std::string fileName = "ConfigLevelSelectAbility5.json";
	//			loadConfig(fileName);
	//			int axisX = 1;
	//			for (int i = 0; i < AbilityIconListDown.size(); i++) {
	//				AbilityIconListDown.at(i)->SetPosition(glm::vec3(configs.at(configNum)->posX + (configs.at(configNum)->offSetX * axisX), configs.at(configNum)->posY, 0));
	//				AbilityIconListDown.at(i)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//				axisX++;
	//			}

	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Config Player Icon Small")) {
	//		configNum = 6;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility6.json";
	//			std::cout << "save config1" << std::endl;
	//			saveConfig(fileName, configs.at(configNum));
	//		}

	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			std::string fileName = "ConfigLevelSelectAbility6.json";
	//			loadConfig(fileName);
	//			int axisX = 1;
	//			for (int i = 0; i < AbilityIconListDown.size(); i++) {
	//				AbilityIconListDown.at(i)->SetPosition(glm::vec3(configs.at(configNum)->posX + (configs.at(configNum)->offSetX * axisX), configs.at(configNum)->posY, 0));
	//				AbilityIconListDown.at(i)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//				axisX++;
	//			}

	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}

	//	if (ImGui::BeginTabItem("Config Ability Icon Small")) {
	//		configNum = 7;
	//		if (ImGui::Button("Save config")) {
	//			std::string fileName = "ConfigLevelSelectAbility7.json";
	//			std::cout << "save config1" << std::endl;
	//			saveConfig(fileName, configs.at(configNum));
	//		}

	//		ImGui::SameLine();
	//		if (ImGui::Button("Load config")) {
	//			std::string fileName = "ConfigLevelSelectAbility7.json";
	//			loadConfig(fileName);
	//			int axisX = 1;
	//			for (int i = 0; i < AbilityIconListDown.size(); i++) {
	//				AbilityIconListDown.at(i)->SetPosition(glm::vec3(configs.at(configNum)->posX + (configs.at(configNum)->offSetX * axisX), configs.at(configNum)->posY, 0));
	//				AbilityIconListDown.at(i)->SetSize(configs.at(configNum)->width, -configs.at(configNum)->height);
	//				axisX++;
	//			}

	//		}
	//		ImGui::InputFloat("PosX", &configs.at(configNum)->posX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("PosY", &configs.at(configNum)->posY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetX", &configs.at(configNum)->offSetX, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("OffSetY", &configs.at(configNum)->offSetY, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Width", &configs.at(configNum)->width, 1.0f, 1.0f, "%.2f");
	//		ImGui::InputFloat("Height", &configs.at(configNum)->height, 1.0f, 1.0f, "%.2f");
	//		ImGui::EndTabItem();
	//	}

	//	ImGui::EndTabBar();
	//}
	

	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());
}

void LevelSelectAbility::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();

	KrillSoundManager::SoundManager::GetInstance()->StopMusic("Ability_Selection");
	//cout << "Free Level" << endl;
}

void LevelSelectAbility::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	GameEngine::GetInstance()->ResetWinScore("../Resource/SceneData/RoundWin.json");

	//cout << "Unload Level" << endl;
}

void LevelSelectAbility::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY){}
void LevelSelectAbility::HandleKey(char key){}
void LevelSelectAbility::HandleMouse(int type, int x, int y){}

void LevelSelectAbility::abilityToFile(const std::string& fileName, int who) {

	ConvertAbility();

	std::ofstream file(fileName);
	nlohmann::json data;
	data["ability0"] = playerAbility[who][0];
	data["ability1"] = playerAbility[who][1];
	data["ability2"] = playerAbility[who][2];
	data["character"] = character[who];

	if (file.is_open()) {
		file << data;
		file.close();
		std::cout << "Saved" << std::endl;
	}

	else {
		std::cout << "Failed" << std::endl;
	}
	
	
}

void LevelSelectAbility::saveConfig(std::string& filename, config* con) {
	nlohmann::json data;
	data["number"] = con->number;
	data["posX"] = con->posX;
	data["posY"] = con->posY;
	data["offSetX"] = con->offSetX;
	data["offSetY"] = con->offSetY;
	data["height"] = con->height;
	data["width"] = con->width;

	std::ofstream file(filename);
	if (file.is_open()) {
		file << data;
		file.close();
		std::cout << "Saved" << std::endl;
	}
	else {
		std::cout << "Failed" << std::endl;
	}
}

void LevelSelectAbility::loadConfig(std::string filename) {
	std::ifstream file(filename);
	
	if (file.is_open()) {
		std::cout << "Opened" << std::endl;
		nlohmann::json data = nlohmann::json::parse(file);
		int id = -1;
		if (data.contains("number") && !data["number"].is_null()) {
			id = data["number"];
			for (int i = 0; i < configs.size(); i++) {
				if (configs.at(i)->number == id) {
					std::cout << "Loaded" << std::endl;
					//configs.at(i).text = data["text"];
					if (data.contains("posX") && !data["posX"].is_null()) {
						configs.at(i)->posX = data["posX"];
					}

					if (data.contains("posY") && !data["posY"].is_null()) {
						configs.at(i)->posY = data["posY"];
					}

					if (data.contains("offSetX") && !data["offSetX"].is_null()) {
						configs.at(i)->offSetX = data["offSetX"];
					}

					if (data.contains("offSetY") && !data["offSetY"].is_null()) {
						configs.at(i)->offSetY = data["offSetY"];
					}

					if (data.contains("height") && !data["height"].is_null()) {
						configs.at(i)->height = data["height"];
					}

					if (data.contains("width") && !data["width"].is_null()) {
						configs.at(i)->width = data["width"];
					}
				}
			}
		}
	}

	else {
		std::cout << "Failed" << std::endl;
	}
}

void LevelSelectAbility::ConvertAbility()
{
	int ability;
	AbilitySelectScene ability_selectScene;
	int ability_afterConvert;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ability = playerAbility[i][j];
			ability_selectScene = static_cast<AbilitySelectScene>(ability);
			
			ability_afterConvert = AbilityConverter.find(ability_selectScene)->second;

			playerAbility[i][j] = ability_afterConvert;
		}
	}
}


