#include "LevelMainMenu.h"

void LevelMainMenu::LevelLoad() {
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);


}

void LevelMainMenu::LevelInit() {
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

	//test text
	config configbutton0;
	configbutton0.number = 0;
	configbutton0.text = "start";
	configbutton0.textPosX = 100.f;
	configbutton0.textPosY = 100.f;
	configbutton0.textSize = 50;
	TextObject* texted = new TextObject();
	configs.push_back(configbutton0);
	loadConfig("button0.json");
	texted->loadText(configs.at(0).text, SDL_Color{255,0,0,0}, configs.at(0).textSize);
	texted->SetPosition(glm::vec3(configs.at(0).textPosX, configs.at(0).textPosY, 0));
	objectsList.push_back(texted);
	textList.push_back(texted);
	

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
	for (int i = 0; i < configs.size(); i++) {
		objectsList.at(i)->SetPosition(glm::vec3(configs.at(i).textPosX, configs.at(i).textPosY, 0));
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
		loadConfig("button0.json");
		textList.at(0)->loadText(configs.at(0).text, SDL_Color{255,0,0,0}, configs.at(0).textSize);
		textList.at(0)->SetPosition(glm::vec3(configs.at(0).textPosX, configs.at(0).textPosY, 0));
	}
	
	for (int i = 0; i < configs.size(); i++) {
		ImGui::Text("Button%d", i);
		//ImGui::InputTextWithHint("Text", "enter text here", &configs.at(i).text[0], configs.at(i).text[0] + 1);
		ImGui::InputInt("Text Size", &configs.at(i).textSize);
		ImGui::SliderFloat("PosX", &configs.at(i).textPosX, -camera.GetCameraWidth() / 2, camera.GetCameraWidth() / 2);
		ImGui::SliderFloat("PosY", &configs.at(i).textPosY, -camera.GetCameraHeight() / 2, camera.GetCameraHeight() / 2);
		if (ImGui::Button("Save config")) {
			LevelMainMenu::config c;
			c.number = configs.at(i).number;
			//c.text = configs.at(i).text;
			c.textPosX = configs.at(i).textPosX;
			c.textPosY = configs.at(i).textPosY;
			c.textSize = configs.at(i).textSize;
			//std::cout << c.text << std::endl;
			std::string fileName = "button" + std::to_string(i) + ".json";
			saveConfig(fileName, c);
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

}

void LevelMainMenu::UpdateUi() {

}

void LevelMainMenu::saveConfig(std::string& filename, config con) {
	nlohmann::json data;
	data["number"] = con.number;
	//data["text"] = con.text;
	data["textPosX"] = con.textPosX;
	data["textPosY"] = con.textPosY;
	data["textSize"] = con.textSize;

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
			if (configs.at(i).number == id) {
				std::cout << "Loaded" << std::endl;
				//configs.at(i).text = data["text"];
				configs.at(i).textPosX = data["textPosX"];
				configs.at(i).textPosY = data["textPosY"];
				configs.at(i).textSize = data["textSize"];
			}
		}
	}

	else {
		std::cout << "Failed" << std::endl;
	}
}