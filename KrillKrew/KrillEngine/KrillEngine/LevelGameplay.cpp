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

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-SCREEN_RATIO_X * 2,
		SCREEN_RATIO_X * 2,
		-SCREEN_RATIO_Y * 2,
		SCREEN_RATIO_Y * 2);

	targetSceneProjection = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue();

	zoomInfo.maxZoom_horizontal = 3;
	zoomInfo.maxZoom_vertical = 3;
	zoomInfo.minZoom_horizontal = 1;
	zoomInfo.minZoom_vertical = 1;

	// Create and Initialize 4 players object

	// Example Code
	ImageObject* obj1 = new ImageObject();
	obj1->SetTexture("../Resource/Texture/Prinny.png");
	obj1->SetSize(1.f, -1.f);
	obj1->SetPosition(glm::vec3(-1.f, -1.f, 0));
	objectsList.push_back(obj1);

	player[0] = obj1;

	ImageObject* obj2 = new ImageObject();
	obj2->SetTexture("../Resource/Texture/Prinny.png");
	obj2->SetSize(1.f, -1.f);
	obj2->SetPosition(glm::vec3(1.f, -1.f, 0));
	objectsList.push_back(obj2);

	player[1] = obj2;

	ImageObject* obj3 = new ImageObject();
	obj3->SetTexture("../Resource/Texture/Prinny.png");
	obj3->SetSize(1.f, -1.f);
	obj3->SetPosition(glm::vec3(-1.f, 1.f, 0));
	objectsList.push_back(obj3);

	player[2] = obj3;

	ImageObject* obj4 = new ImageObject();
	obj4->SetTexture("../Resource/Texture/Prinny.png");
	obj4->SetSize(1.f, -1.f);
	obj4->SetPosition(glm::vec3(1.f, 1.f, 0));
	objectsList.push_back(obj4);

	player[3] = obj4;

	//cout << "Init Level" << endl;
}

void LevelGameplay::LevelUpdate()
{
	dt++;

	CameraLerp(); // update smooth camera here

	//cout << "Update Level" << endl;
}

void LevelGameplay::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
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
	case '1': playerNum = 0; break;
	case '2': playerNum = 1; break;
	case '3': playerNum = 2; break;
	case '4': playerNum = 3; break;

		// control player
	case 'w': player[playerNum]->Translate(glm::vec3(0, 0.3, 0)); break;
	case 's': player[playerNum]->Translate(glm::vec3(0, -0.3, 0)); break;
	case 'a': player[playerNum]->Translate(glm::vec3(-0.3, 0, 0)); break;
	case 'd': player[playerNum]->Translate(glm::vec3(0.3, 0, 0)); break;

	case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVEL1; ; break;
	case 'i':

		GameEngine::GetInstance()->SetDrawArea(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left + SCREEN_RATIO_X * ZOOM_VELOCITY,
			GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right - SCREEN_RATIO_X * ZOOM_VELOCITY,
			GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + SCREEN_RATIO_Y * ZOOM_VELOCITY,
			GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top - SCREEN_RATIO_Y * ZOOM_VELOCITY);

		break;

	case 'o':

		GameEngine::GetInstance()->SetDrawArea(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left - SCREEN_RATIO_X * ZOOM_VELOCITY,
			GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right + SCREEN_RATIO_X * ZOOM_VELOCITY,
			GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom - SCREEN_RATIO_Y * ZOOM_VELOCITY,
			GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top + SCREEN_RATIO_Y * ZOOM_VELOCITY);

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

	top = 0;
	bottom = 0;
	right = 0;
	left = 0;

	for (int i = 0; i < 4; i++) {

		if (player[i]->getPos().x > right) {

			right = player[i]->getPos().x;
		}

		if (player[i]->getPos().x < left) {

			left = player[i]->getPos().x;

		}

		if (player[i]->getPos().y > top) {

			top = player[i]->getPos().y;

		}

		if (player[i]->getPos().y < bottom) {

			bottom = player[i]->getPos().y;

		}
	}
	x = lerp(left, right, 0.5);
	y = lerp(bottom, top, 0.5);
	maxX = abs(left) + abs(right);
	maxY = abs(bottom) + abs(top);

	if (maxX > maxY) {
		diffXY = abs(abs(maxX) - abs(maxY));
		left = (SCREEN_RATIO_X * x) - (1.5 + maxX);
		right = (SCREEN_RATIO_X * x) + (1.5 + maxX);
		bottom = (SCREEN_RATIO_Y * y) - (1.5 + maxY) - (diffXY);
		top = (SCREEN_RATIO_Y * y) + (1.5 + maxY) + (diffXY);
	}

	else {
		diffXY = abs(abs(maxY) - abs(maxX));
		left = (SCREEN_RATIO_X * x) - (1.5 + maxX) - (diffXY);
		right = (SCREEN_RATIO_X * x) + (1.5 + maxX) + (diffXY);
		bottom = (SCREEN_RATIO_Y * y) - (1.5 + maxY);
		top = (SCREEN_RATIO_Y * y) + (1.5 + maxY);
	}

	printf("diffXY = %f | ", diffXY);
	printf("maxX = %f | maxY = %f\n", abs(left) + abs(right), abs(bottom) + abs(top));

	//printf("Left = %f | Right = %f | Bottom = %f | Top = %f \n", left, right, bottom, top);
	GameEngine::GetInstance()->SetDrawArea(left, right, bottom, top);

}