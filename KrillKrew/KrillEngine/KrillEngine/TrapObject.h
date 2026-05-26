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
class TrapObject :public EntityObject
{

public:
	 enum TypeTrap
	 {
		Trap,
		Tnt
	 };

	 virtual enum AnimationState
	 {
		 Idle = 1,
		 Collide
	 };

private:
	int lifeTime;
	int playerNumOwner;
	bool CanKnockback;
	int type;
	bool isExplode;
	
	std::vector<TileObject*> TileInRange;

	AnimationState currAnimState;
	std::map<AnimationState, SpritesheetInfo> animList;

public:
	bool isActivate = false;
	TrapObject();
	virtual ~TrapObject();
	void Render(glm::mat4 globalModelTransform);
	void SetTexture(std::string path);
	void SetLifeTime(int lifeTime);
	void SetPlayerNumber(int Num);
	void ReduceLifeTime();
	void SetCanKnockback(bool isCanKnockback);
	void SetType(int type);
	void SetIsExplode(bool isExplode);

	int GetLifetime();
	int GetPlayerNumber();
	bool GetCanKnockback();
	bool GetType();
	bool GetIsExplode();

	void AddTileInRange(TileObject* tile);
	void DeleteTileInRange(TileObject* tile);
	void ExplodeTileInRange();
	void ChangeStateAfterCollide();

	virtual void UpdateCurrentAnimation();
	virtual void SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo);
	virtual void ChangeAnimationState(AnimationState anim);

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	virtual float getOrderingLayer() const;

};
