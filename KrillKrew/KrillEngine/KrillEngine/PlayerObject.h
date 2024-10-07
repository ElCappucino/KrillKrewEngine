#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "ImageObject.h"
#include "Collider.h"
#include "Ability.h"

/// @brief The class for creating object that render using texture
class PlayerObject :public ImageObject
{
	unsigned int texture;
	SpritesheetInfo sheetInfo;
	Collider* hitbox;
	std::array<Ability*, 3> abilities;

public:
	PlayerObject();
	~PlayerObject();
	void SetTexture(string path);
	void SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void Render(glm::mat4 globalModelTransform);
};
