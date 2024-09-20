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

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-3, 3, -3, 3);

	// Create and Initialize 4 players object

	// Example Code
	/*GameObject* obj = new GameObject();
	obj->SetColor(0.0, 1.0, 0.0);
	objectsList.push_back(obj);

	player = obj;*/

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
	// clamp the zoom result in between current projection and target projection.
	// update the ortho projection little by little base on the dt. ex. if dt %smoothTime = 0 set orthoprojection += or -= velocity

}