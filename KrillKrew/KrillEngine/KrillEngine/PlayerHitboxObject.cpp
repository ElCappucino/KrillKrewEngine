#include "PlayerHitboxObject.h"
#include "PlayerObject.h"

PlayerHitboxObject::PlayerHitboxObject(PlayerObject* parent)
{
	this->parent = parent;
	this->collider = new Collider(Collider::Trigger, parent);
	this->isAnimated = false;

	glm::vec3 attackSize = glm::vec3(parent->getSize().x / 4, parent->getSize().y / 4, 0);
	glm::vec3 attackPos = glm::vec3(parent->getPos().x + 64.f, parent->getPos().y, 0);
	this->size = attackSize;
	this->pos = attackPos;

	this->collider->Update(attackSize, attackPos);

	SpritesheetInfo hitboxSprite = SpritesheetInfo("hitbox", "../Resource/Texture/marker01.png", 500, 500, 500, 500);

	this->SetSpriteInfo(hitboxSprite);

	this->orderingLayer = 2;
}
PlayerHitboxObject::~PlayerHitboxObject()
{
	parent = nullptr;
}

void PlayerHitboxObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}
void PlayerHitboxObject::SetTexture(std::string path)
{
	this->texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}
void PlayerHitboxObject::Render(glm::mat4 globalModelTransform)
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

void PlayerHitboxObject::SetSize(float sizeX, float sizeY)
{
	this->size = glm::vec3(sizeX, sizeY, 0);
}
void PlayerHitboxObject::SetPosition(glm::vec3 newPosition)
{
	this->pos = newPosition;
}

Collider* PlayerHitboxObject::GetCollider()
{
	return this->collider;
}

void PlayerHitboxObject::OnColliderEnter(Collider* other)
{
	TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());
	if (tile != nullptr)
	{
		// KK_TRACE("hit Tile");
		this->parent->AddAimingTile(tile);
	}
}
void PlayerHitboxObject::OnColliderStay(Collider* other)
{

}
void PlayerHitboxObject::OnColliderExit(Collider* other)
{
	TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());
	if (tile != nullptr)
	{
		// KK_TRACE("On ColliderExit PlayerHitboxObject");
		this->parent->ClearAimingTile(tile);
	}
}
void PlayerHitboxObject::OnTriggerEnter(Collider* other)
{

}
void PlayerHitboxObject::OnTriggerStay(Collider* other)
{

}
void PlayerHitboxObject::OnTriggerExit(Collider* other)
{

}