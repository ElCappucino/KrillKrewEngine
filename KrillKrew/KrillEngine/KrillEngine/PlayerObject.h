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
	glm::vec3 velocity;
	bool isShooting = false;

public:
	
	PlayerObject();
	~PlayerObject();
	void SetTexture(std::string path);
	void SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void Render(glm::mat4 globalModelTransform);
	void setVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void setisShooting(bool isShoot);
	glm::vec3 getVelocity();
	bool getIsShooting();
};
