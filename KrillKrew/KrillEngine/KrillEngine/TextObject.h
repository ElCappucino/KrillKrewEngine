#pragma once

#include "DrawableObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <SDL_ttf.h>
#include <string>

class TextObject :public DrawableObject
{
private:
	unsigned int texture;
	float w, h = 0.0f;

public:
	TextObject();
	~TextObject();
	void Render(glm::mat4 globalModelTransform);
	void update(float deltaTime);
	void loadText(std::string text, SDL_Color textColor, int fontSize);
	void InitSDL();
	void cleanSDL();

	virtual float getOrderingLayer() const;
};