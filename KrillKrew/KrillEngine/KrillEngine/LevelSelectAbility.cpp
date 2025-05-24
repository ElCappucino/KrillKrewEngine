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
	spriteList["Ability_IconSmall"] = SpritesheetInfo("Ability_Icon_Small", "../Resource/Texture/CharacterSelection/UI_CS_Abilityicon_Small.png", 72, 72, 576, 72);

	spriteList["Player_Remain"] = SpritesheetInfo("Player_Remain", "../Resource/Texture/CharacterSelection/UI_CS_PlayerRemain.png", 292, 133, 2044, 133);
}

void LevelSelectAbility::LevelInit()
{
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));
	//BG
	UiObject* BG = new UiObject();
	BG->SetSpriteInfo(spriteList.find("BG")->second);
	BG->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
	objectsList.push_back(BG);

	//Player window
	int axisX = 1;
	int axisY = 2;

	config* PlayerWindowConfig = new config();
	PlayerWindowConfig->number = 0;
	PlayerWindowConfig->posX = 0;
	PlayerWindowConfig->posY = 0;
	PlayerWindowConfig->offSetX = 284;
	PlayerWindowConfig->offSetY = 373;
	PlayerWindowConfig->width = 284;
	PlayerWindowConfig->height = 373;
	configs.push_back(PlayerWindowConfig);
	loadConfig("ConfigLevelSelectAbility0.json");

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
	loadConfig("ConfigLevelSelectAbility1.json");

	UiObject* PlayerRemain = new UiObject();
	PlayerRemain->SetSpriteInfo(spriteList.find("Player_Remain")->second);
	PlayerRemain->GetSpriteRenderer()->ShiftTo(PlayerRemain->GetSpriteRenderer()->GetRow(), 3);
	PlayerRemain->SetSize(configs.at(1)->width, -configs.at(1)->height);
	PlayerRemain->SetPosition(glm::vec3(configs.at(1)->posX, configs.at(1)->posY, 0));
	PlayerRemain->setNumOwner(-1);
	objectsList.push_back(PlayerRemain);

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
	loadConfig("ConfigLevelSelectAbility2.json");
	for (int i = 0; i < 3; i++) {
		UiObject* AbilityIconTop = new UiObject();
		AbilityIconTop->SetSpriteInfo(spriteList.find("Ability_Icon")->second);
		AbilityIconTop->GetSpriteRenderer()->ShiftTo(AbilityIconTop->GetSpriteRenderer()->GetRow(), 0);
		AbilityIconTop->SetSize(configs.at(2)->width, -configs.at(2)->height);
		AbilityIconTop->SetPosition(glm::vec3(configs.at(2)->posX + (configs.at(2)->offSetX * axisX), configs.at(2)->posY, 0));
		AbilityIconTop->GetSpriteRenderer()->ShiftTo(AbilityIconTop->GetSpriteRenderer()->GetRow(), i);
		AbilityIconTop->setNumOwner(-1);
		objectsList.push_back(AbilityIconTop);
		AbilityIconListTop.push_back(AbilityIconTop);
	}
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
	loadConfig("ConfigLevelSelectAbility3.json");
	for (int i = 0; i < 4; i++) {
		UiObject* AbilityIconDown = new UiObject();
		AbilityIconDown->SetSpriteInfo(spriteList.find("Ability_Icon")->second);
		AbilityIconDown->GetSpriteRenderer()->ShiftTo(AbilityIconDown->GetSpriteRenderer()->GetRow(), 0);
		AbilityIconDown->SetSize(configs.at(3)->width, -configs.at(3)->height);
		AbilityIconDown->SetPosition(glm::vec3(configs.at(3)->posX + (configs.at(0)->offSetX * axisX), configs.at(3)->posY, 0));
		AbilityIconDown->GetSpriteRenderer()->ShiftTo(AbilityIconDown->GetSpriteRenderer()->GetRow(), i + 3);
		AbilityIconDown->setNumOwner(-1);
		objectsList.push_back(AbilityIconDown);
		AbilityIconListDown.push_back(AbilityIconDown);
	}

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
	//UpdateInput();
	//UpdateUi();

	//Player window
	int axisX = 1;
	int axisY = 2;
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
}

void LevelSelectAbility::UpdateInput()
{
	
	//if (SDL_NumJoysticks() > 0)
	//{

	//	Joystick::Update();
	//	for (int i = 0; i < SDL_NumJoysticks(); i++)
	//	{
	//		std::string fileName = "Ability" + std::to_string(i) + ".txt";
	//		float axisX = Joystick::GetAxis(i, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
	//		/*std::cout << "axisX : " << axisX << std::endl;*/
	//		float axisY = Joystick::GetAxis(i, Joystick::Axis::LeftStickVertical) / 32768.0f;
	//		//std::cout << "axisY : " << axisY << std::endl;
	//		bool up = false ;
	//		bool down = false ;
	//		bool right = false ;
	//		bool left = false ;

	//		if (axisX > 0.8) {
	//			right = true;
	//		}

	//		else if (axisX < -0.8) {
	//			left = true;
	//		}

	//		else if (axisY > 0.8) {
	//			up = true;
	//		}

	//		else if (axisY < -0.8) {
	//			down = true;
	//		}
	//		

	//		if (!playerMove[i]) {
	//			if (right || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Right))
	//			{
	//				if (playerWhere[i] == 3) {
	//					playerWhere[i] = 0;
	//				}

	//				else if (playerWhere[i] == 7) {
	//					playerWhere[i] = 4;
	//				}

	//				else {
	//					playerWhere[i] += 1;
	//				}
	//				playerMove[i] = true;
	//				std::cout << "x" << i << std::endl;
	//			}
	//			else if (left || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Left))
	//			{
	//				if (playerWhere[i] == 0) {
	//					playerWhere[i] = 3;
	//				}

	//				else if (playerWhere[i] == 4) {
	//					playerWhere[i] = 7;
	//				}

	//				else {
	//					playerWhere[i] -= 1;
	//				}
	//				playerMove[i] = true;
	//				std::cout << "-x" << i << std::endl;
	//			}
	//			else if (up || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Up))
	//			{
	//				playerWhere[i] -= 4;
	//				if (playerWhere[i] < 0) {
	//					playerWhere[i] += 8;
	//				}
	//				playerMove[i] = true;
	//				std::cout << "y" << i << std::endl;
	//			}
	//			else if (down || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Down))
	//			{
	//				playerWhere[i] += 4;
	//				if (playerWhere[i] > 7 ) {
	//					playerWhere[i] -= 8;
	//				}
	//				playerMove[i] = true;
	//				std::cout << "-y" << i << std::endl;
	//			}
	//		}

	//		if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
	//			playerMove[i] = false;
	//		}

	//		if (Joystick::GetButtonDown(i, Joystick::Button::Cross)) {
	//			std::cout << "Pos playerX " << players[i]->getPos().y << std::endl;//90
	//			std::cout << "Pos playerY " << SkillBoxList.at(4)->getPos().y + playerHoverPosY << std::endl;//70 0.75
	//			bool press = false;
	//			if (players[i]->getPos().x == SkillBoxList.at(0)->getPos().x + playerHoverPosX &&
	//				players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3){
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Fireball) && !press) {
	//						playerAbility[i][j] = -1;
	//						press = true;
	//					}
	//				}
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == -1 && !press) {
	//						playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Fireball);
	//						press = true;
	//					}
	//				}
	//				//abilityToFile(fileName, PlayerObject::Ability::Fireball, i);
	//			}

	//			if (players[i]->getPos().x == SkillBoxList.at(1)->getPos().x + playerHoverPosX &&
	//				players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3) {
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::TNT) && !press) {
	//						playerAbility[i][j] = -1;
	//						press = true;
	//					}
	//				}
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == -1 && !press) {
	//						playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::TNT);
	//						press = true;
	//					}
	//				}
	//				//abilityToFile(fileName, PlayerObject::Ability::TNT, i);
	//			}

	//			if (players[i]->getPos().x == SkillBoxList.at(2)->getPos().x + playerHoverPosX &&
	//				players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3) {
	//				//bilityToFile(fileName, PlayerObject::Ability::Fireball, i);
	//			}

	//			if (players[i]->getPos().x == SkillBoxList.at(3)->getPos().x + playerHoverPosX &&
	//				players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3) {
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Cleave) && !press) {
	//						playerAbility[i][j] = -1;
	//						press = true;
	//					}
	//				}
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == -1 && !press) {
	//						playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Cleave);
	//						press = true;
	//					}
	//				}
	//				//abilityToFile(fileName, PlayerObject::Ability::Cleave, i);
	//			}

	//			if (players[i]->getPos().x == SkillBoxList.at(4)->getPos().x + playerHoverPosX && 
	//				players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Bola) && !press) {
	//						playerAbility[i][j] = -1;
	//						press = true;
	//					}
	//				}
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == -1 && !press) {
	//						playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Bola);
	//						press = true;
	//					}
	//				}
	//				//abilityToFile(fileName, PlayerObject::Ability::Bola, i);
	//			}

	//			if (players[i]->getPos().x == SkillBoxList.at(5)->getPos().x + playerHoverPosX &&
	//				players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Teleport) && !press) {
	//						playerAbility[i][j] = -1;
	//						press = true;
	//					}
	//				}
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == -1 && !press) {
	//						playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Teleport);
	//						press = true;
	//					}
	//				}
	//				//abilityToFile(fileName, PlayerObject::Ability::Teleport, i);
	//			}

	//			if (players[i]->getPos().x == SkillBoxList.at(6)->getPos().x + playerHoverPosX &&
	//				players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Trap) && !press) {
	//						playerAbility[i][j] = -1;
	//						press = true;
	//					}
	//				}
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == -1 && !press) {
	//						playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Trap);
	//						press = true;
	//					}
	//				}
	//				//abilityToFile(fileName, PlayerObject::Ability::Trap, i);
	//			}

	//			if (players[i]->getPos().x == SkillBoxList.at(7)->getPos().x + playerHoverPosX &&
	//				players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Dash) && !press) {
	//						playerAbility[i][j] = -1;
	//						press = true;
	//					}
	//				}
	//				for (int j = 0; j < 3; j++) {
	//					if (playerAbility[i][j] == -1 && !press) {
	//						playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Dash);
	//						press = true;
	//					}
	//				}
	//				//abilityToFile(fileName, PlayerObject::Ability::Dash, i);
	//			}
	//		}
	//		if (Joystick::GetButtonDown(i, Joystick::Button::Square)) {
	//			if (!ready[i]) {
	//				ready[i]++;
	//			}
	//			else {
	//				ready[i]--;
	//			}
	//		}
	//		if (ready[0] + ready[1] + ready[2] + ready[3] == SDL_NumJoysticks()) {
	//			for (int i = 0; i < SDL_NumJoysticks(); i++)
	//			{
	//				std::string fileName = "Ability" + std::to_string(i) + ".json";
	//				abilityToFile(fileName, i);
	//			}
	//			GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
	//		}

	//		if (Joystick::GetButtonDown(i, Joystick::Button::R1)) {
	//			int Column = playerIconList.at(i)->GetSpriteRenderer()->GetColumn();
	//			Column += 1;
	//			if (Column == 4) {
	//				Column = 0;
	//			}
	//			playerIconList.at(i)->GetSpriteRenderer()->ShiftTo(playerIconList.at(i)->GetSpriteRenderer()->GetRow(), Column);
	//		}

	//		if (Joystick::GetButtonDown(i, Joystick::Button::L1)) {
	//			int Column = playerIconList.at(i)->GetSpriteRenderer()->GetColumn();
	//			Column -= 1;
	//			if (Column == 0) {
	//				Column = 4;
	//			}
	//			playerIconList.at(i)->GetSpriteRenderer()->ShiftTo(playerIconList.at(i)->GetSpriteRenderer()->GetRow(), Column);
	//		}
	//	}
	//}
}

void LevelSelectAbility::UpdateUi() {
	//Player Ui
	/*for (int i = 0; i < 4; i++) {
		players[i]->SetPosition(glm::vec3(playerHoverPosX + SkillBoxList.at(playerWhere[i])->getPos().x, playerHoverPosY + SkillBoxList.at(playerWhere[i])->getPos().y, 0));
	}
	for (int i = 0; i < 4; i++) {
		int count = 0;
		for (int j = 0; j < 4; j++) {
			if (i != j) {
				if (players[i]->getPos() == players[j]->getPos()) {
					count++;
					playerHoverList.at(j)->SetPosition(glm::vec3(players[j]->getPos().x, playerHoverPosY + SkillBoxList.at(playerWhere[j])->getPos().y + playerHoverList.at(i)->getSize().y * count, 0));
				}
			}
		}
	}
	float iconWidth = 129.524;
	float iconHeight = -133.81;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (playerAbility[i][j] == -1) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("NoSkill")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
			if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Fireball)) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("Bomb")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
			if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Trap)) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("Trap")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
			if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Dash)) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("Dash")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
			if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::TNT)) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("TNT")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
			if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Teleport)) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("Teleport")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
			if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Bola)) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("Bola")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
			if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Cleave)) {
				playerIconSkillList[i].at(j)->SetSpriteInfo(spriteList.find("Cleave")->second);
				playerIconSkillList[i].at(j)->SetSize(iconWidth / 3, iconHeight / 3);
			}
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

	//ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);

	if (ImGui::Button("Go levelShowcase")) {
		//abilityToFile("Ability.txt", -1);
		for (int i = 0; i < 4; i++)
		{
			std::string fileName = "Ability" + std::to_string(i) + ".json";
			abilityToFile(fileName, i);
		}
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
	}

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
		if (ImGui::BeginTabItem("Player ability")) {
			for (int i = 0; i < 4; i++)
			{
				std::string fileName = "Ability" + std::to_string(i) + ".txt";
				std::string buttonName;
				ImGui::SeparatorText("");
				ImGui::Text("Ability Player %d", i);

				for (int j = 0; j < 3; j++) {
					ImGui::Text("Ability%d: ", j);
					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Fireball)) {
						ImGui::SameLine();
						ImGui::Text("Fireball");
					}
					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Trap)) {
						ImGui::SameLine();
						ImGui::Text("Trap");
					}
					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Dash)) {
						ImGui::SameLine();
						ImGui::Text("Dash");
					}
					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::TNT)) {
						ImGui::SameLine();
						ImGui::Text("TNT");
					}
					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Teleport)) {
						ImGui::SameLine();
						ImGui::Text("Teleport");
					}
					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Bola)) {
						ImGui::SameLine();
						ImGui::Text("Bola");
					}
					if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Cleave)) {
						ImGui::SameLine();
						ImGui::Text("Cleave");
					}
				}
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Config Player Window")) {
			if (ImGui::Button("Save config")) {
				std::string fileName = "ConfigLevelSelectAbility0.json";
				saveConfig(fileName, configs.at(0));
			}
			
			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				
				std::string fileName = "ConfigLevelSelectAbility0.json";
				loadConfig(fileName);
				int axisX = 1;
				int axisY = 2;
				for (int i = 0; i < playerWindowList.size(); i++) {
					if (i == 2) {
						axisX = 1;
						axisY = 1;
					}
					playerWindowList.at(i)->SetPosition(glm::vec3(configs.at(0)->posX + (configs.at(0)->offSetX * axisX), configs.at(0)->posY + (configs.at(0)->offSetY * axisY), 0));
					playerWindowList.at(i)->SetSize(configs.at(0)->width, -configs.at(0)->height);
					axisX++;
				}
				
			}
			ImGui::InputFloat("PosX", &configs.at(0)->posX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &configs.at(0)->posY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &configs.at(0)->offSetX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &configs.at(0)->offSetY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Width", &configs.at(0)->width, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Height", &configs.at(0)->height, 1.0f, 1.0f, "%.2f");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Config Player remain")) {
			if (ImGui::Button("Save config")) {
				std::string fileName = "ConfigLevelSelectAbility1.json";
				std::cout << "save config1" << std::endl;
				saveConfig(fileName, configs.at(1));
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				std::string fileName = "ConfigLevelSelectAbility1.json";
				loadConfig(fileName);
				objectsList.at(5)->SetPosition(glm::vec3(configs.at(1)->posX, configs.at(1)->posY, 0));
				objectsList.at(5)->SetSize(configs.at(1)->width, -configs.at(1)->height);
				
			}
			ImGui::InputFloat("PosX", &configs.at(1)->posX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &configs.at(1)->posY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &configs.at(1)->offSetX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &configs.at(1)->offSetY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Width", &configs.at(1)->width, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Height", &configs.at(1)->height, 1.0f, 1.0f, "%.2f");
			ImGui::EndTabItem();
		}
		
		if (ImGui::BeginTabItem("Config Ability top")) {
			if (ImGui::Button("Save config")) {
				std::string fileName = "ConfigLevelSelectAbility2.json";
				std::cout << "save config1" << std::endl;
				saveConfig(fileName, configs.at(2));
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				std::string fileName = "ConfigLevelSelectAbility2.json";
				loadConfig(fileName);
				int axisX = 1;
				for (int i = 0; i < AbilityIconListTop.size(); i++) {
					AbilityIconListTop.at(i)->SetPosition(glm::vec3(configs.at(2)->posX + (configs.at(2)->offSetX * axisX), configs.at(2)->posY, 0));
					AbilityIconListTop.at(i)->SetSize(configs.at(2)->width, -configs.at(2)->height);
					axisX++;
				}

			}
			ImGui::InputFloat("PosX", &configs.at(2)->posX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &configs.at(2)->posY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &configs.at(2)->offSetX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &configs.at(2)->offSetY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Width", &configs.at(2)->width, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Height", &configs.at(2)->height, 1.0f, 1.0f, "%.2f");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Config Ability Down")) {
			if (ImGui::Button("Save config")) {
				std::string fileName = "ConfigLevelSelectAbility3.json";
				std::cout << "save config1" << std::endl;
				saveConfig(fileName, configs.at(3));
			}

			ImGui::SameLine();
			if (ImGui::Button("Load config")) {
				std::string fileName = "ConfigLevelSelectAbility3.json";
				loadConfig(fileName);
				int axisX = 1;
				for (int i = 0; i < AbilityIconListDown.size(); i++) {
					AbilityIconListDown.at(i)->SetPosition(glm::vec3(configs.at(3)->posX + (configs.at(3)->offSetX * axisX), configs.at(3)->posY, 0));
					AbilityIconListDown.at(i)->SetSize(configs.at(3)->width, -configs.at(3)->height);
					axisX++;
				}

			}
			ImGui::InputFloat("PosX", &configs.at(3)->posX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("PosY", &configs.at(3)->posY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetX", &configs.at(3)->offSetX, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("OffSetY", &configs.at(3)->offSetY, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Width", &configs.at(3)->width, 1.0f, 1.0f, "%.2f");
			ImGui::InputFloat("Height", &configs.at(3)->height, 1.0f, 1.0f, "%.2f");
			ImGui::EndTabItem();
		}


		ImGui::EndTabBar();
	}
	

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

	//cout << "Free Level" << endl;
}

void LevelSelectAbility::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//cout << "Unload Level" << endl;
}

void LevelSelectAbility::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY){}
void LevelSelectAbility::HandleKey(char key){}
void LevelSelectAbility::HandleMouse(int type, int x, int y){}

void LevelSelectAbility::abilityToFile(const std::string& fileName, int who) {

	std::ofstream file(fileName);
	nlohmann::json data;
	data["ability0"] = playerAbility[who][0];
	data["ability1"] = playerAbility[who][1];
	data["ability2"] = playerAbility[who][2];

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

