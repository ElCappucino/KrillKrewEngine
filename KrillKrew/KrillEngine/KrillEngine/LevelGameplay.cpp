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
	//cout << "Load Level" << endl;
}

void LevelGameplay::LevelInit()
{

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
																  (SCREEN_WIDTH / 2),
																 -(SCREEN_HEIGHT / 2),
																  (SCREEN_HEIGHT / 2));

	timer = Timer::Instance();

	/*targetSceneProjection = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue();

	zoomInfo.maxZoom_horizontal = 3;
	zoomInfo.maxZoom_vertical = 3;
	zoomInfo.minZoom_horizontal = 1;
	zoomInfo.minZoom_vertical = 1;*/

	// Create and Initialize 4 players object

	// Example Code
	PlayerObject* obj1 = new PlayerObject();
	obj1->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj1->SetTexture("../Resource/Texture/Prinny.png");
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-200.f, -200.f, 0));
	obj1->setNumber(0);
	objectsList.push_back(obj1);

	player[0] = obj1;

	PlayerObject* obj2 = new PlayerObject();
	obj2->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj2->SetTexture("../Resource/Texture/Prinny.png");
	obj2->SetSize(256.f, -256.f);
	obj2->SetPosition(glm::vec3(200.f, -200.f, 0));
	obj2->setNumber(1);
	objectsList.push_back(obj2);

	player[1] = obj2;

	PlayerObject* obj3 = new PlayerObject();
	obj3->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj3->SetTexture("../Resource/Texture/Prinny.png");
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-200.f, 200.f, 0));
	obj3->setNumber(2);
	objectsList.push_back(obj3);

	player[2] = obj3;

	PlayerObject* obj4 = new PlayerObject();
	obj4->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj4->SetTexture("../Resource/Texture/Prinny.png");
	obj4->SetSize(256.f, -256.f);
	obj4->SetPosition(glm::vec3(200.f, 200.f, 0));
	obj4->setNumber(3);
	objectsList.push_back(obj4);

	player[3] = obj4;

	/*objectsList.push_back(player[0]->GetCollider()->GetGizmos());
	objectsList.push_back(player[1]->GetCollider()->GetGizmos());
	objectsList.push_back(player[2]->GetCollider()->GetGizmos());
	objectsList.push_back(player[3]->GetCollider()->GetGizmos());*/

	UiObject* uiSkills = new UiObject();
	uiSkills->SetSheetInfo(0, 0, 256, 256, 256, 256);
	uiSkills->SetTexture("../Resource/Texture/trap.png");
	uiSkills->SetPosition(glm::vec3(0,0,0));
	uiSkills->SetSize(128.f, -128.f);
	uiSkills->setNumOwner(0);
	objectsList.push_back(uiSkills);

	std::cout << "Init Level" << std::endl;
}

void LevelGameplay::LevelUpdate()
{
	dt++;

	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();
		for (int i = 0; i < SDL_NumJoysticks(); i++) {

			

			/*printf("Joystick No.1 Triangle: %d Square: %d Cross: %d Circle: %d Leftstick: %f\n",
				Joystick::GetButton(0, Joystick::Button::Triangle),
				Joystick::GetButton(0, Joystick::Button::Square),
				Joystick::GetButton(0, Joystick::Button::Cross),
				Joystick::GetButton(0, Joystick::Button::Circle),
				Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal));*/

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

			else {
				float axis = atan2(axisY, axisX);
				norAxisX = cos(axis);
			}

			if (abs(axisY) < 0.1)
			{
				norAxisY = 0;
			}

			else {
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
			

			if (player[i + playerNum]->getIsAiming() == false) {
				player[i + playerNum]->setVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
			}

			//Select ability
			if (Joystick::GetButtonDown(i, Joystick::Button::L1)) {

			}


			//Aim
			if (Joystick::GetButtonDown(i, Joystick::Button::R1)) 
			{
				
				if (player[i + playerNum]->getIsShooting() == false && player[i + playerNum]->getIsAiming() == false) {
					player[i + playerNum]->setVelocity(0, 0, isPositiveX, isPositiveY);
					player[i + playerNum]->setIsAiming(true);
					ProjectileObject* projectile = new ProjectileObject();
					projectile->SetSheetInfo(0, 0, 256, 256, 256, 256);
					projectile->SetTexture("../Resource/Texture/Bomb_icon.png");
					projectile->SetPosition(player[i + playerNum]->getPos());
					projectile->SetSize(256.f, -256.f);
					projectile->setLifeTime(9999);
					projectile->setNumOwner(player[i + playerNum]->getNumber());
					std::cout << "Owner " << projectile->getNumOwner() << std::endl;
					objectsList.push_back(projectile);
					//objectsList.push_back(projectile->GetCollider()->GetGizmos());
				}
			}
			//Shoot
			if (Joystick::GetButtonUp(i, Joystick::Button::R1)) 
			{
				std::cout << "Shoot " << i + playerNum << std::endl;
				if (player[i + playerNum]->getIsShooting() == false) {
					player[i + playerNum]->setIsShooting(true);
					player[i + playerNum]->setIsAiming(false);
					for (int j = 0; j < objectsList.size(); j++) {
						ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
						if (projectile != nullptr) {
							projectile->setLifeTime(5);
						}
					}
				}
			}

			if (player[i + playerNum]->getIsAiming())
			{
				for (int j = 0; j < objectsList.size(); j++) {
					ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[j]);
					if (projectile != nullptr && i + playerNum == projectile->getNumOwner()) {
						if (abs(norAxisX) > 0 || norAxisY > 0) {
							projectile->setVelocity(abs(norAxisX), abs(norAxisY), isPositiveX, isPositiveY);
						}
						projectile->SetPosition(player[i + playerNum]->getPos() + (projectile->getVelocity() * glm::vec3(15.f, 15.f, 0.f)));
					}
				}
			}

			//Place trap
			if (Joystick::GetButtonDown(i, Joystick::Button::Triangle)) 
			{
				if (player[i + playerNum]->getCooldown(1) <= 0) {
					player[i + playerNum]->setCooldown(1, 3);
					TrapObject* Trap = new TrapObject();
					Trap->SetSheetInfo(0, 0, 512, 512, 512, 512);
					Trap->SetTexture("../Resource/Texture/trap.png");
					Trap->SetPosition(player[i + playerNum]->getPos());
					Trap->SetSize(128.f, -128.f);
					Trap->setNumOwner(player[i + playerNum]->getNumber());
					//std::cout << "Owner " << Trap->getNumOwner() << std::endl;
					objectsList.push_back(Trap);
				}
			}

			// Debug other player
			if (Joystick::GetButtonDown(i, Joystick::Button::L1))
			{
				playerNum += 1;
				if (playerNum >= 4) {
					playerNum = 0;
				}
				std::cout << "Control player " << playerNum << std::endl;
			}

			player[i + playerNum]->Translate(player[i + playerNum]->getVelocity());
		}
		
	}

	
	camera.LerpCamera(player[0]->getPos(), player[1]->getPos(), player[2]->getPos(), player[3]->getPos()); // update smooth camera here

	

	// player collier player
	for (int i = 0; i < objectsList.size(); i++)
	{

		PlayerObject* player1 = dynamic_cast<PlayerObject*>(objectsList[i]);
		if (player1 == nullptr)
		{
			continue;
		}
		else
		{
			for (int j = 0; j < objectsList.size(); j++)
			{
				// std::cout << "j = " << j << std::endl;
				if (i == j)
				{
					continue;
				}
				PlayerObject* player2 = dynamic_cast<PlayerObject*>(objectsList[j]);
				if (player2 != nullptr)
				{

					Collider col1 = *player1->GetCollider();
					Collider col2 = *player2->GetCollider();

					glm::vec2 delta = glm::vec2(abs(player1->getPos().x - player2->getPos().x),
						abs(player1->getPos().y - player2->getPos().y));

					// std::cout << "i = " << i << " j = " << j << " delta = " << delta.x << ", " << delta.y << std::endl;

					float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
					float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

					// std::cout << i << ", " << j << " overlapX = " << overlapX << " overlapY = " << overlapY << std::endl;
					if (overlapX > 0 && overlapY > 0)
					{
						std::cout << i << " Overlapping with " << j << std::endl;
					}

				}
			}
		}
	}

	// projectile collier player

	for (int i = 0; i < objectsList.size(); i++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (projectile != nullptr) 
		{
			//std::cout << "Have projectile" << std::endl;
			for (int j = 0; j < objectsList.size(); j++)
				{
					if (i == j)
					{
						continue;
					}
					PlayerObject* player2 = dynamic_cast<PlayerObject*>(objectsList[j]);
					if (player2 != nullptr)
					{
						if (projectile->getNumOwner() != player2->getNumber()) {
							Collider col1 = *projectile->GetCollider();
							Collider col2 = *player2->GetCollider();

							glm::vec2 delta = glm::vec2(abs(projectile->getPos().x - player2->getPos().x),
								abs(projectile->getPos().y - player2->getPos().y));

							// std::cout << "i = " << i << " j = " << j << " delta = " << delta.x << ", " << delta.y << std::endl;

							float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
							float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

							// std::cout << i << ", " << j << " overlapX = " << overlapX << " overlapY = " << overlapY << std::endl;
							if (overlapX > 0 && overlapY > 0)
							{
								std::cout << "Fireball :" << projectile->getNumOwner() << " hit " << "Player" << player2->getNumber() << std::endl;
								player[projectile->getNumOwner()]->setIsShooting(false);
								objectsList.erase(objectsList.begin() + i);
							}
						}
					}
				}
		}
		else
		{
			//std::cout << "No projectile" << std::endl;
			continue;
		}
	}

	// trap collier player
	for (int i = 0; i < objectsList.size(); i++) {
		TrapObject* trap = dynamic_cast<TrapObject*>(objectsList[i]);
		if (trap != nullptr)
		{
			//std::cout << "Have projectile" << std::endl;
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

						// std::cout << "i = " << i << " j = " << j << " delta = " << delta.x << ", " << delta.y << std::endl;

						float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
						float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

						// std::cout << i << ", " << j << " overlapX = " << overlapX << " overlapY = " << overlapY << std::endl;
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
		else
		{
			//std::cout << "No Trap" << std::endl;
			continue;
		}
	}

	// delete projectile
	for (int i = 0; i < objectsList.size(); i++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (projectile != nullptr) {

			if ((dt % 50) == 0) {
				projectile->reduceLifeTime();
			}

			if (projectile->getLifetime() <= 0) {
				std::cout << "delete projectile " << projectile->getNumOwner() << std::endl;
				player[projectile->getNumOwner()]->setIsShooting(false);
				objectsList.erase(objectsList.begin() + i);
			}
			projectile->Translate(projectile->getVelocity());
		}

	}

	// reduce cooldown skill
	for (int i = 0; i < SDL_NumJoysticks() + playerNum; i++) {
		timer->tick();
		timer->reset();
		time[i + playerNum] += timer->getDeltaTime();
		//std::cout << time[i] << std::endl;
		for (int j = 0; j < 3; j++) {
			if (time[i + playerNum] >= 1.0f && player[i + playerNum]->getCooldown(j) > 0) {
				player[i + playerNum]->reduceCooldown();
				time[i + playerNum] = 0.0f;
			}
		}
	}

	// slowness
	for (int i = 0; i < SDL_NumJoysticks() + playerNum; i++) {
		if (player[i]->getIsSlowness() == true) 
		{
			player[i]->reduceDurationSlowness();
		}

		if (player[i]->getDurationSlowness() <= 0) {
			player[i]->setIsSlowness(false);
		}
	}

	//Ui Skills
	for (int i = 0; i < objectsList.size(); i++)
	{
		//std::cout << "Height | " << camera.GetCameraHeight() << std::endl;
		//std::cout << "Width | " << camera.GetCameraWidth() << std::endl;
		UiObject* ui = dynamic_cast<UiObject*>(objectsList[i]);
		if (ui != nullptr) {
			ui->SetPosition(glm::vec3(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left + (100 * camera.GetCameraWidth() / 1246),
									  GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + (100 * camera.GetCameraHeight() / 720), 0));
			ui->SetSize(128 * camera.GetCameraWidth() / 1246, -128 * camera.GetCameraHeight() / 720);
		}
	}
}

void LevelGameplay::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	

	for (int i = 0; i < objectsList.size(); i++)
	{
		// std::cout << "Hello" << std::endl;
		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (player != nullptr)
		{
			player->GetCollider()->Update(player->getSize(), player->getPos());
		}
		if (projectile != nullptr) {
			projectile->GetCollider()->Update(projectile->getSize(), projectile->getPos());
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
	
	// control player
	/*case 'w': player[playerNum]->setVelocity(5, false); break;
	case 's': player[playerNum]->setVelocity(-5, false); break;
	case 'a': player[playerNum]->setVelocity(-5, true); break;
	case 'd': player[playerNum]->setVelocity(5, true); break;*/

	case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELMAPTEST; ; break;
	case 'i':

		GameEngine::GetInstance()->SetDrawArea(camera.getCameraOrthoValue().left + SCREEN_WIDTH * ZOOM_VELOCITY,
											   camera.getCameraOrthoValue().right - SCREEN_WIDTH * ZOOM_VELOCITY,
											   camera.getCameraOrthoValue().bottom + SCREEN_HEIGHT * ZOOM_VELOCITY,
											   camera.getCameraOrthoValue().top - SCREEN_HEIGHT * ZOOM_VELOCITY);
		
		break;

	case 'o':

		GameEngine::GetInstance()->SetDrawArea(camera.getCameraOrthoValue().left - SCREEN_WIDTH * ZOOM_VELOCITY,
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
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;
}

void LevelGameplay::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {
	// player[playerNum]->setVelocity(axisX, axisY, isPositiveX, isPositiveY);
}

