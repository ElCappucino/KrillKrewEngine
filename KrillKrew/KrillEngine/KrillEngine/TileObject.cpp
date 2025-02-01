#include "TileObject.h"

TileObject::TileObject()
{
	this->isBreakable = false;
	this->collider = new Collider(Collider::Trigger, this);

	this->maxDurability = 3;
	this->currentDurability = 3;

	SpritesheetInfo crackEffectSprite = SpritesheetInfo("CrackEffect", "../Resource/Texture/tileCrack.png", 128, 128, 512, 128);

	this->crackOverlay = new ImageObject();
	this->crackOverlay->SetSpriteInfo(crackEffectSprite);
	this->crackOverlay->SetSize(128.f, -128.f);
	this->crackOverlay->GetSpriteRenderer()->ShiftColumn();
	this->crackOverlay->GetSpriteRenderer()->ShiftColumn();

}
TileObject::~TileObject()
{

}

void TileObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}
void TileObject::SetTexture(std::string path)
{
	this->texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void TileObject::SetIsBreakable(bool isBreakable)
{
	this->isBreakable = isBreakable;
	if (!isBreakable)
	{
		this->crackOverlay->SetIsActive(false);
	}
}

void TileObject::Render(glm::mat4 globalModelTransform)
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

void TileObject::SetSize(float sizeX, float sizeY)
{
	size = glm::vec3(sizeX, sizeY, 1);
	crackOverlay->SetSize(sizeX, sizeY);

}
void TileObject::SetPosition(glm::vec3 newPosition)
{
	pos = newPosition;
	crackOverlay->SetPosition(newPosition);
}

Collider* TileObject::GetCollider()
{
	return this->collider;
}

ImageObject* TileObject::GetOverlaySprite()
{
	return this->crackOverlay;
}

void TileObject::OnColliderEnter(Collider* other)
{

}
void TileObject::OnColliderStay(Collider* other)
{

}
void TileObject::OnColliderExit(Collider* other)
{

}
void TileObject::OnTriggerEnter(Collider* other)
{
	KK_TRACE("Trigger Tile");
	PlayerObject* player = dynamic_cast<PlayerObject*>(other->GetParent());

	if (player != nullptr)
	{
		KK_TRACE("Add Tile");
		player->AddAimingTile(this);
	}
}
void TileObject::OnTriggerStay(Collider* other)
{

}
void TileObject::OnTriggerExit(Collider* other)
{

}