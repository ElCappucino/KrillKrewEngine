#include "UiObject.h"

UiObject::UiObject()
{
	this->pos = glm::vec3(0, 0, 0);
}


UiObject::~UiObject()
{
}

void UiObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

//void UiObject::SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight) {
//	sheetInfo.row = row;
//	sheetInfo.column = column;
//	sheetInfo.spritewidth = spritewidth;
//	sheetInfo.spriteheight = spriteheight;
//	sheetInfo.sheetwidth = sheetwidth;
//	sheetInfo.sheetheight = sheetheight;
//}

void UiObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		std::cout << "Error: Can't perform transformation " << std::endl;
		return;
	}
	if (renderModeId == -1) {
		std::cout << "Error: Can't set renderMode in ImageObject " << std::endl;
		return;
	}

	squareMesh->ChangeTextureData(spriteRenderer->GetRow(),
		spriteRenderer->GetColumn(),
		spriteRenderer->GetSpriteWidth(),
		spriteRenderer->GetSpriteHeight(),
		spriteRenderer->GetSheetWidth(),
		spriteRenderer->GetSheetHeight());

	std::vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->Render();

	}
}

void UiObject::setNumOwner(int num) {
	playerNumOwner = num;
}

int UiObject::getNumOwner() {
	return playerNumOwner;
}

