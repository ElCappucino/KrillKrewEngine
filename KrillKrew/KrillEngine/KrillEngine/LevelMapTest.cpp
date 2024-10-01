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
	
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_RATIO_X / 2),
		(SCREEN_RATIO_X / 2),
		-(SCREEN_RATIO_Y / 2),
		(SCREEN_RATIO_Y));

	// targetSceneProjection = GameEngine::GetInstance()->GetRenderer()->GetOrthovalue();

	/*zoomInfo.maxZoom_horizontal = 3;
	zoomInfo.maxZoom_vertical = 3;
	zoomInfo.minZoom_horizontal = 1;
	zoomInfo.minZoom_vertical = 1;*/

	TileImport(groundTile, "../Resource/Texture/Tilemap1.txt");

	// Create and Initialize 4 players object

	SquareMeshVbo* square = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			int flag = groundTile[i][j];
			cout << flag << ",";
			ImageObject* obj = new ImageObject();
			obj->SetSheetInfo(0, flag, 128, 128, 256, 128);
			obj->SetTexture("../Resource/Texture/groundTile.png");
			obj->SetSize(128.f, -128.f);
			obj->SetPosition(glm::vec3(-200.f + (j * 128), 100.f - (i * 128), 0));
			objectsList.push_back(obj);
		}
		cout << endl;
	}

	//square->ChangeTextureData(0, 0, 128, 128, 256, 128);

	//ImageObject* obj1 = new ImageObject();
	//obj1->SetSheetInfo(0, 0, 128, 128, 256, 128);
	//obj1->SetTexture("../Resource/Texture/groundTile.png");
	//obj1->SetSize(256.f, -256.f);
	//obj1->SetPosition(glm::vec3(-500.f, -500.f, 0));
	//objectsList.push_back(obj1);

	//player[0] = obj1;

	////square->ChangeTextureData(0, 1, 128, 128, 256, 128);

	//ImageObject* obj2 = new ImageObject();
	//obj2->SetSheetInfo(0, 1, 128, 128, 256, 128);
	//obj2->SetTexture("../Resource/Texture/groundTile.png");
	//obj2->SetSize(256.f, -256.f);
	//obj2->SetPosition(glm::vec3(500.f, -500.f, 0));
	//objectsList.push_back(obj2);

	//player[1] = obj2;

	////square->ChangeTextureData(0, 0, 128, 128, 256, 128);

	//ImageObject* obj3 = new ImageObject();
	//obj3->SetSheetInfo(0, 0, 128, 128, 256, 128);
	//obj3->SetTexture("../Resource/Texture/groundTile.png");
	//obj3->SetSize(256.f, -256.f);
	//obj3->SetPosition(glm::vec3(-500.f, 500.f, 0));
	//objectsList.push_back(obj3);

	//player[2] = obj3;

	////square->ChangeTextureData(0, 1, 128, 128, 256, 128);

	//ImageObject* obj4 = new ImageObject();
	//obj4->SetSheetInfo(0, 1, 128, 128, 256, 128);
	//obj4->SetTexture("../Resource/Texture/groundTile.png");
	//obj4->SetSize(256.f, -256.f);
	//obj4->SetPosition(glm::vec3(500.f, 500.f, 0));
	//objectsList.push_back(obj4);

	//player[3] = obj4;

	//cout << "Init Level" << endl;
}

void LevelMapTest::LevelUpdate()
{
	// dt++;

	// CameraLerp(); // update smooth camera here

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
				cout << line << "(" << counter << ":" << counter / MAP_HEIGHT << ":" << counter % MAP_WIDTH << "),";


				/*if (column == MAP_WIDTH - 1 ) {
					cout << endl;
					column = 0;
				}
				column++;*/
				counter++;
			}
		}
		cout << endl << "--------------------------------------------" << endl;
		mapfile.close();

		/*for (int i = 0; i < MAP_HEIGHT; i++) {
			for (int j = 0; j < MAP_WIDTH; j++) {
				cout << TileBuffer[i][j] << " ";
			}
			cout << endl;
		}*/
	}
}