#include "LevelMapTest.h"

void LevelMapTest::LevelLoad()
{
	TileMeshVbo* tile = new TileMeshVbo();
	
	GameEngine::GetInstance()->AddMesh(TileMeshVbo::MESH_NAME, tile);

	//cout << "Load Level" << endl;
}

void LevelMapTest::LevelInit()
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
	SquareMeshVbo *square = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));
	
	square->ChangeTextureData(0, 0, 128, 128, 256, 128);
	
	ImageObject* obj1 = new ImageObject();
	obj1->SetTexture("../Resource/Texture/Prinny.png");
	obj1->SetSize(1.f, -1.f);
	obj1->SetPosition(glm::vec3(-1.f, -1.f, 0));
	objectsList.push_back(obj1);

	player[0] = obj1;

	square->ChangeTextureData(0, 1, 128, 128, 256, 128);

	ImageObject* obj2 = new ImageObject();
	obj2->SetTexture("../Resource/Texture/Prinny.png");
	obj2->SetSize(1.f, -1.f);
	obj2->SetPosition(glm::vec3(1.f, -1.f, 0));
	objectsList.push_back(obj2);

	player[1] = obj2;

	square->ChangeTextureData(0, 0, 128, 128, 256, 128);

	ImageObject* obj3 = new ImageObject();
	obj3->SetTexture("../Resource/Texture/Prinny.png");
	obj3->SetSize(1.f, -1.f);
	obj3->SetPosition(glm::vec3(-1.f, 1.f, 0));
	objectsList.push_back(obj3);

	player[2] = obj3;

	square->ChangeTextureData(0, 1, 128, 128, 256, 128);

	ImageObject* obj4 = new ImageObject();
	obj4->SetTexture("../Resource/Texture/Prinny.png");
	obj4->SetSize(1.f, -1.f);
	obj4->SetPosition(glm::vec3(1.f, 1.f, 0));
	objectsList.push_back(obj4);

	player[3] = obj4;

	//cout << "Init Level" << endl;
}

void LevelMapTest::LevelUpdate()
{
	dt++;

	CameraLerp(); // update smooth camera here

	//cout << "Update Level" << endl;
}

void LevelMapTest::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
}

void LevelMapTest::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void LevelMapTest::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	//cout << "Unload Level" << endl;
}

void LevelMapTest::HandleKey(char key)
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

void LevelMapTest::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	// player->SetPosition(glm::vec3(realX, realY, 0));
}

void LevelMapTest::CameraLerp() {
	// check if the length of horizontal and vertical of projection + (target projection - current projection) * zoomInfo.t is not exceed the minimum and maximum.
	// if not, calculate the lerp of left right bottom top and update using SetDrawArea().

}