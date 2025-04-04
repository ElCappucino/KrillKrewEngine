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
	
	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Trap.png", 512, 512, 512, 512);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/TNT.png", 348, 348, 348, 348);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/EnderPearl.png", 512, 512, 512, 512);
	spriteList["Bola"] = SpritesheetInfo("Bola", "../Resource/Texture/Bola.png", 317, 314, 317, 314);
	spriteList["Cleave"] = SpritesheetInfo("Cleave", "../Resource/Texture/Cleave.png", 647, 386, 647, 386);

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
	obj1->SetIsAnimated(true);
	obj1->GetSpriteRenderer()->SetFrame(10);
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-200.f, -200.f, 0));
	obj1->SetPlayerNumber(0);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	// New enum type
	 obj1->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	 obj1->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	 obj1->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Cleave);
	/*obj1->setAbility(0, 5);
	obj1->setAbility(1, 1);
	obj1->setAbility(2, 2);*/
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
	obj2->SetPlayerNumber(1);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj2->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	obj2->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::TNT);
	obj2->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Dash);
	objectsList.push_back(obj2);
	playerSize++;
	players[1] = obj2;

	PlayerObject* obj3 = new PlayerObject();
	obj3->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj3->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-200.f, 200.f, 0));
	obj3->GetSpriteRenderer()->SetFrame(15);
	obj3->SetPlayerNumber(2);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj3->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	obj3->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	obj3->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Dash);
	objectsList.push_back(obj3);
	playerSize++;
	players[2] = obj3;
	

	PlayerObject* obj4 = new PlayerObject();
	obj4->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj4->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj4->SetSize(256.f, -256.f);
	obj4->SetPosition(glm::vec3(200.f, 200.f, 0));
	obj4->GetSpriteRenderer()->SetFrame(15);
	obj4->SetPlayerNumber(3);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj4->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	obj4->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	obj4->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Dash);
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

	for (int i = 0; i < objectsList.size(); i++)
	{
		if (objectsList[i]->GetIsActive() == false)
		{
			objectsList.erase(objectsList.begin() + i);
		}
	}

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
	UpdateMovement();

	//Ui Skills
	UpdateUI();

	//std::cout << time[0] << std::endl;
	//Time update
	UpdateTime();


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

			if (players[i + playerNum]->GetIsKnockback() == false) {
				if (players[i + playerNum]->GetIsStun() == false) {
					if (players[i + playerNum]->GetIsDashing() == false) {
						if (players[i + playerNum]->GetIsAiming() == false)
						{
							players[i + playerNum]->SetVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
						}
						norAxisXOld = norAxisX;
						norAxisYOld = norAxisY;
						isPositiveXOld = isPositiveX;
						isPositiveYOld = isPositiveY;
					}
					else {
						players[i + playerNum]->SetVelocity(abs(norAxisXOld), abs(norAxisYOld), isPositiveXOld, isPositiveYOld);
					}
				}
				
			}
			
			

			//Select ability
			if (Joystick::GetButtonDown(i, Joystick::Button::R1)) {
				std::cout << "SDL_NumJoysticks() > 0" << std::endl;
			}

			//Aim
			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{

			}
			//Shoot
			if (Joystick::GetButtonUp(i, Joystick::Button::Square))
			{

			}

			if (players[i + playerNum]->GetIsAiming() && players[i + playerNum]->GetHoldingProjectile() != 0)
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
			}

			
			//Place trap
			if (Joystick::GetButtonDown(i, Joystick::Button::Square))
			{
				std::cout << "Square" << std::endl;
			}

			//Ability Cross
			if (Joystick::GetButtonDown(i, Joystick::Button::Cross))
			{
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Cross) <= 0) {
					UsingAbility(i + playerNum, PlayerObject::AbilityButton::Cross);
				}
				std::cout << "Cross" << std::endl;
			}

			//Ability Circle
			if (Joystick::GetButtonDown(i, Joystick::Button::Circle))
			{
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Circle) <= 0) {
					/*players[i + playerNum]->setCooldown(2, 3);
					players[i + playerNum]->setIsDash(true);
					players[i + playerNum]->setDurationDash(2);*/
					UsingAbility(i + playerNum, PlayerObject::AbilityButton::Circle);
				}
				

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

			//Ability Triangle
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle))
			{
				std::cout << "Triangle" << std::endl;
				if (players[i + playerNum]->GetCooldown(PlayerObject::AbilityButton::Triangle) <= 0) {
					//players[i + playerNum]->setCooldown(1, 3);
					//TrapObject* Trap = new TrapObject();
					//Trap->SetSpriteInfo(spriteList.find("Trap")->second);
					//Trap->SetTexture(spriteList.find("Trap")->second.texture);
					//Trap->SetPosition(players[i + playerNum]->getPos());
					//Trap->SetSize(128.f, -128.f);
					//Trap->setNumOwner(players[i + playerNum]->getNumber());
					////std::cout << "Owner " << Trap->getNumOwner() << std::endl;
					//objectsList.push_back(Trap);
					//trap(i + playerNum);
					UsingAbility(i + playerNum, PlayerObject::AbilityButton::Triangle);
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

			/*if (Joystick::GetButtonDown(i, Joystick::Button::L1))
			{
				playerNum = 0;
				if (playerNum <= 0) {
					playerNum = 4;
				}
			}*/
			players[1]->Translate(players[1]->GetVelocity());
			players[i + playerNum]->Translate(players[i + playerNum]->GetVelocity());
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
				if (trap->GetPlayerNumber() != player2->GetPlayerNumber()) {
					Collider col1 = *trap->GetCollider();
					Collider col2 = *player2->GetCollider();

					glm::vec2 delta = glm::vec2(abs(trap->getPos().x - player2->getPos().x),
						abs(trap->getPos().y - player2->getPos().y));

					float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
					float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

					if (overlapX > 0 && overlapY > 0)
					{
						std::cout << "Trap :" << trap->GetPlayerNumber() << " hit " << "Player" << player2->GetPlayerNumber() << std::endl;
						if (trap->GetCanKnockback()) {
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
					// OnEnter collider for all types of collision
					entity1->OnColliderEnter(entity2->GetCollider());
					entity2->OnColliderEnter(entity1->GetCollider());

					// resolve collider for kinematic and static
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
}

void LevelGameplay::UpdateProjectile()
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
			if (trap->GetCanKnockback()) {
				objectsList.erase(objectsList.begin() + i);
			}
		}

	}

}

void LevelGameplay::UpdateCooldown()
{
	for (int i = 0; i < /*SDL_NumJoysticks() + playerNum*/ 4 ; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			
			if (time1s >= 1.0f && players[i]->GetCooldown(static_cast<PlayerObject::AbilityButton>(j)) > 0)
			{
				//std::cout << j << std::endl;
				players[i + playerNum]->ReduceAbilityCooldown(j, time1s);
				
			}
		}
		UpdateTime();
	}
}

void LevelGameplay::UpdateMovement()
{
	for (int i = 0; i < /*SDL_NumJoysticks() + playerNum*/ 4; i++)
	{
		if (time1s >= 1.0f && players[i]->GetIsSlow() == true)
		{
			players[i]->ReduceSlowDuration();
		}

		if (players[i]->GetSlowDuration() <= 0)
		{
			players[i]->SetIsSlow(false);
		}

		if (time1s >= 1.0f && players[i]->GetIsDashing() == true) {
			std::cout << "reduce dash time" << std::endl;
			players[i]->ReduceDashDuration();
		}

		if (players[i]->GetDashDuration() <= 0)
		{
			players[i]->SetIsDashing(false);
		}

		if (time05s >= 0.1f && players[i]->GetIsKnockback() == true) {
			
			/*players[i + playerNum]->reduceDurationKnockback();
			std::cout << "DurationKnockback | " << players[i + playerNum]->getDurationKnockback() << std::endl;*/
			glm::vec3 knockbackVelo = players[i]->GetVelocity();
			float knockbackVeloX = abs(knockbackVelo.x) / 5;
			float knockbackVeloY = abs(knockbackVelo.y) / 5;
			/*std::cout << "knockbackVeloX | " << knockbackVeloX << std::endl;
			std::cout << "knockbackVeloY | " << knockbackVeloY << std::endl;*/
			players[i]->SetVelocity(knockbackVeloX / 1.1, knockbackVeloY / 1.1, players[i]->GetXIsPositive(), players[i]->GetYIsPositive());
			//std::cout << "knockbackVeloY | " << knockbackVeloY / 1.1 << std::endl;
		}

		if (players[i]->GetDurationKnockback() <= 0)
		{
			players[i]->SetIsKnockback(false);
			players[i]->SetVelocity(0, 0, false, false);
		}

		if (players[i]->GetIsKnockback() == true && (abs(players[i]->GetVelocity().x) / 5 < 0.05) && (abs(players[i]->GetVelocity().y) / 5 < 0.05))
		{
			players[i]->SetIsKnockback(false);
			players[i]->SetVelocity(0, 0, false, false);
		}
		
		if (time1s >= 1.0f && players[i]->GetIsStun() == true)
		{
			players[i]->ReduceStunDuration();
		}

		if (players[i]->GetStunDuration() <= 0)
		{
			players[i]->SetIsStun(false);
		}
		//UpdateTime();
	}
}

void LevelGameplay::UpdateKnockback(DrawableObject* obj1, DrawableObject* obj2) {
	ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(obj1);
	TrapObject* trap = dynamic_cast<TrapObject*>(obj1);
	PlayerObject* player = dynamic_cast<PlayerObject*>(obj2);
	
	if (player != NULL && projectile != NULL && projectile->GetCanKnockback()) {
		if (projectile->GetOwner()->GetPlayerNumber() != player->GetPlayerNumber()) {
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
	if (player != NULL && trap != NULL && trap->GetCanKnockback()) {
		if (trap->GetPlayerNumber() != player->GetPlayerNumber()) {
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

void LevelGameplay::UpdateTime() {
	
		timer->tick();
		timer->reset();
		time1s += timer->getDeltaTime();
		time05s += timer->getDeltaTime();


		if (time1s >= 1.01f) {
			time1s = 0.0f;
			//std::cout << "Time | " << time[i + playerNum] << std::endl;
		}

		if (time05s >= 0.11f) {
			time05s = 0.0f;
			//std::cout << "Time | " << time[i + playerNum] << std::endl;
		}
	
}

void LevelGameplay::UpdateUI()
{
	for (int i = 0; i < objectsList.size(); i++)
	{
		UiObject* ui = dynamic_cast<UiObject*>(objectsList[i]);
		if (ui != nullptr) 
		{
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
		//ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		TrapObject* trap = dynamic_cast<TrapObject*>(objectsList[i]);
		if (player != nullptr)
		{
			player->GetCollider()->Update(player->getSize(), player->getPos());
		}
		if (trap != nullptr) {
			objectsList.push_back(trap->GetCollider()->GetGizmos());
			trap->GetCollider()->Update(trap->getSize(), trap->getPos());
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


void LevelGameplay::UsingAbility(int numPlayer, PlayerObject::AbilityButton button) {

	PlayerObject::Ability idAbility = players[numPlayer]->GetAbilityByButton(button);
	// std::cout << "idAbility " << idAbility << std::endl;
	if (players[numPlayer]->GetCooldown(button) <= 0) {
		switch (idAbility) {

		case PlayerObject::Ability::Fireball:
			if (!players[numPlayer]->GetIsAiming()) {
				AimFireball(numPlayer, button);
				break;
			}
			else if(players[numPlayer]->GetIsAiming())
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
					if(realTnt != NULL){
						if (realTnt->GetType() == TrapObject::TypeTrap::Tnt && realTnt->GetPlayerNumber() == numPlayer) {
							realTnt->SetCanKnockback(true);
							realTnt->SetIsActive(true);
							realTnt->GetCollider()->Update(glm::vec3(500, 500, 0), realTnt->getPos());
							realTnt->ExplodeTileInRange();
							players[numPlayer]->SetAbilityCooldown(button, 3);
							players[numPlayer]->SetIsTNT(false);
							
						}
					}
					
				}
			}
			break;

		case PlayerObject::Ability::Teleport:
			if (!players[numPlayer]->GetIsAiming()){
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

void LevelGameplay::AimFireball(int numPlayer, PlayerObject::AbilityButton button) 
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
	projectile->SetCanKnockback(true);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	//objectsList.push_back(projectile->GetCollider()->GetGizmos());
}

void LevelGameplay::ShootFireball(int numPlayer, PlayerObject::AbilityButton button) {
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

void LevelGameplay::Trap(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetAbilityCooldown(button, 3);
	TrapObject* Trap = new TrapObject();
	Trap->SetSpriteInfo(spriteList.find("Trap")->second);
	Trap->SetTexture(spriteList.find("Trap")->second.texture);
	Trap->SetPosition(players[numPlayer]->getPos());
	Trap->SetSize(128.f, -128.f);
	Trap->SetPlayerNumber(players[numPlayer]->GetPlayerNumber());
	Trap->SetType(TrapObject::TypeTrap::Trap);
	Trap->SetIsActive(true);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(Trap);
	//std::cout << "place trap" << std::endl;
}

void LevelGameplay::Dash(int num, PlayerObject::AbilityButton button) {
	players[num]->SetAbilityCooldown(button, 3);
	players[num]->SetIsDashing(true);
	players[num]->SetDashDuration(2);
}

void LevelGameplay::TNT(int numPlayer, PlayerObject::AbilityButton button) {
	players[numPlayer]->SetIsTNT(true);
	TrapObject* TNT = new TrapObject();
	TNT->SetSpriteInfo(spriteList.find("TNT")->second);
	TNT->SetTexture(spriteList.find("TNT")->second.texture);
	TNT->SetPosition(players[numPlayer]->getPos());
	TNT->SetSize(128.f, -128.f);
	TNT->SetPlayerNumber(players[numPlayer]->GetPlayerNumber());
	TNT->SetType(TrapObject::TypeTrap::Tnt);
	//TNT->setIsCanKnockback(true);
	//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
	objectsList.push_back(TNT);
}

void LevelGameplay::AimTeleport(int numPlayer, PlayerObject::AbilityButton button) {
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
	projectile->SetCanKnockback(false);
	projectile->SetIsCanStun(false);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
}

void LevelGameplay::ShootTeleport(int numPlayer, PlayerObject::AbilityButton button) {
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

void LevelGameplay::AimBola(int numPlayer, PlayerObject::AbilityButton button) {
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
	projectile->SetCanKnockback(false);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
}

void LevelGameplay::ShootBola(int numPlayer, PlayerObject::AbilityButton button) {
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

void LevelGameplay::AimCleave(int numPlayer, PlayerObject::AbilityButton button){
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
	projectile->SetCanKnockback(false);
	projectile->SetIsCanStun(true);
	projectile->SetIsShooting(false);
	std::cout << "Owner " << projectile->GetOwner()->GetPlayerNumber() << std::endl;
	objectsList.push_back(projectile);
	players[numPlayer]->SetAbilityCooldown(button, 2);
}

void LevelGameplay::ShootCleave(int numPlayer, PlayerObject::AbilityButton button) {
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
