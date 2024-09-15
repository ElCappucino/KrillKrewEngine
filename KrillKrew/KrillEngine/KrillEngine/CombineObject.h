#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

/// @brief The class for creating two shape combine to each other
class CombineObject :public DrawableObject
{
	glm::vec3 color;
	glm::vec3 color2;

public:
	/// @brief The constructor of combine object class. using for setup the default color
	CombineObject();
	/// @brief The Destructor of combine object class.
	/// @note There is no any command.
	~CombineObject();
	/// @brief The function to set the first object color
	/// @param r describe the r(rgb) value
	/// @param g describe the g(rgb) value
	/// @param b describe the b(rgb) value
	void SetColor(float r, float g, float b);
	/// @brief The function to set the second object color
	/// @param r describe the r(rgb) value
	/// @param g describe the g(rgb) value
	/// @param b describe the b(rgb) value
	void SetColor2(float r, float g, float b);
	/// @brief 
	/// @param globalModelTransform 
	void Render(glm::mat4 globalModelTransform);
};
