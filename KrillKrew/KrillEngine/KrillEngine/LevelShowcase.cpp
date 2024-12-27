#include "LevelShowcase.h"

void getAim(int playerNum)
{
	// std::cout << "Owner " << std::endl;
}

void HoldBomb(int playerNum, 
			  PlayerObject* playerObj, 
			  std::vector<DrawableObject*>& objectList, 
			  SpritesheetInfo sheetinfo)
{
	std::cout << "Hold" << std::endl;
	playerObj->SetVelocity(0, 0, false, false);
	playerObj->SetIsAiming(true);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(sheetinfo);
	projectile->SetTexture(sheetinfo.texture);
	projectile->SetPosition(playerObj->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->setLifeTime(9999);
	projectile->setNumOwner(playerObj->GetPlayerNumber());
	// std::cout << "Owner " << projectile->getNumOwner() << std::endl;
	objectList.push_back(projectile);
	//objectsList.push_back(projectile->GetCollider()->GetGizmos());
}

void LevelShowcase::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	LineMeshVbo* line = new LineMeshVbo();
	line->LoadData();
	GameEngine::GetInstance()->AddMesh(LineMeshVbo::MESH_NAME, line);

	spriteList["Prinny"] = SpritesheetInfo("Prinny", "../Resource/Texture/Prinny.png", 538, 538, 538, 538);
	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Bomb_icon.png", 256, 256, 256, 256);
	spriteList["Shark_run"] = SpritesheetInfo("Shark_run", "../Resource/Texture/shark_run_test.png", 256, 256, 1024, 256);
	spriteList["Shark_idle"] = SpritesheetInfo("Shart_idle", "../Resource/Texture/shark_Idle_test.png", 256, 256, 256, 256);
	spriteList["Trap"] = SpritesheetInfo("Bomb", "../Resource/Texture/Trap.png", 512, 512, 512, 512);
	spriteList["Xoey_UI"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	spriteList["Byssa_UI"] = SpritesheetInfo("Byssa_UI", "../Resource/Texture/byssa.png", 430, 220, 430, 220);
	spriteList["Crunk_UI"] = SpritesheetInfo("Crunk_UI", "../Resource/Texture/crunk.png", 430, 220, 430, 220);
	spriteList["Ham_UI"] = SpritesheetInfo("Ham_UI", "../Resource/Texture/Ham.png", 430, 220, 430, 220);
	spriteList["Blobtile"] = SpritesheetInfo("Blobtile", "../Resource/Texture/tileset_01.png", 128, 128, 1664, 512);

	abilities.emplace(std::string("HoldBomb"), HoldBomb);
	//cout << "Load Level" << endl;
}

void LevelShowcase::LevelInit()
{
	std::cout << "Init Level" << std::endl;

	glClearColor(0.f, 180.f / 255.f, 171.f / 255.f, 1.f);

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(
		-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	timer = Timer::Instance();

	std::map<int, std::pair<int, int>> blob_lookup_table = {

	{666,	{1, 1}},
	{777,	{2, 1}},
	{888,	{3, 1}},
	{999,	{4, 1}},

	{16,	{1, 2}},
	{17,	{2, 2}},
	{1,		{3, 2}},
	{0,		{4, 2}},

	{20,	{1, 3}},
	{21,	{2, 3}},
	{5,		{3, 3}},
	{4,		{4, 3}},

	{84,	{1, 4}},
	{85,	{2, 4}},
	{69,	{3, 4}},
	{68,	{4, 4}},

	{80,	{1, 5}},
	{81,	{2, 5}},
	{65,	{3, 5}},
	{64,	{4, 5}},

	{213,	{1, 6}},
	{29,	{2, 6}},
	{23,	{3, 6}},
	{117,	{4, 6}},

	{92,	{1, 7}},
	{127,	{2, 7}},
	{223,	{3, 7}},
	{71,	{4, 7}},

	{116,	{1, 8}},
	{253,	{2, 8}},
	{247,	{3, 8}},
	{197,	{4, 8}},

	{87,	{1, 9}},
	{113,	{2, 9}},
	{209,	{3, 9}},
	{93,	{4, 9}},

	{28,	{1, 10}},
	{31,	{2, 10}},
	{95,	{3, 10}},
	{7,		{4, 10}},

	{125,	{1, 11}},
	{119,	{2, 11}},
	{255,	{3, 11}},
	{199,	{4, 11}},

	{124,	{1, 12}},
	{256,	{2, 12}}, // blank
	{221,	{3, 12}},
	{215,	{4, 12}},

	{112,	{1, 13}},
	{245,	{2, 13}},
	{241,	{3, 13}},
	{193,	{4, 13}},
	};

	std::map<int, std::pair<int, int>> blob_lookup_table_underground = {
	// 1
	{16,	{2, 12}},
	{17,	{2, 12}},
	{1,		{4, 1}},
	{0,		{4, 1}},
	// 2
	{20,	{2, 12}},
	{21,	{2, 12}},
	{5,		{3, 1}},
	{4,		{3, 1}},
	// 3
	{84,	{2, 12} },
	{ 85,	{2, 12} },
	{ 69,	{2, 1} },
	{68,	{2, 1}},
	// 4
	{80,	{2, 12}},
	{81,	{2, 12}},
	{65,	{1, 1}},
	{64,	{1, 1}},
	// 5
	{213,	{2, 12}},
	{29,	{2, 12}},
	{23,	{2, 12}},
	{117,	{2, 12}},
	// 6
	{92,	{2, 12}},
	{127,	{2, 12}},
	{223,	{2, 12}},
	{71,	{2, 1}},
	// 7
	{116,	{2, 12}},
	{253,	{2, 12}},
	{247,	{2, 12}},
	{197,	{2, 1}},
	// 8
	{87,	{2, 12}},
	{113,	{2, 12}},
	{209,	{2, 12}},
	{93,	{2, 12}},

	{28,	{2, 12}},
	{31,	{2, 12}},
	{95,	{2, 12}},
	{7,		{3, 1}},

	{125,	{2, 12}},
	{119,	{2, 12}},
	{255,	{2, 12}},
	{199,	{2, 1}},

	{124,	{2, 12}},
	{256,	{2, 12}}, // blank
	{221,	{2, 12}},
	{215,	{2, 12}},

	{112,	{2, 12}	},
	{245,	{2, 12}	},
	{241,	{2, 12}	},
	{193,	{1, 1}	},
	};

	TileImport(groundTile, "../Resource/Texture/Tilemap1.txt");

	// Create and Initialize 4 players object

	float map_left = -1280.f;
	float map_top = 1080.f;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			int flag = groundTile[i][j];

			std::pair<int, int> pos;

			if (i == 0 ||
				i == MAP_HEIGHT - 1 ||
				j == 0 ||
				j == MAP_WIDTH - 1)
			{
				continue;
			}
			else if (flag == 0)
			{
				if (groundTile[i - 1][j] == 0)
				{
					pos = { 2, 12 };
				}
				else
				{

					int upperPos = i - 1;

					std::bitset<8> surround;
					surround[0] = groundTile[upperPos - 1][j];
					surround[1] = groundTile[upperPos - 1][j + 1];
					surround[2] = groundTile[upperPos][j + 1];
					surround[3] = groundTile[upperPos + 1][j + 1];
					surround[4] = groundTile[upperPos + 1][j];
					surround[5] = groundTile[upperPos + 1][j - 1];
					surround[6] = groundTile[upperPos][j - 1];
					surround[7] = groundTile[upperPos - 1][j - 1];

					if (!(surround[0] && surround[2])) { surround[1] = 0; }
					if (!(surround[2] && surround[4])) { surround[3] = 0; }
					if (!(surround[4] && surround[6])) { surround[5] = 0; }
					if (!(surround[6] && surround[0])) { surround[7] = 0; }

					auto it = blob_lookup_table_underground.find((int)(surround.to_ulong()));

					// std::cout << "Bitset = " << (int)surround.to_ulong() << std::endl;

					if (it != blob_lookup_table_underground.end())
					{
						pos = it->second;

						// std::cout << "pair = " << it->second.first << " " << it->second.second << std::endl;
					}
					else 
					{
						pos = { 2, 12 };
						// std::cout << "blob_lookup_table.end()" << std::endl;
					}
				}
				
			}
			else
			{
				std::bitset<8> surround;
				surround[0] = groundTile[i - 1][j];
				surround[1] = groundTile[i - 1][j + 1];
				surround[2] = groundTile[i][j + 1];
				surround[3] = groundTile[i + 1][j + 1];
				surround[4] = groundTile[i + 1][j];
				surround[5] = groundTile[i + 1][j - 1];
				surround[6] = groundTile[i][j - 1];
				surround[7] = groundTile[i - 1][j - 1];

				if (!(surround[0] && surround[2])) { surround[1] = 0; }
				if (!(surround[2] && surround[4])) { surround[3] = 0; }
				if (!(surround[4] && surround[6])) { surround[5] = 0; }
				if (!(surround[6] && surround[0])) { surround[7] = 0; }

				auto it = blob_lookup_table.find((int)(surround.to_ulong()));
				// std::cout << "Bitset = " << (int)surround.to_ulong() << std::endl;
				if (it != blob_lookup_table.end())
				{
					pos = it->second;

					// std::cout << "pair = " << it->second.first << " " << it->second.second << std::endl;
				}
				else {
					// std::cout << "blob_lookup_table.end()" << std::endl;
				}
			}

			// std::cout << flag << ",";
			ImageObject* obj = new ImageObject();
			obj->SetSpriteInfo(spriteList.find("Blobtile")->second);
			obj->GetSpriteRenderer()->ShiftTo(pos.first - 1, pos.second - 1);
			obj->SetTexture(spriteList.find("Blobtile")->second.texture);
			obj->SetSize(128.f, -128.f);
			obj->SetPosition(glm::vec3(map_left + (j * 128.f), map_top - (i * 128.f), 0));
			objectsList.push_back(obj);

			// std::cout << "posX = " << obj->getPos().x << " posY = " << obj->getPos().y << std::endl;
		}
		// std::cout << std::endl;
	}
	// Create and Initialize 4 players object

	// Example Code
	PlayerObject* obj1 = new PlayerObject();
	obj1->GetCollider()->SetCollisionType(Collider::Kinematic);
	obj1->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj1->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj1->SetIsAnimated(true);
	obj1->GetSpriteRenderer()->SetFrame(10);
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-800.f, -700.f, 0));
	obj1->SetPlayerNumber(0);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	objectsList.push_back(obj1);
	playerSize++;
	players[0] = obj1;

	PlayerObject* obj2 = new PlayerObject();
	obj2->GetCollider()->SetCollisionType(Collider::Static);
	obj2->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj2->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj2->SetIsAnimated(true);
	obj2->GetSpriteRenderer()->SetFrame(15);
	obj2->SetSize(256.f, -256.f);
	obj2->SetPosition(glm::vec3(800.f, -700.f, 0));
	obj2->SetPlayerNumber(1);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	objectsList.push_back(obj2);
	playerSize++;
	players[1] = obj2;

	PlayerObject* obj3 = new PlayerObject();
	obj3->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj3->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj3->SetIsAnimated(true);
	obj3->GetSpriteRenderer()->SetFrame(15);
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-800.f, 700.f, 0));
	obj3->SetPlayerNumber(2);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	objectsList.push_back(obj3);
	playerSize++;
	players[2] = obj3;

	PlayerObject* obj4 = new PlayerObject();
	obj4->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj4->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj4->SetIsAnimated(true);
	obj4->GetSpriteRenderer()->SetFrame(15);
	obj4->SetSize(256.f, -256.f);
	obj4->SetPosition(glm::vec3(800.f, 700.f, 0));
	obj4->SetPlayerNumber(3);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	objectsList.push_back(obj4);
	playerSize++;
	players[3] = obj4;

	objectsList.push_back(players[0]->GetCollider()->GetGizmos());
	objectsList.push_back(players[1]->GetCollider()->GetGizmos());
	objectsList.push_back(players[2]->GetCollider()->GetGizmos());
	objectsList.push_back(players[3]->GetCollider()->GetGizmos());

	//create Ui by PlayerObject
	int sizePlayer = objectsList.size();
	int count = 0;
	for (int i = 0; i < sizePlayer; i++) {

		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		if (player != nullptr)
		{
			if (count == 0) {
				UiObject* uiSkills = new UiObject();
				uiSkills->SetSpriteInfo(spriteList.find("Xoey_UI")->second);
				uiSkills->SetTexture(spriteList.find("Xoey_UI")->second.texture);
				uiSkills->SetPosition(glm::vec3(0, 0, 0));
				uiSkills->SetSize(215.f, -100.f);
				uiSkills->setNumOwner(0);
				objectsList.push_back(uiSkills);
				count++;
				// std::cout << "create Ui xoey" << std::endl;
			}
			else if (count == 1) {
				UiObject* uiSkills1 = new UiObject();
				uiSkills1->SetSpriteInfo(spriteList.find("Ham_UI")->second);
				uiSkills1->SetTexture(spriteList.find("Ham_UI")->second.texture);
				uiSkills1->SetPosition(glm::vec3(0, 0, 0));
				uiSkills1->SetSize(215.f, -100.f);
				uiSkills1->setNumOwner(1);
				objectsList.push_back(uiSkills1);
				count++;
				// std::cout << "create Ui Ham" << std::endl;
			}
			else if (count == 2) {
				UiObject* uiSkills2 = new UiObject();
				uiSkills2->SetSpriteInfo(spriteList.find("Byssa_UI")->second);
				uiSkills2->SetTexture(spriteList.find("Byssa_UI")->second.texture);
				uiSkills2->SetPosition(glm::vec3(0, 0, 0));
				uiSkills2->SetSize(215.f, -100.f);
				uiSkills2->setNumOwner(2);
				objectsList.push_back(uiSkills2);
				count++;
				// std::cout << "create Ui byssa" << std::endl;
			}
			else if (count == 3) {
				UiObject* uiSkills3 = new UiObject();
				uiSkills3->SetSpriteInfo(spriteList.find("Crunk_UI")->second);
				uiSkills3->SetTexture(spriteList.find("Crunk_UI")->second.texture);
				uiSkills3->SetPosition(glm::vec3(0, 0, 0));
				uiSkills3->SetSize(215.f, -100.f);
				uiSkills3->setNumOwner(3);
				objectsList.push_back(uiSkills3);
				count++;
				// std::cout << "create Ui crunk" << std::endl;
			}
		}
	}

	std::cout << "Init Level" << std::endl;
}

void LevelShowcase::LevelUpdate()
{
	dt++;

	// Clear inactive object
	for (int i = 0; i < objectsList.size(); i++)
	{
		if (objectsList[i]->GetIsActive() == false)
		{
			objectsList.erase(objectsList.begin() + i);
		}
	}

	// UpdateInput();
	UpdateInput();

	for (int i = 0; i < playerSize; i++) {
		camera.setPlayerPos(i, players[i]->getPos());
	}
	camera.LerpCamera(playerSize); // update smooth camera here

	// Set Animation
	for (int i = 0; i < objectsList.size(); i++)
	{
		EntityObject* entity = dynamic_cast<EntityObject*>(objectsList[i]);
		if (entity == nullptr)
		{
			continue;
		}
		else
		{
			if (entity->GetIsAnimated() &&
				dt % entity->GetSpriteRenderer()->GetFrame() == 0)
			{
				entity->GetSpriteRenderer()->ShiftColumn();
				entity->UpdateCurrentAnimation();
			}
		}
	}


	// projectile collier player
	UpdateCollision();

	// delete projectile
	UpdateProjectile();

	// reduce cooldown skill
	UpdateCooldown();

	// slowness
	UpdateMovement();

	//Ui Skills
	UpdateUI();

}

void LevelShowcase::UpdateInput()
{
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			float axisX = Joystick::GetAxis(i, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
			float axisY = Joystick::GetAxis(i, Joystick::Axis::LeftStickVertical) / 32768.0f;
			float norAxisX = 0;
			float norAxisY = 0;

			bool isPositiveX = false;
			bool isPositiveY = false;

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

			// update facing
			if (abs(axisX) > 0.2f) { players[i + playerNum]->UpdateFacingSide(!isPositiveX); }

			if (players[i + playerNum]->GetIsAiming() == false)
			{
				players[i + playerNum]->SetVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
			}

			//Aim
			if (Joystick::GetButtonDown(i, Joystick::Button::L1))
			{

				if (players[i + playerNum]->GetIsShooting() == false && players[i + playerNum]->GetIsAiming() == false) 
				{
					players[i + playerNum]->SetVelocity(0, 0, isPositiveX, isPositiveY);
					players[i + playerNum]->SetIsAiming(true);
					ProjectileObject* projectile = new ProjectileObject();
					projectile->SetSpriteInfo(spriteList.find("Bomb")->second);
					projectile->SetTexture(spriteList.find("Bomb")->second.texture);
					projectile->SetPosition(players[i + playerNum]->getPos());
					projectile->SetSize(256.f, -256.f);
					projectile->setLifeTime(9999);
					projectile->setNumOwner(players[i + playerNum]->GetPlayerNumber());
					projectile->setOwner(players[i + playerNum]);
					std::cout << "Owner " << projectile->getNumOwner() << std::endl;
					objectsList.push_back(projectile);
					//objectsList.push_back(projectile->GetCollider()->GetGizmos());

					// (abilities.find("HoldBomb")->second)(i, players[i + playerNum], objectsList, spriteList.find("Bomb")->second);
				}
			}

			//Shoot
			if (Joystick::GetButtonUp(i, Joystick::Button::L1))
			{
				// std::cout << "Shoot " << i + playerNum << std::endl;
				if (players[i + playerNum]->GetIsAiming() == true) {
					players[i + playerNum]->SetIsShooting(true);
					players[i + playerNum]->SetIsAiming(false);
					for (int j = 0; j < objectsList.size(); j++) {
						ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
						if (projectile != nullptr) {
							projectile->setLifeTime(5);
						}
					}
				}
			}

			if (players[i + playerNum]->GetIsAiming())
			{
				for (int j = 0; j < objectsList.size(); j++) {
					ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
					if (projectile != nullptr && i + playerNum == projectile->getNumOwner()) {
						if (abs(norAxisX) > 0 || norAxisY > 0) {
							projectile->setVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
						}
						projectile->SetPosition(players[i + playerNum]->getPos() + (projectile->getVelocity() * glm::vec3(15.f, 15.f, 0.f)));
					}
				}
			}

			//Place trap
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle))
			{
				if (players[i + playerNum]->GetCooldown(1) <= 0) {
					players[i + playerNum]->SetAbilityCooldown(1, 3);
					TrapObject* Trap = new TrapObject();
					Trap->SetSpriteInfo(spriteList.find("Trap")->second);
					Trap->SetTexture(spriteList.find("Trap")->second.texture);
					Trap->SetPosition(players[i + playerNum]->getPos());
					Trap->SetSize(128.f, -128.f);
					Trap->setNumOwner(players[i + playerNum]->GetPlayerNumber());
					//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
					objectsList.push_back(Trap);
				}
			}

			// Debug other player
			if (Joystick::GetButtonDown(i, Joystick::Button::R1))
			{
				playerNum += 1;
				if (playerNum >= 4) {
					playerNum = 0;
				}
			}

			players[i + playerNum]->Translate(players[i + playerNum]->GetVelocity());

			if (Joystick::GetButtonDown(i, Joystick::Button::P5Button))
			{
				GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELGAMEPLAY;
				GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
			}
		}

	}
}

void LevelShowcase::UpdateCollision()
{
	// player collier player
	for (int i = 0; i < objectsList.size(); i++)
	{
		EntityObject* entity1 = dynamic_cast<EntityObject*>(objectsList[i]);

		if (entity1 == nullptr || entity1->GetCollider()->GetCollisionType() == Collider::Static)
		{
			continue;
		}
		for (int j = 0; j < objectsList.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			EntityObject* entity2 = dynamic_cast<EntityObject*>(objectsList[j]);

			if (entity2 != nullptr)
			{
				Collider col1 = *entity1->GetCollider();
				Collider col2 = *entity2->GetCollider();

				glm::vec2 delta = glm::vec2(abs(entity1->getPos().x - entity2->getPos().x),
					abs(entity1->getPos().y - entity2->getPos().y));

				glm::vec2 previousDelta = glm::vec2(abs(col1.GetPreviousPos().x - col2.GetPreviousPos().x),
					abs(col1.GetPreviousPos().y - col2.GetPreviousPos().y));

				float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
				float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

				// for resolve collider
				float previousOverlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - previousDelta.x;
				float previousOverlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - previousDelta.y;

				if (overlapX > 0 && overlapY > 0)
				{
					entity1->OnColliderEnter(entity2->GetCollider());
					entity2->OnColliderEnter(entity1->GetCollider());

					if (col1.GetCollisionType() == Collider::Kinematic &&
						col2.GetCollisionType() == Collider::Static)
					{
						glm::vec3 newPos(entity1->getPos().x, entity1->getPos().y, entity1->getPos().z);

						if (previousOverlapX > 0)
						{
							bool isTopSide = (col1.GetPreviousPos().y - col2.GetPreviousPos().y) > 0 ? true : false;

							newPos.y = entity1->getPos().y + (overlapY * (isTopSide ? 1 : -1));
						}
						if (previousOverlapY > 0)
						{
							bool isLeftSide = (col1.GetPreviousPos().x - col2.GetPreviousPos().x) < 0 ? true : false;
							newPos.x = entity1->getPos().x + (overlapX * (isLeftSide ? -1 : 1));
						}
						entity1->SetPosition(newPos);
					}
				}

				entity2->GetCollider()->SetPreviousPos(entity2->getPos());

			}
		}
		entity1->GetCollider()->SetPreviousPos(entity1->getPos());
	}
}

void LevelShowcase::UpdateProjectile()
{
	for (int i = 0; i < objectsList.size(); i++)
	{
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (projectile != nullptr) {

			if ((dt % 50) == 0) {
				projectile->reduceLifeTime();
			}

			if (projectile->getLifetime() <= 0)
			{
				players[projectile->getNumOwner()]->SetIsShooting(false);
				objectsList.erase(objectsList.begin() + i);
			}

			projectile->Translate(projectile->getVelocity());
		}

	}
}

void LevelShowcase::UpdateCooldown()
{
	for (int i = 0; i < playerNum; i++)
	{
		timer->tick();
		timer->reset();
		time[i + playerNum] += timer->getDeltaTime();

		for (int j = 0; j < 3; j++)
		{
			if (time[i + playerNum] >= 1.0f && players[i + playerNum]->GetCooldown(j) > 0)
			{
				players[i + playerNum]->ReduceAbilityCooldown(j);
				time[i + playerNum] = 0.0f;
			}
		}
	}
}

void LevelShowcase::UpdateMovement()
{
	for (int i = 0; i < SDL_NumJoysticks() + playerNum; i++)
	{
		if (players[i]->GetIsSlow() == true)
		{
			players[i]->ReduceSlowDuration();
		}

		if (players[i]->GetSlowDuration() <= 0)
		{
			players[i]->SetIsSlow(false);
		}
	}
}

void LevelShowcase::UpdateUI()
{
	for (int i = 0; i < objectsList.size(); i++)
	{
		UiObject* ui = dynamic_cast<UiObject*>(objectsList[i]);
		if (ui != nullptr) 
		{
			ui->SetPosition(glm::vec3(
				GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left + (((300 * (ui->getNumOwner() + 1)) - (85 * ui->getNumOwner())) * camera.GetCameraWidth() / 1246),
				GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + (50 * camera.GetCameraHeight() / 720), 0));
			ui->SetSize(215.f * camera.GetCameraWidth() / 1246, -100.f * camera.GetCameraHeight() / 720);
		}
	}
}

void LevelShowcase::LevelDraw()
{
	// Collider position update
	for (int i = 0; i < objectsList.size(); i++)
	{
		EntityObject* object = dynamic_cast<EntityObject*>(objectsList[i]);
		if (object != nullptr)
		{
			object->GetCollider()->Update(object->getSize(), object->getPos());
		}
	}

	GameEngine::GetInstance()->Render(objectsList);

	// cout << "Draw Level" << endl;
}

void LevelShowcase::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();

	//cout << "Free Level" << endl;
}

void LevelShowcase::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	//cout << "Unload Level" << endl;
}

void LevelShowcase::HandleKey(char key)
{

	switch (key)
	{
		// switch player
	case '1': this->playerNum = 0; break;
	case '2': this->playerNum = 1; break;
	case '3': this->playerNum = 2; break;
	case '4': this->playerNum = 3; break;

	case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'e':
		GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELGAMEPLAY;
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING; ; break;
	case 'i':

		GameEngine::GetInstance()->SetDrawArea
		(camera.getCameraOrthoValue().left + SCREEN_WIDTH * ZOOM_VELOCITY,
			camera.getCameraOrthoValue().right - SCREEN_WIDTH * ZOOM_VELOCITY,
			camera.getCameraOrthoValue().bottom + SCREEN_HEIGHT * ZOOM_VELOCITY,
			camera.getCameraOrthoValue().top - SCREEN_HEIGHT * ZOOM_VELOCITY);

		break;

	case 'o':

		GameEngine::GetInstance()->SetDrawArea
		(camera.getCameraOrthoValue().left - SCREEN_WIDTH * ZOOM_VELOCITY,
			camera.getCameraOrthoValue().right + SCREEN_WIDTH * ZOOM_VELOCITY,
			camera.getCameraOrthoValue().bottom - SCREEN_HEIGHT * ZOOM_VELOCITY,
			camera.getCameraOrthoValue().top + SCREEN_HEIGHT * ZOOM_VELOCITY);

		break;

	case 'y':
		this->playerNum++;

		if (this->playerNum >= 4) {
			this->playerNum = 0;
		}
		break;
	}
}

void LevelShowcase::HandleMouse(int type, int x, int y)
{

}

void LevelShowcase::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY)
{

}

void LevelShowcase::TileImport(int TileBuffer[][MAP_WIDTH], std::string fileName) {
	std::ifstream mapfile(fileName);
	std::string line;
	int row = 0;
	int column = 1;
	if (!mapfile.is_open()) {
		// error
		std::cout << "Error: reading tile information" << std::endl;
	}
	else {
		int counter = 0;
		while (!mapfile.eof()) {
			//string line;
			if (getline(mapfile, line, ',')) {

				TileBuffer[counter / MAP_WIDTH][counter % MAP_WIDTH] = std::stoi(line);

				counter++;
			}
		}
		mapfile.close();

	}
}