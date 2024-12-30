#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "ImageObject.h"
#include "Collider.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

/// @brief The class for creating object that render using texture
class UiObject : public ImageObject
{
	int playerNumOwner;

public:
	UiObject();
	~UiObject();
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
	void setNumOwner(int Num);
	int getNumOwner();
};
#pragma once
