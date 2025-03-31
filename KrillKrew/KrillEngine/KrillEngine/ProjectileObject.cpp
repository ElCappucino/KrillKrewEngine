
#include "ProjectileObject.h"



ProjectileObject::ProjectileObject()
{
	collider = new Collider(Collider::Trigger, this);
	this->pos = glm::vec3(0, 0, 0);
	this->playerOwner = nullptr;

	this->orderingLayer = 3;
}


ProjectileObject::~ProjectileObject()
{
}

void ProjectileObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}


void ProjectileObject::Render(glm::mat4 globalModelTransform)
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

void ProjectileObject::SetVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY) {

	if (!isPositiveX) {
		axisX = -axisX;
	}
	if (!isPositiveY) {
		axisY = -axisY;
	}
	velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0);

}

glm::vec3 ProjectileObject::GetVelocity() 
{
	return velocity;
}

void ProjectileObject::SetLifeTime(float lifeTime) 
{
	this->lifeTime = lifeTime;
}
void ProjectileObject::SetOwner(PlayerObject* player)
{
	this->playerOwner = player;
}
void ProjectileObject::ReduceLifeTime() 
{
	lifeTime -= 1;
	if (lifeTime <= 0) 
	{ 
		
		playerOwner->SetIsShooting(false);
		if (this->type == TypeProjectile::Fireball)
		{
			ExplodeTileInRange();
		}
		else if (this->type == ProjectileObject::TypeProjectile::Teleport) {
			playerOwner->SetPosition(this->getPos());
		}
		else
		{
			KK_ERROR("This is not fireball");
		}
	}
}

void ProjectileObject::AddTileInRange(TileObject* tile)
{
	KK_TRACE("AddTileInRange");
	TileInRange.push_back(tile);
}
void ProjectileObject::DeleteTileInRange(TileObject* tile)
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
void ProjectileObject::ExplodeTileInRange()
{
	KK_TRACE("Tile in range = {0}", TileInRange.size());
	for (TileObject* tile : TileInRange)
	{
		tile->GotHit();
	}
	this->isActive = false;
}

int ProjectileObject::GetLifetime() 
{
	return lifeTime;
}
Collider* ProjectileObject::GetCollider()
{
	return collider;
}

void ProjectileObject::OnColliderEnter(Collider* other)
{
	// Base
	EntityObject::OnColliderEnter(other);

	TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());

	if (tile != nullptr)
	{
		AddTileInRange(tile);
	}
	// Behavior
	PlayerObject* player = dynamic_cast<PlayerObject*>(other->GetParent());
	if (player != nullptr)
	{
		if (this->playerOwner != player)
		{
			if (playerOwner == nullptr)
			{
				KK_ERROR("Projectile has no owner");
			}
			else
			{
				KK_INFO("Projectile Hit Player");
				playerOwner->SetIsShooting(false);

				if (this->type == TypeProjectile::Fireball)
				{
					ExplodeTileInRange();
				}
				else if (this->type == ProjectileObject::TypeProjectile::Teleport) {
					playerOwner->SetPosition(this->getPos());
					playerOwner->GetGroundColliderObject()->SetPosition(this->getPos());
					playerOwner->SetPosition(this->getPos());
				}
				else
				{
					KK_ERROR("This is not fireball");
				}

				this->isActive = false;

				
			}
		}
		
	}
}
void ProjectileObject::OnColliderStay(Collider* other)
{
	// Base
	EntityObject::OnColliderStay(other);

	// Behavior
}
void ProjectileObject::OnColliderExit(Collider* other)
{
	// Base
	EntityObject::OnColliderExit(other);

	TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());

	if (tile != nullptr)
	{
		DeleteTileInRange(tile);
	}
	// Behavior
}
void ProjectileObject::OnTriggerEnter(Collider* other)
{
	// Base
	EntityObject::OnTriggerEnter(other);

	// Behavior
}
void ProjectileObject::OnTriggerStay(Collider* other)
{
	// Base
	EntityObject::OnTriggerStay(other);

	// Behavior
}
void ProjectileObject::OnTriggerExit(Collider* other)
{
	// Base
	EntityObject::OnTriggerExit(other);

	// Behavior
}
//int ProjectileObject::getNumOwner() {
//	return playerNumOwner;
//}

PlayerObject* ProjectileObject::GetOwner()
{
	return playerOwner;
}

void ProjectileObject::SetIsCanKnockback(bool isCanKnockback) {
	this->isCanKnockback = isCanKnockback;
}

bool ProjectileObject::GetIsCanKnockback() {
	return isCanKnockback;
}

void ProjectileObject::SetType(TypeProjectile Type) {
	this->type = Type;
}

ProjectileObject::TypeProjectile ProjectileObject::GetType() {
	return type;
}

void ProjectileObject::SetIsShooting(bool isShooting) {
	this->isShooting = isShooting;
}
bool ProjectileObject::GetIsShooting() {
	return isShooting;
}

void ProjectileObject::SetIsCanStun(bool isCanStun) {
	this->isCanStun = isCanStun;
}

bool ProjectileObject::GetIsCanStun() {
	return isCanStun;
}