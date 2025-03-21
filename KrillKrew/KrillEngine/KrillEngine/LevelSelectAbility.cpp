#include "LevelSelectAbility.h"

void LevelSelectAbility::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
}

void LevelSelectAbility::LevelInit()
{
	GameEngine::GetInstance()->GetRenderer()->SetOrthoProjection(-(SCREEN_WIDTH / 2),
		(SCREEN_WIDTH / 2),
		-(SCREEN_HEIGHT / 2),
		(SCREEN_HEIGHT / 2));

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
	//std::ofstream MyFile("Ability.txt");
	//std::ofstream abilityFile("Ability.txt");
	for (int i = 0; i < 4; i++)
	{
		std::string fileName = "Ability" + std::to_string(i) + ".txt";
		std::ofstream abilityFile(fileName);
		abilityFile.close();
	}
}

void LevelSelectAbility::LevelUpdate()
{
	dt++;
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

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	//ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);

	if (ImGui::Button("Go levelShowcase")) {
		//abilityToFile("Ability.txt", -1);
		GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVELSHOWCASE;
	}

	for (int i = 0; i < 4; i++)
	{
		std::string fileName = "Ability" + std::to_string(i) + ".txt";
		std::string buttonName;
		ImGui::SeparatorText("");
		ImGui::Text("Ability Player %d", i);

		buttonName = "FireBall##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Fireball, i);
		}

		ImGui::SameLine();
		buttonName = "Trap##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Trap, i);
		}

		ImGui::SameLine();
		buttonName = "Dash##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Dash, i);
		}

		ImGui::SameLine();
		buttonName = "TNT##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::TNT, i);
		}

		buttonName = "Teleport##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Teleport, i);
		}

		ImGui::SameLine();
		buttonName = "Bola##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Bola, i);
		}
		ImGui::SameLine();
		buttonName = "Cleave##" + std::to_string(i);
		if (ImGui::Button(buttonName.c_str())) {
			abilityToFile(fileName, PlayerObject::Ability::Cleave, i);
		}
	}

	// Rendering
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(GameEngine::GetInstance()->GetSDLWindow());
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

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//cout << "Unload Level" << endl;
}

void LevelSelectAbility::Movement(float axisX, float axisY, bool isPositiveX, bool isPositiveY){}
void LevelSelectAbility::HandleKey(char key){}
void LevelSelectAbility::HandleMouse(int type, int x, int y){}

void LevelSelectAbility::abilityToFile(const std::string& fileName, PlayerObject::Ability abilityId, int who) {
	std::ifstream readFile(fileName);
	std::string oldContent[3];
	std::string line;
	clicked[who]++;
	int count = 0;
	int num;
	while (std::getline(readFile, line)) {
		oldContent[count] += line + "\n";
		count++;
		std::cout << "have content" << std::endl;
	}
	//std::getline(readFile, oldContent);
	readFile.close();

	std::ofstream abilityFile(fileName);
	std::cout << clicked[who] << std::endl;
	if (clicked[who] > 3) {
		if (clicked[who] % 3 == 0) {
			num = static_cast<int>(abilityId);
			oldContent[2] = std::to_string(num) + "\n";
			std::cout << "new ablity 3" << std::endl;
		}
		else if (clicked[who] % 3 == 1) {
			num = static_cast<int>(abilityId);
			oldContent[0] = std::to_string(num) + "\n";
			std::cout << "new ablity 1" << std::endl;
		}
		else if (clicked[who] % 3 == 2) {
			num = static_cast<int>(abilityId);
			oldContent[1] = std::to_string(num) + "\n";
			std::cout << "new ablity 2" << std::endl;
		}
		for (int i = 0; i < count; i++) {
			abilityFile << oldContent[i];
		}
		abilityFile.close();
	}
	else {
		for (int i = 0; i < count; i++) {
			abilityFile << oldContent[i];
		}
		abilityFile << static_cast<int>(abilityId);
		abilityFile.close();
	}
	
}

