#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include "InfoStruct.h"

/// @brief The class for creating object that render using texture
class ImageObject :public DrawableObject
{
	unsigned int texture;
	SpritesheetInfo sheetInfo;

public:
	ImageObject();
	~ImageObject();
	void SetTexture(std::string path);
	void SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void Render(glm::mat4 globalModelTransform);
};
