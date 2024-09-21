#include "LevelGameplay.h"

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
	obj1->SetSize(1.5f, -1.5f);
	obj1->SetPosition(glm::vec3(-1.f, -1.f, 0));
	objectsList.push_back(obj1);

	player[0] = obj1;

	ImageObject* obj2 = new ImageObject();
	obj2->SetTexture("../Resource/Texture/Prinny.png");
	obj2->SetSize(1.5f, -1.5f);
	obj2->SetPosition(glm::vec3(1.f, -1.f, 0));
	objectsList.push_back(obj2);

	player[1] = obj2;

	ImageObject* obj3 = new ImageObject();
	obj3->SetTexture("../Resource/Texture/Prinny.png");
	obj3->SetSize(1.5f, -1.5f);
	obj3->SetPosition(glm::vec3(-1.f, 1.f, 0));
	objectsList.push_back(obj3);

	player[2] = obj3;

	ImageObject* obj4 = new ImageObject();
	obj4->SetTexture("../Resource/Texture/Prinny.png");
	obj4->SetSize(1.5f, -1.5f);
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
	/*case 'w': player->Translate(glm::vec3(0, 0.3, 0)); break;
	case 's': player->Translate(glm::vec3(0, -0.3, 0)); break;
	case 'a': player->Translate(glm::vec3(-0.3, 0, 0)); break;
	case 'd': player->Translate(glm::vec3(0.3, 0, 0)); break;*/
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

}