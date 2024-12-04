#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "ImageObject.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Ability.h"
#include "InfoStruct.h"

/// @brief The class for creating object that render using texture
class EntityObject : public ImageObject
{
protected:
	
	Collider* collider;
	
public:

	EntityObject();
	~EntityObject();

	virtual void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	// void SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void Render(glm::mat4 globalModelTransform);

	virtual Collider* GetCollider();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);
};
