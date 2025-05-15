#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "EntityObject.h"
#include "Collider.h"
#include "PlayerObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

/// @brief The class for creating object that render using texture
class ProjectileObject : public EntityObject
{
public:
	enum TypeProjectile
	{
		Fireball = 1,
		Teleport,
		Bola,
		Cleave
	};

	virtual enum AnimationState
	{
		Idle = 1,
		Collide
	};

	AnimationState currAnimState;
	std::map<AnimationState, SpritesheetInfo> animList;

	glm::vec3 velocity;
	float lifeTime;
	PlayerObject* playerOwner;
	bool CanKnockback;
	TypeProjectile type;
	
	bool isShooting;
	bool CanStun;

	std::vector<TileObject*> TileInRange;

public:
	ProjectileObject();
	~ProjectileObject();
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
	virtual void SetSize(float sizeX, float sizeY);
	void SetVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void SetLifeTime(float lifeTime);
	void SetOwner(PlayerObject* player);

	glm::vec3 GetVelocity();
	void ReduceLifeTime(float dt);
	float GetLifetime();
	void SetCanKnockback(bool isCanKnockback);
	bool GetCanKnockback();
	PlayerObject* GetOwner();
	void SetType(TypeProjectile Type);
	TypeProjectile GetType();
	void SetIsShooting(bool isShooting);
	bool GetIsShooting();
	void SetIsCanStun(bool isCanStun);
	bool GetIsCanStun();

	void AddTileInRange(TileObject* tile);
	void DeleteTileInRange(TileObject* tile);
	void ExplodeTileInRange();

	virtual Collider* GetCollider();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	virtual void UpdateCurrentAnimation();
	virtual void SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo);
	virtual void ChangeAnimationState(AnimationState anim);
	virtual void UpdateCollider();
};
