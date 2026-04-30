
#include "ProjectileObject.h"
#include "SoundManager.h"


ProjectileObject::ProjectileObject()
{
	collider = new Collider(Collider::Trigger, this);
	this->pos = glm::vec3(0, 0, 0);
	this->playerOwner = nullptr;
	
	this->orderingLayer = 3;

	this->isAnimated = true;
	this->rotateAngle = 0;

	this->spriteRenderer->SetFrame(10);
}


ProjectileObject::~ProjectileObject()
{
	TileInRange.clear();
	playerOwner = nullptr;
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
void ProjectileObject::SetSize(float sizeX, float sizeY)
{
	size = glm::vec3(sizeX, sizeY, 1);
	this->collider->setColliderSize(size);
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
void ProjectileObject::ReduceLifeTime(float dt) 
{
	lifeTime -= dt;
	if (lifeTime <= 0.0f && currAnimState != AnimationState::Collide)
	{
		if (type == ProjectileObject::TypeProjectile::Cleave)
		{
			this->SetIsActive(false);
		}
		if (type == ProjectileObject::TypeProjectile::Teleport) 
		{
			playerOwner->SetPosition(this->getPos());
		}
		
		if (this->type == TypeProjectile::Fireball)
		{
			this->SetRotation(0);
			ExplodeTileInRange();
		}
		else if (this->type == ProjectileObject::TypeProjectile::Teleport) 
		{
			playerOwner->SetPosition(this->getPos());
		}
		else
		{
			//KK_ERROR("This is not fireball");
		}
		auto CollideSprite = animList.find(AnimationState::Collide);
		if (CollideSprite != animList.end())
		{
			ProjectileObject::ChangeAnimationState(AnimationState::Collide);
		}
		
	}
}

void ProjectileObject::AddTileInRange(TileObject* tile)
{
	//KK_TRACE("AddTileInRange");
	TileInRange.push_back(tile);
}
void ProjectileObject::DeleteTileInRange(TileObject* tile)
{
	auto clearTile = std::find(TileInRange.begin(), TileInRange.end(), tile);

	// KK_INFO("clearTile");

	if (clearTile != TileInRange.end())
	{
		// KK_INFO("completely clear tile");
		//KK_TRACE("DeleteTileInRange");
		TileInRange.erase(clearTile);

	}
}
void ProjectileObject::ExplodeTileInRange()
{
	//KK_TRACE("Tile in range = {0}", TileInRange.size());
	for (TileObject* tile : TileInRange)
	{
		tile->GotHit();
	}
	//this->isActive = false;
}

float ProjectileObject::GetLifetime()
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

		if (this->type == TypeProjectile::Cleave && this->isShooting)
		{
			auto checktile = std::find(TileInRange.begin(), TileInRange.end(), tile);
			if (checktile != TileInRange.end())
			{
				tile->GotHit();
			}
		}
		
	}
	// Behavior
	PlayerObject* player = dynamic_cast<PlayerObject*>(other->GetParent());
	if (player != nullptr)
	{
		if (this->playerOwner != player)
		{
			playerOwner->SetIsShooting(false);
			playerOwner->SetIsAiming(false);
			if (playerOwner == nullptr)
			{
				//KK_ERROR("Projectile has no owner");
			}
			else if (currAnimState != AnimationState::Collide)
			{
				//KK_INFO("Projectile Hit Player");
				playerOwner->SetIsShooting(false);
				KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Player_Damaged", false);

				if (this->type == TypeProjectile::Fireball)
				{
					ExplodeTileInRange();
					player->ApplyKnockback(this);
					KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Bomb_Explosion", false);
				}
				else if (this->type == TypeProjectile::Bola)
				{
					player->SetIsStun(true);
					player->SetStunDuraion(10);
					KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Bola_Hit", false);
				}
				else if (this->type == ProjectileObject::TypeProjectile::Teleport) {
					playerOwner->SetPosition(this->getPos());
					playerOwner->GetGroundColliderObject()->SetPosition(this->getPos());
					playerOwner->SetPosition(this->getPos());
					KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Teleport_Hit", false);
				}
				else
				{
					//KK_ERROR("This is not fireball");
				}
				
				/*playerOwner->RemoveOwningProjectile(this);
				this->isActive = false;*/

				// updateSpritesheet
				if (this->type == TypeProjectile::Fireball)
				{
					this->SetRotation(0);
				}
				

				auto CollideSprite = animList.find(AnimationState::Collide);
				if (CollideSprite != animList.end())
				{
					ProjectileObject::ChangeAnimationState(AnimationState::Collide);
				}
				
				// set column to 0
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

void ProjectileObject::SetCanKnockback(bool isCanKnockback) {
	this->CanKnockback = isCanKnockback;
}

bool ProjectileObject::GetCanKnockback() {
	return CanKnockback;
}

void ProjectileObject::SetType(TypeProjectile Type) {
	this->type = Type;

	switch (type)
	{
		case ProjectileObject::TypeProjectile::Fireball:
			this->SetSize(300.f, -300.f);
			break;
		case ProjectileObject::TypeProjectile::Teleport:
			this->SetSize(211.f * 0.8f, -97.f * 0.8f);
			break;
		case ProjectileObject::TypeProjectile::Bola:
			this->SetSize(400.f * 0.7f, -400.f * 0.7f);
			break;
		case ProjectileObject::TypeProjectile::Cleave:
			this->SetSize(358.f * 0.8f, -258.f * 0.8f);
			break;
	}
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
	this->CanStun = isCanStun;
}

bool ProjectileObject::GetIsCanStun() {
	return CanStun;
}
void ProjectileObject::UpdateCurrentAnimation()
{
	
	if (currAnimState == AnimationState::Collide)
	{
		this->SetVelocity(0, 0, true, true);
		
		float lastFrame = (GetSpriteRenderer()->GetSheetWidth() / GetSpriteRenderer()->GetSpriteWidth()) - 1;
		KK_CORE_WARN("ProjectileObject: lastFrame = {0}", lastFrame);
		KK_CORE_WARN("ProjectileObject: GetSpriteRenderer()->GetColumn() = {0}", GetSpriteRenderer()->GetColumn());
		if (GetIsAnimated() && GetSpriteRenderer()->GetColumn() == lastFrame)
		{
			this->SetIsActive(false);
			playerOwner->SetIsShooting(false);
			playerOwner->RemoveOwningProjectile(this);
		}
	}
}

void ProjectileObject::SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo)
{
	animList.insert({ state, spriteInfo });
}

void ProjectileObject::ChangeAnimationState(AnimationState anim)
{
	if (currAnimState != anim)
	{
		currAnimState = anim;
		this->SetTextureWithID(animList.find(anim)->second, animList.find(anim)->second.textureid);
		this->spriteRenderer->SetTexture(animList.find(anim)->second.texture);
		//this->SetTexture(animList.find(anim)->second.texture);
		this->spriteRenderer->ShiftTo(0, 0);
		this->spriteRenderer->isLoop = animList.find(anim)->second.isLoop;

		if (anim == AnimationState::Collide)
		{
			// up size explode effect
			this->SetSize(this->getSize().x * 2.0f, this->getSize().y * 2.0f);
		}
		
	}
}

void ProjectileObject::UpdateCollider()
{
	this->GetCollider()->Update(this->getSize() * 0.5f, this->getPos());
}

float ProjectileObject::getOrderingLayer() const {
	return -2000;
}