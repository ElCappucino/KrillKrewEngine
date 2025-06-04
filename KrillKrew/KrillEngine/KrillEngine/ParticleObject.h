#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include "InfoStruct.h"
#include "SpriteRenderer.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "Collider.h"
#include "EntityObject.h"

/// @brief The class for creating object that render using texture
class ParticleObject :public EntityObject
{
public:

	virtual enum AnimationState
	{
		idle,
		Init
	};

	virtual enum ParticleType
	{
		SmallProp,
		BigProp,
		Tentacle
	};
	ParticleType type;
	AnimationState currAnimState;
private:

	
	std::map<AnimationState, SpritesheetInfo> animList;
	

public:

	ParticleObject();
	virtual ~ParticleObject();

	virtual void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);

	virtual void SetColliderSize(glm::vec3 size);

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	virtual void UpdateCurrentAnimation();
	virtual void UpdateCollider();
	virtual void UpdateSpriteSheetPosition();
	virtual void SetAnimationSprite(ParticleObject::AnimationState state, SpritesheetInfo spriteInfo);

	virtual void ChangeAnimationState(AnimationState anim);

	virtual float getOrderingLayer() const;
};
