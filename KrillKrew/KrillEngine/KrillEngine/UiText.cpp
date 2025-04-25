#include "UiText.h"

UiText::UiText() {
	this->pos = glm::vec3(0, 0, 0);
	this->size = glm::vec3(215.f, -100.f, 0);
}

UiText::~UiText() {

}

void UiText::SetTexture(std::string path) {
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void UiText::Render(glm::mat4 globalModelTransform) {
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint modeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	glBindTexture(GL_TEXTURE_2D, texture);

	if (modelMatixId == -1) {
		std::cout << "Error: Can't perform transformation " << std::endl;
		return;
	}

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(modeId, 1);
		squareMesh->Render();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}