#include "LevelShowcase.h"

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
	projectile->setOwner(playerObj);
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
	
	spriteList["Shark_run"] = SpritesheetInfo("Shark_run", "../Resource/Texture/shark_run_test.png", 256, 256, 1024, 256);
	spriteList["Shark_idle"] = SpritesheetInfo("Shart_idle", "../Resource/Texture/shark_Idle_test.png", 256, 256, 256, 256);
	
	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Bomb_icon.png", 256, 256, 256, 256);
	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Trap.png", 512, 512, 512, 512);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/TNT.png", 348, 348, 348, 348);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/EnderPearl.png", 512, 512, 512, 512);
	
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

	

	TileImport(groundTile, "../Resource/Texture/Tilemap1.txt");

	// Create and Initialize 4 players object

	float map_left = -1280.f;
	float map_top = 1080.f;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			int flag = groundTile[i][j];

			// currentGroundTile[i][j] = groundTile[i][j];

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
					// blank
					pos = { 99, 99 };
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
						pos = { 99, 99 };
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
					pos = { 99, 99 };
					// std::cout << "blob_lookup_table.end()" << std::endl;
				}
			}

			// std::cout << flag << ",";

			if (pos.first != 99)
			{
				TileObject* obj = new TileObject();
				obj->SetSpriteInfo(spriteList.find("Blobtile")->second);
				obj->GetSpriteRenderer()->ShiftTo(pos.first - 1, pos.second - 1);
				obj->SetTexture(spriteList.find("Blobtile")->second.texture);
				obj->SetSize(128.f, -128.f);
				obj->SetPosition(glm::vec3(map_left + (j * 126.f), map_top - (i * 126.f), 0));
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
				/*obj->groundTileInfo = &currentGroundTile;

				obj->SetTilePosition(i, j);*/

				objectsList.push_back(obj);
				objectsList.push_back(obj->GetCollider()->GetGizmos());
				objectsList.push_back(obj->GetOverlaySprite());
			}
			

			// std::cout << "posX = " << obj->getPos().x << " posY = " << obj->getPos().y << std::endl;
		}
		// std::cout << std::endl;
	}


	// Create and Initialize 4 players object

	// Example Code

	PlayerObject* p1 = new PlayerObject();
	// Assign all animation property
	p1->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p1->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p1->GetSpriteRenderer()->SetFrame(10);
	// Set Sprite
	p1->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	// Set Start Position
	p1->SetPosition(glm::vec3(-800.f, -700.f, 0));
	// Set Player Number
	p1->SetPlayerNumber(0);
	// Store inside player array
	objectsList.push_back(p1);
	playerSize++;
	players[0] = p1;

	PlayerObject* p2 = new PlayerObject();
	p2->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p2->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p2->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	p2->SetPosition(glm::vec3(800.f, -700.f, 0));
	p2->GetSpriteRenderer()->SetFrame(10);
	p2->SetPlayerNumber(1);
	objectsList.push_back(p2);
	playerSize++;
	players[1] = p2;

	PlayerObject* p3 = new PlayerObject();
	p3->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p3->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p3->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	p3->SetPosition(glm::vec3(800.f, 700.f, 0));
	p3->GetSpriteRenderer()->SetFrame(10);
	p3->SetPlayerNumber(2);
	objectsList.push_back(p3);
	playerSize++;
	players[2] = p3;

	PlayerObject* p4 = new PlayerObject();
	p4->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	p4->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	p4->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	p4->SetPosition(glm::vec3(-800.f, 700.f, 0));
	p4->GetSpriteRenderer()->SetFrame(10);
	p4->SetPlayerNumber(3);
	objectsList.push_back(p4);
	playerSize++;
	players[3] = p4;

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
	objectsList.push_back(players[3]->GetCollider()->GetGizmos());

	


	//create Ui by PlayerObject
	int playerSize = 4;
	int count = 0;

	for (int i = 0; i < 4; i++) {

		if (count == 0) {

			UiObject* uiSkills = new UiObject();
			uiSkills->SetSpriteInfo(spriteList.find("Xoey_UI")->second);
			uiSkills->setNumOwner(0);
			objectsList.push_back(uiSkills);
			count++;

			// std::cout << "create Ui xoey" << std::endl;
		}
		else if (count == 1) {

			UiObject* uiSkills = new UiObject();
			uiSkills->SetSpriteInfo(spriteList.find("Ham_UI")->second);
			uiSkills->setNumOwner(1);
			objectsList.push_back(uiSkills);
			count++;
			// std::cout << "create Ui Ham" << std::endl;
		}
		else if (count == 2) {

			UiObject* uiSkills = new UiObject();
			uiSkills->SetSpriteInfo(spriteList.find("Byssa_UI")->second);
			uiSkills->setNumOwner(2);
			objectsList.push_back(uiSkills);
			count++;
			// std::cout << "create Ui byssa" << std::endl;
		}
		else if (count == 3) {

			UiObject* uiSkills = new UiObject();
			uiSkills->SetSpriteInfo(spriteList.find("Crunk_UI")->second);
			uiSkills->setNumOwner(3);
			objectsList.push_back(uiSkills);
			count++;
			// std::cout << "create Ui crunk" << std::endl;
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

			// KK_TRACE("Controller player : {0} = {1}, {2}", i, norAxisX, norAxisY);
			
			// update facing
			if (abs(axisX) > 0.2f) 
			{ 
				players[i + playerNum]->UpdateFacingSide(isPositiveX); 
			}

			if (players[i + playerNum]->GetIsAiming() == false)
			{
				players[i + playerNum]->SetVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
			}

			//Aim
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle))
			{
				Teleport(i, PlayerObject::AbilityButton::Triangle);
			}

			//Shoot
			if (Joystick::GetButtonUp(i, Joystick::Button::Triangle))
			{
				ShootFireball(i, PlayerObject::AbilityButton::Triangle);
			}

			if (players[i + playerNum]->GetIsAiming())
			{
				for (int j = 0; j < objectsList.size(); j++) {
					ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
					if (projectile != nullptr && i + playerNum == projectile->GetOwner()->GetPlayerNumber()) {
						if (abs(norAxisX) > 0 || norAxisY > 0) {
							projectile->setVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
						}
						projectile->SetPosition(players[i + playerNum]->getPos() + (projectile->getVelocity() * glm::vec3(15.f, 15.f, 0.f)));
					}
				}
			}

			//Place trap
			if (Joystick::GetButtonDown(i, Joystick::Button::Circle))
			{
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Circle) <= 0)
				{
					SetTrap(i, PlayerObject::AbilityButton::Circle);
				}
			}

			if (Joystick::GetButtonDown(i, Joystick::Button::Cross))
			{
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Cross) <= 0)
				{
					TNT(i, PlayerObject::AbilityButton::Cross);
				}
			}

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

			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{
				players[playerNum]->HitAimingTile();
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

		PlayerHitboxObject* hitbox = dynamic_cast<PlayerHitboxObject*>(objectsList[i]);
		

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
				
				Collider* col1 = entity1->GetCollider();
				Collider* col2 = entity2->GetCollider();

				glm::vec2 delta = glm::vec2(abs(entity1->getPos().x - entity2->getPos().x),
					abs(entity1->getPos().y - entity2->getPos().y));

				glm::vec2 previousDelta = glm::vec2(abs(col1->GetPreviousPos().x - col2->GetPreviousPos().x),
					abs(col1->GetPreviousPos().y - col2->GetPreviousPos().y));

				float overlapX = (abs(col1->GetHalfSize().x)) + (abs(col2->GetHalfSize().x)) - delta.x;
				float overlapY = (abs(col1->GetHalfSize().y)) + (abs(col2->GetHalfSize().y)) - delta.y;

				// for resolve collider
				float previousOverlapX = (abs(col1->GetHalfSize().x)) + (abs(col2->GetHalfSize().x)) - previousDelta.x;
				float previousOverlapY = (abs(col1->GetHalfSize().y)) + (abs(col2->GetHalfSize().y)) - previousDelta.y;

				if (overlapX > 0 && overlapY > 0)
				{

					/*if (hitbox != nullptr)
					{
						KK_TRACE("Hitbox size = {0}, {1}", hitbox->GetCollider()->GetSize().x, hitbox->GetCollider()->GetSize().y);
						KK_TRACE("Hitbox pos = {0}, {1}", hitbox->getPos().x, hitbox->getPos().y);
					}*/

					if (previousCollisions.find({ col1, col2 }) == previousCollisions.end())
					{
						// KK_TRACE("enter");
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
						// KK_TRACE("OnColliderExit");

						entity1->OnColliderExit(entity2->GetCollider());
						// entity2->OnColliderExit(entity1->GetCollider());
					}
				}

				entity2->GetCollider()->SetPreviousPos(entity2->getPos());

			}
		}
		entity1->GetCollider()->SetPreviousPos(entity1->getPos());
	}

	previousCollisions = currentCollisions;
	currentCollisions.clear();

	/*KK_TRACE("preiousCollisions size = {0}", previousCollisions.size());
	KK_TRACE("currentCollisions size = {0}", currentCollisions.size());*/
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
				players[projectile->GetOwner()->GetPlayerNumber()]->SetIsShooting(false);
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
			/*if (time[i + playerNum] >= 1.0f && players[i + playerNum]->GetCooldown(static_cast<PlayerObject::AbilityButton>(j)) > 0)
			{
				players[i + playerNum]->ReduceAbilityCooldown(static_cast<PlayerObject::AbilityButton>(j));
				time[i + playerNum] = 0.0f;
			}*/
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
			ui->SetPosition(glm::vec3(posX, posY, 0));
			ui->SetSize(uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH, -uiHeight * camera.GetCameraHeight() / SCREEN_HEIGHT);
			
			posX += uiWidth * camera.GetCameraWidth() / SCREEN_WIDTH;
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
			glm::vec3 attackPos = glm::vec3(player->getPos().x + 256.f, player->getPos().y, 0);
			player->GetAttackColliderObject()->SetSize(attackSize.x, attackSize.y);
			player->GetAttackColliderObject()->SetPosition(attackPos);
			player->GetAttackCollider()->Update(attackSize, attackPos);
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

			groundTile[i][j] = tilesList[i][j]->GetIsBroke() ? 0 : 1;


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
					// blank
					pos = { 99, 99 };
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
						pos = { 99, 99 };
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

void LevelShowcase::AimFireball(int numPlayer, PlayerObject::AbilityButton button)
{
	players[numPlayer]->SetVelocity(0, 0, false, false);
	players[numPlayer]->SetIsAiming(true);

	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("TNT")->second);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->setLifeTime(9999.f);
	projectile->setOwner(players[numPlayer]);
	projectile->setType(ProjectileObject::TypeProjectile::Fireball);
	projectile->setIsCanKnockback(true);
	objectsList.push_back(projectile);

	KK_TRACE("Create Fireball and Aim. Owner = {0}", projectile->GetOwner()->GetPlayerNumber());
}

void LevelShowcase::ShootFireball(int numPlayer, PlayerObject::AbilityButton button)
{
	if (players[numPlayer]->GetIsShooting() == false) 
	{
		players[numPlayer]->SetIsShooting(true);
		players[numPlayer]->SetIsAiming(false);

		for (int j = 0; j < objectsList.size(); j++) 
		{
			ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);

			if (projectile != nullptr) 
			{
				projectile->setLifeTime(5);

				KK_TRACE("Player {0} is Shooting Fireball", numPlayer);
			}
		}
	}
}

void LevelShowcase::SetTrap(int numPlayer, PlayerObject::AbilityButton button)
{
	players[numPlayer]->SetAbilityCooldown(button, 3);
	TrapObject* Trap = new TrapObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->SetPosition(players[numPlayer]->getPos());
	Trap->SetSize(128.f, -128.f);
	Trap->setNumOwner(players[numPlayer]->GetPlayerNumber());
	Trap->setType(TrapObject::TypeTrap::Trap);

	objectsList.push_back(Trap);

	KK_TRACE("Player {0} is set trap. trap type = {0}", static_cast<int>(TrapObject::TypeTrap::Trap));
}

void LevelShowcase::Dash(int numPlayer, PlayerObject::AbilityButton button)
{
	players[numPlayer]->SetAbilityCooldown(button, 3);
	players[numPlayer]->SetIsDashing(true);
	players[numPlayer]->SetDashDuration(2);

	KK_TRACE("Player {0} is dashing", numPlayer);
}

void LevelShowcase::TNT(int numPlayer, PlayerObject::AbilityButton button)
{
	players[numPlayer]->setIsTNT(true);
	TrapObject* TNT = new TrapObject();
	TNT->SetSpriteInfo(spriteList.find("TNT")->second);
	TNT->SetPosition(players[numPlayer]->getPos());
	TNT->SetSize(128.f, -128.f);
	TNT->setNumOwner(players[numPlayer]->GetPlayerNumber());
	TNT->setType(TrapObject::TypeTrap::Tnt);
	objectsList.push_back(TNT);

	KK_TRACE("Create TNT. Owner = {0}", numPlayer);
}

void LevelShowcase::Teleport(int numPlayer, PlayerObject::AbilityButton button)
{
	players[numPlayer]->SetIsShooting(true);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Teleport")->second);
	projectile->SetPosition(players[numPlayer]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->setLifeTime(3.f);
	projectile->setOwner(players[numPlayer]);
	projectile->setType(ProjectileObject::TypeProjectile::Teleport);
	projectile->setIsCanKnockback(false);
	projectile->setVelocity(
		abs(players[numPlayer]->GetVelocity().x) / 5, 
		abs(players[numPlayer]->GetVelocity().y) / 5, 
		players[numPlayer]->getXIsPositive(), 
		players[numPlayer]->getYIsPositive()
	);
	objectsList.push_back(projectile);

	KK_TRACE("Create Teleport. Owner = {0}", projectile->GetOwner()->GetPlayerNumber());
}