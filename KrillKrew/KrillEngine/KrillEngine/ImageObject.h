#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include "InfoStruct.h"
#include "SpriteRenderer.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

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
	~ImageObject();
	SpriteRenderer* GetSpriteRenderer();
	void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);

	void SetIsAnimated(bool value);
	bool GetIsAnimated();

};
