#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "GameEngine.h"
#include "SquareMeshVbo.h"

/// @brief The class for creating game object
/// @note There nothing implemented here yet.
class GameObject :public DrawableObject
{
	glm::vec3 color;

public:
	GameObject();
	~GameObject();
	void SetColor(float r, float g, float b);
	void Render(glm::mat4 globalModelTransform);
};

