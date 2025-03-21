#include "LevelShowcase.h"

bool compareLayer(const DrawableObject* a, const DrawableObject* b)
{
	return a->getOrderingLayer() < b->getOrderingLayer();
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
	
	spriteList["Shark_hit"] = SpritesheetInfo("Shark_hit", "../Resource/Texture/Ham/P1-SmashDiagDown.png", 402, 402, 1608, 402);
	spriteList["Shark_run"] = SpritesheetInfo("Shark_run", "../Resource/Texture/Ham/P1_MoveSide.png", 302, 302, 1208, 302);
	spriteList["Shark_idle"] = SpritesheetInfo("Shart_idle", "../Resource/Texture/Ham/P1_Idle.png", 302, 302, 302, 302);
	
	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Bomb_icon.png", 256, 256, 256, 256);
	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Trap.png", 512, 512, 512, 512);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/TNT.png", 348, 348, 348, 348);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/EnderPearl.png", 512, 512, 512, 512);
	spriteList["Bola"] = SpritesheetInfo("Bola", "../Resource/Texture/Bola.png", 317, 314, 317, 314);
	spriteList["Cleave"] = SpritesheetInfo("Cleave", "../Resource/Texture/Cleave.png", 647, 386, 647, 386);
	
	spriteList["Xoey_UI"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	spriteList["Byssa_UI"] = SpritesheetInfo("Byssa_UI", "../Resource/Texture/byssa.png", 430, 220, 430, 220);
	spriteList["Crunk_UI"] = SpritesheetInfo("Crunk_UI", "../Resource/Texture/crunk.png", 430, 220, 430, 220);
	spriteList["Ham_UI"] = SpritesheetInfo("Ham_UI", "../Resource/Texture/Ham.png", 430, 220, 430, 220);

	spriteList["Blobtile"] = SpritesheetInfo("Blobtile", "../Resource/Texture/tileset_01.png", 128, 128, 1664, 512);

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

	TileImport(groundTile, "../Resource/Texture/Tilemap0.txt");
	TileImport(currentGroundTile, "../Resource/Texture/Tilemap0.txt");

	// Create and Initialize 4 players object

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			std::cout << groundTile[i][j] << ", ";
		}
		std::cout << std::endl;
	}

	float map_left = -1280.f;
	float map_top = 1080.f;

	int tileCount = 0;

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
			else
			{
				int checkPosRow;

				if (flag == 0)
				{
					checkPosRow = i - 1;
				}
				else if (flag == 1)
				{
					checkPosRow = i;
				}

				std::bitset<8> surround;
				surround[0] = groundTile[checkPosRow - 1][j];
				surround[1] = groundTile[checkPosRow - 1][j + 1];
				surround[2] = groundTile[checkPosRow][j + 1];
				surround[3] = groundTile[checkPosRow + 1][j + 1];
				surround[4] = groundTile[checkPosRow + 1][j];
				surround[5] = groundTile[checkPosRow + 1][j - 1];
				surround[6] = groundTile[checkPosRow][j - 1];
				surround[7] = groundTile[checkPosRow - 1][j - 1];

				if (!(surround[0] && surround[2])) { surround[1] = 0; }
				if (!(surround[2] && surround[4])) { surround[3] = 0; }
				if (!(surround[4] && surround[6])) { surround[5] = 0; }
				if (!(surround[6] && surround[0])) { surround[7] = 0; }

				if (flag == 0)
				{
					auto lookup_sheet = blob_lookup_table_underground.find((int)(surround.to_ulong()));

					if (lookup_sheet != blob_lookup_table_underground.end() && groundTile[checkPosRow][j] != 0)
					{
						pos = lookup_sheet->second;
					}
					else
					{
						pos = { 2, 12 };
					}
				}
				else if (flag == 1)
				{
					auto lookup_sheet = blob_lookup_table.find((int)(surround.to_ulong()));

					if (lookup_sheet != blob_lookup_table_underground.end())
					{
						pos = lookup_sheet->second;
					}
					else
					{
						pos = { 2, 12 };
					}
				}
			}

			if (pos.first == 2 && pos.second == 12)
			{
				// KK_TRACE("Pos.first = 2, pos.second = 12");
			}
			else
			{
				// KK_TRACE("Pos {0}, {1} pos.first = {2} pos.second = {3} ", i, j, pos.first, pos.second);
				TileObject* obj = new TileObject();
				obj->SetSpriteInfo(spriteList.find("Blobtile")->second);
				obj->GetSpriteRenderer()->ShiftTo(pos.first - 1, pos.second - 1);
				obj->SetTexture(spriteList.find("Blobtile")->second.texture);
				obj->SetSize(128.f, -128.f);
				obj->SetPosition(glm::vec3(map_left + (j * 126.f), map_top - (i * 126.f), 0));
				obj->SetTilePosition(i, j);
				obj->SetUpdateTileset(&currentGroundTile);

				if (flag == 0)
				{
					obj->SetIsBreakable(false);
					obj->SetIsBroke(true);
				}
				else if (flag == 1)
				{
					obj->SetIsBreakable(true);
					obj->SetIsBroke(false);
				}

				tilesList[i][j] = obj;

				entityObjects.push_back(obj);
				tileCount++;
				objectsList.push_back(obj);
				objectsList.push_back(obj->GetCollider()->GetGizmos());
				objectsList.push_back(obj->GetOverlaySprite());
			}
		}
	}

	// Example Code

	PlayerObject* p1 = new PlayerObject();
	p1->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Melee, spriteList.find("Shark_hit")->second);
	p1->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	p1->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Dash);
	p1->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Trap);
	p1->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	p1->SetPosition(glm::vec3(-800.f, -700.f, 10.f));
	p1->GetSpriteRenderer()->SetFrame(10);
	p1->SetPlayerNumber(0);
	entityObjects.push_back(p1);
	objectsList.push_back(p1);
	playerSize++;
	players[0] = p1;

	PlayerObject* p2 = new PlayerObject();
	p2->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Melee, spriteList.find("Shark_hit")->second);
	p2->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::TNT);
	p2->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Teleport);
	p2->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Bola);
	p2->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	p2->SetPosition(glm::vec3(800.f, -700.f, 0));
	p2->GetSpriteRenderer()->SetFrame(10);
	p2->SetPlayerNumber(1);
	entityObjects.push_back(p2);
	objectsList.push_back(p2);
	playerSize++;
	players[1] = p2;

	PlayerObject* p3 = new PlayerObject();
	p3->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Melee, spriteList.find("Shark_hit")->second);
	p3->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Cleave);
	p3->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	p3->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Cleave);
	p3->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	p3->SetPosition(glm::vec3(800.f, 700.f, 0));
	p3->GetSpriteRenderer()->SetFrame(10);
	p3->SetPlayerNumber(2);
	entityObjects.push_back(p3);
	objectsList.push_back(p3);
	playerSize++;
	players[2] = p3;

	PlayerObject* p4 = new PlayerObject();
	p4->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Melee, spriteList.find("Shark_hit")->second);
	p4->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	p4->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	p4->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Cleave);
	p4->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	p4->SetPosition(glm::vec3(-800.f, 700.f, 0));
	p4->GetSpriteRenderer()->SetFrame(10);
	p4->SetPlayerNumber(3);
	entityObjects.push_back(p4);
	objectsList.push_back(p4);
	playerSize++;
	players[3] = p4;

	/*entityObjects.push_back(players[0]->GetAttackColliderObject());
	entityObjects.push_back(players[1]->GetAttackColliderObject());
	entityObjects.push_back(players[2]->GetAttackColliderObject());
	entityObjects.push_back(players[3]->GetAttackColliderObject());

	objectsList.push_back(players[0]->GetAttackColliderObject());
	objectsList.push_back(players[1]->GetAttackColliderObject());
	objectsList.push_back(players[2]->GetAttackColliderObject());
	objectsList.push_back(players[3]->GetAttackColliderObject());

	objectsList.push_back(players[0]->GetAttackCollider()->GetGizmos());
	objectsList.push_back(players[1]->GetAttackCollider()->GetGizmos());
	objectsList.push_back(players[2]->GetAttackCollider()->GetGizmos());
	objectsList.push_back(players[3]->GetAttackCollider()->GetGizmos());

	objectsList.push_back(players[0]->GetCollider()->GetGizmos());
	objectsList.push_back(players[1]->GetCollider()->GetGizmos());
	objectsList.push_back(players[2]->GetCollider()->GetGizmos());
	objectsList.push_back(players[3]->GetCollider()->GetGizmos());*/

	for (int i = 0; i < 4; i++)
	{
		entityObjects.push_back(players[i]->GetAttackColliderObject());
		objectsList.push_back(players[i]->GetAttackColliderObject());
		objectsList.push_back(players[i]->GetAttackCollider()->GetGizmos());
		objectsList.push_back(players[i]->GetCollider()->GetGizmos());

		entityObjects.push_back(players[i]->GetGroundColliderObject());
		objectsList.push_back(players[i]->GetGroundCollider()->GetGizmos());
	}

	//create Ui by PlayerObject
	int playerSize = 4;
	int count = 0;

	if (playerSize >= 0) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Xoey_UI")->second);
		uiSkills->setNumOwner(0);
		objectsList.push_back(uiSkills);
	}
	if (playerSize >= 1) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Ham_UI")->second);
		uiSkills->setNumOwner(1);
		objectsList.push_back(uiSkills);
	}
	if (playerSize >= 2) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Byssa_UI")->second);
		uiSkills->setNumOwner(2);
		objectsList.push_back(uiSkills);
	}
	if (playerSize >= 3) {

		UiObject* uiSkills = new UiObject();
		uiSkills->SetSpriteInfo(spriteList.find("Crunk_UI")->second);
		uiSkills->setNumOwner(3);
		objectsList.push_back(uiSkills);
	}

	// sort with ordering layer
	std::sort(objectsList.begin(), objectsList.end(), compareLayer);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	const char* glsl_version = "#version 330";
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(GameEngine::GetInstance()->GetSDLWindow(), GameEngine::GetInstance()->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

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
			if (entity->GetIsAnimated() && dt % entity->GetSpriteRenderer()->GetFrame() == 0)
			{
				entity->GetSpriteRenderer()->ShiftColumn();
				entity->UpdateCurrentAnimation();
			}
		}
	}

	// projectile collider player
	UpdateCollision();

	// delete projectile
	UpdateProjectile();

	// reduce cooldown skill
	UpdateCooldown();

	// slowness
	UpdateMovement();

	//Ui Skills
	UpdateUI();

	GroundTileRefactor();

	std::sort(objectsList.begin(), objectsList.end(), compareLayer);
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

			if (norAxisX != 0 || norAxisY != 0)
			{
				players[i + playerNum]->SetCurrentDirection(glm::vec2(norAxisX, norAxisY));
			}

			// update facing
			if (abs(axisX) > 0.2f) 
			{ 
				players[i + playerNum]->UpdateFacingSide(isPositiveX); 
			}

			// movement control
			if (players[i + playerNum]->GetIsKnockback() == false)
			{
				if (players[i + playerNum]->GetIsStun() == true)
				{
					// velo to zero if stun
					players[i + playerNum]->SetVelocity(0, 0, isPositiveXOld, isPositiveYOld);
				}
				else if (players[i + playerNum]->GetIsDashing() == true)
				{
					// use old velo during dash to disable control
					players[i + playerNum]->SetVelocity(
						abs(norAxisXOld), 
						abs(norAxisYOld), 
						isPositiveXOld, 
						isPositiveYOld
					);
				}
				else if (players[i + playerNum]->GetIsAiming() == false)
				{
					// if not affect by anything, use normaml velocity
					players[i + playerNum]->SetVelocity(
						abs(norAxisX), 
						abs(norAxisY), 
						isPositiveX, 
						isPositiveY
					);
				}
			}

			// update old velocity in case dashing
			norAxisXOld = norAxisX;
			norAxisYOld = norAxisY;
			isPositiveXOld = isPositiveX;
			isPositiveYOld = isPositiveY;

			// ************change it to attach to player
			if (players[i + playerNum]->GetIsAiming())
			{
				for (int j = 0; j < objectsList.size(); j++) 
				{
					ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
					if ((projectile != nullptr) &&
						(players[i + playerNum]->GetPlayerNumber() == projectile->GetOwner()->GetPlayerNumber()) &&
						(projectile->GetIsShooting() == false)) 
					{
						if (abs(norAxisX) > 0 || norAxisY > 0) 
						{
							projectile->SetVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
						}
						projectile->SetPosition(players[i + playerNum]->getPos() + (projectile->GetVelocity() * glm::vec3(15.f, 15.f, 0.f)));

					}
				}
			}

			/*if (players[i + playerNum]->GetIsAiming() && players[i + playerNum]->GetHoldingProjectile() != 0)
			{
				for (int j = 0; j < objectsList.size(); j++) {
					ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
					if ((projectile != nullptr) &&
						(players[i + playerNum]->GetPlayerNumber() == projectile->GetOwner()->GetPlayerNumber()) &&
						(projectile->GetIsShooting() == false)) {
						if (abs(norAxisX) > 0 || norAxisY > 0) {
							projectile->SetVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
						}
						projectile->SetPosition(players[i + playerNum]->getPos() + (projectile->GetVelocity() * glm::vec3(15.f, 15.f, 0.f)));

					}
				}
			}*/

			//Aim
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle))
			{
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Triangle) <= 0)
				{
					UsingAbility(i + playerNum, PlayerObject::AbilityButton::Triangle);
				}
			}

			//Place trap
			if (Joystick::GetButtonDown(i, Joystick::Button::Circle))
			{
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Circle) <= 0)
				{
					UsingAbility(i + playerNum, PlayerObject::AbilityButton::Circle);
				}
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::Cross))
			{
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Cross) <= 0)
				{
					UsingAbility(i + playerNum, PlayerObject::AbilityButton::Cross);
				}
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{
				players[playerNum]->ChangeAnimationState(PlayerObject::AnimationState::Melee);
				players[playerNum]->HitAimingTile();
			}

			// players[i + playerNum]->Translate(players[i + playerNum]->GetVelocity());

			// Debug other player
			if (Joystick::GetButtonDown(i, Joystick::Button::R1))
			{
				players[playerNum]->ChangeAnimationState(PlayerObject::AnimationState::Idle);
				players[playerNum]->SetVelocity(0, 0, false, false);
				playerNum += 1;
				if (playerNum >= 4) {
					playerNum = 0;
				}
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::P5Button))
			{
				GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELGAMEPLAY;
				GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;
			}

			// players[i + playerNum % 4]->Translate(players[0]->GetVelocity());
			players[0]->Translate(players[0]->GetVelocity());
			players[1]->Translate(players[1]->GetVelocity());
			players[2]->Translate(players[2]->GetVelocity());
			players[3]->Translate(players[3]->GetVelocity());
			//players[i + playerNum]->Translate(players[i + playerNum]->GetVelocity());
		}

	}
}

void LevelShowcase::UpdateCollision()
{
	for (int i = 0; i < 4; i++)
	{
		players[i]->SetIsOnGround(false);
	}

	// trap collider player
	for (int i = 0; i < objectsList.size(); i++)
	{
		TrapObject* trap = dynamic_cast<TrapObject*>(objectsList[i]);
		if (trap == nullptr)
		{
			continue;
		}
		for (int j = 0; j < objectsList.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			PlayerObject* player2 = dynamic_cast<PlayerObject*>(objectsList[j]);
			if (player2 != nullptr)
			{
				if (trap->GetNumOwner() != player2->GetPlayerNumber()) {
					Collider col1 = *trap->GetCollider();
					Collider col2 = *player2->GetCollider();

					glm::vec2 delta = glm::vec2(abs(trap->getPos().x - player2->getPos().x),
						abs(trap->getPos().y - player2->getPos().y));

					float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
					float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

					if (overlapX > 0 && overlapY > 0)
					{
						std::cout << "Trap :" << trap->GetNumOwner() << " hit " << "Player" << player2->GetPlayerNumber() << std::endl;
						if (trap->GetIsCanKnockback()) {
							UpdateKnockback(trap, player2);
							objectsList.erase(objectsList.begin() + i);
						}
						else {
							player2->SetSlowDuration(100);
							player2->SetIsSlow(true);
							objectsList.erase(objectsList.begin() + i);
						}
						
					}
				}
			}
		}
	}
	int entityCount = 0;
	for (int i = 0; i < entityObjects.size(); i++)
	{
		EntityObject* entity1 = entityObjects[i];
		TileObject* tile = dynamic_cast<TileObject*>(entityObjects[i]);

		if (entity1->GetCollider()->GetCollisionType() == Collider::Static ||
			tile != nullptr)
		{
			continue;
		}

		for (int j = 0; j < entityObjects.size(); j++)
		{
			entityCount++;
			
			if (i == j)
			{
				continue;
			}

			EntityObject* entity2 = entityObjects[j];

			Collider* col1 = entity1->GetCollider();
			Collider* col2 = entity2->GetCollider();

			float deltaX = entity1->getPos().x - entity2->getPos().x;
			float deltaY = entity1->getPos().y - entity2->getPos().y;
			glm::vec2 delta(abs(deltaX), abs(deltaY));

			float previousDeltaX = col1->GetPreviousPos().x - col2->GetPreviousPos().x;
			float previousDeltaY = col1->GetPreviousPos().y - col2->GetPreviousPos().y;
			glm::vec2 previousDelta(abs(previousDeltaX), abs(previousDeltaY));

			float halfSizeAbsX1 = abs(col1->GetHalfSize().x);
			float halfSizeAbsX2 = abs(col2->GetHalfSize().x);

			float halfSizeAbsY1 = abs(col1->GetHalfSize().y);
			float halfSizeAbsY2 = abs(col2->GetHalfSize().y);

			float overlapX = halfSizeAbsX1 + halfSizeAbsX2 - delta.x;

			float overlapY = halfSizeAbsY1 + halfSizeAbsY2 - delta.y;


			// for resolve collider
			float previousOverlapX = (abs(col1->GetHalfSize().x)) + (abs(col2->GetHalfSize().x)) - previousDelta.x;
			float previousOverlapY = (abs(col1->GetHalfSize().y)) + (abs(col2->GetHalfSize().y)) - previousDelta.y;

			if (overlapX > 0 && overlapY > 0)
			{

				if (previousCollisions.find({ col1, col2 }) == previousCollisions.end())
				{
					entity1->OnColliderEnter(entity2->GetCollider());
					// entity2->OnColliderEnter(entity1->GetCollider());
				}
				else
				{
					
					entity1->OnColliderStay(entity2->GetCollider());
					// entity2->OnColliderStay(entity1->GetCollider());
				}

				currentCollisions.insert({ col1, col2 });

				if (col1->GetCollisionType() == Collider::Kinematic &&
					col2->GetCollisionType() == Collider::Static)
				{
					glm::vec3 newPos(entity1->getPos().x, entity1->getPos().y, entity1->getPos().z);

					if (previousOverlapX > 0)
					{
						bool isTopSide = (col1->GetPreviousPos().y - col2->GetPreviousPos().y) > 0 ? true : false;

						newPos.y = entity1->getPos().y + (overlapY * (isTopSide ? 1 : -1));
					}
					if (previousOverlapY > 0)
					{
						bool isLeftSide = (col1->GetPreviousPos().x - col2->GetPreviousPos().x) < 0 ? true : false;
						newPos.x = entity1->getPos().x + (overlapX * (isLeftSide ? -1 : 1));
					}
					entity1->SetPosition(newPos);
				}
			}
			else if (overlapX <= 0 || overlapY <= 0)
			{
				if (previousCollisions.find({ col1, col2 }) != previousCollisions.end())
				{
					entity1->OnColliderExit(entity2->GetCollider());
					// entity2->OnColliderExit(entity1->GetCollider());
				}
			}

			entity2->GetCollider()->SetPreviousPos(entity2->getPos());
		}
		entity1->GetCollider()->SetPreviousPos(entity1->getPos());
	}

	// previousCollisions = currentCollisions;
	std::swap(previousCollisions, currentCollisions);
	currentCollisions.clear();

	// projectile
	for (int i = 0; i < objectsList.size(); i++)
	{
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);

		if (projectile == nullptr)
		{
			continue;
		}

		for (int j = 0; j < objectsList.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[j]);

			if (player != nullptr)
			{
				if (projectile->GetOwner()->GetPlayerNumber() != player->GetPlayerNumber())
				{
					Collider col1 = *projectile->GetCollider();
					Collider col2 = *player->GetCollider();

					glm::vec2 delta = glm::vec2(abs(projectile->getPos().x - player->getPos().x),
						abs(projectile->getPos().y - player->getPos().y));

					float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
					float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

					if (overlapX > 0 && overlapY > 0)
					{
						if (projectile->GetType() == ProjectileObject::TypeProjectile::Teleport) {
							players[projectile->GetOwner()->GetPlayerNumber()]->SetPosition(projectile->getPos());
						}
						if (projectile->GetIsCanStun()) {
							player->SetIsStun(true);
							player->SetStunDuraion(5);
						}
						players[projectile->GetOwner()->GetPlayerNumber()]->SetIsShooting(false);
						UpdateKnockback(projectile, player);
						if (players[projectile->GetOwner()->GetPlayerNumber()]->GetHoldingProjectile() == projectile->GetType()) {
							players[projectile->GetOwner()->GetPlayerNumber()]->SetIsAiming(false);
							players[projectile->GetOwner()->GetPlayerNumber()]->SetHoldingProjectile(0);
						}
						objectsList.erase(objectsList.begin() + i);
					}
				}

			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		players[i]->CheckIfOnGround();
	}
}

void LevelShowcase::UpdateProjectile()
{
	for (int i = 0; i < objectsList.size(); i++)
	{
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (projectile != nullptr) {

			if ((dt % 50) == 0) {
				projectile->ReduceLifeTime();
			}

			if (projectile->GetLifetime() <= 0)
			{
				if (projectile->GetType() == ProjectileObject::TypeProjectile::Teleport) {
					players[projectile->GetOwner()->GetPlayerNumber()]->SetPosition(projectile->getPos());
				}
				players[projectile->GetOwner()->GetPlayerNumber()]->SetIsShooting(false);
				objectsList.erase(objectsList.begin() + i);

			}

			projectile->Translate(projectile->GetVelocity());
		}

		//delete trap after use
		TrapObject* trap = dynamic_cast<TrapObject*>(objectsList[i]);
		if (trap != nullptr) {
			if (trap->GetIsCanKnockback()) {
				objectsList.erase(objectsList.begin() + i);
			}
		}

	}
}

void LevelShowcase::UpdateCooldown()
{
	for (int i = 0; i < /*SDL_NumJoysticks() + playerNum*/ 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			if (time1s >= 1.0f && players[i]->GetCooldown(static_cast<PlayerObject::AbilityButton>(j)) > 0)
			{
				//std::cout << j << std::endl;
				players[i + playerNum]->ReduceAbilityCooldown(j);

			}
		}
		UpdateTime();
	}
}

void LevelShowcase::UpdateMovement()
{
	for (int i = 0; i < 4; i++)
	{
		if (time1s >= 1.0f && players[i]->GetIsSlow() == true)
		{
			players[i]->ReduceSlowDuration();
		}

		if (players[i]->GetSlowDuration() <= 0)
		{
			players[i]->SetIsSlow(false);
		}

		if (time05s >= 0.1f && players[i]->GetIsKnockback() == true) 
		{
			glm::vec3 knockbackVelo = players[i]->GetVelocity();

			float knockbackVeloX = abs(knockbackVelo.x) / 5;
			float knockbackVeloY = abs(knockbackVelo.y) / 5;

			players[i]->SetVelocity(knockbackVeloX / 1.1, 
									knockbackVeloY / 1.1, 
									players[i]->GetXIsPositive(), 
									players[i]->GetYIsPositive());
		}

		if (players[i]->GetDurationKnockback() <= 0 &&
			players[i]->GetIsKnockback() &&
			(abs(players[i]->GetVelocity().x) / 5 < 0.05) &&
			(abs(players[i]->GetVelocity().y) / 5 < 0.05))
		{
			players[i]->SetIsKnockback(false);
			players[i]->SetVelocity(0, 0, false, false);
		}

		if (time1s >= 1.0f && players[i]->GetIsKnockback() == true)
		{
			players[i]->ReduceKnockbackDuration();
		}

		if (players[i]->GetDurationKnockback() <= 0)
		{
			players[i]->SetIsKnockback(false);
		}

		if (time1s >= 1.0f && players[i]->GetIsStun() == true)
		{
			players[i]->ReduceStunDuration();
		}

		if (players[i]->GetStunDuration() <= 0)
		{
			players[i]->SetIsStun(false);
		}

		UpdateTime();
	}
}

void LevelShowcase::UpdateKnockback(DrawableObject* obj1, DrawableObject* obj2) 
{
	ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(obj1);
	TrapObject* trap = dynamic_cast<TrapObject*>(obj1);
	PlayerObject* player = dynamic_cast<PlayerObject*>(obj2);

	if (player != NULL && projectile != NULL && projectile->GetIsCanKnockback()) 
	{
		if (projectile->GetOwner()->GetPlayerNumber() != player->GetPlayerNumber()) 
		{
			player->SetIsKnockback(true);
			player->SetKnockbackDuration(2);
			glm::vec3 knockbackDirection = obj1->getPos() - player->getPos();

			float knockbackDirectionX = knockbackDirection.x / 255;
			float knockbackDirectionY = knockbackDirection.y / 255;
			bool knockbackDirectionXisPositive = false;
			bool knockbackDirectionYisPositive = false;
			if (knockbackDirection.x < 0)
			{
				knockbackDirectionXisPositive = true;
			}
			else if (knockbackDirection.x > 0)
			{
				knockbackDirectionXisPositive = false;
			}

			if (knockbackDirection.y > 0)
			{
				knockbackDirectionYisPositive = false;
			}
			else if (knockbackDirection.y < 0)
			{
				knockbackDirectionYisPositive = true;
			}

			knockbackDirectionX = abs(knockbackDirectionX);
			knockbackDirectionY = abs(knockbackDirectionY);


			player->SetVelocity(knockbackDirectionX, knockbackDirectionY, knockbackDirectionXisPositive, knockbackDirectionYisPositive);
			std::cout << knockbackDirectionY << std::endl;
		}
	}
	if (player != NULL && trap != NULL && trap->GetIsCanKnockback()) 
	{
		if (trap->GetNumOwner() != player->GetPlayerNumber()) 
		{
			player->SetIsKnockback(true);
			player->SetKnockbackDuration(2);
			glm::vec3 knockbackDirection = obj1->getPos() - player->getPos();

			float knockbackDirectionX = knockbackDirection.x / 255;
			float knockbackDirectionY = knockbackDirection.y / 255;
			bool knockbackDirectionXisPositive = false;
			bool knockbackDirectionYisPositive = false;
			if (knockbackDirection.x < 0)
			{
				knockbackDirectionXisPositive = true;
			}
			else if (knockbackDirection.x > 0)
			{
				knockbackDirectionXisPositive = false;
			}

			if (knockbackDirection.y > 0)
			{
				knockbackDirectionYisPositive = false;
			}
			else if (knockbackDirection.y < 0)
			{
				knockbackDirectionYisPositive = true;
			}

			knockbackDirectionX = abs(knockbackDirectionX);
			knockbackDirectionY = abs(knockbackDirectionY);


			player->SetVelocity(knockbackDirectionX, knockbackDirectionY, knockbackDirectionXisPositive, knockbackDirectionYisPositive);
			std::cout << knockbackDirectionY << std::endl;
		}
	}

}

void LevelShowcase::UpdateTime() {

	timer->tick();
	timer->reset();
	time1s += timer->getDeltaTime();
	time05s += timer->getDeltaTime();

	if (time1s >= 1.01f) 
	{
		time1s = 0.0f;
	}

	if (time05s >= 0.11f) 
	{
		time05s = 0.0f;

		for (int i = 0; i < 4; i++)
		{
			if (players[i]->GetIsDashing() == true)
			{
				players[i]->ReduceDashDuration();
				
			}

			if (players[i]->GetDashDuration() <= 0)
			{
				players[i]->SetIsDashing(false);
			}
		}
	}

}

void LevelShowcase::UpdateUI()
{
	int playerNumber = 4; // Change later
	float uiWidth = 215.f;
	float uiHeight = 100.f;
	
	float posX = camera.GetCenterX() - (uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH / 2.f) * (playerNumber - 1);
	float posY = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + ((uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT) / 2.f);
	
	for (int i = 0; i < objectsList.size(); i++)
	{
		UiObject* ui = dynamic_cast<UiObject*>(objectsList[i]);
		if (ui != nullptr) 
		{
			ui->SetPosition(glm::vec3(posX + (ui->getNumOwner() * uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH), posY, 0));
			ui->SetSize(uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);
			
			//posX += uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH;
		}
	}
}

void LevelShowcase::LevelDraw()
{
	// Collider position update
	for (int i = 0; i < objectsList.size(); i++)
	{
		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		PlayerHitboxObject* hitbox = dynamic_cast<PlayerHitboxObject*>(objectsList[i]);
		GizmosObject* gizmos = dynamic_cast<GizmosObject*>(objectsList[i]);

		if (player != nullptr)
		{
			player->GetCollider()->Update(player->getSize(), player->getPos());

			glm::vec3 attackSize = glm::vec3(player->getSize().x / 4, player->getSize().y / 4, 0);
			glm::vec3 attackPos = glm::vec3(
				player->getPos().x + (player->GetCurrentDirection().x * 128.f), 
				player->getPos().y - (player->GetCurrentDirection().y * 128.f), 
				0);
			player->GetAttackColliderObject()->SetSize(attackSize.x, attackSize.y);
			player->GetAttackColliderObject()->SetPosition(attackPos);
			player->GetAttackCollider()->Update(attackSize, attackPos);

			// KK_TRACE("{0} groundColX = {1}, groundColY = {2}", player->GetPlayerNumber(), groundColX[player->GetPlayerNumber()], groundColY[player->GetPlayerNumber()]);
			glm::vec3 groundCheckSize = glm::vec3
			(
				groundColX[player->GetPlayerNumber()],
				groundColY[player->GetPlayerNumber()],
				0
			);

			glm::vec3 groundCheckPos = glm::vec3
			(
				player->getPos().x,
				player->getPos().y - 128.f,
				0
			);

			player->GetGroundColliderObject()->SetSize(groundCheckSize.x, groundCheckSize.y);
			player->GetGroundColliderObject()->SetPosition(groundCheckPos);
			player->GetGroundCollider()->Update(groundCheckSize, groundCheckPos);

			/*players[i + playerNum]->GetAttackColliderObject()->SetPosition(glm::vec3(
				players[i + playerNum]->getPos().x + players[i + playerNum]->GetCurrentDirection().x,
				players[i + playerNum]->getPos().y + players[i + playerNum]->GetCurrentDirection().y,
				0));*/
		}
		else if (hitbox == nullptr)
		{
			EntityObject* object = dynamic_cast<EntityObject*>(objectsList[i]);
			if (object != nullptr)
			{
				object->GetCollider()->Update(object->getSize(), object->getPos());
			}
		}
	}

	GameEngine::GetInstance()->Render(objectsList);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	for (int i = 0; i < 4; i++)
	{
		ImGui::SeparatorText("");
		ImGui::Text("Player %d", i);
		ImGui::Text("Position: %f, %f, %f", players[i]->getPos().x, players[i]->getPos().y, players[i]->getPos().z);
		ImGui::Text("isShooting: %s", players[i]->GetIsShooting() ? "true" : "false");
		ImGui::Text("isAiming: %s", players[i]->GetIsAiming() ? "true" : "false");
		ImGui::Text("isSlow: %s", players[i]->GetIsSlow() ? "true" : "false");
		ImGui::Text("isDashing: %s", players[i]->GetIsDashing() ? "true" : "false");
		ImGui::Text("isKnockback: %s", players[i]->GetIsKnockback() ? "true" : "false");
		ImGui::Text("isStun: %s", players[i]->GetIsStun() ? "true" : "false");
		ImGui::Text("isOnGround: %s", players[i]->GetIsOnGround() ? "true" : "false");

		if (ImGui::Button(buttonName[i]))
			clicked[i]++;
		if (clicked[i] & 1)
		{
			ImGui::SameLine();
			ImGui::Text("Thanks for clicking me!");
		}

		ImGui::InputFloat(groundColXName[i], &groundColX[i], 2.0f, 10.0f, "%.3f");
		ImGui::InputFloat(groundColYName[i], &groundColY[i], 2.0f, 10.0f, "%.3f");
	}
	


	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());


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

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

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

void LevelShowcase::GroundTileRefactor()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (i == 0 ||
				i == MAP_HEIGHT - 1 ||
				j == 0 ||
				j == MAP_WIDTH - 1)
			{
				continue;
			}

			if (tilesList[i][j] == nullptr)
			{
				continue;
			}

			// currentGroundTile[i][j] = tilesList[i][j]->GetIsBroke() ? 0 : 1;


			int flag = currentGroundTile[i][j];


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
				// tilesList[i][j]->GetCollider()->GetGizmos()->SetIsActive(false);
				tilesList[i][j]->DisableOverlaySprite();

				if (currentGroundTile[i - 1][j] == 0)
				{
					// blank
					pos = { 99, 99 };
				}
				else
				{
					
					int upperPos = i - 1;

					std::bitset<8> surround;
					surround[0] = currentGroundTile[upperPos - 1][j];
					surround[1] = currentGroundTile[upperPos - 1][j + 1];
					surround[2] = currentGroundTile[upperPos][j + 1];
					surround[3] = currentGroundTile[upperPos + 1][j + 1];
					surround[4] = currentGroundTile[upperPos + 1][j];
					surround[5] = currentGroundTile[upperPos + 1][j - 1];
					surround[6] = currentGroundTile[upperPos][j - 1];
					surround[7] = currentGroundTile[upperPos - 1][j - 1];

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
						pos = { 99, 99 };
						// std::cout << "blob_lookup_table.end()" << std::endl;
					}
				}

			}
			else
			{
				std::bitset<8> surround;
				surround[0] = currentGroundTile[i - 1][j];
				surround[1] = currentGroundTile[i - 1][j + 1];
				surround[2] = currentGroundTile[i][j + 1];
				surround[3] = currentGroundTile[i + 1][j + 1];
				surround[4] = currentGroundTile[i + 1][j];
				surround[5] = currentGroundTile[i + 1][j - 1];
				surround[6] = currentGroundTile[i][j - 1];
				surround[7] = currentGroundTile[i - 1][j - 1];

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
					pos = { 99, 99 };
					// std::cout << "blob_lookup_table.end()" << std::endl;
				}
			}

			// std::cout << flag << ",";

			if (pos.first != 99)
			{
				tilesList[i][j]->GetSpriteRenderer()->ShiftTo(pos.first - 1, pos.second - 1);
			}
			else
			{
				tilesList[i][j]->SetIsActive(false);
			}


			// std::cout << "posX = " << obj->getPos().x << " posY = " << obj->getPos().y << std::endl;
		}
		// std::cout << std::endl;
	}
}

void LevelShowcase::TileImport(std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> &TileBuffer, std::string fileName) {
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

void LevelShowcase::UsingAbility(int numPlayer, PlayerObject::AbilityButton button) {

	PlayerObject::Ability idAbility = players[numPlayer]->GetAbilityByButton(button);
	// std::cout << "idAbility " << idAbility << std::endl;
	if (players[numPlayer]->GetCooldown(button) <= 0) {
		switch (idAbility) {

		case PlayerObject::Ability::Fireball:
			if (!players[numPlayer]->GetIsAiming()) {
				AimFireball(numPlayer, button);
				break;
			}
			else if (players[numPlayer]->GetIsAiming())
			{
				if (players[numPlayer]->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Fireball) {
					ShootFireball(numPlayer, button);
					break;
				}

			}
			break;

		case PlayerObject::Ability::Trap:
			Trap(numPlayer, button);
			break;
		case PlayerObject::Ability::Dash:
			Dash(numPlayer, button);
			break;

		case PlayerObject::Ability::TNT:
			if (!players[numPlayer]->GetIsTNT()) {
				TNT(numPlayer, button);
			}
			else if (players[numPlayer]->GetIsTNT()) {
				for (int i = 0; i < objectsList.size(); i++) // find tnt
				{
					TrapObject* realTnt = dynamic_cast<TrapObject*>(objectsList[i]);
					if (realTnt != NULL) {
						if (realTnt->GetType() == TrapObject::TypeTrap::Tnt && realTnt->GetNumOwner() == numPlayer) {
							realTnt->SetIsCanKnockback(true);
							realTnt->SetIsActive(true);
							realTnt->GetCollider()->Update(glm::vec3(500, 500, 0), realTnt->getPos());
							players[numPlayer]->SetAbilityCooldown(button, 3);
							players[numPlayer]->SetIsTNT(false);

						}
					}

				}
			}
			break;

		case PlayerObject::Ability::Teleport:
			if (!players[numPlayer]->GetIsAiming()) {
				if (players[numPlayer]->GetIsShooting()) {
					for (int i = 0; i < objectsList.size(); i++) // find teleport
					{
						ProjectileObject* Teleport = dynamic_cast<ProjectileObject*>(objectsList[i]);
						if (Teleport != NULL) {
							if (Teleport->GetType() == ProjectileObject::TypeProjectile::Teleport && Teleport->GetOwner()->GetPlayerNumber() == numPlayer) {
								players[numPlayer]->SetPosition(Teleport->getPos());
								players[numPlayer]->SetIsShooting(false);
								objectsList.erase(objectsList.begin() + i);
								players[numPlayer]->SetAbilityCooldown(button, 6);
							}
						}
					}
					break;
				}
				AimTeleport(numPlayer, button);
				break;
			}
			else if (players[numPlayer]->GetIsAiming())
			{
				if (players[numPlayer]->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Teleport) {
					ShootTeleport(numPlayer, button);
					break;
				}

			}
			break;

		case PlayerObject::Ability::Bola:
			if (!players[numPlayer]->GetIsAiming()) {
				AimBola(numPlayer, button);
				break;
			}
			else if (players[numPlayer]->GetIsAiming())
			{
				if (players[numPlayer]->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Bola) {
					ShootBola(numPlayer, button);
					break;
				}

			}
			break;

		case PlayerObject::Ability::Cleave:
			if (!players[numPlayer]->GetIsAiming()) {
				AimCleave(numPlayer, button);
				break;
			}
			else if (players[numPlayer]->GetIsAiming())
			{
				if (players[numPlayer]->GetHoldingProjectile() == ProjectileObject::TypeProjectile::Cleave) {
					ShootCleave(numPlayer, button);
					break;
				}

			}
			break;
		}

	}
}

void LevelShowcase::AimFireball(int numPlayer, PlayerObject::AbilityButton button)
{
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Fireball);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Bomb")->second);
	projectile->SetTexture(spriteList.find("Bomb")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Fireball);
	projectile->SetIsCanKnockback(true);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	//objectsList.push_back(projectile->GetCollider()->GetGizmos());
}

void LevelShowcase::ShootFireball(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsAiming(false);
	for (int j = 0; j < objectsList.size(); j++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
		if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Fireball) {
			projectile->SetLifeTime(2);
			projectile->SetIsShooting(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, 6);
}

void LevelShowcase::Trap(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetAbilityCooldown(button, 3);
	TrapObject* Trap = new TrapObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->SetTexture(spriteList.find("Trap")->second.texture);
	Trap->SetPosition(players[numPlayer]->getPos());
	Trap->SetSize(128.f, -128.f);
	Trap->SetNumOwner(players[numPlayer]->GetPlayerNumber());
	Trap->SetType(TrapObject::TypeTrap::Trap);
	Trap->SetIsActive(true);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(Trap);
	//std::cout << "place trap" << std::endl;
}

void LevelShowcase::Dash(int num, PlayerObject::AbilityButton button) {
	players[num]->SetAbilityCooldown(button, 3);
	players[num]->SetIsDashing(true);
	players[num]->SetDashDuration(0.4f);
}

void LevelShowcase::TNT(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsTNT(true);
	TrapObject* TNT = new TrapObject();
	TNT->SetSpriteInfo(spriteList.find("TNT")->second);
	TNT->SetTexture(spriteList.find("TNT")->second.texture);
	TNT->SetPosition(players[numPlayer]->getPos());
	TNT->SetSize(128.f, -128.f);
	TNT->SetNumOwner(players[numPlayer]->GetPlayerNumber());
	TNT->SetType(TrapObject::TypeTrap::Tnt);
	//TNT->setIsCanKnockback(true);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(TNT);
}

void LevelShowcase::AimTeleport(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Teleport);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Teleport")->second);
	projectile->SetTexture(spriteList.find("Teleport")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Teleport);
	projectile->SetIsCanKnockback(false);
	projectile->SetIsCanStun(false);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
}

void LevelShowcase::ShootTeleport(int numPlayer, PlayerObject::AbilityButton button) {
	if (players[numPlayer]->GetIsShooting() == false) {
		players[numPlayer]->SetIsShooting(true);
		players[numPlayer]->SetIsAiming(false);
		for (int j = 0; j < objectsList.size(); j++) {
			ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
			if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Teleport) {
				projectile->SetLifeTime(2);
				projectile->SetIsShooting(true);
				players[numPlayer]->SetHoldingProjectile(0);
			}
		}
	}
}

void LevelShowcase::AimBola(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Bola);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Bola")->second);
	projectile->SetTexture(spriteList.find("Bola")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Bola);
	projectile->SetIsCanKnockback(false);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
}

void LevelShowcase::ShootBola(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsAiming(false);
	for (int j = 0; j < objectsList.size(); j++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
		if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Bola) {
			projectile->SetLifeTime(2);
			projectile->SetIsShooting(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, 6);
}

void LevelShowcase::AimCleave(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);
	players[numPlayer]->SetHoldingProjectile(ProjectileObject::TypeProjectile::Cleave);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Cleave")->second);
	projectile->SetTexture(spriteList.find("Cleave")->second.texture);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->SetLifeTime(9999);
	projectile->SetOwner(players[numPlayer]);
	projectile->SetType(ProjectileObject::TypeProjectile::Cleave);
	projectile->SetIsCanKnockback(false);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	players[numPlayer]->SetAbilityCooldown(button, 2);
}

void LevelShowcase::ShootCleave(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsAiming(false);
	for (int j = 0; j < objectsList.size(); j++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
		if (projectile != nullptr && projectile->GetOwner() == players[numPlayer] && projectile->GetType() == ProjectileObject::TypeProjectile::Cleave) {
			projectile->SetLifeTime(2);
			projectile->SetIsShooting(true);
			players[numPlayer]->SetHoldingProjectile(0);
		}
	}
	players[numPlayer]->SetAbilityCooldown(button, 6);
}