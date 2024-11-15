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
	//cout << "Load Level" << endl;
}

void LevelGameplay::LevelInit()
{

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
																  (SCREEN_WIDTH / 2),
																 -(SCREEN_HEIGHT / 2),
																  (SCREEN_HEIGHT / 2));

	/*targetSceneProjection = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue();

	zoomInfo.maxZoom_horizontal = 3;
	zoomInfo.maxZoom_vertical = 3;
	zoomInfo.minZoom_horizontal = 1;
	zoomInfo.minZoom_vertical = 1;*/

	// Create and Initialize 4 players object

	// Example Code

	/*GizmosObject* gameobject = new GizmosObject();
	gameobject->SetPosition(glm::vec3(0.f, 0.f, 0.f));
	gameobject->SetColor(1.f, 0.f, 0.f);
	gameobject->SetSize(256.f, 256.f);
	objectsList.push_back(gameobject);*/


	PlayerObject* obj1 = new PlayerObject();
	obj1->GetCollider()->SetCollisionType(Collider::Kinematic);
	obj1->SetSpriteInfo(spriteList.find("Prinny")->second);
	obj1->SetTexture(spriteList.find("Prinny")->second.texture);
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-200.f, -200.f, 0));
	objectsList.push_back(obj1);

	player[0] = obj1;

	PlayerObject* obj2 = new PlayerObject();
	obj2->GetCollider()->SetCollisionType(Collider::Static);
	obj2->SetSpriteInfo(spriteList.find("Prinny")->second);
	obj2->SetTexture(spriteList.find("Prinny")->second.texture);
	obj2->SetSize(256.f, -256.f);
	obj2->SetPosition(glm::vec3(200.f, -200.f, 0));
	objectsList.push_back(obj2);

	player[1] = obj2;

	PlayerObject* obj3 = new PlayerObject();
	obj3->SetSpriteInfo(spriteList.find("Prinny")->second);
	obj3->SetTexture(spriteList.find("Prinny")->second.texture);
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-200.f, 200.f, 0));
	objectsList.push_back(obj3);

	player[2] = obj3;

	PlayerObject* obj4 = new PlayerObject();
	obj4->SetSpriteInfo(spriteList.find("Prinny")->second);
	obj4->SetTexture(spriteList.find("Prinny")->second.texture);
	obj4->SetSize(256.f, -256.f);
	obj4->SetPosition(glm::vec3(200.f, 200.f, 0));
	objectsList.push_back(obj4);

	player[3] = obj4;

	TrapObject* trap1 = new TrapObject();
	trap1->GetCollider()->SetCollisionType(Collider::Trigger);
	trap1->SetSpriteInfo(spriteList.find("Prinny")->second);
	trap1->SetTexture(spriteList.find("Prinny")->second.texture);
	trap1->SetSize(256.f, -256.f);
	trap1->SetPosition(glm::vec3(500.f, 500.f, 0));
	objectsList.push_back(trap1);

	objectsList.push_back(player[0]->GetCollider()->GetGizmos());
	objectsList.push_back(player[1]->GetCollider()->GetGizmos());
	objectsList.push_back(player[2]->GetCollider()->GetGizmos());
	objectsList.push_back(player[3]->GetCollider()->GetGizmos());
	objectsList.push_back(trap1->GetCollider()->GetGizmos());

	std::cout << "Init Level" << std::endl;
}

void LevelGameplay::LevelUpdate()
{
	dt++;

	// update Joystick
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();

		/*printf("Joystick No.1 Triangle: %d Square: %d Cross: %d Circle: %d Leftstick: %f\n",
			Joystick::GetButton(0, Joystick::Button::Triangle),
			Joystick::GetButton(0, Joystick::Button::Square),
			Joystick::GetButton(0, Joystick::Button::Cross),
			Joystick::GetButton(0, Joystick::Button::Circle),
			Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal));*/

		float axisX = Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
		float axisY = Joystick::GetAxis(0, Joystick::Axis::LeftStickVertical) / 32768.0f;
		bool isPositiveX = false;
		bool isPositiveY = false;

		if (abs(axisX) < 0.2)
		{
			axisX = 0;
		}
		
		if (abs(axisY) < 0.2)
		{
			axisY = 0;
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

		player[playerNum]->setVelocity(abs(axisX), abs(axisY), isPositiveX, isPositiveY);
	}

	// Update Movement
	player[playerNum]->Translate(player[playerNum]->getVelocity());
	camera.LerpCamera(player[0]->getPos(), player[1]->getPos(), player[2]->getPos(), player[3]->getPos()); // update smooth camera here

	// Update Projectile
	for (int i = 0; i < objectsList.size(); i++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (projectile != nullptr) {

			if ((dt % 50) == 0) {
				projectile->reduceLifeTime();
			}

			if (projectile->getLifetime() <= 0) {
				objectsList.erase(objectsList.begin() + i);
				player[playerNum]->setisShooting(false);
				std::cout << "delete projectile" << std::endl;
			}
			projectile->Translate(projectile->getVelocity());
		}

	}

	// Update Overlapping Collider
	for (int i = 0; i < objectsList.size(); i++)
	{
		// std::cout << "i = " << i << std::endl;
		// std::cout << "Hello" << std::endl;
		EntityObject* entity1 = dynamic_cast<EntityObject*>(objectsList[i]);
		if (entity1 == nullptr || entity1->GetCollider()->GetCollisionType() == Collider::Static)
		{
			continue;
		}
		else
		{
			for (int j = i; j < objectsList.size(); j++)
			{
				// std::cout << "j = " << j << std::endl;
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

					// std::cout << "i = " << i << " j = " << j << " delta = " << delta.x << ", " << delta.y << std::endl;

					float overlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - delta.x;
					float overlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - delta.y;

					float previousOverlapX = (abs(col1.GetHalfSize().x)) + (abs(col2.GetHalfSize().x)) - previousDelta.x;
					float previousOverlapY = (abs(col1.GetHalfSize().y)) + (abs(col2.GetHalfSize().y)) - previousDelta.y;

					// std::cout << i << ", " << j << " overlapX = " << overlapX << " overlapY = " << overlapY << std::endl;
					if (overlapX > 0 && overlapY > 0)
					{
						entity1->OnColliderEnter(entity2->GetCollider());
						entity2->OnColliderEnter(entity1->GetCollider());

						// std::cout << i << " Overlapping with " << j << std::endl;
						if (col1.GetCollisionType() == Collider::Kinematic &&
							col2.GetCollisionType() == Collider::Static)
						{
							std::cout << "Kinematic Static " << std::endl;
							glm::vec3 newPos(entity1->getPos().x, entity1->getPos().y, entity1->getPos().z);

							if (previousOverlapX > 0)
							{
								std::cout << "previousOverlapX > 0 " << std::endl;
								bool isTopSide = (col1.GetPreviousPos().y - col2.GetPreviousPos().y) > 0 ? true : false;
								
								newPos.y = entity1->getPos().y + (overlapY * (isTopSide ? 1 : -1));
							}
							if (previousOverlapY > 0)
							{
								std::cout << "previousOverlapY > 0 " << std::endl;
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

}

void LevelGameplay::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);

	// Collider Gizmos update
	for (int i = 0; i < objectsList.size(); i++)
	{
		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
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

	case 'n':
		if (player[playerNum]->getIsShooting() == false) {
			player[playerNum]->setisShooting(true);
			ProjectileObject* projectile = new ProjectileObject();
			projectile->SetSpriteInfo(spriteList.find("Bomb")->second);
			projectile->SetTexture(spriteList.find("Bomb")->second.texture);
			projectile->SetPosition(player[playerNum]->getPos());
			projectile->SetSize(256.f, -256.f);
			projectile->setLifeTime(10);
			projectile->setVelocity(player[playerNum]->getVelocity());
			objectsList.push_back(projectile);
		}

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

