#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include <map>
#include <chrono>
#include <vector>
#include <cstdlib>

#include "Collider.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "UiObject.h"
#include "EntityObject.h"
#include "PlayerGroundColliderObject.h"
#include "ProjectileObject.h"
#include "TrapObject.h"


class PlayerHitboxObject;
class TileObject;
class ProjectileObject;
class TrapObject;
class PropObject;

/// @brief The class for creating object that render using texture
class PlayerObject : public EntityObject
{
public:
	virtual enum class AnimationState
	{
		
		//Running,
		//Melee,
		//Shooting,

		Idle, // Done
		FellDown, // Done
		Stun, // Done
		GetHit, // Done
		PlaceItem, // Done
		Cast, // Done

		Move_Back, // Done
		Move_Front, // Done
		Move_Side, // Done
		
		Smash_DiagDown, // Done
		Smash_DiagUp, // Done
		Smash_Down, // Done
		Smash_Side, // Done
		Smash_Up, // Done
		
		Dash_Back,
		Dash_Front,
		Dash_Side,
		Cleave_Down,
		Cleave_Up,
		Cleave_Side,
		
	};

	enum class Ability
	{
		Fireball = 0,
		Trap = 1,
		Dash = 2,
		TNT = 3,
		Teleport = 4,
		Bola = 5,
		Cleave = 6
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
	std::vector<ProjectileObject*> ownProjectile;
	std::vector<TrapObject*> ownTrap;

	// Slow Status
	ImageObject* slowStatusObject;
	
	glm::vec3 velocity;
	glm::vec2 currDirection;

	bool isShooting;
	bool isAiming;
	bool isFacingLeft;
	bool isSlow;
	bool isDashing;
	bool isOnGround;
	bool isFell;

	int playerNumber;

	std::array<Ability, 3> abilities;
	std::array<float, 3> abilityCooldown = {0};
	float meleeCooldown = 0;

	float slowness = 2;
	float slowDuration; // add value if slow and decrease over time
	
	float dashSpeed = 2;
	float dashDuration; // add value if dashing and decrease over time

	// UI
	UiObject* playerUI;
	PlayerHitboxObject* attackCollider;
	PlayerGroundColliderObject* groundCheckCollider;
	
	std::vector<TileObject*> aimingTile;
	std::vector<PropObject*> aimingProp;
	float durationSlowness;
	bool isSlowness;
	bool isDash;
	bool isKnockback;
	float durationKnockback;
	bool xIsPositive;
	bool yIsPositive;
	bool isTNT;
	int holdingProjectile = 0;
	bool isStun;
	float durationStun;
	

public:
	
	float projectileHoldDuration = 0;

	PlayerObject();
	virtual ~PlayerObject();
	
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
	void UpdateFacingSide(bool isLeft);

	void SetVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void SetIsShooting(bool isShooting);
	void SetIsAiming(bool isAiming);
	void SetPlayerNumber(int num);
	void SetAbilityCooldown(PlayerObject::AbilityButton button, int duration);
	void SetSlowDuration(int time);
	void SetIsSlow(bool isSlow);
	void SetIsDashing(bool isDashing);
	void SetDashDuration(float duration);
	void SetAbility(AbilityButton numberAbility, Ability idAbility);
	void SetPlayerUI(UiObject* ui);
	void SetCurrentDirection(glm::vec2 dir);


	void SetIsKnockback(bool isKnockback);
	void SetKnockbackDuration(int time);
	void SetIsTNT(bool isTNT);
	void SetHoldingProjectile(int projectile);
	void SetIsStun(bool isStun);
	void SetStunDuraion(int time);
	void SetIsOnGround(bool isOnGround);

	void ReduceAbilityCooldown(int button, float dt);
	void ReduceSlowDuration(float dt);
	void ReduceDashDuration(float dt);
	void ReduceKnockbackDuration(float dt);
	void ReduceStunDuration(float dt);
	

	virtual void SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo);
	virtual void ChangeAnimationState(AnimationState anim);
	virtual void UpdateCurrentAnimation();
	virtual void UpdateCollider();
	virtual void UpdateSpriteSheetPosition();
	void ChangeMeleeAnimation();

	virtual Collider* GetCollider() const;
	Collider* GetAttackCollider() const;
	PlayerHitboxObject* GetAttackColliderObject() const;
	Collider* GetGroundCollider() const;
	PlayerGroundColliderObject* GetGroundColliderObject() const;

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
	float GetCooldown(PlayerObject::AbilityButton button) const;
	float GetSlowDuration() const;
	float GetDashDuration() const;
	glm::vec2 GetCurrentDirection() const;
	float GetStunDuration() const;
	bool GetIsOnGround() const;
	bool GetIsFell() const;

	PlayerObject::Ability GetAbilityByButton(AbilityButton button) const;


	void ClearAimingTile(TileObject* tile);
	void AddAimingTile(TileObject* tile);

	void ClearAimingProp(PropObject* prop);
	void AddAimingProp(PropObject* prop);

	void HitAimingTile();
	bool GetXIsPositive();
	bool GetYIsPositive();
	bool GetIsKnockback();
	float GetDurationKnockback();
	bool GetIsTNT();
	int GetHoldingProjectile();
	bool GetIsStun();

	bool GetMeleeCooldown() const;
	void SetMeleeCooldown(float duration);

	void CheckIfOnGround();

	void ApplyKnockback(EntityObject* obj);
	void UpdateAbilityCooldown(float dt);

	// Owning trap and projectile will remove owning when object is destroyed
	std::vector<ProjectileObject*> GetOwningProjectile() const;
	void AddOwningProjectile(ProjectileObject* projectile);
	void RemoveOwningProjectile(ProjectileObject* projectile);

	std::vector<TrapObject*> GetOwningTrap() const;
	void AddOwningTrap(TrapObject* trap);
	void RemoveOwningTrap(TrapObject* trap);

	virtual float getOrderingLayer() const;
};
