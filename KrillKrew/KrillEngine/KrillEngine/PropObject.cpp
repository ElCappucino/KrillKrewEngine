#include "PropObject.h"

PropObject::PropObject()
{

	this->collider = new Collider(Collider::Trigger, this);

	this->maxDurability = 3;
	this->currentDurability = 0;
	//this->isAnimated = false; // change later
	//this->GetSpriteRenderer()->SetFrame(10);

	this->orderingLayer = 3;

	this->currAnimState = AnimationState::Idle;
}
PropObject::~PropObject()
{

}

// int(*groundTileInfo)[MAP_HEIGHT][MAP_WIDTH];

void PropObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}
void PropObject::SetTexture(std::string path)
{
	this->texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}
void PropObject::Render(glm::mat4 globalModelTransform)
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

//virtual void SetSize(float sizeX, float sizeY);
//virtual void SetPosition(glm::vec3 newPosition);

void PropObject::CheckIfBreak()
{
	if (currentDurability >= maxDurability)
	{
		currAnimState = AnimationState::Breaking;
	}
}
void PropObject::GotHit()
{
	currentDurability++;
	CheckIfBreak();
}

Collider* PropObject::GetCollider()
{
	return this->collider;
}

void PropObject::OnColliderEnter(Collider* other)
{

}
void PropObject::OnColliderStay(Collider* other) 
{

}
void PropObject::OnColliderExit(Collider* other) 
{

}
void PropObject::OnTriggerEnter(Collider* other) 
{

}
void PropObject::OnTriggerStay(Collider* other) 
{

}
void PropObject::OnTriggerExit(Collider* other) 
{

}

void PropObject::UpdateSpriteSheetPosition() 
{

}

float PropObject::getOrderingLayer() const {
	return this->pos.y + (this->size.y / 2.f);
	//if (propType == PropType::Small)
	//{
	//	return this->pos.y;
	//}
	//else if (propType == PropType::Tree)
	//{
	//	//KK_CORE_INFO("pos.y = {0} Size y = {1} order = {2}", this->pos.y, this->size.y, this->pos.y + this->size.y);
	//	return this->pos.y + (this->size.y / 2.f);
	//}
	
}