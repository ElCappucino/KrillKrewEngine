#include "ParticleObject.h"

ParticleObject::ParticleObject() 
{
	isAnimated = true;
	collider = new Collider(Collider::Trigger, this);
	collider->setColliderSize(this->size);
	spriteRenderer = new SpriteRenderer("");
	this->pos = glm::vec3(0, 0, 0);

	this->orderingLayer = -2000;
		
	currAnimState = AnimationState::idle;
	type = ParticleType::BigProp;

	this->spriteRenderer->ShiftTo(0, 0);
	this->spriteRenderer->SetFrame(10);
	this->SetSize(this->spriteRenderer->GetSpriteWidth(), this->spriteRenderer->GetSpriteHeight());

	//this->SetTexture("../Resource/Texture/Props/prop_spr_vfx_leaf.png");
}
ParticleObject::~ParticleObject() 
{

}

void ParticleObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}


void ParticleObject::Render(glm::mat4 globalModelTransform)
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

void ParticleObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}

void ParticleObject::SetColliderSize(glm::vec3 size) 
{

}
void ParticleObject::OnColliderEnter(Collider* other) 
{

}
void ParticleObject::OnColliderStay(Collider* other) 
{

}
void ParticleObject::OnColliderExit(Collider* other) 
{

}
void ParticleObject::OnTriggerEnter(Collider* other) 
{

}
void ParticleObject::OnTriggerStay(Collider* other) 
{

}
void ParticleObject::OnTriggerExit(Collider* other) 
{

}
void ParticleObject::UpdateSpriteSheetPosition()
{
	this->GetSpriteRenderer()->ShiftColumn();
}
void ParticleObject::UpdateCurrentAnimation() 
{
	KK_CORE_WARN("ParticleObject: UpdateCurrentAnimation");
	KK_CORE_WARN("ParticleObject: Position = {0} {1} {2}", this->pos.x, this->pos.y, this->pos.z);
	int currentColumn = this->GetSpriteRenderer()->GetColumn();
	float lastFrame = (GetSpriteRenderer()->GetSheetWidth() / GetSpriteRenderer()->GetSpriteWidth()) - 1;

	if (currentColumn == lastFrame)
	{
		this->SetIsActive(false);
	}
}
void ParticleObject::UpdateCollider() 
{

}

float ParticleObject::getOrderingLayer() const
{
	return 1000;
}
