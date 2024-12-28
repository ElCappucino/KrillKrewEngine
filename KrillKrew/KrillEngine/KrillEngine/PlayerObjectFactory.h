#pragma once
#include "PlayerObject.h"
#include "ObjectFactory.h"

class PlayerObjectFactory : public ObjectFactory
{
	PlayerObject::AnimationState currAnimState;
	std::map< PlayerObject::AnimationState, SpritesheetInfo> animList;
	glm::vec3 position;
	glm::vec3 velocity;
	int frame;
	float size;
	bool isShooting = false;
	bool isAiming = false;
	bool isFacingLeft = true;
	bool isSlow = false;
	bool isDashing = false;
	bool isAnimated = true;

	int playerNumber = 0;

	int abilities[3] = { 0 };
	float abilityCooldown[3] = { 0 };

	float slowness = 2;
	float slowDuration = 0; // add value if slow and decrease over time

	float dashSpeed = 5;
	float dashDuration = 0; // add value if dashing and decrease over time

public:
	void SetCurrentAnimState(PlayerObject::AnimationState state);
	void SetAnimationSprite(PlayerObject::AnimationState state, SpritesheetInfo spriteInfo);
	void SetPosition(glm::vec3 pos);
	void SetVelocity(glm::vec3 vel);
	void SetSize(float size);
	void SetFrame(int frame);
	void SetIsAnimated(bool isAnimated);
	void SetIsShooting(bool isShooting);
	void SetIsAiming(bool isAiming);
	void SetIsFacingLeft(bool isFacingLeft);
	void SetIsSlow(bool isSlow);
	void SetIsDashing(bool isDashing);
	void SetPlayerNumber(int num);
	void SetAbilities(int order, int id);
	void SetSlowness(int val);
	void SetDashSpeed(int val);
	void Reset();
	virtual PlayerObject* CreateObject();
};