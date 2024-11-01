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

	std::cout << "Init Level" << std::endl;
}

void LevelGameplay::LevelUpdate()
{
	dt++;

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

		if (abs(axisX) < 0.1)
		{
			axisX = 0;
		}
		
		if (abs(axisY) < 0.1)
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

		if (player[playerNum]->getIsAiming() == false) {
			player[playerNum]->setVelocity(abs(axisX), abs(axisY), isPositiveX, isPositiveY);
		}

		//Select ability
		if (Joystick::GetButtonDown(0, Joystick::Button::L1)) {

		}
		

		//Shoot
		if (Joystick::GetButton(0, Joystick::Button::R1)) {
			if (player[playerNum]->getIsShooting() == false && player[playerNum]->getIsAiming() == false) {
				player[playerNum]->setVelocity(0, 0, isPositiveX, isPositiveY);
				player[playerNum]->setIsAiming(true);
				ProjectileObject* projectile = new ProjectileObject();
				projectile->SetSheetInfo(0, 0, 256, 256, 256, 256);
				projectile->SetTexture("../Resource/Texture/Bomb_icon.png");
				projectile->SetPosition(player[playerNum]->getPos());
				projectile->SetSize(256.f, -256.f);
				projectile->setLifeTime(9999);
				objectsList.push_back(projectile);
			}
		}

		if (Joystick::GetButtonUp(0, Joystick::Button::R1)) {
			
			if (player[playerNum]->getIsShooting() == false) {
				player[playerNum]->setIsShooting(true);
				player[playerNum]->setIsAiming(false);
				for (int i = 0; i < objectsList.size(); i++) {
					ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
					if (projectile != nullptr) {
						projectile->setLifeTime(10);
					}
				}
			}
		}

		if (player[playerNum]->getIsAiming()) {
			for (int i = 0; i < objectsList.size(); i++) {
				ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
				if (projectile != nullptr) {
					projectile->setVelocity(abs(axisX), abs(axisY), isPositiveX, isPositiveY);
					projectile->SetPosition(player[playerNum]->getPos() + (projectile->getVelocity() * glm::vec3(15.f ,15.f ,0.f)));
				}
			}
		}

		//Place trap
		if (Joystick::GetButtonDown(0, Joystick::Button::R2)) {

		}
	}

	player[playerNum]->Translate(player[playerNum]->getVelocity());
	camera.LerpCamera(player[0]->getPos(), player[1]->getPos(), player[2]->getPos(), player[3]->getPos()); // update smooth camera here

	for (int i = 0; i < objectsList.size(); i++) {
		ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		if (projectile != nullptr) {

			if ((dt % 50) == 0) {
				projectile->reduceLifeTime();
			}

			if (projectile->getLifetime() <= 0) {
				objectsList.erase(objectsList.begin() + i);
				player[playerNum]->setIsShooting(false);
				std::cout << "delete projectile" << std::endl;
			}
			projectile->Translate(projectile->getVelocity());
		}

	}
}

void LevelGameplay::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);

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

