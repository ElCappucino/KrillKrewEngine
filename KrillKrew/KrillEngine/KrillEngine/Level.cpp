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

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-3, 3, -3, 3);
	//cout << "Init Level" << endl;
}

void Level::LevelUpdate()
{
	dt += 1;
	cout << dt << endl;
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
		case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVEL2; ; break;


		// This part needs to move to GameplayScene class later
		case 'i': 
			
			GameEngine::GetInstance()->SetDrawArea(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left + 0.2f,
												   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right - 0.2f,
												   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom + 0.2f,
												   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top - 0.2f);
			break;

		case 'o': 

			GameEngine::GetInstance()->SetDrawArea(GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().left - 0.2f,
												   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().right + 0.2f,
												   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().bottom - 0.2f,
												   GameEngine::GetInstance()->GetRenderer()->GetOrthovalue().top + 0.2f);
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

	player->SetPosition(glm::vec3(realX, realY, 0));
}


