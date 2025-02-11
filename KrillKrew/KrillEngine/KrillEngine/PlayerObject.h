#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include <map>
#include "EntityObject.h"
#include <chrono>
#include "ImageObject.h"
#include "Collider.h"
#include "Ability.h"

/// @brief The class for creating object that render using texture
class PlayerObject :public EntityObject
{
public:
	virtual enum class AnimationState
	{
		Idle,
		Running,
		Melee,
		Shooting,
		PlaceItem
	};

private:

	AnimationState currAnimState;
	std::map<AnimationState, SpritesheetInfo> animList;
	//std::array<Ability*, 3> abilities;
	int abilities[3] = { 0 };
	glm::vec3 velocity;
	bool isShooting;
	bool isAiming;
	bool isFacingLeft;
	int number;
	float cooldown[3] = {0};
	float slowness = 2;
	float durationSlowness;
	bool isSlowness;
	bool isDash;
	float dashSpeed = 5.f;
	float durationDash;
	bool isKnockback;
	float durationKnockback;
	bool xIsPositive;
	bool yIsPositive;
	bool isTNT;

public:
	
	PlayerObject();
	~PlayerObject();
	void UpdateFacingSide(bool isLeft);
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
	void setVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void setIsShooting(bool isShoot);
	void setIsAiming(bool isAim);
	void setNumber(int num);
	void setCooldown(int skill, int time);
	void reduceCooldown(int skill);
	void setDurationSlowness(int time);
	void reduceDurationSlowness();
	void setIsSlowness(bool isSlow);
	void setIsDash(bool isDash);
	void setDurationDash(int time);
	void reduceDurationDash();
	bool getIsShooting();
	void setAbility(int numberAbility, int idAbility);
	void setIsKnockback(bool isKnockback);
	void setDurationKnockback(int time);
	void reduceDurationKnockback();
	void setIsTNT(bool isTNT);

	virtual void SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo);
	virtual void ChangeAnimationState(AnimationState anim);
	virtual void UpdateCurrentAnimation();

	virtual Collider* GetCollider();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);
	
	glm::vec3 getVelocity();
	bool getXIsPositive();
	bool getYIsPositive();
	bool getIsAiming();
	int getNumber();
	float getCooldown(int skill);
	float getDurationSlowness();
	bool getIsSlowness();
	bool getIsDash();
	float getDurationDash();
	int getIdAbility(int numberAbility);
	bool getIsKnockback();
	float getDurationKnockback();
	bool getIsTNT();
};
