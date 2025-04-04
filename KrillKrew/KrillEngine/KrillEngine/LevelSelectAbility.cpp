#include "LevelSelectAbility.h"

void LevelSelectAbility::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	spriteList["Xoey_UI"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	spriteList["Byssa_UI"] = SpritesheetInfo("Byssa_UI", "../Resource/Texture/byssa.png", 430, 220, 430, 220);
	spriteList["Crunk_UI"] = SpritesheetInfo("Crunk_UI", "../Resource/Texture/crunk.png", 430, 220, 430, 220);
	spriteList["Ham_UI"] = SpritesheetInfo("Ham_UI", "../Resource/Texture/Ham.png", 430, 220, 430, 220);
	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Bomb_icon.png", 256, 256, 256, 256);
	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Trap.png", 512, 512, 512, 512);
	spriteList["Dash"] = SpritesheetInfo("Dash", "../Resource/Texture/Dash.png", 360, 340, 360, 340);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/TNT.png", 348, 348, 348, 348);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/EnderPearl.png", 512, 512, 512, 512);
	spriteList["Bola"] = SpritesheetInfo("Bola", "../Resource/Texture/Bola.png", 317, 314, 317, 314);
	spriteList["Cleave"] = SpritesheetInfo("Cleave", "../Resource/Texture/Cleave.png", 647, 386, 647, 386);
	spriteList["Xoey_Check"] = SpritesheetInfo("Xoey_Check", "../Resource/Texture/Xoeycheck.png", 256, 256, 256, 256);
	spriteList["Byssa_Check"] = SpritesheetInfo("Byssa_Check", "../Resource/Texture/Byssacheck.png", 256, 256, 256, 256);
	spriteList["Crunk_Check"] = SpritesheetInfo("Crunk_Check", "../Resource/Texture/Crunkcheck.png", 256, 256, 256, 256);
	spriteList["Ham_Check"] = SpritesheetInfo("Ham_Check", "../Resource/Texture/Hamcheck.png", 256, 256, 256, 256);
}

void LevelSelectAbility::LevelInit()
{
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	// player ui
	UiObject* uiSkills = new UiObject();
	uiSkills->SetSpriteInfo(spriteList.find("Xoey_UI")->second);
	uiSkills->setNumOwner(0);
	objectsList.push_back(uiSkills);
	UiObject* uiSkills2 = new UiObject();
	uiSkills2->SetSpriteInfo(spriteList.find("Byssa_UI")->second);
	uiSkills2->setNumOwner(1);
	objectsList.push_back(uiSkills2);
	UiObject* uiSkills3 = new UiObject();
	uiSkills3->SetSpriteInfo(spriteList.find("Crunk_UI")->second);
	uiSkills3->setNumOwner(2);
	objectsList.push_back(uiSkills3);
	UiObject* uiSkills4 = new UiObject();
	uiSkills4->SetSpriteInfo(spriteList.find("Ham_UI")->second);
	uiSkills4->setNumOwner(3);
	objectsList.push_back(uiSkills4);

	// player select
	PlayerObject* p1 = new PlayerObject();
	p1->SetSpriteInfo(spriteList.find("Xoey_Check")->second);
	p1->SetPlayerNumber(0);
	p1->SetPosition(glm::vec3(posX + uiWidth + posX / playerNumber - 1, uiHeight * 2 + 50, 0));
	objectsList.push_back(p1);
	players[0] = p1;
	PlayerObject* p2 = new PlayerObject();
	p2->SetSpriteInfo(spriteList.find("Byssa_Check")->second);
	p2->SetPlayerNumber(1);
	p2->SetPosition(glm::vec3(posX + uiWidth + posX / playerNumber - 1, uiHeight * 2 + 50, 0));
	objectsList.push_back(p2);
	players[1] = p2;
	PlayerObject* p3 = new PlayerObject();
	p3->SetSpriteInfo(spriteList.find("Crunk_Check")->second);
	p3->SetPlayerNumber(2);
	p3->SetPosition(glm::vec3(posX + uiWidth + posX / playerNumber - 1, uiHeight * 2 + 50, 0));
	objectsList.push_back(p3);
	players[2] = p3;
	PlayerObject* p4 = new PlayerObject();
	p4->SetSpriteInfo(spriteList.find("Ham_Check")->second);
	p4->SetPlayerNumber(3);
	p4->SetPosition(glm::vec3(posX + uiWidth + posX / playerNumber - 1, uiHeight * 2 + 50, 0));
	objectsList.push_back(p4);
	players[3] = p4;

	// skill
	UiObject* bomb = new UiObject();
	bomb->SetSpriteInfo(spriteList.find("Bomb")->second);
	bomb->setNumOwner(5);
	objectsList.push_back(bomb);
	UiObject* Trap = new UiObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->setNumOwner(5);
	objectsList.push_back(Trap);
	UiObject* Dash = new UiObject();
	Dash->SetSpriteInfo(spriteList.find("Dash")->second);
	Dash->setNumOwner(5);
	objectsList.push_back(Dash);
	UiObject* TNT = new UiObject();
	TNT->SetSpriteInfo(spriteList.find("TNT")->second);
	TNT->setNumOwner(5);
	objectsList.push_back(TNT);
	UiObject* Teleport = new UiObject();
	Teleport->SetSpriteInfo(spriteList.find("Teleport")->second);
	Teleport->setNumOwner(5);
	objectsList.push_back(Teleport);
	UiObject* Bola = new UiObject();
	Bola->SetSpriteInfo(spriteList.find("Bola")->second);
	Bola->setNumOwner(5);
	objectsList.push_back(Bola);
	UiObject* Cleave = new UiObject();
	Cleave->SetSpriteInfo(spriteList.find("Cleave")->second);
	Cleave->setNumOwner(5);
	objectsList.push_back(Cleave);
	

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
	ImGui_ImplSDL2_InitForOpenGL(GameEngine::GetInstance()->GetSDLWindow(), GameEngine::GetInstance()->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	std::cout << GameEngine::GetInstance()->GetStateController()->loadingState << std::endl;
	//std::ofstream MyFile("Ability.txt");
	//std::ofstream abilityFile("Ability.txt");
	for (int i = 0; i < 4; i++)
	{
		std::string fileName = "Ability" + std::to_string(i) + ".txt";
		std::ofstream abilityFile(fileName);
		abilityFile.close();
	}
}

void LevelSelectAbility::LevelUpdate()
{
	UpdateInput();
	players[1]->SetPosition(glm::vec3(posX + uiWidth + posX / playerNumber - 1, uiHeight * 2 + 50, 0));
	players[2]->SetPosition(glm::vec3(posX + uiWidth + posX / playerNumber - 1, uiHeight * 2 + 50, 0));
	players[3]->SetPosition(glm::vec3(posX + uiWidth + posX / playerNumber - 1, uiHeight * 2 + 50, 0));
	UpdateUi();
}

void LevelSelectAbility::UpdateInput()
{
	
	if (SDL_NumJoysticks() > 0)
	{

		Joystick::Update();
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			std::string fileName = "Ability" + std::to_string(i) + ".txt";
			float axisX = Joystick::GetAxis(i, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
			float axisY = Joystick::GetAxis(i, Joystick::Axis::LeftStickVertical) / 32768.0f;
			float norAxisX = 0;
			float norAxisY = 0;

			bool isPositiveX;
			bool isPositiveY;

			if (abs(axisX) < 0.1)
			{
				norAxisX = 0;
			}
			else
			{
				float axis = atan2(axisY, axisX);
				norAxisX = cos(axis);
			}

			if (abs(axisY) < 0.1)
			{
				norAxisY = 0;
			}
			else
			{
				float axis = atan2(axisY, axisX);
				norAxisY = sin(axis);
			}

			if (axisX > 0)
			{
				isPositiveX = true;
			}
			else if (axisX <= 0)
			{
				isPositiveX = false;
			}

			if (axisY > 0)
			{
				isPositiveY = false;
			}
			else if (axisY < 0)
			{
				isPositiveY = true;
			}

			//if (norAxisX != 0 && norAxisY != 0) {
			//	if (isPositiveX)
			//	{
			//		players[0]->SetPosition(glm::vec3(players[0]->getPos().x * 2, players[0]->getPos().y, 0));
			//		/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x + (posX + uiWidth + posX / playerNumber - 1), players[1]->getPos().y, 0));
			//		players[2]->SetPosition(glm::vec3(players[2]->getPos().x + (posX + uiWidth + posX / playerNumber - 1), players[2]->getPos().y, 0));
			//		players[3]->SetPosition(glm::vec3(players[3]->getPos().x + (posX + uiWidth + posX / playerNumber - 1), players[3]->getPos().y, 0));*/
			//		std::cout << "x" << i << std::endl;
			//	}
			//	else if (!isPositiveX)
			//	{
			//		players[0]->SetPosition(glm::vec3(players[0]->getPos().x - (posX + uiWidth + posX / playerNumber - 1), players[0]->getPos().y, 0));
			//		/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x - (posX + uiWidth + posX / playerNumber - 1), players[1]->getPos().y, 0));
			//		players[2]->SetPosition(glm::vec3(players[2]->getPos().x - (posX + uiWidth + posX / playerNumber - 1), players[2]->getPos().y, 0));
			//		players[3]->SetPosition(glm::vec3(players[3]->getPos().x - (posX + uiWidth + posX / playerNumber - 1), players[3]->getPos().y, 0));*/
			//		std::cout << "-x" << i << std::endl;
			//	}
			//	if (isPositiveY)
			//	{
			//		players[0]->SetPosition(glm::vec3(players[0]->getPos().x, players[0]->getPos().y + (uiHeight * 2 + 50), 0));
			//		/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x, players[1]->getPos().y + (uiHeight * 2 + 50), 0));
			//		players[2]->SetPosition(glm::vec3(players[2]->getPos().x, players[2]->getPos().y + (uiHeight * 2 + 50), 0));
			//		players[3]->SetPosition(glm::vec3(players[3]->getPos().x, players[3]->getPos().y + (uiHeight * 2 + 50), 0));*/
			//		std::cout << "y" << i << std::endl;
			//	}
			//	else if (!isPositiveY)
			//	{
			//		players[0]->SetPosition(glm::vec3(players[0]->getPos().x, players[0]->getPos().y - (uiHeight * 2 + 50), 0));
			//		/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x, players[1]->getPos().y - (uiHeight * 2 + 50), 0));
			//		players[2]->SetPosition(glm::vec3(players[2]->getPos().x, players[2]->getPos().y - (uiHeight * 2 + 50), 0));
			//		players[3]->SetPosition(glm::vec3(players[3]->getPos().x, players[3]->getPos().y - (uiHeight * 2 + 50), 0));*/
			//		std::cout << "-y" << i << std::endl;
			//	}
			//}

			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Left))
			{
				players[0]->SetPosition(glm::vec3(players[0]->getPos().x - (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH + uiWidth), players[0]->getPos().y, 0));
				/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x + (posX + uiWidth + posX / playerNumber - 1), players[1]->getPos().y, 0));
				players[2]->SetPosition(glm::vec3(players[2]->getPos().x + (posX + uiWidth + posX / playerNumber - 1), players[2]->getPos().y, 0));
				players[3]->SetPosition(glm::vec3(players[3]->getPos().x + (posX + uiWidth + posX / playerNumber - 1), players[3]->getPos().y, 0));*/
				std::cout << "x" << i << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Right))
			{
				players[0]->SetPosition(glm::vec3(players[0]->getPos().x + (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH + uiWidth), players[0]->getPos().y, 0));
				/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x - (posX + uiWidth + posX / playerNumber - 1), players[1]->getPos().y, 0));
				players[2]->SetPosition(glm::vec3(players[2]->getPos().x - (posX + uiWidth + posX / playerNumber - 1), players[2]->getPos().y, 0));
				players[3]->SetPosition(glm::vec3(players[3]->getPos().x - (posX + uiWidth + posX / playerNumber - 1), players[3]->getPos().y, 0));*/
				std::cout << "-x" << i << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Up))
			{
				players[0]->SetPosition(glm::vec3(players[0]->getPos().x, players[0]->getPos().y + (uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT + (uiHeight / 2)), 0));
				/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x, players[1]->getPos().y + (uiHeight * 2 + 50), 0));
				players[2]->SetPosition(glm::vec3(players[2]->getPos().x, players[2]->getPos().y + (uiHeight * 2 + 50), 0));
				players[3]->SetPosition(glm::vec3(players[3]->getPos().x, players[3]->getPos().y + (uiHeight * 2 + 50), 0));*/
				std::cout << "y" << i << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Down))
			{
				players[0]->SetPosition(glm::vec3(players[0]->getPos().x, players[0]->getPos().y - (uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT + (uiHeight / 2)), 0));
				/*players[1]->SetPosition(glm::vec3(players[1]->getPos().x, players[1]->getPos().y - (uiHeight * 2 + 50), 0));
				players[2]->SetPosition(glm::vec3(players[2]->getPos().x, players[2]->getPos().y - (uiHeight * 2 + 50), 0));
				players[3]->SetPosition(glm::vec3(players[3]->getPos().x, players[3]->getPos().y - (uiHeight * 2 + 50), 0));*/
				std::cout << "-y" << i << std::endl;
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::R1)) {
				std::cout << "Pos playerX " << players[i]->getPos().x << std::endl;//189.125 240.875
				std::cout << "Pos playerY " << players[i]->getPos().y << std::endl;//250 100 -50 -200
				std::cout << "wantX " << posX + uiWidth << std::endl;//-107.5
				std::cout << "wantX2 " << posX + uiWidth + (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH + uiWidth) << std::endl;//332.5

				if (players[i]->getPos().x < 240.875 &&
					players[i]->getPos().y == 250) {
					abilityToFile(fileName, PlayerObject::Ability::Fireball, i);
				}

				if (players[i]->getPos().x >= 240.875 &&
					players[i]->getPos().y == 250) {
					abilityToFile(fileName, PlayerObject::Ability::Trap, i);
				}

				if (players[i]->getPos().x < 240.875 &&
					players[i]->getPos().y == 100) {
					abilityToFile(fileName, PlayerObject::Ability::Dash, i);
				}

				if (players[i]->getPos().x >= 240.875 &&
					players[i]->getPos().y == 100) {
					abilityToFile(fileName, PlayerObject::Ability::TNT, i);
				}

				if (players[i]->getPos().x < 240.875 &&
					players[i]->getPos().y == -50) {
					abilityToFile(fileName, PlayerObject::Ability::Teleport, i);
				}

				if (players[i]->getPos().x >= 240.875 &&
					players[i]->getPos().y == -50) {
					abilityToFile(fileName, PlayerObject::Ability::Bola, i);
				}

				if (players[i]->getPos().x < 240.875 &&
					players[i]->getPos().y == -200) {
					abilityToFile(fileName, PlayerObject::Ability::Cleave, i);
				}
			}
		}
	}
}

void LevelSelectAbility::UpdateUi() {
	//Player Ui
	float posXPlayerUi = posX - 200;
	float posYPlayerUi = posY;
	float posXSkillUi = posX + uiWidth;
	float posYSkillUi = posY + 50;
	float posXPlayerSelect[4];
	float posYPlayerSelect[4];
	for (int i = 0; i < 4; i++) {
		posXPlayerSelect[i] = players[i]->getPos().x;
		posYPlayerSelect[i] = players[i]->getPos().y;
		for (int j = 0; j < 4; j++) {
			if (i != j) {
				if (posXPlayerSelect[i] == posXPlayerSelect[j] && posYPlayerSelect[i] == posYPlayerSelect[j]) {
					posXPlayerSelect[i] += (uiWidth / playerNumber) * camera.GetCameraWidth() / SCREEN_WIDTH;
					//std::cout << "move" << i << std::endl;
				}
			}
		}
	}
	

	for (int i = 0; i < objectsList.size(); i++)
	{
		UiObject* ui = dynamic_cast<UiObject*>(objectsList[i]);
		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		if (ui != nullptr)
		{
			if (ui->getNumOwner() < 5) {
				ui->SetPosition(glm::vec3(posXPlayerUi, posYPlayerUi, 0));
				ui->SetSize(uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);
				posYPlayerUi -= uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT;
			}
			else {
				ui->SetPosition(glm::vec3(posXSkillUi, posYSkillUi, 0));
				ui->SetSize(uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);
				posXSkillUi += uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH + uiWidth;
				if (posXSkillUi > camera.GetCameraWidth() / 2) {
					posXSkillUi = posX + uiWidth;
					posYSkillUi -= uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT + (uiHeight / 2);
				}
			}
		}
		if (player != nullptr) {
			player->SetPosition(glm::vec3(posXPlayerSelect[player->GetPlayerNumber()], posYPlayerSelect[player->GetPlayerNumber()], 0));
			player->SetSize((uiWidth / playerNumber) * camera.GetCameraWidth() / SCREEN_WIDTH, (-uiHeight / playerNumber)* camera.GetCameraHeight() / SCREEN_HEIGHT);
			
			// debug will delete
			if (player->GetPlayerNumber() == 0) {
				if (posXPlayerSelect[0] > -(posX + uiWidth + posX / playerNumber - 1) + (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH + uiWidth)) {
					posXPlayerSelect[0] = posX + uiWidth + posX / playerNumber - 1;
					std::cout << "> posX" << std::endl;
				}
				else if (posXPlayerSelect[0] < (posX + uiWidth + posX / playerNumber - 1)) {
					posXPlayerSelect[0] = (posX + uiWidth + posX / playerNumber - 1) + (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH + uiWidth);
					std::cout << "< posX" << std::endl;
				}

				if (posYPlayerSelect[0] > uiHeight * 2 + 50) {
					posYPlayerSelect[0] = uiHeight * 2 + 50 - (uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT + (uiHeight / 2)) * 3;
					std::cout << "> posY" << std::endl;
				}
				else if (posYPlayerSelect[0] < uiHeight * 2 + 50 - (uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT + (uiHeight / 2)) * 3) {
					posYPlayerSelect[0] = uiHeight * 2 + 50;
					std::cout << "< posY" << std::endl;
				}

				if (posXPlayerSelect[0] == (posX + uiWidth + posX / playerNumber - 1) + (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH + uiWidth) && 
					posYPlayerSelect[0] == uiHeight * 2 + 50 - (uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT + (uiHeight / 2)) * 3){
					posXPlayerSelect[0] = posX + uiWidth + posX / playerNumber - 1;
					std::cout << "last" << std::endl;
				}

				player->SetPosition(glm::vec3(posXPlayerSelect[0], posYPlayerSelect[0], 0));
			}
			

		}
	}
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
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
	}

	for (int i = 0; i < 4; i++)
	{
		std::string fileName = "Ability" + std::to_string(i) + ".txt";
		std::string buttonName;
		ImGui::SeparatorText("");
		ImGui::Text("Ability Player %d", i);

		buttonName = "FireBall##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Fireball, i);
		}

		ImGui::SameLine();
		buttonName = "Trap##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Trap, i);
		}

		ImGui::SameLine();
		buttonName = "Dash##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Dash, i);
		}

		ImGui::SameLine();
		buttonName = "TNT##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::TNT, i);
		}

		buttonName = "Teleport##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Teleport, i);
		}

		ImGui::SameLine();
		buttonName = "Bola##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Bola, i);
		}
		ImGui::SameLine();
		buttonName = "Cleave##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Cleave, i);
		}

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

void LevelSelectAbility::abilityToFile(const std::string& fileName, PlayerObject::Ability abilityId, int who) {
	std::ifstream readFile(fileName);
	std::string oldContent[3];
	std::string line;
	clicked[who]++;
	int count = 0;
	int num;
	while (std::getline(readFile, line)) {
		oldContent[count] += line + "\n";
		count++;
		std::cout << "have content" << std::endl;
	}
	//std::getline(readFile, oldContent);
	readFile.close();

	std::ofstream abilityFile(fileName);
	std::cout << clicked[who] << std::endl;
	if (clicked[who] > 3) {
		if (clicked[who] % 3 == 0) {
			num = static_cast<int>(abilityId);
			oldContent[2] = std::to_string(num) + "\n";
			std::cout << "new ablity 3" << std::endl;
			playerAbility[who][2] = static_cast<int>(abilityId);
		}
		else if (clicked[who] % 3 == 1) {
			num = static_cast<int>(abilityId);
			oldContent[0] = std::to_string(num) + "\n";
			std::cout << "new ablity 1" << std::endl;
			playerAbility[who][0] = static_cast<int>(abilityId);
		}
		else if (clicked[who] % 3 == 2) {
			num = static_cast<int>(abilityId);
			oldContent[1] = std::to_string(num) + "\n";
			std::cout << "new ablity 2" << std::endl;
			playerAbility[who][1] = static_cast<int>(abilityId);
		}
		for (int i = 0; i < count; i++) {
			abilityFile << oldContent[i];
		}
		abilityFile.close();
	}
	else {
		for (int i = 0; i < count; i++) {
			abilityFile << oldContent[i];
			playerAbility[who][i] = stoi(oldContent[i]);
		}
		abilityFile << static_cast<int>(abilityId);
		if (count < 4) {
			playerAbility[who][count] = static_cast<int>(abilityId);
		}
		abilityFile.close();
	}
	
}

