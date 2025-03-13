#include "LevelSelectAbility.h"

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void LevelSelectAbility::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	LineMeshVbo* line = new LineMeshVbo();
	line->LoadData();
	GameEngine::GetInstance()->AddMesh(LineMeshVbo::MESH_NAME, line);

	spriteList["Prinny"] = SpritesheetInfo("Prinny", "../Resource/Texture/Prinny.png", 538, 538, 538, 538);
	spriteList["Bomb"] = SpritesheetInfo("Bomb", "../Resource/Texture/Bomb_icon.png", 256, 256, 256, 256);
	spriteList["Shark_run"] = SpritesheetInfo("Shark_run", "../Resource/Texture/shark_run_test.png", 256, 256, 1024, 256);
	spriteList["Shark_idle"] = SpritesheetInfo("Shart_idle", "../Resource/Texture/shark_Idle_test.png", 256, 256, 256, 256);

	spriteList["Trap"] = SpritesheetInfo("Trap", "../Resource/Texture/Trap.png", 512, 512, 512, 512);
	spriteList["TNT"] = SpritesheetInfo("TNT", "../Resource/Texture/TNT.png", 348, 348, 348, 348);
	spriteList["Teleport"] = SpritesheetInfo("Teleport", "../Resource/Texture/EnderPearl.png", 512, 512, 512, 512);
	spriteList["Bola"] = SpritesheetInfo("Bola", "../Resource/Texture/Bola.png", 317, 314, 317, 314);
	spriteList["Cleave"] = SpritesheetInfo("Cleave", "../Resource/Texture/Cleave.png", 647, 386, 647, 386);

	spriteList["Xoey_UI"] = SpritesheetInfo("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	spriteList["Byssa_UI"] = SpritesheetInfo("Byssa_UI", "../Resource/Texture/byssa.png", 430, 220, 430, 220);
	spriteList["Crunk_UI"] = SpritesheetInfo("Crunk_UI", "../Resource/Texture/crunk.png", 430, 220, 430, 220);
	spriteList["Ham_UI"] = SpritesheetInfo("Ham_UI", "../Resource/Texture/Ham.png", 430, 220, 430, 220);
	//cout << "Load Level" << endl;


}

void LevelSelectAbility::LevelInit()
{

	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	GameEngine::GetInstance()->GetRenderer()->SetClearColor(1.0f, 1.0f, 200.0f / 255);
	timer = Timer::Instance();

	// Create and Initialize 4 players object

	// Example Code
	PlayerObject* obj1 = new PlayerObject();
	obj1->GetCollider()->SetCollisionType(Collider::Kinematic);
	obj1->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj1->SetIsAnimated(true);
	obj1->GetSpriteRenderer()->SetFrame(10);
	obj1->SetSize(256.f, -256.f);
	obj1->SetPosition(glm::vec3(-200.f, -200.f, 0));
	obj1->SetPlayerNumber(0);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj1->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	// New enum type
	obj1->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	obj1->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	obj1->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Cleave);
	/*obj1->setAbility(0, 5);
	obj1->setAbility(1, 1);
	obj1->setAbility(2, 2);*/
	objectsList.push_back(obj1);
	playerSize++;
	players[0] = obj1;

	PlayerObject* obj2 = new PlayerObject();
	obj2->GetCollider()->SetCollisionType(Collider::Static);
	obj2->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj2->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj2->SetIsAnimated(true);
	obj2->GetSpriteRenderer()->SetFrame(15);
	obj2->SetSize(256.f, -256.f);
	obj2->SetPosition(glm::vec3(200.f, -200.f, 0));
	obj2->SetPlayerNumber(1);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj2->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj2->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	obj2->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	obj2->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Dash);
	objectsList.push_back(obj2);
	playerSize++;
	players[1] = obj2;

	PlayerObject* obj3 = new PlayerObject();
	obj3->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj3->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj3->SetSize(256.f, -256.f);
	obj3->SetPosition(glm::vec3(-200.f, 200.f, 0));
	obj3->GetSpriteRenderer()->SetFrame(15);
	obj3->SetPlayerNumber(2);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj3->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj3->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	obj3->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	obj3->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Dash);
	objectsList.push_back(obj3);
	playerSize++;
	players[2] = obj3;


	PlayerObject* obj4 = new PlayerObject();
	obj4->SetSpriteInfo(spriteList.find("Shark_idle")->second);
	obj4->SetTexture(spriteList.find("Shark_idle")->second.texture);
	obj4->SetSize(256.f, -256.f);
	obj4->SetPosition(glm::vec3(200.f, 200.f, 0));
	obj4->GetSpriteRenderer()->SetFrame(15);
	obj4->SetPlayerNumber(3);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Idle, spriteList.find("Shark_idle")->second);
	obj4->SetAnimationSprite(PlayerObject::AnimationState::Running, spriteList.find("Shark_run")->second);
	obj4->SetAbility(PlayerObject::AbilityButton::Triangle, PlayerObject::Ability::Fireball);
	obj4->SetAbility(PlayerObject::AbilityButton::Circle, PlayerObject::Ability::Trap);
	obj4->SetAbility(PlayerObject::AbilityButton::Cross, PlayerObject::Ability::Dash);
	objectsList.push_back(obj4);
	playerSize++;
	players[3] = obj4;

	objectsList.push_back(players[0]->GetCollider()->GetGizmos());
	objectsList.push_back(players[1]->GetCollider()->GetGizmos());
	objectsList.push_back(players[2]->GetCollider()->GetGizmos());
	objectsList.push_back(players[3]->GetCollider()->GetGizmos());

	//create Ui by PlayerObject
	int sizePlayer = objectsList.size();
	int count = 0;
	for (int i = 0; i < sizePlayer; i++) {

		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		if (player != nullptr)
		{
			if (count == 0) {
				UiObject* uiSkills = new UiObject();
				uiSkills->SetSpriteInfo(spriteList.find("Xoey_UI")->second);
				uiSkills->SetTexture(spriteList.find("Xoey_UI")->second.texture);
				uiSkills->SetPosition(glm::vec3(0, 0, 0));
				uiSkills->SetSize(215.f, -100.f);
				uiSkills->setNumOwner(0);
				objectsList.push_back(uiSkills);
				count++;
				std::cout << "create Ui xoey" << std::endl;
			}
			else if (count == 1) {
				UiObject* uiSkills1 = new UiObject();
				uiSkills1->SetSpriteInfo(spriteList.find("Ham_UI")->second);
				uiSkills1->SetTexture(spriteList.find("Ham_UI")->second.texture);
				uiSkills1->SetPosition(glm::vec3(0, 0, 0));
				uiSkills1->SetSize(215.f, -100.f);
				uiSkills1->setNumOwner(1);
				objectsList.push_back(uiSkills1);
				count++;
				std::cout << "create Ui Ham" << std::endl;
			}
			else if (count == 2) {
				UiObject* uiSkills2 = new UiObject();
				uiSkills2->SetSpriteInfo(spriteList.find("Byssa_UI")->second);
				uiSkills2->SetTexture(spriteList.find("Byssa_UI")->second.texture);
				uiSkills2->SetPosition(glm::vec3(0, 0, 0));
				uiSkills2->SetSize(215.f, -100.f);
				uiSkills2->setNumOwner(2);
				objectsList.push_back(uiSkills2);
				count++;
				std::cout << "create Ui byssa" << std::endl;
			}
			else if (count == 3) {
				UiObject* uiSkills3 = new UiObject();
				uiSkills3->SetSpriteInfo(spriteList.find("Crunk_UI")->second);
				uiSkills3->SetTexture(spriteList.find("Crunk_UI")->second.texture);
				uiSkills3->SetPosition(glm::vec3(0, 0, 0));
				uiSkills3->SetSize(215.f, -100.f);
				uiSkills3->setNumOwner(3);
				objectsList.push_back(uiSkills3);
				count++;
				std::cout << "create Ui crunk" << std::endl;
			}
		}
	}

	std::cout << "Init Level" << std::endl;
}

void LevelSelectAbility::LevelUpdate()
{
	dt++;

	for (int i = 0; i < objectsList.size(); i++)
	{
		if (objectsList[i]->GetIsActive() == false)
		{
			objectsList.erase(objectsList.begin() + i);
		}
	}

	// UpdateInput();
	UpdateInput();

	for (int i = 0; i < playerSize; i++) {
		camera.setPlayerPos(i, players[i]->getPos());
	}
	camera.LerpCamera(playerSize); // update smooth camera here

	// Set Animation
	for (int i = 0; i < objectsList.size(); i++)
	{
		EntityObject* entity = dynamic_cast<EntityObject*>(objectsList[i]);
		if (entity == nullptr)
		{
			continue;
		}
		else
		{
			if (entity->GetIsAnimated() &&
				dt % entity->GetSpriteRenderer()->GetFrame() == 0)
			{
				entity->GetSpriteRenderer()->ShiftColumn();
				entity->UpdateCurrentAnimation();
			}
		}
	}
}

void LevelSelectAbility::UpdateInput()
{
	if (SDL_NumJoysticks() > 0)
	{

		Joystick::Update();
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{

		}
	}
}

void LevelSelectAbility::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);

	// Collider Gizmos update
	for (int i = 0; i < objectsList.size(); i++)
	{
		PlayerObject* player = dynamic_cast<PlayerObject*>(objectsList[i]);
		//ProjectileObject* projectile = dynamic_cast<ProjectileObject*>(objectsList[i]);
		TrapObject* trap = dynamic_cast<TrapObject*>(objectsList[i]);
		if (player != nullptr)
		{
			player->GetCollider()->Update(player->getSize(), player->getPos());
		}
		if (trap != nullptr) {
			objectsList.push_back(trap->GetCollider()->GetGizmos());
			trap->GetCollider()->Update(trap->getSize(), trap->getPos());
		}

		else
		{
			EntityObject* object = dynamic_cast<EntityObject*>(objectsList[i]);
			if (object != nullptr)
			{
				object->GetCollider()->Update(object->getSize(), object->getPos());
			}
		}
	}
	// cout << "Draw Level" << endl;
}

void LevelSelectAbility::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();

	//cout << "Free Level" << endl;
}

void LevelSelectAbility::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();

	//cout << "Unload Level" << endl;
}

void LevelSelectAbility::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY){}
void LevelSelectAbility::HandleKey(char key){}
void LevelSelectAbility::HandleMouse(int type, int x, int y){}

