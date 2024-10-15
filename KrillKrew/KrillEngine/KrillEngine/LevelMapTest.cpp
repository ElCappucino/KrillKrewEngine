#include "LevelMapTest.h"

void LevelMapTest::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void LevelMapTest::LevelInit()
{
	cout << "Init Level" << endl;
	
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
																  (SCREEN_WIDTH / 2),
																 -(SCREEN_HEIGHT / 2),
																  (SCREEN_HEIGHT / 2));

	// targetSceneProjection = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue();

	/*zoomInfo.maxZoom_horizontal = 3;
	zoomInfo.maxZoom_vertical = 3;
	zoomInfo.minZoom_horizontal = 1;
	zoomInfo.minZoom_vertical = 1;*/

	TileImport(groundTile, "../Resource/Texture/Tilemap1.txt");

	// Create and Initialize 4 players object

	SquareMeshVbo* square = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	float map_left = -300.f;
	float map_top = 250.f;

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			int flag = groundTile[i][j];
			cout << flag << ",";
			ImageObject* obj = new ImageObject();
			obj->SetSheetInfo(0, flag, 128, 128, 256, 128);
			obj->SetTexture("../Resource/Texture/groundTile.png");
			obj->SetSize(32.f, -32.f);
			obj->SetPosition(glm::vec3(map_left + (j * 32.f), map_top - (i * 32.f), 0));
			objectsList.push_back(obj);

			cout << "posX = " << obj->getPos().x << " posY = " << obj->getPos().y << endl;
		}
		cout << endl;
	}

	//cout << "Init Level" << endl;
}

void LevelMapTest::LevelUpdate()
{
	// dt++;

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
	case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELGAMEPLAY; ; break;
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

void LevelMapTest::TileImport(int TileBuffer[][MAP_WIDTH], string fileName) {
	ifstream mapfile(fileName);
	string line;
	int row = 0;
	int column = 1;
	if (!mapfile.is_open()) {
		// error
		cout << "Error: reading tile information" << endl;
	}
	else {
		int counter = 0;
		while (!mapfile.eof()) {
			//string line;
			if (getline(mapfile, line, ',')) {

				TileBuffer[counter / MAP_WIDTH][counter % MAP_WIDTH] = stoi(line);

				counter++;
			}
		}
		mapfile.close();

	}
}

void LevelMapTest::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

}