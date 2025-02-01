#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include <map>
#include "EntityObject.h"
#include <chrono>
#include <vector>
#include "ImageObject.h"
#include "Collider.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "UiObject.h"
#include "TileObject.h"

class TileObject;

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

	enum class Ability
	{
		Fireball = 0,
		Trap = 1,
		Dash = 2
	};

	enum class AbilityButton
	{
		Triangle = 0,
		Circle = 1,
		Cross = 2
		// Square is melee
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

	std::array<Ability, 3> abilities;
	float abilityCooldown[3] = {0};

	float slowness = 2;
	float slowDuration; // add value if slow and decrease over time
	
	float dashSpeed = 5;
	float dashDuration; // add value if dashing and decrease over time

	// UI
	UiObject* playerUI;
	Collider* attackCollider;
	
	std::vector<TileObject*> aimingTile;

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
	void SetAbility(AbilityButton numberAbility, Ability idAbility);
	void SetPlayerUI(UiObject* ui);

	void ReduceAbilityCooldown(AbilityButton button);
	void ReduceSlowDuration();
	void ReduceDashDuration();

	virtual void SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo);
	virtual void ChangeAnimationState(AnimationState anim);
	virtual void UpdateCurrentAnimation();


	virtual Collider* GetCollider() const;
	Collider* GetAttackCollider() const;

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
	float GetCooldown(AbilityButton button) const;
	float GetSlowDuration() const;
	float GetDashDuration() const;
	PlayerObject::Ability GetAbilityByButton(AbilityButton button) const;

	void AddAimingTile(TileObject* tile);
};
