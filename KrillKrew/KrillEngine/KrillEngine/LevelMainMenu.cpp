#include "LevelMainMenu.h"

void LevelMainMenu::LevelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	spriteList["BG"] = SpritesheetInfo("BG", "../Resource/Texture/Menu/UI_Menu_BG.png", 1920, 1080, 1920, 1080);
	spriteList["Text"] = SpritesheetInfo("Text", "../Resource/Texture/Menu/UI_Menu_Text.png", 289, 65, 2312, 65);
	spriteList["Name"] = SpritesheetInfo("Name", "../Resource/Texture/Menu/UI_Menu_KrillsKrew.png", 470, 55, 940, 55);
}

void LevelMainMenu::LevelInit() {
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	//BG
	UiObject* BG = new UiObject();
	BG->SetSpriteInfo(spriteList.find("BG")->second);
	BG->SetSize(camera.GetCameraWidth(), -camera.GetCameraHeight());
	objectsList.push_back(BG);
	

	//text
	for (int i = 0; i < 4; i++) {
		std::string fileName = "text" + std::to_string(i) + ".json";
		config* configtext = new config();
		configtext->number = i;
		configtext->posX = 100;
		configtext->posY = 100;
		configtext->width = 289;
		configtext->height = 65;
		configs.push_back(configtext);
		loadConfig(fileName);
		UiObject* text = new UiObject();
		text->SetSpriteInfo(spriteList.find("Text")->second);
		text->SetPosition(glm::vec3(configs.at(i)->posX, configs.at(i)->posY, 0));
		text->SetSize(configs.at(i)->width, -configs.at(i)->height);
		text->GetSpriteRenderer()->ShiftTo(text->GetSpriteRenderer()->GetRow(), i * 2);
		objectsList.push_back(text);
		textList.push_back(text);
		
	}
	
	// game name
	config* configName = new config();
	configName->number = 4;
	configName->posX = 100;
	configName->posY = 100;
	configName->width = 470;
	configName->height = 55;
	configs.push_back(configName);
	loadConfig("text4.json");
	UiObject* name = new UiObject();
	name->SetSpriteInfo(spriteList.find("Name")->second);
	name->SetPosition(glm::vec3(configs.at(4)->posX, configs.at(4)->posY, 0));
	name->SetSize(configs.at(4)->width, configs.at(4)->width);
	objectsList.push_back(name);
	textList.push_back(name);
	

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	const char* glsl_version = "#version 330";
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(GameEngine::GetInstance()->GetSDLWindow(), GameEngine::GetInstance()->GetglContext());
	ImGui_ImplOpenGL3_Init(glsl_version);

	std::cout << GameEngine::GetInstance()->GetStateController()->loadingState << std::endl;
}
void LevelMainMenu::LevelUpdate() {
	UpdateInput();
	UpdateUi();

	// select box
	/*for (int i = 0; i < configs.size(); i++)
	{
		if (configs.at(i)->number == playerWhere[0])
		{
			textList.at(i)->GetSpriteRenderer()->ShiftColumn();
		}
		else {
			textList.at(i)->GetSpriteRenderer()->ShiftTo(0,0);
		}
		
	}*/

	
}

void LevelMainMenu::LevelDraw() {
	GameEngine::GetInstance()->Render(objectsList);
	
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	if (ImGui::Button("Go levelSelectAbility")) {
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSELECTABILITY;
	}

	if (ImGui::Button("Save config")) {
		for (int i = 0; i < configs.size(); i++) {
			std::string fileName = "text" + std::to_string(i) + ".json";
			saveConfig(fileName, configs.at(i));
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Load config")) {
		for(int i = 0; i < configs.size(); i++) {
			std::string fileName = "text" + std::to_string(i) + ".json";
			loadConfig(fileName);
			textList.at(i)->SetPosition(glm::vec3(configs.at(i)->posX, configs.at(i)->posY, 0));
			textList.at(i)->SetSize(configs.at(i)->width, -configs.at(i)->height);
		}
	}
	
	for (int i = 0; i < configs.size(); i++) {
		ImGui::PushID(i);
		ImGui::Text("Text%d", i);
		ImGui::InputFloat("PosX", &configs.at(i)->posX, 1.0f, 1.0f, "%.2f");
		ImGui::InputFloat("PosY", &configs.at(i)->posY, 1.0f, 1.0f, "%.2f");
		ImGui::InputFloat("Width", &configs.at(i)->width, 1.0f, 1.0f, "%.2f");
		ImGui::InputFloat("Height", &configs.at(i)->height, 1.0f, 1.0f, "%.2f");
		ImGui::PopID();
	}

	
	
	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());

	// cout << "Draw Level" << endl;
}

void LevelMainMenu::LevelFree() {
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
}

void LevelMainMenu::LevelUnload() {
	GameEngine::GetInstance()->ClearMesh();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void LevelMainMenu::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

}

void LevelMainMenu::HandleKey(char key) {

}

void LevelMainMenu::HandleMouse(int type, int x, int y) {

}

void LevelMainMenu::UpdateInput() {
	if (SDL_NumJoysticks() > 0)
	{
		Joystick::Update();
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			float axisX = Joystick::GetAxis(i, Joystick::Axis::LeftStickHorizontal) / 32768.0f;
			/*std::cout << "axisX : " << axisX << std::endl;*/
			float axisY = Joystick::GetAxis(i, Joystick::Axis::LeftStickVertical) / 32768.0f;
			//std::cout << "axisY : " << axisY << std::endl;
			bool up = false;
			bool down = false;
			bool right = false;
			bool left = false;

			if (axisX > 0.8) {
				right = true;
			}

			else if (axisX < -0.8) {
				left = true;
			}

			else if (axisY > 0.8) {
				up = true;
			}

			else if (axisY < -0.8) {
				down = true;
			}

			if (!playerMove[i]) {
				if (up || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Up))
				{
					playerWhere[i] -= 1;
					if (playerWhere[i] < 0) {
						playerWhere[i] = 1;
					}
					playerMove[i] = true;
					std::cout << "y" << i << std::endl;
				}
				else if (down || Joystick::GetButtonDown(i, Joystick::Button::DPAD_Down))
				{
					playerWhere[i] += 1;
					if (playerWhere[i] > 1) {
						playerWhere[i] = 0;
					}
					playerMove[i] = true;
					std::cout << "-y" << i << std::endl;
				}
			}

			if (axisX <= 0.3 && axisX >= -0.3 && axisY <= 0.3 && axisY >= -0.3) {
				playerMove[i] = false;
			}
		}
	}
}

void LevelMainMenu::UpdateUi() {


	//Updata by config
	//text
	for (int i = 0; i < configs.size(); i++) {
		textList.at(i)->SetPosition(glm::vec3(configs.at(i)->posX, configs.at(i)->posY, 0));
		textList.at(i)->SetSize(configs.at(i)->width, -configs.at(i)->height);
	}
}

void LevelMainMenu::saveConfig(std::string& filename, config* con) {
	nlohmann::json data;
	data["number"] = con->number;
	data["posX"] = con->posX;
	data["posY"] = con->posY;
	data["hight"] = con->height;
	data["width"] = con->width;

	std::ofstream file(filename);
	if (file.is_open()) {
		file << data;
		file.close();
		std::cout << "Saved" << std::endl;
	}
	else {
		std::cout << "Failed" << std::endl;
	}
}

void LevelMainMenu::loadConfig(std::string filename) {
	std::ifstream file(filename);

	if (file.is_open()) {
		nlohmann::json data = nlohmann::json::parse(file);
		int id = -1;
		std::cout << "Opened" << std::endl;
		if (data.contains("number") && !data["number"].is_null()) {
			id = data["number"];
			for (int i = 0; i < configs.size(); i++) {
				if (configs.at(i)->number == id) {
					std::cout << "Loaded" << std::endl;
					//configs.at(i).text = data["text"];
					if (data.contains("posX") && !data["posX"].is_null()) {
						configs.at(i)->posX = data["posX"];
					}

					if (data.contains("posY") && !data["posY"].is_null()) {
						configs.at(i)->posY = data["posY"];
					}

					if (data.contains("hight") && !data["hight"].is_null()) {
						configs.at(i)->height = data["hight"];
					}

					if (data.contains("width") && !data["width"].is_null()) {
						configs.at(i)->width = data["width"];
					}
				}
			}
		}
	}

	else {
		std::cout << "Failed" << std::endl;
	}
}
