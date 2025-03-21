#include "LevelLoading.h"


void LevelLoading::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	spriteList["LoadPage"] = SpritesheetInfo("LoadPage", "../Resource/Texture/loading.png", 1920, 1080, 1920, 1080);

	//cout << "Load Level" << endl;
}

void LevelLoading::LevelInit()
{
	std::cout << "Level Loading Init" << std::endl;

	glClearColor(0.f, 180.f / 255.f, 171.f / 255.f, 1.f);

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));


	// Example Code
	ImageObject* obj1 = new ImageObject();
	obj1->SetSpriteInfo(spriteList.find("LoadPage")->second);
	obj1->SetTexture(spriteList.find("LoadPage")->second.texture);
	obj1->SetSize(SCREEN_WIDTH, -SCREEN_HEIGHT);
	obj1->SetPosition(glm::vec3(0.f, 0.f, 0));
	objectsList.push_back(obj1);

	std::cout << GameEngine::GetInstance()->GetStateController()->loadingState << std::endl;
	
}

void LevelLoading::LevelUpdate()
{
	dt++;

}

void LevelLoading::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);

	GameEngine::GetInstance()->GetStateController()->gameStateNext = GameEngine::GetInstance()->GetStateController()->loadingState;
	// cout << "Draw Level" << endl;
}

void LevelLoading::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();

	//cout << "Free Level" << endl;
}

void LevelLoading::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	//cout << "Unload Level" << endl;
}

void LevelLoading::HandleKey(char key)
{

	switch (key)
	{
	case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELMAPTEST; ; break;
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

void LevelLoading::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;
}