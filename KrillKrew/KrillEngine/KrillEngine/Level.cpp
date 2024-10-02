#include "Level.h"


void Level::LevelLoad()
{
	SquareMeshVbo * square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	ImageObject * obj = new ImageObject();
	obj->SetTexture("../Resource/Texture/Prinny.png");
	obj->SetSize(1.5f, -1.5f);
	objectsList.push_back(obj);

	player = obj;

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-SCREEN_WIDTH * 2, 
																 SCREEN_WIDTH * 2, 
														         -SCREEN_HEIGHT * 2, 
																 SCREEN_HEIGHT * 2);
	//cout << "Init Level" << endl;
}

void Level::LevelUpdate()
{
	dt += 1;
	// cout << dt << endl;
	//cout << "Update Level" << endl;
}

void Level::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
}

void Level::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void Level::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	//cout << "Unload Level" << endl;
}

void Level::HandleKey(char key)
{

	switch (key)
	{
		case 'w': player->Translate(glm::vec3(0, 0.3, 0)); break;
		case 's': player->Translate(glm::vec3(0, -0.3, 0)); break;
		case 'a': player->Translate(glm::vec3(-0.3, 0, 0)); break;
		case 'd': player->Translate(glm::vec3(0.3, 0, 0)); break;
		case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELGAMEPLAY; ; break;


		// This part needs to move to GameplayScene class later
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

void Level::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	GameEngine::GetInstance()->GetWindowWidth();
	GameEngine::GetInstance()->GetWindowHeight();

	cout << "X : " << realX << " Y : " << realY << endl;

	float cameraWidth = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right - GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left;
	float cameraHeight = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top - GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom;

	cout << "cameraWidth : " << cameraWidth << " cameraHeight : " << cameraHeight << endl;

	player->SetPosition(glm::vec3(((cameraWidth / (float)GameEngine::GetInstance()->GetWindowWidth()) * realX) - (cameraWidth / 2.f), -(((cameraHeight / (float)GameEngine::GetInstance()->GetWindowHeight()) * realY) - (cameraHeight / 2.f)), 0));

	cout << "Player position x : " << cameraWidth / (float)GameEngine::GetInstance()->GetWindowWidth() * realX <<
		"Player position y : " << cameraHeight / (float)GameEngine::GetInstance()->GetWindowHeight() * realY << endl;
}


