#include "UiObject.h"

UiObject::UiObject()
{
	SpritesheetInfo placeholder("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	this->sheetInfo = placeholder;
	this->isAnimated = false;
	this->pos = glm::vec3(0, 0, 0);
	this->size = glm::vec3(215.f, -100.f, 0);
	this->playerNumOwner = 0;

	this->orderingLayer = 4;
}


UiObject::~UiObject()
{
}

void UiObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

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

void UiObject::OnColliderEnter(Collider* other)
{

}
void UiObject::OnColliderStay(Collider* other)
{

}
void UiObject::OnColliderExit(Collider* other)
{

}
void UiObject::OnTriggerEnter(Collider* other)
{

}
void UiObject::OnTriggerStay(Collider* other)
{

}
void UiObject::OnTriggerExit(Collider* other)
{

}

