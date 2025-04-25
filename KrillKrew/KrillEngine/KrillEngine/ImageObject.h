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

/// @brief The class for creating object that render using texture
class ImageObject :public DrawableObject
{

protected:

	unsigned int texture;
	SpriteRenderer* spriteRenderer;
	SpritesheetInfo sheetInfo;
	bool isAnimated;

public:
	ImageObject();
	virtual ~ImageObject();
	SpriteRenderer* GetSpriteRenderer();
	void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);

	void SetIsAnimated(bool value);
	bool GetIsAnimated();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

};
