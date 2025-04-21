
#include "TrapObject.h"



TrapObject::TrapObject()
{
	collider = new Collider(Collider::Trigger, this);
	this->pos = glm::vec3(0, 0, 0);

	this->orderingLayer = 3;
}


TrapObject::~TrapObject()
{
	TileInRange.clear();
	
}

void TrapObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void TrapObject::Render(glm::mat4 globalModelTransform)
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

void TrapObject::SetLifeTime(int lifeTime) {
	this->lifeTime = lifeTime;
}

void TrapObject::ReduceLifeTime() {
	lifeTime -= 1;
}
int TrapObject::GetLifetime() {
	return lifeTime;
}

void TrapObject::SetPlayerNumber(int num) {
	playerNumOwner = num;
}

int TrapObject::GetPlayerNumber() {
	return playerNumOwner;
}

void TrapObject::AddTileInRange(TileObject* tile)
{
	KK_TRACE("AddTileInRange");
	TileInRange.push_back(tile);
}
void TrapObject::DeleteTileInRange(TileObject* tile)
{
	auto clearTile = std::find(TileInRange.begin(), TileInRange.end(), tile);

	// KK_INFO("clearTile");

	if (clearTile != TileInRange.end())
	{
		// KK_INFO("completely clear tile");
		KK_TRACE("DeleteTileInRange");
		TileInRange.erase(clearTile);

	}
}
void TrapObject::ExplodeTileInRange()
{
	KK_TRACE("Tile in range = {0}", TileInRange.size());
	for (TileObject* tile : TileInRange)
	{
		tile->GotHit();
	}
	this->isActive = false;
}

void TrapObject::OnColliderEnter(Collider* other)
{
	TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());

	if (tile != nullptr)
	{
		AddTileInRange(tile);
	}

	// Behavior when collide with player
	PlayerObject* player = dynamic_cast<PlayerObject*>(other->GetParent());
	if (player != nullptr)
	{
		
		if (this->GetPlayerNumber() != player->GetPlayerNumber())
		{
			//KK_TRACE("Collide with TNT");
			switch (type)
			{
				case TypeTrap::Trap:
					//KK_TRACE("Trap of player {0} hit player {1}", this->GetPlayerNumber(), player->GetPlayerNumber());
					player->SetSlowDuration(100);
					player->SetIsSlow(true);

					// player->ApplyKnockback(this);


					this->isActive = false;
					break;
				case TypeTrap::Tnt:
					if (isActivate)
					{
						//KK_TRACE("Activate TNT");
						SetCanKnockback(true);
						player->ApplyKnockback(this);
						this->isActive = false;
						
					}
					break;
			}
			
		}
	}
	
}
void TrapObject::OnColliderStay(Collider* other)
{
	PlayerObject* player = dynamic_cast<PlayerObject*>(other->GetParent());
	if (player != nullptr)
	{

		if (this->GetPlayerNumber() != player->GetPlayerNumber())
		{
			//KK_TRACE("Collide with TNT");
			switch (type)
			{
			case TypeTrap::Tnt:
				if (isActivate)
				{
					//KK_TRACE("Activate TNT");
					SetCanKnockback(true);
					player->ApplyKnockback(this);
					this->isActive = false;

				}
				break;
			}

		}
	}
}
void TrapObject::OnColliderExit(Collider* other)
{
	TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());

	if (tile != nullptr)
	{
		DeleteTileInRange(tile);
	}
}
void TrapObject::OnTriggerEnter(Collider* other)
{

}
void TrapObject::OnTriggerStay(Collider* other)
{

}
void TrapObject::OnTriggerExit(Collider* other)
{
}

void TrapObject::SetCanKnockback(bool isCanKnockback) {
	this->CanKnockback = isCanKnockback;
}

bool TrapObject::GetCanKnockback() {
	return CanKnockback;
}

void TrapObject::SetType(int type) {
	this->type = type;
}

bool TrapObject::GetType() {
	return type;
}