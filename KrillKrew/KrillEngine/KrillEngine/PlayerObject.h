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
	
	glm::vec3 velocity;

	bool isShooting;
	bool isAiming;
	bool isFacingLeft;
	bool isSlow;
	bool isDashing;

	int playerNumber;

	int abilities[3] = { 0 };
	float abilityCooldown[3] = {0};

	float slowness = 2;
	float slowDuration; // add value if slow and decrease over time
	
	float dashSpeed = 5;
	float dashDuration; // add value if dashing and decrease over time

public:
	
	PlayerObject();
	~PlayerObject();
	
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
	void UpdateFacingSide(bool isLeft);

	void SetVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void SetIsShooting(bool isShooting);
	void SetIsAiming(bool isAiming);
	void SetPlayerNumber(int num);
	void SetAbilityCooldown(int skill, int duration);
	void SetSlowDuration(int time);
	void SetIsSlow(bool isSlow);
	void SetIsDashing(bool isDashing);
	void SetDashDuration(int duration);
	void SetAbility(int numberAbility, int idAbility);

	void ReduceAbilityCooldown(int skill);
	void ReduceSlowDuration();
	void ReduceDashDuration();

	virtual void SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo);
	virtual void ChangeAnimationState(AnimationState anim);
	virtual void UpdateCurrentAnimation();

	virtual Collider* GetCollider() const;

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);
	
	glm::vec3 GetVelocity() const;
	bool GetIsAiming() const;
	bool GetIsSlow() const;
	bool GetIsDashing() const;
	bool GetIsShooting() const;
	int GetPlayerNumber() const;
	float GetCooldown(int skill) const;
	float GetSlowDuration() const;
	float GetDashDuration() const;
};
