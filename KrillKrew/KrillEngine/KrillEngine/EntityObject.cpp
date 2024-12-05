
#include "EntityObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"


EntityObject::EntityObject()
{
	isAnimated = false;
	collider = new Collider(Collider::Trigger, this);
	spriteRenderer = new SpriteRenderer("");
	this->pos = glm::vec3(0, 0, 0);
}


EntityObject::~EntityObject()
{
}

void EntityObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void EntityObject::SetSpriteInfo(SpritesheetInfo info)
{
	spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
}
//void EntityObject::SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight) {
//	sheetInfo.row = row;
//	sheetInfo.column = column;
//	sheetInfo.spritewidth = spritewidth;
//	sheetInfo.spriteheight = spriteheight;
//	sheetInfo.sheetwidth = sheetwidth;
//	sheetInfo.sheetheight = sheetheight;
//}

void EntityObject::Render(glm::mat4 globalModelTransform)
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
Collider* EntityObject::GetCollider()
{
	return collider;
}
void EntityObject::OnColliderEnter(Collider* other)
{
	std::cout << "On Collider Enter" << std::endl;
}
void EntityObject::OnColliderStay(Collider* other)
{
	std::cout << "On Collider Stay" << std::endl;
}
void EntityObject::OnColliderExit(Collider* other)
{
	std::cout << "On Collider Exit" << std::endl;
}
void EntityObject::OnTriggerEnter(Collider* other)
{
	std::cout << "On Trigger Enter" << std::endl;
}
void EntityObject::OnTriggerStay(Collider* other)
{
	std::cout << "On Trigger Enter" << std::endl;
}
void EntityObject::OnTriggerExit(Collider* other)
{
	std::cout << "On Trigger Enter" << std::endl;
}