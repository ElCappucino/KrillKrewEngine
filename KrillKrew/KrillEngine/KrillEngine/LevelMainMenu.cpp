#include "LevelMainMenu.h"

void LevelMainMenu::LevelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	spriteList["SkillIconBox"] = SpritesheetInfo("SkillIconBox", "../Resource/Texture/SkillIconBox.png", 167, 157, 334, 157);

}

void LevelMainMenu::LevelInit() {
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	//test text
	config* configbutton0 = new config();
	configbutton0->number = 0;
	configbutton0->text = "start";
	configbutton0->textPosX = 100.f;
	configbutton0->textPosY = 100.f;
	configbutton0->textSize = 50.f;
	configbutton0->boxHight = 157.f;
	configbutton0->boxWidth = 167.f;
	configbutton0->boxPosX = 100.f;
	configbutton0->boxPosY = 100.f;
	configs.push_back(configbutton0);
	if (checkConfig("button0.json")) {
		loadConfig("button0.json");
	}
	UiObject* box0 = new UiObject();
	box0->SetSpriteInfo(spriteList.find("SkillIconBox")->second);
	box0->SetPosition(glm::vec3(configs.at(0)->boxPosX, configs.at(0)->boxPosY, 0.f));
	box0->SetSize(configs.at(0)->boxWidth, configs.at(0)->boxHight);
	TextObject* text0 = new TextObject();
	text0->loadText(configs.at(0)->text, SDL_Color{255,0,0,0}, configs.at(0)->textSize);
	text0->SetPosition(glm::vec3(configs.at(0)->textPosX, configs.at(0)->textPosY, 0.f));
	objectsList.push_back(box0);
	boxList.push_back(box0);
	objectsList.push_back(text0);
	textList.push_back(text0);

	config* configbutton1 = new config();
	configbutton1->number = 1;
	configbutton1->text = "text1";
	configbutton1->textPosX = 100.f;
	configbutton1->textPosY = 100.f;
	configbutton1->textSize = 50.f;
	configbutton1->boxHight = 157.f;
	configbutton1->boxWidth = 167.f;
	configbutton1->boxPosX = 100.f;
	configbutton1->boxPosY = 100.f;
	configs.push_back(configbutton1);
	if (checkConfig("button1.json")) {
		loadConfig("button1.json");
	}
	UiObject* box1 = new UiObject();
	box1->SetSpriteInfo(spriteList.find("SkillIconBox")->second);
	box1->SetPosition(glm::vec3(configs.at(1)->boxPosX, configs.at(1)->boxPosY, 0.f));
	box1->SetSize(configs.at(1)->boxWidth, configs.at(1)->boxHight);
	TextObject* text1 = new TextObject();
	text1->loadText(configs.at(1)->text, SDL_Color { 255, 0, 0, 0 }, configs.at(1)->textSize);
	text1->SetPosition(glm::vec3(configs.at(1)->textPosX, configs.at(1)->textPosY, 0.f));
	objectsList.push_back(box1);
	boxList.push_back(box1);
	objectsList.push_back(text1);
	textList.push_back(text1);
	
	

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

	// select box
	for (int i = 0; i < configs.size(); i++)
	{
		if (configs.at(i)->number == playerWhere[0])
		{
			boxList.at(i)->GetSpriteRenderer()->ShiftColumn();
		}
		else {
			boxList.at(i)->GetSpriteRenderer()->ShiftTo(0,0);
		}
		
	}

	for (int i = 0; i < configs.size(); i++) {
		textList.at(i)->loadText(configs.at(i)->text, SDL_Color { 255, 0, 0, 0 }, configs.at(i)->textSize);
		textList.at(i)->SetPosition(glm::vec3(configs.at(i)->textPosX, configs.at(i)->textPosY, 0));
		boxList.at(i)->SetSize(configs.at(i)->boxWidth, configs.at(i)->boxHight);
		boxList.at(i)->SetPosition(glm::vec3(configs.at(i)->boxPosX, configs.at(i)->boxPosY, 0));
	}
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

	if (ImGui::Button("Load config")) {
		for(int i = 0; i < configs.size(); i++) {
			std::string fileName = "button" + std::to_string(i) + ".json";
			loadConfig(fileName);
			textList.at(i)->loadText(configs.at(i)->text, SDL_Color{ 255,0,0,0 }, configs.at(0)->textSize);
			textList.at(i)->SetPosition(glm::vec3(configs.at(i)->textPosX, configs.at(i)->textPosY, 0));
			boxList.at(i)->SetSize(configs.at(i)->boxWidth, configs.at(i)->boxHight);
			boxList.at(i)->SetPosition(glm::vec3(configs.at(i)->boxPosX, configs.at(i)->boxPosY, 0));
		}
		
	}
	
	for (int i = 0; i < configs.size(); i++) {
		ImGui::PushID(i);
		ImGui::Text("Button%d", i);
		//ImGui::InputTextWithHint("Text", "enter text here", &configs.at(i).text[0], configs.at(i).text[0] + 1);
		ImGui::InputFloat("Text Size", &configs.at(i)->textSize);
		ImGui::SliderFloat("Text PosX", &configs.at(i)->textPosX, -camera.GetCameraWidth() / 2, camera.GetCameraWidth() / 2);
		ImGui::SliderFloat("Text PosY", &configs.at(i)->textPosY, -camera.GetCameraHeight() / 2, camera.GetCameraHeight() / 2);
		ImGui::InputFloat("Box Hight", &configs.at(i)->boxHight);
		ImGui::InputFloat("Box Width", &configs.at(i)->boxWidth);
		ImGui::SliderFloat("Box PosX", &configs.at(i)->boxPosX, -camera.GetCameraWidth() / 2, camera.GetCameraWidth() / 2);
		ImGui::SliderFloat("Box PosY", &configs.at(i)->boxPosY, -camera.GetCameraHeight() / 2, camera.GetCameraHeight() / 2);
		ImGui::PopID();
	}

	if (ImGui::Button("Save config")) {
		for (int i = 0; i < configs.size(); i++) {
			std::string fileName = "button" + std::to_string(i) + ".json";
			saveConfig(fileName, configs.at(i));
		}
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

}

void LevelMainMenu::saveConfig(std::string& filename, config* con) {
	nlohmann::json data;
	data["number"] = con->number;
	//data["text"] = con.text;
	data["textPosX"] = con->textPosX;
	data["textPosY"] = con->textPosY;
	data["textSize"] = con->textSize;
	data["boxPosX"] = con->boxPosX;
	data["boxPosY"] = con->boxPosY;
	data["boxHight"] = con->boxHight;
	data["boxWidth"] = con->boxWidth;

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
	nlohmann::json data = nlohmann::json::parse(file);
	int id = data["number"];

	if (file.is_open()) {
		std::cout << "Opened" << std::endl;
		for (int i = 0; i < configs.size(); i++) {
			if (configs.at(i)->number == id) {
				std::cout << "Loaded" << std::endl;
				//configs.at(i).text = data["text"];
				if (data.contains("textPosX") && !data["textPosX"].is_null()) {
					configs.at(i)->textPosX = data["textPosX"];
				}
				
				if (data.contains("textPosY") && !data["textPosY"].is_null()) {
					configs.at(i)->textPosY = data["textPosY"];
				}
				
				if (data.contains("textSize") && !data["textSize"].is_null()) {
					configs.at(i)->textSize = data["textSize"];
				}

				if (data.contains("boxPosX") && !data["boxPosX"].is_null()) {
					configs.at(i)->boxPosX = data["boxPosX"];
				}
				
				if (data.contains("boxPosY") && !data["boxPosY"].is_null()) {
					configs.at(i)->boxPosY = data["boxPosY"];
				}

				if (data.contains("boxHight") && !data["boxHight"].is_null()) {
					configs.at(i)->boxHight = data["boxHight"];
				}
				
				if (data.contains("boxWidth") && !data["boxWidth"].is_null()) {
					configs.at(i)->boxWidth = data["boxWidth"];
				}
			}
		}
	}

	else {
		std::cout << "Failed" << std::endl;
	}
}

bool LevelMainMenu::checkConfig(std::string filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		nlohmann::json data = nlohmann::json::parse(file);
		if (!data.contains("textPosX") || data["textPosX"].is_null()) {
			return false;
		}

		if (!data.contains("textPosY") || data["textPosY"].is_null()) {
			return false;
		}

		if (!data.contains("textSize") || data["textSize"].is_null()) {
			return false;
		}

		if (!data.contains("boxPosX") || data["boxPosX"].is_null()) {
			return false;
		}

		if (!data.contains("boxPosY") || data["boxPosY"].is_null()) {
			return false;
		}

		if (!data.contains("boxHight") || data["boxHight"].is_null()) {
			return false;
		}

		if (!data.contains("boxWidth") || data["boxWidth"].is_null()) {
			return false;
		}
	}
	else {
		std::cout << "No file for check" << std::endl;
		return false;
	}
	return true;
}