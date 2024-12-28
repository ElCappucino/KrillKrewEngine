#include "PlayerObjectFactory.h"

void PlayerObjectFactory::SetCurrentAnimState(PlayerObject::AnimationState state)
{
	this->currAnimState = state;
}
void PlayerObjectFactory::SetAnimationSprite(PlayerObject::AnimationState state, SpritesheetInfo spriteInfo)
{
	animList.insert({ state, spriteInfo });
}
void PlayerObjectFactory::SetPosition(glm::vec3 pos)
{
	this->position = pos;
}
void PlayerObjectFactory::SetVelocity(glm::vec3 vel)
{
	this->velocity = vel;
}
void PlayerObjectFactory::SetSize(float size)
{
	this->size = size;
}
void PlayerObjectFactory::SetFrame(int frame)
{
	this->frame = frame;
}
void PlayerObjectFactory::SetIsAnimated(bool isAnimated)
{
	this->isAnimated = isAnimated;
}
void PlayerObjectFactory::SetIsShooting(bool isShooting)
{
	this->isShooting = isShooting;
}
void PlayerObjectFactory::SetIsAiming(bool isAiming)
{
	this->isAiming = isAiming;
}
void PlayerObjectFactory::SetIsFacingLeft(bool isFacingLeft)
{
	this->isFacingLeft = isFacingLeft;
}
void PlayerObjectFactory::SetIsSlow(bool isSlow)
{
	this->isSlow = isSlow;
}
void PlayerObjectFactory::SetIsDashing(bool isDashing)
{
	this->isDashing = isDashing;
}
void PlayerObjectFactory::SetPlayerNumber(int num)
{
	this->playerNumber = num;
}
void PlayerObjectFactory::SetAbilities(int order, int id)
{
	this->abilities[order] = id;
}
void PlayerObjectFactory::SetSlowness(int val)
{
	this->slowness = val;
}
void PlayerObjectFactory::SetDashSpeed(int val)
{
	this->dashSpeed = val;
}
void PlayerObjectFactory::Reset()
{
	currAnimState = PlayerObject::AnimationState::Idle;
	position = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);
	frame = 10;
	size = 256.f;
	isShooting = false;
	isAiming = false;
	isFacingLeft = true;
	isSlow = false;
	isDashing = false;
	isAnimated = true;

	playerNumber = 0;

	abilities[0] = 0;
	abilities[1] = 0;
	abilities[2] = 0;

	abilityCooldown[0] = 0;
	abilityCooldown[1] = 0;
	abilityCooldown[2] = 0;

	slowness = 2;
	slowDuration = 0;

	dashSpeed = 5;
	dashDuration = 0;
}
PlayerObject* PlayerObjectFactory::Create()
{
	PlayerObject* obj = new PlayerObject();
	obj->GetCollider()->SetCollisionType(Collider::Kinematic);
	obj->SetSpriteInfo(animList.find(PlayerObject::AnimationState::Idle)->second);
	obj->SetTexture(animList.find(PlayerObject::AnimationState::Idle)->second.texture);
	obj->SetIsAnimated(true);
	obj->GetSpriteRenderer()->SetFrame(this->frame);
	obj->SetSize(this->size, -this->size);
	obj->SetPosition(this->position);
	obj->SetPlayerNumber(this->playerNumber);
	obj->SetIsAnimated(this->isAnimated);
	
	for (auto it = animList.begin(); it != animList.end(); it++)
	{
		obj->SetAnimationSprite(it->first, it->second);
	}

	return obj;
}