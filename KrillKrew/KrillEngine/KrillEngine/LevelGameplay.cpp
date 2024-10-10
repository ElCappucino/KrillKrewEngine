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

	cout << "Init Level" << endl;
}

void LevelGameplay::LevelUpdate()
{
	dt++;

	camera.LerpCamera(player[0]->getPos(), player[1]->getPos(), player[2]->getPos(), player[3]->getPos()); // update smooth camera here

	/*cout << "Joystick left stick X axis: " << Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal)
		<< " A: " << Joystick::GetButton(0, Joystick::Button::A)
		<< " B: " << Joystick::GetButton(0, Joystick::Button::B)
		<< " X: " << Joystick::GetButton(0, Joystick::Button::X)
		<< " Y: " << Joystick::GetButton(0, Joystick::Button::Y) << endl;*/
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
	case 'w': player[playerNum]->Translate(glm::vec3(0, 5, 0)); break;
	case 's': player[playerNum]->Translate(glm::vec3(0, -5, 0)); break;
	case 'a': player[playerNum]->Translate(glm::vec3(-5, 0, 0)); break;
	case 'd': player[playerNum]->Translate(glm::vec3(5, 0, 0)); break;

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
	}
}

void LevelGameplay::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;
}