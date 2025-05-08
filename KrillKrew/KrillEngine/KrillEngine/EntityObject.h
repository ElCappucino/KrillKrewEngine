#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "ImageObject.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "InfoStruct.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

/// @brief The class for creating object that render using texture
class EntityObject : public ImageObject
{
	virtual enum class AnimationState
	{
		Idle
	};

protected:

	
	Collider* collider;
	std::map<AnimationState, SpritesheetInfo> animList;
	AnimationState currAnimState;

public:

	EntityObject();
	virtual ~EntityObject();

	virtual void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	// void SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void Render(glm::mat4 globalModelTransform);

	virtual void SetSize(float sizeX, float sizeY);
	virtual Collider* GetCollider();
	virtual void setColliderSize(glm::vec3 size);
	
	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	virtual void SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo);
	virtual void ChangeAnimationState(AnimationState anim);
	virtual void UpdateCurrentAnimation();
	virtual void UpdateCollider();
};
