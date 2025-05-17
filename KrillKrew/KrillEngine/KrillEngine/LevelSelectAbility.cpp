#include "LevelSelectAbility.h"

void LevelSelectAbility::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	spriteList["BG"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/BG_Selection.png", 1920, 1080, 1920, 1080);

	spriteList["Xoey_UI"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/PlayerWindow.png", 310, 376, 1240, 376);
	spriteList["Byssa_UI"] = SpritesheetInfo("Byssa_UI", "../Resource/Texture/PlayerWindow.png", 310, 376, 1240, 376);
	spriteList["Crunk_UI"] = SpritesheetInfo("Crunk_UI", "../Resource/Texture/PlayerWindow.png", 310, 376, 1240, 376);
	spriteList["Ham_UI"] = SpritesheetInfo("Ham_UI", "../Resource/Texture/PlayerWindow.png", 310, 376, 1240, 376);

	spriteList["Xoey_Icon"] = SpritesheetInfo("Xoey_Icon", "../Resource/Texture/PlayerIcon.png", 125, 120, 500, 120);
	spriteList["Byssa_Icon"] = SpritesheetInfo("Byssa_Icon", "../Resource/Texture/PlayerIcon.png", 125, 120, 500, 120);
	spriteList["Crunk_Icon"] = SpritesheetInfo("Crunk_Icon", "../Resource/Texture/PlayerIcon.png", 125, 120, 500, 120);
	spriteList["Ham_Icon"] = SpritesheetInfo("Ham_Icon", "../Resource/Texture/PlayerIcon.png", 125, 120, 500, 120);

	spriteList["Xoey_Check"] = SpritesheetInfo("Xoey_Check", "../Resource/Texture/PlayerAbilityHover.png", 450, 283, 1800, 283);
	spriteList["Byssa_Check"] = SpritesheetInfo("Byssa_Check", "../Resource/Texture/PlayerAbilityHover.png",  450, 283, 1800, 283);
	spriteList["Crunk_Check"] = SpritesheetInfo("Crunk_Check", "../Resource/Texture/PlayerAbilityHover.png", 450, 283, 1800, 283);
	spriteList["Ham_Check"] = SpritesheetInfo("Ham_Check", "../Resource/Texture/PlayerAbilityHover.png", 450, 283, 1800, 283);

	spriteList["SkillIconBox"] = SpritesheetInfo("SkillIconBox", "../Resource/Texture/SkillIconBox.png", 167, 157, 334, 157);
	spriteList["NoSkill"] = SpritesheetInfo("NoSkill", "../Resource/Texture/NOskill.png", 272, 281, 272, 281);

	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Icon_Bomb.png", 272, 281, 272, 281);
	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Icon_Jellyfish.png", 272, 281, 272, 281);
	spriteList["Dash"] = SpritesheetInfo("Dash", "../Resource/Texture/Icon_Dash.png", 272, 281, 272, 281);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/Icon_Landmine.png", 272, 281, 272, 281);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/EnderPearl.png", 512, 512, 512, 512);
	spriteList["Bola"] = SpritesheetInfo("Bola", "../Resource/Texture/Icon_Bola.png", 272, 281, 272, 281);
	spriteList["Cleave"] = SpritesheetInfo("Cleave", "../Resource/Texture/Cleave.png", 647, 386, 647, 386);
	spriteList["WaterBall"] = SpritesheetInfo("WaterBall", "../Resource/Texture/WaterBall_Icon.png", 272, 281, 272, 281);

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

	int playerUiX = -400;
	int playerUiY = 100;

	// player ui
	UiObject* uiSkills = new UiObject();
	uiSkills->SetSpriteInfo(spriteList.find("Xoey_UI")->second);
	uiSkills->GetSpriteRenderer()->ShiftTo(uiSkills->GetSpriteRenderer()->GetRow(), 0);
	uiSkills->SetSize(uiSkills->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -uiSkills->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	uiSkills->SetPosition(glm::vec3(playerUiX, playerUiY, 0));
	uiSkills->setNumOwner(0);
	objectsList.push_back(uiSkills);

	UiObject* uiSkills2 = new UiObject();
	uiSkills2->SetSpriteInfo(spriteList.find("Byssa_UI")->second);
	uiSkills2->GetSpriteRenderer()->ShiftTo(uiSkills2->GetSpriteRenderer()->GetRow(), 1);
	uiSkills2->SetSize(uiSkills2->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -uiSkills2->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	uiSkills2->SetPosition(glm::vec3(playerUiX + uiSkills2->GetSpriteRenderer()->GetSpriteWidth() / 1.5 , playerUiY, 0));
	uiSkills2->setNumOwner(1);
	objectsList.push_back(uiSkills2);

	UiObject* uiSkills3 = new UiObject();
	uiSkills3->SetSpriteInfo(spriteList.find("Crunk_UI")->second);
	uiSkills3->GetSpriteRenderer()->ShiftTo(uiSkills3->GetSpriteRenderer()->GetRow(), 2);
	uiSkills3->SetSize(uiSkills3->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -uiSkills3->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	uiSkills3->SetPosition(glm::vec3(playerUiX , playerUiY - uiSkills3->GetSpriteRenderer()->GetSheetHeight() / 1.5, 0));
	uiSkills3->setNumOwner(2);
	objectsList.push_back(uiSkills3);

	UiObject* uiSkills4 = new UiObject();
	uiSkills4->SetSpriteInfo(spriteList.find("Ham_UI")->second);
	uiSkills4->GetSpriteRenderer()->ShiftTo(uiSkills4->GetSpriteRenderer()->GetRow(), 3);
	uiSkills4->SetSize(uiSkills4->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -uiSkills4->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	uiSkills4->SetPosition(glm::vec3(playerUiX + uiSkills4->GetSpriteRenderer()->GetSpriteWidth() / 1.5, playerUiY - uiSkills4->GetSpriteRenderer()->GetSheetHeight() / 1.5, 0));
	uiSkills4->setNumOwner(3);
	objectsList.push_back(uiSkills4);

	// player icon
	UiObject* playerIcon = new UiObject();
	playerIcon->SetSpriteInfo(spriteList.find("Xoey_Icon")->second);
	playerIcon->GetSpriteRenderer()->ShiftTo(playerIcon->GetSpriteRenderer()->GetRow(), 0);
	playerIcon->SetSize(playerIcon->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -playerIcon->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	playerIcon->SetPosition(glm::vec3(playerUiX, playerUiY, 0));
	playerIcon->setNumOwner(0);
	objectsList.push_back(playerIcon);
	playerIconList.push_back(playerIcon);

	UiObject* playerIcon2 = new UiObject();
	playerIcon2->SetSpriteInfo(spriteList.find("Xoey_Icon")->second);
	playerIcon2->GetSpriteRenderer()->ShiftTo(playerIcon2->GetSpriteRenderer()->GetRow(), 0);
	playerIcon2->SetSize(playerIcon2->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -playerIcon2->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	playerIcon2->SetPosition(glm::vec3(playerUiX + uiSkills2->GetSpriteRenderer()->GetSpriteWidth() / 1.5, playerUiY, 0));
	playerIcon2->setNumOwner(1);
	objectsList.push_back(playerIcon2);
	playerIconList.push_back(playerIcon2);

	UiObject* playerIcon3 = new UiObject();
	playerIcon3->SetSpriteInfo(spriteList.find("Xoey_Icon")->second);
	playerIcon3->GetSpriteRenderer()->ShiftTo(playerIcon3->GetSpriteRenderer()->GetRow(), 0);
	playerIcon3->SetSize(playerIcon3->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -playerIcon3->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	playerIcon3->SetPosition(glm::vec3(playerUiX, playerUiY - uiSkills3->GetSpriteRenderer()->GetSheetHeight() / 1.5, 0));
	playerIcon3->setNumOwner(2);
	objectsList.push_back(playerIcon3);
	playerIconList.push_back(playerIcon3);

	UiObject* playerIcon4 = new UiObject();
	playerIcon4->SetSpriteInfo(spriteList.find("Xoey_Icon")->second);
	playerIcon4->GetSpriteRenderer()->ShiftTo(playerIcon4->GetSpriteRenderer()->GetRow(), 0);
	playerIcon4->SetSize(playerIcon4->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -playerIcon4->GetSpriteRenderer()->GetSheetHeight() / 1.5);
	playerIcon4->SetPosition(glm::vec3(playerUiX + uiSkills4->GetSpriteRenderer()->GetSpriteWidth() / 1.5, playerUiY - uiSkills4->GetSpriteRenderer()->GetSheetHeight() / 1.5, 0));
	playerIcon4->setNumOwner(3);
	objectsList.push_back(playerIcon4);
	playerIconList.push_back(playerIcon4);

	// skill Box
	UiObject* box[8];
	int boxPosX = 30;
	int boxPosY = 35;
	int axisX = 0;
	int axisY = 0;
	int offsetX = 30;
	int offsetY = 50;
	for (int i = 0; i < 8; i++) {
		box[i] = new UiObject();
		box[i]->SetSpriteInfo(spriteList.find("SkillIconBox")->second);
		box[i]->SetSize(box[i]->GetSpriteRenderer()->GetSpriteWidth() / 1.5, -box[i]->GetSpriteRenderer()->GetSpriteHeight() / 1.5);
		box[i]->SetPosition(glm::vec3(boxPosX + (offsetX + box[i]->GetSpriteRenderer()->GetSpriteWidth() / 1.5) * axisX,
									  boxPosY + (offsetY + box[i]->GetSpriteRenderer()->GetSpriteHeight() / 1.5) * axisY, 0));
		objectsList.push_back(box[i]);
		SkillBoxList.push_back(box[i]);
		axisX++;
		if (axisX > 3) {
			axisX = 0;
			axisY--;
		}
		
	}
	
	// For no icon
	float iconWidth = 129.524;
	float iconHeight = -133.81;

	UiObject* bomb = new UiObject();
	bomb->SetSpriteInfo(spriteList.find("Bomb")->second);
	bomb->SetSize(bomb->GetSpriteRenderer()->GetSpriteWidth() / 2.1, -bomb->GetSpriteRenderer()->GetSpriteHeight() / 2.1);
	bomb->SetPosition(glm::vec3(box[0]->getPos().x, box[0]->getPos().y, 0));
	objectsList.push_back(bomb);
	std::cout << "X : " << bomb->GetSpriteRenderer()->GetSpriteWidth() / 2.1 << " Y : " << -bomb->GetSpriteRenderer()->GetSpriteHeight() / 2.1 << std::endl;

	UiObject* TNT = new UiObject();
	TNT->SetSpriteInfo(spriteList.find("TNT")->second);
	TNT->SetSize(TNT->GetSpriteRenderer()->GetSpriteWidth() / 2.1, -TNT->GetSpriteRenderer()->GetSpriteHeight() / 2.1);
	TNT->SetPosition(glm::vec3(box[1]->getPos().x, box[1]->getPos().y, 0));
	objectsList.push_back(TNT);

	//Water Ball
	UiObject* WaterBall = new UiObject();
	WaterBall->SetSpriteInfo(spriteList.find("WaterBall")->second);
	WaterBall->SetSize(iconWidth / 1.3, iconHeight / 1.3);
	WaterBall->SetPosition(glm::vec3(box[2]->getPos().x, box[2]->getPos().y, 0));
	objectsList.push_back(WaterBall);

	UiObject* Cleave = new UiObject();
	Cleave->SetSpriteInfo(spriteList.find("Cleave")->second);
	Cleave->SetSize(iconWidth / 1.5, iconHeight / 1.5);
	Cleave->SetPosition(glm::vec3(box[3]->getPos().x, box[3]->getPos().y, 0));
	objectsList.push_back(Cleave);

	UiObject* Bola = new UiObject();
	Bola->SetSpriteInfo(spriteList.find("Bola")->second);
	Bola->SetSize(Bola->GetSpriteRenderer()->GetSpriteWidth() / 2.1, -Bola->GetSpriteRenderer()->GetSpriteHeight() / 2.1);
	Bola->SetPosition(glm::vec3(box[4]->getPos().x, box[4]->getPos().y, 0));
	objectsList.push_back(Bola);

	UiObject* Teleport = new UiObject();
	Teleport->SetSpriteInfo(spriteList.find("Teleport")->second);
	Teleport->SetSize(iconWidth / 1.5, iconHeight / 1.5);
	Teleport->SetPosition(glm::vec3(box[5]->getPos().x, box[5]->getPos().y, 0));
	objectsList.push_back(Teleport);

	UiObject* Trap = new UiObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->SetSize(Trap->GetSpriteRenderer()->GetSpriteWidth() / 2.1, -Trap->GetSpriteRenderer()->GetSpriteHeight() / 2.1);
	Trap->SetPosition(glm::vec3(box[6]->getPos().x, box[6]->getPos().y, 0));
	objectsList.push_back(Trap);

	UiObject* Dash = new UiObject();
	Dash->SetSpriteInfo(spriteList.find("Dash")->second);
	Dash->SetSize(Dash->GetSpriteRenderer()->GetSpriteWidth() / 2.1, -Dash->GetSpriteRenderer()->GetSpriteHeight() / 2.1);
	Dash->SetPosition(glm::vec3(box[7]->getPos().x, box[7]->getPos().y, 0));
	objectsList.push_back(Dash);

	// player hover
	PlayerObject* p1 = new PlayerObject();
	p1->SetSpriteInfo(spriteList.find("Xoey_Check")->second);
	p1->SetPlayerNumber(0);
	p1->SetSize(p1->GetSpriteRenderer()->GetSpriteWidth() / 12, -p1->GetSpriteRenderer()->GetSheetHeight() / 12);
	p1->SetPosition(glm::vec3(playerHoverPosX + box[0]->getPos().x, playerHoverPosY + box[0]->getPos().y, 0));
	p1->GetSpriteRenderer()->ShiftTo(p1->GetSpriteRenderer()->GetRow(), 0);
	objectsList.push_back(p1);
	playerHoverList.push_back(p1);
	players[0] = p1;

	PlayerObject* p2 = new PlayerObject();
	p2->SetSpriteInfo(spriteList.find("Byssa_Check")->second);
	p2->SetPlayerNumber(1);
	p2->SetSize(p2->GetSpriteRenderer()->GetSpriteWidth() / 12, -p2->GetSpriteRenderer()->GetSheetHeight() / 12);
	p2->SetPosition(glm::vec3(playerHoverPosX + box[0]->getPos().x, playerHoverPosY + box[0]->getPos().y, 0));
	p2->GetSpriteRenderer()->ShiftTo(p2->GetSpriteRenderer()->GetRow(), 1);
	objectsList.push_back(p2);
	playerHoverList.push_back(p2);
	players[1] = p2;

	PlayerObject* p3 = new PlayerObject();
	p3->SetSpriteInfo(spriteList.find("Crunk_Check")->second);
	p3->SetPlayerNumber(2);
	p3->SetSize(p3->GetSpriteRenderer()->GetSpriteWidth() / 12, -p3->GetSpriteRenderer()->GetSheetHeight() / 12);
	p3->SetPosition(glm::vec3(playerHoverPosX + box[0]->getPos().x, playerHoverPosY + box[0]->getPos().y, 0));
	p3->GetSpriteRenderer()->ShiftTo(p3->GetSpriteRenderer()->GetRow(), 2);
	objectsList.push_back(p3);
	playerHoverList.push_back(p3);
	players[2] = p3;

	PlayerObject* p4 = new PlayerObject();
	p4->SetSpriteInfo(spriteList.find("Ham_Check")->second);
	p4->SetPlayerNumber(3);
	p4->SetSize(p4->GetSpriteRenderer()->GetSpriteWidth() / 12, -p4->GetSpriteRenderer()->GetSheetHeight() / 12);
	p4->SetPosition(glm::vec3(playerHoverPosX + box[0]->getPos().x, playerHoverPosY + box[0]->getPos().y, 0));
	p4->GetSpriteRenderer()->ShiftTo(p4->GetSpriteRenderer()->GetRow(), 3);
	objectsList.push_back(p4);
	playerHoverList.push_back(p4);
	players[3] = p4;
	
	// player icon skill
	int ps1PosX = -52;
	int ps2PosX = 1;
	int ps3PosX = 54;
	int psPosY = -55;

	std::vector<UiObject*> p1List;
	UiObject* p1s1 = new UiObject();
	p1s1->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p1s1->SetSize(iconWidth / 5, iconHeight / 5);
	p1s1->SetPosition(glm::vec3(ps1PosX + uiSkills->getPos().x, psPosY + uiSkills->getPos().y, 0));
	p1List.push_back(p1s1);
	objectsList.push_back(p1s1);
	UiObject* p1s2 = new UiObject();
	p1s2->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p1s2->SetSize(iconWidth / 5, iconHeight / 5);
	p1s2->SetPosition(glm::vec3(ps2PosX + uiSkills->getPos().x, psPosY + uiSkills->getPos().y, 0));
	p1List.push_back(p1s2);
	objectsList.push_back(p1s2);
	UiObject* p1s3 = new UiObject();
	p1s3->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p1s3->SetSize(iconWidth / 5, iconHeight / 5);
	p1s3->SetPosition(glm::vec3(ps3PosX + uiSkills->getPos().x, psPosY + uiSkills->getPos().y, 0));
	p1List.push_back(p1s3);
	objectsList.push_back(p1s3);
	playerIconSkillList[0] = p1List;

	std::vector<UiObject*> p2List;
	UiObject* p2s1 = new UiObject();
	p2s1->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p2s1->SetSize(iconWidth / 5, iconHeight / 5);
	p2s1->SetPosition(glm::vec3(ps1PosX + uiSkills2->getPos().x, psPosY + uiSkills2->getPos().y, 0));
	p2List.push_back(p2s1);
	objectsList.push_back(p2s1);
	UiObject* p2s2 = new UiObject();
	p2s2->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p2s2->SetSize(iconWidth / 5, iconHeight / 5);
	p2s2->SetPosition(glm::vec3(ps2PosX + uiSkills2->getPos().x, psPosY + uiSkills2->getPos().y, 0));
	p2List.push_back(p2s2);
	objectsList.push_back(p2s2);
	UiObject* p2s3 = new UiObject();
	p2s3->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p2s3->SetSize(iconWidth / 5, iconHeight / 5);
	p2s3->SetPosition(glm::vec3(ps3PosX + uiSkills2->getPos().x, psPosY + uiSkills2->getPos().y, 0));
	p2List.push_back(p2s3);
	objectsList.push_back(p2s3);
	playerIconSkillList[1]= p2List;

	std::vector<UiObject*> p3List;
	UiObject* p3s1 = new UiObject();
	p3s1->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p3s1->SetSize(iconWidth / 5, iconHeight / 5);
	p3s1->SetPosition(glm::vec3(ps1PosX + uiSkills3->getPos().x, psPosY + uiSkills3->getPos().y, 0));
	p3List.push_back(p3s1);
	objectsList.push_back(p3s1);
	UiObject* p3s2 = new UiObject();
	p3s2->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p3s2->SetSize(iconWidth / 5, iconHeight / 5);
	p3s2->SetPosition(glm::vec3(ps2PosX + uiSkills3->getPos().x, psPosY + uiSkills3->getPos().y, 0));
	p3List.push_back(p3s2);
	objectsList.push_back(p3s2);
	UiObject* p3s3 = new UiObject();
	p3s3->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p3s3->SetSize(iconWidth / 5, iconHeight / 5);
	p3s3->SetPosition(glm::vec3(ps3PosX + uiSkills3->getPos().x, psPosY + uiSkills3->getPos().y, 0));
	p3List.push_back(p3s3);
	objectsList.push_back(p3s3);
	playerIconSkillList[2] = p3List;

	std::vector<UiObject*> p4List;
	UiObject* p4s1 = new UiObject();
	p4s1->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p4s1->SetSize(iconWidth / 5, iconHeight / 5);
	p4s1->SetPosition(glm::vec3(ps1PosX + uiSkills4->getPos().x, psPosY + uiSkills4->getPos().y, 0));
	p4List.push_back(p4s1);
	objectsList.push_back(p4s1);
	UiObject* p4s2 = new UiObject();
	p4s2->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p4s2->SetSize(iconWidth / 5, iconHeight / 5);
	p4s2->SetPosition(glm::vec3(ps2PosX + uiSkills4->getPos().x, psPosY + uiSkills4->getPos().y, 0));
	p4List.push_back(p4s2);
	objectsList.push_back(p4s2);
	UiObject* p4s3 = new UiObject();
	p4s3->SetSpriteInfo(spriteList.find("NoSkill")->second);
	p4s3->SetSize(iconWidth / 5, iconHeight / 5);
	p4s3->SetPosition(glm::vec3(ps3PosX + uiSkills4->getPos().x, psPosY + uiSkills4->getPos().y, 0));
	p4List.push_back(p4s3);
	objectsList.push_back(p4s3);
	playerIconSkillList[3] = p4List;

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
			/*std::cout << "axisX : " << axisX << std::endl;*/
			float axisY = Joystick::GetAxis(i, Joystick::Axis::LeftStickVertical) / 32768.0f;
			//std::cout << "axisY : " << axisY << std::endl;
			bool up = false ;
			bool down = false ;
			bool right = false ;
			bool left = false ;

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
			

			if (!playerMove[i]) {
				if (right || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Right))
				{
					if (playerWhere[i] == 3) {
						playerWhere[i] = 0;
					}

					else if (playerWhere[i] == 7) {
						playerWhere[i] = 4;
					}

					else {
						playerWhere[i] += 1;
					}
					playerMove[i] = true;
					std::cout << "x" << i << std::endl;
				}
				else if (left || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Left))
				{
					if (playerWhere[i] == 0) {
						playerWhere[i] = 3;
					}

					else if (playerWhere[i] == 4) {
						playerWhere[i] = 7;
					}

					else {
						playerWhere[i] -= 1;
					}
					playerMove[i] = true;
					std::cout << "-x" << i << std::endl;
				}
				else if (up || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Up))
				{
					playerWhere[i] -= 4;
					if (playerWhere[i] < 0) {
						playerWhere[i] += 8;
					}
					playerMove[i] = true;
					std::cout << "y" << i << std::endl;
				}
				else if (down || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Down))
				{
					playerWhere[i] += 4;
					if (playerWhere[i] > 7 ) {
						playerWhere[i] -= 8;
					}
					playerMove[i] = true;
					std::cout << "-y" << i << std::endl;
				}
			}

			if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
				playerMove[i] = false;
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::Cross)) {
				std::cout << "Pos playerX " << players[i]->getPos().y << std::endl;//90
				std::cout << "Pos playerY " << SkillBoxList.at(4)->getPos().y + playerHoverPosY << std::endl;//70 0.75
				bool press = false;
				if (players[i]->getPos().x == SkillBoxList.at(0)->getPos().x + playerHoverPosX &&
					players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3){
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Fireball) && !press) {
							playerAbility[i][j] = -1;
							press = true;
						}
					}
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == -1 && !press) {
							playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Fireball);
							press = true;
						}
					}
					//abilityToFile(fileName, PlayerObject::Ability::Fireball, i);
				}

				if (players[i]->getPos().x == SkillBoxList.at(1)->getPos().x + playerHoverPosX &&
					players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3) {
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::TNT) && !press) {
							playerAbility[i][j] = -1;
							press = true;
						}
					}
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == -1 && !press) {
							playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::TNT);
							press = true;
						}
					}
					//abilityToFile(fileName, PlayerObject::Ability::TNT, i);
				}

				if (players[i]->getPos().x == SkillBoxList.at(2)->getPos().x + playerHoverPosX &&
					players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3) {
					//bilityToFile(fileName, PlayerObject::Ability::Fireball, i);
				}

				if (players[i]->getPos().x == SkillBoxList.at(3)->getPos().x + playerHoverPosX &&
					players[i]->getPos().y >= SkillBoxList.at(0)->getPos().y + playerHoverPosY + playerHoverList.at(i)->getSize().y * 3) {
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Cleave) && !press) {
							playerAbility[i][j] = -1;
							press = true;
						}
					}
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == -1 && !press) {
							playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Cleave);
							press = true;
						}
					}
					//abilityToFile(fileName, PlayerObject::Ability::Cleave, i);
				}

				if (players[i]->getPos().x == SkillBoxList.at(4)->getPos().x + playerHoverPosX && 
					players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Bola) && !press) {
							playerAbility[i][j] = -1;
							press = true;
						}
					}
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == -1 && !press) {
							playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Bola);
							press = true;
						}
					}
					//abilityToFile(fileName, PlayerObject::Ability::Bola, i);
				}

				if (players[i]->getPos().x == SkillBoxList.at(5)->getPos().x + playerHoverPosX &&
					players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Teleport) && !press) {
							playerAbility[i][j] = -1;
							press = true;
						}
					}
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == -1 && !press) {
							playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Teleport);
							press = true;
						}
					}
					//abilityToFile(fileName, PlayerObject::Ability::Teleport, i);
				}

				if (players[i]->getPos().x == SkillBoxList.at(6)->getPos().x + playerHoverPosX &&
					players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Trap) && !press) {
							playerAbility[i][j] = -1;
							press = true;
						}
					}
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == -1 && !press) {
							playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Trap);
							press = true;
						}
					}
					//abilityToFile(fileName, PlayerObject::Ability::Trap, i);
				}

				if (players[i]->getPos().x == SkillBoxList.at(7)->getPos().x + playerHoverPosX &&
					players[i]->getPos().y <= SkillBoxList.at(4)->getPos().y + playerHoverPosY) {
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == static_cast<int>(PlayerObject::Ability::Dash) && !press) {
							playerAbility[i][j] = -1;
							press = true;
						}
					}
					for (int j = 0; j < 3; j++) {
						if (playerAbility[i][j] == -1 && !press) {
							playerAbility[i][j] = static_cast<int>(PlayerObject::Ability::Dash);
							press = true;
						}
					}
					//abilityToFile(fileName, PlayerObject::Ability::Dash, i);
				}
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::Square)) {
				if (!ready[i]) {
					ready[i]++;
				}
				else {
					ready[i]--;
				}
			}
			if (ready[0] + ready[1] + ready[2] + ready[3] == SDL_NumJoysticks()) {
				for (int i = 0; i < SDL_NumJoysticks(); i++)
				{
					std::string fileName = "Ability" + std::to_string(i) + ".json";
					abilityToFile(fileName, i);
				}
				GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::R1)) {
				int Column = playerIconList.at(i)->GetSpriteRenderer()->GetColumn();
				Column += 1;
				if (Column == 4) {
					Column = 0;
				}
				playerIconList.at(i)->GetSpriteRenderer()->ShiftTo(playerIconList.at(i)->GetSpriteRenderer()->GetRow(), Column);
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::L1)) {
				int Column = playerIconList.at(i)->GetSpriteRenderer()->GetColumn();
				Column -= 1;
				if (Column == 0) {
					Column = 4;
				}
				playerIconList.at(i)->GetSpriteRenderer()->ShiftTo(playerIconList.at(i)->GetSpriteRenderer()->GetRow(), Column);
			}
		}
	}
}

void LevelSelectAbility::UpdateUi() {
	//Player Ui
	for (int i = 0; i < 4; i++) {
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
		for (int i = 0; i < 4; i++)
		{
			std::string fileName = "Ability" + std::to_string(i) + ".json";
			abilityToFile(fileName, i);
		}
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
	}

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

