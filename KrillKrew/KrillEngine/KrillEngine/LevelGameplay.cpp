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
	obj1->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj1->SetTexture("../Resource/Texture/Prinny.png");
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-200.f, -200.f, 0));
	objectsList.push_back(obj1);

	player[0] = obj1;

	PlayerObject* obj2 = new PlayerObject();
	obj2->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj2->SetTexture("../Resource/Texture/Prinny.png");
	obj2->SetSize(256.f, -256.f);
	obj2->SetPosition(glm::vec3(200.f, -200.f, 0));
	objectsList.push_back(obj2);

	player[1] = obj2;

	PlayerObject* obj3 = new PlayerObject();
	obj3->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj3->SetTexture("../Resource/Texture/Prinny.png");
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-200.f, 200.f, 0));
	objectsList.push_back(obj3);

	player[2] = obj3;

	PlayerObject* obj4 = new PlayerObject();
	obj4->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj4->SetTexture("../Resource/Texture/Prinny.png");
	obj4->SetSize(256.f, -256.f);
	obj4->SetPosition(glm::vec3(200.f, 200.f, 0));
	objectsList.push_back(obj4);

	player[3] = obj4;

	objectsList.push_back(player[0]->GetCollider()->GetGizmos());
	objectsList.push_back(player[1]->GetCollider()->GetGizmos());
	objectsList.push_back(player[2]->GetCollider()->GetGizmos());
	objectsList.push_back(player[3]->GetCollider()->GetGizmos());

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
		PlayerObject* player1 = dynamic_cast<PlayerObject*>(objectsList[i]);
		if (player1 == nullptr)
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
}

void LevelGameplay::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);

	for (int i = 0; i < objectsList.size(); i++)
	{
		// std::cout << "Hello" << std::endl;
		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		if (player != nullptr)
		{
			player->GetCollider()->Update(player->getSize(), player->getPos());
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

	//switch (key)
	//{
	//// switch player
	//case '1': this->playerNum = 0; break;
	//case '2': this->playerNum = 1; break;
	//case '3': this->playerNum = 2; break;
	//case '4': this->playerNum = 3; break;
	//
	//// control player
	///*case 'w': player[playerNum]->setVelocity(5, false); break;
	//case 's': player[playerNum]->setVelocity(-5, false); break;
	//case 'a': player[playerNum]->setVelocity(-5, true); break;
	//case 'd': player[playerNum]->setVelocity(5, true); break;*/

	//case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
	//case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	//case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELMAPTEST; ; break;
	//case 'i':

	//	GameEngine::GetInstance()->SetDrawArea(camera.getCameraOrthoValue().left + SCREEN_WIDTH * ZOOM_VELOCITY,
	//										   camera.getCameraOrthoValue().right - SCREEN_WIDTH * ZOOM_VELOCITY,
	//										   camera.getCameraOrthoValue().bottom + SCREEN_HEIGHT * ZOOM_VELOCITY,
	//										   camera.getCameraOrthoValue().top - SCREEN_HEIGHT * ZOOM_VELOCITY);
	//	
	//	break;

	//case 'o':

	//	GameEngine::GetInstance()->SetDrawArea(camera.getCameraOrthoValue().left - SCREEN_WIDTH * ZOOM_VELOCITY,
	//											camera.getCameraOrthoValue().right + SCREEN_WIDTH * ZOOM_VELOCITY,
	//											camera.getCameraOrthoValue().bottom - SCREEN_HEIGHT * ZOOM_VELOCITY,
	//											camera.getCameraOrthoValue().top + SCREEN_HEIGHT * ZOOM_VELOCITY);
	//	
	//	break;
	//case 'y':
	//	this->playerNum++;
	//	if (this->playerNum >= 4) {
	//		this->playerNum = 0;
	//	}
	//	std::cout << "Player " << this->playerNum << std::endl;
	//	break;

	//case 'n':
	//	if (player[playerNum]->getIsShooting() == false) {
	//		player[playerNum]->setisShooting(true);
	//		ProjectileObject* projectile = new ProjectileObject();
	//		projectile->SetSheetInfo(0, 0, 256, 256, 256, 256);
	//		projectile->SetTexture("../Resource/Texture/Bomb_icon.png");
	//		projectile->SetPosition(player[playerNum]->getPos());
	//		projectile->SetSize(256.f, -256.f);
	//		projectile->setLifeTime(10);
	//		projectile->setVelocity(player[playerNum]->getVelocity());
	//		objectsList.push_back(projectile);
	//	}

	//	break;
	//}

	
	
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

