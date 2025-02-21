
#include "PlayerObject.h"
#include "Collider.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

#include "PlayerHitboxObject.h"
#include "TileObject.h"

PlayerObject::PlayerObject()
{
	this->isAnimated = true;

	this->playerNumber = 0;

	this->slowness = 2;
	this->slowDuration = 0;
	this->dashSpeed = 5;
	this->dashDuration = 0;

	this->isSlow = false;
	this->isShooting = false;
	this->isAiming = false;
	this->isFacingLeft = false;
	this->isDashing = false;

	this->pos = glm::vec3(0, 0, 0);
	this->velocity = glm::vec3(0, 0, 0);
	this->size = glm::vec3(256.f, -256.f, 0);
	this->currDirection = glm::vec2(1.f, 0.f);

	currAnimState = AnimationState::Idle;

	this->GetCollider()->SetCollisionType(Collider::Kinematic);

	this->attackCollider = new PlayerHitboxObject(this);
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}
void PlayerObject::Render(glm::mat4 globalModelTransform)
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

	squareMesh->ChangeTextureData(
		spriteRenderer->GetRow(),
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

void PlayerObject::UpdateFacingSide(bool isLeft)
{
	if (isLeft && isFacingLeft == false || !isLeft && isFacingLeft == true)
	{
		this->size.x = this->size.x * -1;
		isFacingLeft = isLeft;
	}
}
void PlayerObject::SetVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY)
{
	xIsPositive = isPositiveX;
	yIsPositive = isPositiveY;

	if (!isPositiveX) {
		axisX = -axisX;
	}

	if (!isPositiveY) {
		axisY = -axisY;
	}

	if (isDashing) 
	{
		velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0) * dashSpeed;
	}
	else if (isSlow) 
	{
		std::cout << "IsSlow" << std::endl;
		velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0) / slowness;
	}
	else
	{
		velocity = glm::vec3(axisX * 5.f, axisY * 5.f, 0);
	}

}

bool PlayerObject::getXIsPositive() 
{
	return xIsPositive;
}

bool PlayerObject::getYIsPositive() 
{
	return yIsPositive;
}
void PlayerObject::SetIsShooting(bool isShooting)
{
	this->isShooting = isShooting;
}
void PlayerObject::SetIsAiming(bool isAiming)
{
	this->isAiming = isAiming;
}
void PlayerObject::SetPlayerNumber(int num) 
{
	this->playerNumber = num;
}
void PlayerObject::SetAbilityCooldown(PlayerObject::AbilityButton button, int duration)
{
	abilityCooldown[static_cast<int>(button)] = duration;
}
void PlayerObject::SetSlowDuration(int duration)
{
	this->slowDuration = duration;
}
void PlayerObject::SetIsSlow(bool isSlow)
{
	this->isSlow = isSlow;
}
void PlayerObject::SetIsDashing(bool isDashing)
{
	this->isDashing = isDashing;
}
void PlayerObject::SetDashDuration(int duration) 
{
	this->dashDuration = duration;
}
void PlayerObject::SetAbility(AbilityButton button, Ability ability)
{
	abilities[static_cast<int>(button)] = ability;
}
void PlayerObject::SetPlayerUI(UiObject* ui)
{
	this->playerUI = ui;
}
void PlayerObject::SetCurrentDirection(glm::vec2 dir)
{
	this->currDirection = dir;
}
void PlayerObject::ReduceAbilityCooldown(int button)
{
	abilityCooldown[button] -= 1;
	// KK_TRACE("Reduce Cooldown Skill: {0} Cooldown {1}", button, GetCooldown(button));
}
void PlayerObject::ReduceSlowDuration()
{
	slowDuration -= 1;
	// KK_TRACE("Reduce slow duration: Player Number {0} Duration: {1}", GetPlayerNumber(), slowDuration);
}
void PlayerObject::ReduceDashDuration() 
{
	dashDuration -= 1;
}
void PlayerObject::SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo)
{
	animList.insert({ state, spriteInfo });
}
void PlayerObject::ChangeAnimationState(AnimationState anim)
{
	if (currAnimState != anim)
	{
		currAnimState = anim;
		this->SetSpriteInfo(animList.find(anim)->second);
		this->spriteRenderer->SetTexture(animList.find(anim)->second.texture);
		this->SetTexture(animList.find(anim)->second.texture);
		this->spriteRenderer->ShiftTo(0, 0);
	}
}
void PlayerObject::UpdateCurrentAnimation()
{
	/*if (currAnimState == AnimationState::Melee)
	{
		KK_INFO("Current Animation : Melee");
	}
	else if (currAnimState == AnimationState::Idle)
	{
		KK_INFO("Current Animation : Idle");
	}
	else if (currAnimState == AnimationState::Running)
	{
		KK_INFO("Current Animation : Running");
	}*/

	if (currAnimState == AnimationState::Melee)
	{
		if (this->spriteRenderer->GetColumn() == (this->spriteRenderer->GetSheetWidth() / this->spriteRenderer->GetSpriteWidth()) - 1)
		{
			ChangeAnimationState(AnimationState::Idle);
		}
	}
	else if 
	(
		(abs(this->velocity.x) > 0 || abs(this->velocity.y > 0)) && 
		currAnimState != AnimationState::Running &&
		currAnimState != AnimationState::Melee
	)
	{
		ChangeAnimationState(AnimationState::Running);
	}
	else if 
	(
		abs(this->velocity.x) <= 0 || abs(this->velocity.y <= 0) && 
		currAnimState == AnimationState::Running &&
		currAnimState != AnimationState::Melee
	)
	{
		ChangeAnimationState(AnimationState::Idle);
	}
}
Collider* PlayerObject::GetCollider() const
{
	return collider;
}
Collider* PlayerObject::GetAttackCollider() const
{
	return attackCollider->GetCollider();
}
PlayerHitboxObject* PlayerObject::GetAttackColliderObject() const
{
	return attackCollider;
}
void PlayerObject::OnColliderEnter(Collider* other)
{
	// Base
	EntityObject::OnColliderEnter(other);

	// Behavior
}
void PlayerObject::OnColliderStay(Collider* other)
{
	// Base
	EntityObject::OnColliderStay(other);

	// Behavior
}
void PlayerObject::OnColliderExit(Collider* other)
{
	// Base
	EntityObject::OnColliderExit(other);

	// Behavior
}
void PlayerObject::OnTriggerEnter(Collider* other)
{
	// Base
	EntityObject::OnTriggerEnter(other);

	// Behavior
}
void PlayerObject::OnTriggerStay(Collider* other)
{
	// Base
	EntityObject::OnTriggerStay(other);

	// Behavior
}
void PlayerObject::OnTriggerExit(Collider* other)
{
	// Base
	EntityObject::OnTriggerExit(other);

	// Behavior
}
glm::vec3 PlayerObject::GetVelocity() const
{
	return velocity;
}
bool PlayerObject::GetIsAiming() const
{
	return isAiming;
}
bool PlayerObject::GetIsSlow() const
{
	return isSlow;
}
bool PlayerObject::GetIsDashing() const
{
	return isDashing;
}
bool PlayerObject::GetIsShooting() const
{
	return isShooting;
}
int PlayerObject::GetPlayerNumber() const
{
	return playerNumber;
}
float PlayerObject::GetCooldown(PlayerObject::AbilityButton button) const
{
	return abilityCooldown[static_cast<int>(button)];
}
float PlayerObject::GetSlowDuration() const
{
	return slowDuration;
}
float PlayerObject::GetDashDuration() const
{
	return dashDuration;
}
glm::vec2 PlayerObject::GetCurrentDirection() const
{
	return currDirection;
}
PlayerObject::Ability PlayerObject::GetAbilityByButton(AbilityButton button) const
{
	return abilities[static_cast<int>(button)];
}
void PlayerObject::AddAimingTile(TileObject* tile)
{
	aimingTile.push_back(tile);
}
void PlayerObject::clearAimingTile(TileObject* tile)
{
	auto clearTile = std::find(aimingTile.begin(), aimingTile.end(), tile);

	// KK_INFO("clearTile");

	if (clearTile != aimingTile.end())
	{
		// KK_INFO("completely clear tile");
		aimingTile.erase(clearTile);
		
	}
}

void PlayerObject::HitAimingTile()
{
	// KK_INFO("aiming Tile Amount = {0}", aimingTile.size());
	for (int i = 0; i < aimingTile.size(); i++)
	{
		if (aimingTile[i]->GetIsActive() == false)
		{
			auto clearTile = std::find(aimingTile.begin(), aimingTile.end(), aimingTile[i]);
			aimingTile.erase(clearTile);
		}
		else
		{
			if (aimingTile[i]->GetIsBreakable())
			{
				aimingTile[i]->GotHit();
			}
			
		}
		
	}
}

//int PlayerObject::getIdAbility(int numberAbility) {
//	return abilities[numberAbility];
//}

void PlayerObject::setIsKnockback(bool isKnockback) {
	this->isKnockback = isKnockback;
}

void PlayerObject::setDurationKnockback(int time){
	durationKnockback = time;
}

void PlayerObject::reduceDurationKnockback(){
	durationKnockback -= 1;
}

bool PlayerObject::getIsKnockback() {
	return isKnockback;
}

float PlayerObject::getDurationKnockback(){
	return durationKnockback;
}

void PlayerObject::setIsTNT(bool isTNT) {
	this->isTNT = isTNT;
}

bool PlayerObject::getIsTNT() {
	return isTNT;
}
