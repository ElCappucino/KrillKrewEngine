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
	std::cout << "Init Level" << std::endl;
	
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
																  (SCREEN_WIDTH / 2),
																 -(SCREEN_HEIGHT / 2),
																  (SCREEN_HEIGHT / 2));

	std::map<int, std::pair<int, int>> blob_lookup_table = {
	{16,	{1, 1}},
	{17,	{2, 1}},
	{1,		{3, 1}},
	{0,		{4, 1}},

	{20,	{1, 2}},
	{21,	{2, 2}},
	{5,		{3, 2}},
	{4,		{4, 2}},

	{84,	{1, 3}},
	{85,	{2, 3}},
	{69,	{3, 3}},
	{68,	{4, 3}},

	{80,	{1, 4}},
	{81,	{2, 4}},
	{65,	{3, 4}},
	{64,	{4, 4}},

	{213,	{1, 5}},
	{29,	{2, 5}},
	{23,	{3, 5}},
	{117,	{4, 5}},

	{92,	{1, 6}},
	{127,	{2, 6}},
	{223,	{3, 6}},
	{71,	{4, 6}},

	{116,	{1, 7}},
	{253,	{2, 7}},
	{247,	{3, 7}},
	{197,	{4, 7}},

	{87,	{1, 8}},
	{113,	{2, 8}},
	{209,	{3, 8}},
	{93,	{4, 8}},

	{28,	{1, 9}},
	{31,	{2, 9}},
	{95,	{3, 9}},
	{7,		{4, 9}},

	{125,	{1, 10}},
	{119,	{2, 10}},
	{255,	{3, 10}},
	{199,	{4, 10}},

	{124,	{1, 11}},
	{256,	{2, 11}}, // blank
	{221,	{3, 11}},
	{215,	{4, 11}},

	{112,	{1, 12}},
	{245,	{2, 12}},
	{241,	{3, 12}},
	{193,	{4, 12}},
	};
	
	TileImport(groundTile, "../Resource/Texture/Tilemap1.txt");

	// Create and Initialize 4 players object

	SquareMeshVbo* square = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	float map_left = -300.f;
	float map_top = 250.f;

	for (int i = 0; i < MAP_HEIGHT; i++) 
	{
		for (int j = 0; j < MAP_WIDTH; j++) 
		{
			int flag = groundTile[i][j];

			std::pair<int, int> pos;

			if (i == 0 ||
				i == MAP_HEIGHT - 1 ||
				j == 0 ||
				j == MAP_WIDTH - 1 ||
				flag == 0)
			{
				continue;

				/*auto it = blob_lookup_table.find(256);
				if (it != blob_lookup_table.end())
				{
					pos = it->second;
					std::cout << "Bitset = " << 256 << std::endl;
					std::cout << "pair = " << it->second.first << " " << it->second.second << std::endl;
				}*/
				
			}
			else 
			{
				std::bitset<8> surround;
				surround[0] = groundTile[i - 1][j];
				surround[1] = groundTile[i - 1][j + 1];
				surround[2] = groundTile[i]    [j + 1];
				surround[3] = groundTile[i + 1][j + 1];
				surround[4] = groundTile[i + 1][j];
				surround[5] = groundTile[i + 1][j - 1];
				surround[6] = groundTile[i]    [j - 1];
				surround[7] = groundTile[i - 1][j - 1];

				if (!(surround[0] && surround[2])) { surround[1] = 0; } 
				if (!(surround[2] && surround[4])) { surround[3] = 0; }
				if (!(surround[4] && surround[6])) { surround[5] = 0; }
				if (!(surround[6] && surround[0])) { surround[7] = 0; }

				auto it = blob_lookup_table.find((int)(surround.to_ulong()));
				std::cout << "Bitset = " << (int)surround.to_ulong() << std::endl;
				if (it != blob_lookup_table.end())
				{
					pos = it->second;
					
					std::cout << "pair = " << it->second.first << " " << it->second.second << std::endl;
				}
				else {
					std::cout << "blob_lookup_table.end()" << std::endl;
				}
			}

			// std::cout << flag << ",";
			ImageObject* obj = new ImageObject();
			obj->SetSheetInfo(pos.first - 1, pos.second - 1, 128, 128, 1536, 512);
			obj->SetTexture("../Resource/Texture/blobtile_test.png");
			obj->SetSize(32.f, -32.f);
			obj->SetPosition(glm::vec3(map_left + (j * 32.f), map_top - (i * 32.f), 0));
			objectsList.push_back(obj);

			// std::cout << "posX = " << obj->getPos().x << " posY = " << obj->getPos().y << std::endl;
		}
		std::cout << std::endl;
	}

	//cout << "Init Level" << endl;
}

void LevelMapTest::LevelUpdate()
{
	// dt++;

	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();

		printf("Joystick No.1 Triangle: %d Square: %d Cross: %d Circle: %d Leftstick: %f\n",
			Joystick::GetButton(0, Joystick::Button::Triangle),
			Joystick::GetButton(0, Joystick::Button::Square),
			Joystick::GetButton(0, Joystick::Button::Cross),
			Joystick::GetButton(0, Joystick::Button::Circle),
			Joystick::GetAxis(0, Joystick::Axis::LeftStickHorizontal));
	}
	

	

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

void LevelMapTest::TileImport(int TileBuffer[][MAP_WIDTH], std::string fileName) {
	std::ifstream mapfile(fileName);
	std::string line;
	int row = 0;
	int column = 1;
	if (!mapfile.is_open()) {
		// error
		std::cout << "Error: reading tile information" << std::endl;
	}
	else {
		int counter = 0;
		while (!mapfile.eof()) {
			//string line;
			if (getline(mapfile, line, ',')) {

				TileBuffer[counter / MAP_WIDTH][counter % MAP_WIDTH] = std::stoi(line);

				counter++;
			}
		}
		mapfile.close();

	}
}

void LevelMapTest::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

}