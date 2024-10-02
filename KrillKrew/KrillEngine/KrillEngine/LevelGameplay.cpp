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
	ImageObject* obj1 = new ImageObject();
	obj1->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj1->SetTexture("../Resource/Texture/Prinny.png");
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-200.f, -200.f, 0));
	objectsList.push_back(obj1);

	player[0] = obj1;

	ImageObject* obj2 = new ImageObject();
	obj2->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj2->SetTexture("../Resource/Texture/Prinny.png");
	obj2->SetSize(256.f, -256.f);
	obj2->SetPosition(glm::vec3(200.f, -200.f, 0));
	objectsList.push_back(obj2);

	player[1] = obj2;

	ImageObject* obj3 = new ImageObject();
	obj3->SetSheetInfo(0, 0, 538, 581, 538, 581);
	obj3->SetTexture("../Resource/Texture/Prinny.png");
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-200.f, 200.f, 0));
	objectsList.push_back(obj3);

	player[2] = obj3;

	ImageObject* obj4 = new ImageObject();
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

	CameraLerp(); // update smooth camera here

	// cout << "Playere Num = " << playerNum << endl;
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

		GameEngine::GetInstance()->SetDrawArea(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left + SCREEN_WIDTH * ZOOM_VELOCITY,
											   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right - SCREEN_WIDTH * ZOOM_VELOCITY,
											   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + SCREEN_HEIGHT * ZOOM_VELOCITY,
											   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top - SCREEN_HEIGHT * ZOOM_VELOCITY);
		
		break;

	case 'o':

		GameEngine::GetInstance()->SetDrawArea(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left - SCREEN_WIDTH * ZOOM_VELOCITY,
											   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right + SCREEN_WIDTH * ZOOM_VELOCITY,
											   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom - SCREEN_HEIGHT * ZOOM_VELOCITY,
		                                       GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top + SCREEN_HEIGHT * ZOOM_VELOCITY);
		
		break;
	}
}

void LevelGameplay::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	// player->SetPosition(glm::vec3(realX, realY, 0));
}

void LevelGameplay::CameraLerp() {

	// check if the length of horizontal and vertical of projection + (target projection - current projection) * zoomInfo.t is not exceed the minimum and maximum.
	// if not, calculate the lerp of left right bottom top and update using SetDrawArea().

	float current_top = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top;
	float current_bottom = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom;
	float current_left = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left;
	float current_right = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right;

	float currentWidth = current_right - current_left;
	float currentHeight = current_top - current_bottom;

	float currentRatio = std::round((currentWidth / currentHeight) * 100.f) / 100.f;

	float maxLeft = 0;
	float maxRight = 0;
	float maxTop = 0;
	float maxBottom = 0;

	for (int i = 0; i < 4; i++) {

		if (player[i]->getPos().x > maxRight) {

			maxRight = player[i]->getPos().x;
		}

		if (player[i]->getPos().x < maxLeft) {

			maxLeft = player[i]->getPos().x;

		}

		if (player[i]->getPos().y > maxTop) {

			maxTop = player[i]->getPos().y;

		}

		if (player[i]->getPos().y < maxBottom) {

			maxBottom = player[i]->getPos().y;

		}
	}

	float newWidth = maxRight - maxLeft;
	float newHeight = maxTop - maxBottom;

	if (newWidth == lastWidth && newHeight == lastHeight) {
		return;
	}
	else {
		float newRatio = std::round(newWidth / newHeight * 100.f) / 100.f;
		cout << newRatio << endl;
		if (newRatio > SCREEN_RATIO_X)
		{
			current_left = maxLeft;
			current_right = maxRight;
			current_top = maxTop + (((newWidth / SCREEN_RATIO_X) - newHeight) / 2.f);
			current_bottom = maxBottom - (((newWidth / SCREEN_RATIO_X) - newHeight) / 2.f);

			lastWidth = newWidth;
			lastHeight = newHeight;

			// add padding
			current_left -= CAMERA_PADDING * SCREEN_RATIO_X;
			current_right += CAMERA_PADDING * SCREEN_RATIO_X;
			current_top += CAMERA_PADDING * SCREEN_RATIO_Y;
			current_bottom -= CAMERA_PADDING * SCREEN_RATIO_Y;

			GameEngine::GetInstance()->SetDrawArea(current_left, current_right, current_bottom, current_top);
		}
		else if (newRatio < SCREEN_RATIO_X)
		{
			current_top = maxTop;
			current_bottom = maxBottom;
			current_left = maxLeft - (((newHeight * SCREEN_RATIO_X) - newWidth) / 2.f);
			current_right = maxRight + (((newHeight * SCREEN_RATIO_X) - newWidth) / 2.f);

			lastWidth = newWidth;
			lastHeight = newHeight;

			// add padding
			current_left -= CAMERA_PADDING * SCREEN_RATIO_X;
			current_right += CAMERA_PADDING * SCREEN_RATIO_X;
			current_top += CAMERA_PADDING * SCREEN_RATIO_Y;
			current_bottom -= CAMERA_PADDING * SCREEN_RATIO_Y;

			GameEngine::GetInstance()->SetDrawArea(current_left, current_right, current_bottom, current_top);
		}
	}
}