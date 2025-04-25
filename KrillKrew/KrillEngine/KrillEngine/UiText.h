#pragma once
#include "TextObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <SDL_ttf.h>
#include <string>
#include "GameEngine.h"
#include "SquareMeshVbo.h"

/// @brief The class for creating object that render using texture
class UiText : public TextObject
{
	unsigned int texture;

public:
	UiText();
	~UiText();
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
};