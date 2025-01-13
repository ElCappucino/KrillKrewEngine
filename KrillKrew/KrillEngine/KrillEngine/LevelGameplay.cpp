#include "LevelGameplay.h"

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void LevelGameplay::LevelLoad()
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
	//cout << "Load Level" << endl;
}

void LevelGameplay::LevelInit()
{

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
																  (SCREEN_WIDTH / 2),
																 -(SCREEN_HEIGHT / 2),
																  (SCREEN_HEIGHT / 2));

	GameEngine::GetInstance()->GetRenderer()->SetClearColor(1.0f, 1.0f, 200.0f / 255);
	timer = Timer::Instance();

	// Create and Initialize 4 players object

	// Example Code
	PlayerObject* obj1 = new PlayerObject();
	obj1->GetCollider()->SetCollisionType(Collider::Kinematic);
	obj1->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj1->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj1->SetIsAnimated(true);
	obj1->GetSpriteRenderer()->SetFrame(10);
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-200.f, -200.f, 0));
	obj1->setNumber(0);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj1->setAbility(0, 1);
	obj1->setAbility(1, 2);
	obj1->setAbility(2, 3);
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
	obj2->SetPosition(glm::vec3(200.f, -200.f, 0));
	obj2->setNumber(1);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj2->setAbility(0, 2);
	obj2->setAbility(1, 2);
	obj2->setAbility(2, 2);
	objectsList.push_back(obj2);
	playerSize++;
	players[1] = obj2;

	PlayerObject* obj3 = new PlayerObject();
	obj3->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj3->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-200.f, 200.f, 0));
	obj3->setNumber(2);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj3->setAbility(0, 3);
	obj3->setAbility(1, 1);
	obj3->setAbility(2, 2);
	objectsList.push_back(obj3);
	playerSize++;
	players[2] = obj3;
	

	PlayerObject* obj4 = new PlayerObject();
	obj4->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj4->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj4->SetSize(256.f, -256.f);
	obj4->SetPosition(glm::vec3(200.f, 200.f, 0));
	obj4->setNumber(3);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	objectsList.push_back(obj4);
	playerSize++;
	players[3] = obj4;

	TrapObject* trap1 = new TrapObject();
	trap1->GetCollider()->SetCollisionType(Collider::Trigger);
	trap1->SetSpriteInfo(spriteList.find("Trap")->second);
	trap1->SetTexture(spriteList.find("Trap")->second.texture);
	trap1->SetSize(256.f, -256.f);
	trap1->SetPosition(glm::vec3(500.f, 500.f, 0));
	objectsList.push_back(trap1);

	objectsList.push_back(players[0]->GetCollider()->GetGizmos());
	objectsList.push_back(players[1]->GetCollider()->GetGizmos());
	objectsList.push_back(players[2]->GetCollider()->GetGizmos());
	objectsList.push_back(players[3]->GetCollider()->GetGizmos());
	objectsList.push_back(trap1->GetCollider()->GetGizmos());

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
				std::cout << "create Ui xoey" << std::endl;
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
				std::cout << "create Ui Ham" << std::endl;
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
				std::cout << "create Ui byssa" << std::endl;
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
				std::cout << "create Ui crunk" << std::endl;
			}
		}
	}

	std::cout << "Init Level" << std::endl;
}

void LevelGameplay::LevelUpdate()
{
	dt++;

	// UpdateInput();
	UpdateInput();

	for(int i = 0; i < playerSize; i++){
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

	// slowness & dash
	//UpdateMovement();

	//Ui Skills
	UpdateUI();

}

void LevelGameplay::UpdateInput()
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
			else if (axisX < 0)
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


			if (players[i + playerNum]->getIsAiming() == false && !players[i + playerNum]->getIsDash())
			{
				players[i + playerNum]->setVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
			}

			//Select ability
			if (Joystick::GetButtonDown(i, Joystick::Button::R1)) {
				std::cout << "SDL_NumJoysticks() > 0" << std::endl;
			}


			//Aim
			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{
				std::cout << "Shoot " << i + playerNum << std::endl;
				if (players[i + playerNum]->getIsShooting() == false && players[i + playerNum]->getIsAiming() == false) {
					players[i + playerNum]->setVelocity(0, 0, isPositiveX, isPositiveY);
					players[i + playerNum]->setIsAiming(true);
					ProjectileObject* projectile = new ProjectileObject();
					projectile->SetSpriteInfo(spriteList.find("Bomb")->second);
					projectile->SetTexture(spriteList.find("Bomb")->second.texture);
					projectile->SetPosition(players[i + playerNum]->getPos());
					projectile->SetSize(256.f, -256.f);
					projectile->setLifeTime(9999);
					projectile->setNumOwner(players[i + playerNum]->getNumber());
					std::cout << "Owner " << projectile->getNumOwner() << std::endl;
					objectsList.push_back(projectile);
					//objectsList.push_back(projectile->GetCollider()->GetGizmos());
				}
				usingAbility(i, 1);
			}
			//Shoot
			if (Joystick::GetButtonUp(i, Joystick::Button::Square))
			{
				std::cout << "Shoot " << i + playerNum << std::endl;
				if (players[i + playerNum]->getIsShooting() == false) {
					players[i + playerNum]->setIsShooting(true);
					players[i + playerNum]->setIsAiming(false);
					for (int j = 0; j < objectsList.size(); j++) {
						ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
						if (projectile != nullptr) {
							projectile->setLifeTime(5);
						}
					}
				}
				usingAbility(i, 1);
			}

			if (players[i + playerNum]->getIsAiming())
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
			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{
				std::cout << "Square" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::Cross))
			{
				std::cout << "Cross" << std::endl;
			}

			//Dash
			if (Joystick::GetButtonDown(i, Joystick::Button::Circle))
			{
				if (players[i + playerNum]->getCooldown(2) <= 0) {
					players[i + playerNum]->setCooldown(2, 3);
					players[i + playerNum]->setIsDash(true);
					players[i + playerNum]->setDurationDash(2);
				}
				usingAbility(i, 3);

			}
			if (Joystick::GetButtonDown(i, Joystick::Button::L1))
			{
				std::cout << "L1" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::R1))
			{
				std::cout << "R1" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::LeftStickDown))
			{
				std::cout << "LeftStickDown" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::RightStickDown))
			{
				std::cout << "RightStickDown" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Up))
			{
				std::cout << "DPAD_Up" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Down))
			{
				std::cout << "DPAD_Down" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Left))
			{
				std::cout << "DPAD_Left" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::DPAD_Right))
			{
				std::cout << "DPAD_Right" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::ShareButton))
			{
				std::cout << "Back" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::P5Button))
			{
				std::cout << "Guide" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::OptionsButton))
			{
				std::cout << "Start" << std::endl;
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::P5Button))
			{
				/*GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELMAPTEST;
				GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELLOADING;*/
			}
			if (Joystick::GetButtonDown(i, Joystick::Button::Touchpad))
			{
				std::cout << "SDL_CONTROLLER_BUTTON_TOUCHPAD" << std::endl;
			}

			//Trap
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle))
			{
				std::cout << "Triangle" << std::endl;
				if (players[i + playerNum]->getCooldown(1) <= 0) {
					//players[i + playerNum]->setCooldown(1, 3);
					//TrapObject* Trap = new TrapObject();
					//Trap->SetSpriteInfo(spriteList.find("Trap")->second);
					//Trap->SetTexture(spriteList.find("Trap")->second.texture);
					//Trap->SetPosition(players[i + playerNum]->getPos());
					//Trap->SetSize(128.f, -128.f);
					//Trap->setNumOwner(players[i + playerNum]->getNumber());
					////std::cout << "Owner " << Trap->getNumOwner() << std::endl;
					//objectsList.push_back(Trap);
					trap(i + playerNum);
					usingAbility(i, 2);
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

			players[i + playerNum]->Translate(players[i + playerNum]->getVelocity());
		}

	}
}

void LevelGameplay::UpdateCollision()
{
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
				if (trap->getNumOwner() != player2->getNumber()) {
					Collider col1 = *trap->GetCollider();
					Collider col2 = *player2->GetCollider();

					glm::vec2 delta = glm::vec2(abs(trap->getPos().x - player2->getPos().x),
						abs(trap->getPos().y - player2->getPos().y));

					float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
					float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

					if (overlapX > 0 && overlapY > 0)
					{
						std::cout << "Trap :" << trap->getNumOwner() << " hit " << "Player" << player2->getNumber() << std::endl;
						player2->setDurationSlowness(100);
						player2->setIsSlowness(true);
						objectsList.erase(objectsList.begin() + i);
					}
				}
			}
		}
	}

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
				if (projectile->getNumOwner() != player->getNumber()) 
				{
					Collider col1 = *projectile->GetCollider();
					Collider col2 = *player->GetCollider();

					glm::vec2 delta = glm::vec2(abs(projectile->getPos().x - player->getPos().x),
						abs(projectile->getPos().y - player->getPos().y));

					float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
					float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

					if (overlapX > 0 && overlapY > 0)
					{
						players[projectile->getNumOwner()]->setIsShooting(false);
						objectsList.erase(objectsList.begin() + i);
					}
				}
			}
		}
	}
}

void LevelGameplay::UpdateProjectile()
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
				players[projectile->getNumOwner()]->setIsShooting(false);
				objectsList.erase(objectsList.begin() + i);
			}

			projectile->Translate(projectile->getVelocity());
		}

	}
}

void LevelGameplay::UpdateCooldown()
{
	for (int i = 0; i < SDL_NumJoysticks() + playerNum; i++)
	{
		timer->tick();
		timer->reset();
		time[i + playerNum] += timer->getDeltaTime();

		//slowness & dash
		UpdateMovement();

		for (int j = 0; j < 3; j++)
		{
			if (time[i + playerNum] >= 1.0f && players[i + playerNum]->getCooldown(j) > 0)
			{
				std::cout << j << std::endl;
				players[i + playerNum]->reduceCooldown(j);
				
			}
			
		}
		if (time[i + playerNum] >= 1.0f) {
			time[i + playerNum] = 0.0f;
		}
	}
}

void LevelGameplay::UpdateMovement()
{
	for (int i = 0; i < SDL_NumJoysticks() + playerNum; i++)
	{
		if (time[i + playerNum] >= 1.0f && players[i + playerNum]->getIsSlowness() == true)
		{
			players[i + playerNum]->reduceDurationSlowness();
		}

		if (players[i]->getDurationSlowness() <= 0)
		{
			players[i]->setIsSlowness(false);
		}

		if (time[i + playerNum] >= 1.0f && players[i + playerNum]->getIsDash() == true) {
			std::cout << "reduce dash time" << std::endl;
			players[i]->reduceDurationDash();
		}

		if (players[i + playerNum]->getDurationDash() <= 0)
		{
			players[i]->setIsDash(false);
		}
	}
}

void LevelGameplay::UpdateUI()
{
	for (int i = 0; i < objectsList.size(); i++)
	{
		UiObject* ui = dynamic_cast<UiObject*>(objectsList[i]);
		if (ui != nullptr) {
			//std::cout << "Ui id | " << ui->getNumOwner() << std::endl;
			ui->SetPosition(glm::vec3(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left + (((300 * (ui->getNumOwner() + 1)) - (85 * ui->getNumOwner())) * camera.GetCameraWidth() / 1246),
				GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + (50 * camera.GetCameraHeight() / 720), 0));
			ui->SetSize(215.f * camera.GetCameraWidth() / 1246, -100.f * camera.GetCameraHeight() / 720);
		}
	}
}

void LevelGameplay::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	

	// Collider Gizmos update
	for (int i = 0; i < objectsList.size(); i++)
	{
		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (player != nullptr)
		{
			player->GetCollider()->Update(player->getSize(), player->getPos());
		}
		else
		{
			EntityObject* object = dynamic_cast<EntityObject*>(objectsList[i]);
			if (object != nullptr)
			{
				object->GetCollider()->Update(object->getSize(), object->getPos());
			}
		}


	}

	// cout << "Draw Level" << endl;
}

void LevelGameplay::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();

	//cout << "Free Level" << endl;
}

void LevelGameplay::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	//cout << "Unload Level" << endl;
}

void LevelGameplay::HandleKey(char key)
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
		GameEngine::GetInstance()->GetStateController()->loadingState = GameState::GS_LEVELMAPTEST;
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
		std::cout << "Player " << this->playerNum << std::endl;
		break;
	}
}

void LevelGameplay::HandleMouse(int type, int x, int y)
{
	
}

void LevelGameplay::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) 
{
	
}


void LevelGameplay::usingAbility(int numPlayer, int numberAbility) {

	if (players[numPlayer + playerNum]->getCooldown(numberAbility) <= 0) {
		switch (numberAbility) {

		case 1 :
			if (!players[numPlayer + playerNum]->getIsAiming()) {
				aimFireball(numPlayer + playerNum);
				break;
			}
			else if(players[numPlayer + playerNum]->getIsAiming())
			{
				shootFireball(numPlayer + playerNum);
				break;
			}
			break;

		case 2 :
			trap(numPlayer + playerNum);
			break;

		case 3 :
			dash(numPlayer + playerNum);
			break;
		}
		
	}

}

void LevelGameplay::aimFireball(int num) {
	players[num + playerNum]->setVelocity(0, 0, false, false);
	players[num + playerNum]->setIsAiming(true);
	ProjectileObject* projectile = new ProjectileObject();
	projectile->SetSpriteInfo(spriteList.find("Bomb")->second);
	projectile->SetTexture(spriteList.find("Bomb")->second.texture);
	projectile->SetPosition(players[num + playerNum]->getPos());
	projectile->SetSize(256.f, -256.f);
	projectile->setLifeTime(9999);
	projectile->setNumOwner(players[num + playerNum]->getNumber());
	std::cout << "Owner " << projectile->getNumOwner() << std::endl;
	objectsList.push_back(projectile);
	//objectsList.push_back(projectile->GetCollider()->GetGizmos());
}

void LevelGameplay::shootFireball(int num) {
	if (players[num + playerNum]->getIsShooting() == false) {
		players[num + playerNum]->setIsShooting(true);
		players[num + playerNum]->setIsAiming(false);
		for (int j = 0; j < objectsList.size(); j++) {
			ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
			if (projectile != nullptr) {
				projectile->setLifeTime(5);
			}
		}
	}
}

void LevelGameplay::trap(int num) {
	players[num + playerNum]->setCooldown(1, 3);
	TrapObject* Trap = new TrapObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->SetTexture(spriteList.find("Trap")->second.texture);
	Trap->SetPosition(players[num + playerNum]->getPos());
	Trap->SetSize(128.f, -128.f);
	Trap->setNumOwner(players[num + playerNum]->getNumber());
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(Trap);
}

void LevelGameplay::dash(int num) {
	players[num + playerNum]->setCooldown(2, 3);
	players[num + playerNum]->setIsDash(true);
	players[num + playerNum]->setDurationDash(2);
}
