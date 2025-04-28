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
	TextObject* texted = new TextObject();
	texted->loadText("Start", SDL_Color{ 255,0,0,0 }, 50);
	texted->SetPosition(glm::vec3(100, 100, 0));
	posX.push_back(texted->getPos().x);
	posY.push_back(texted->getPos().y);
	objectsList.push_back(texted);

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
	for (int i = 0; i < posX.size(); i++) {
		objectsList.at(i)->SetPosition(glm::vec3(posX.at(i), posY.at(i), 0));
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

	for (int i = 0; i < posX.size(); i++) {
		ImGui::Text("Button%d", i);
		ImGui::SliderFloat("posX", &posX.at(i), -camera.GetCameraWidth() / 2, camera.GetCameraWidth() / 2);
		ImGui::SliderFloat("posY", &posY.at(i), -camera.GetCameraHeight() / 2, camera.GetCameraHeight() / 2);
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