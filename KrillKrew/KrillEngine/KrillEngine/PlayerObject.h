#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include <chrono>
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
	bool isAiming = false;
	int number;
	float cooldown[3];
	float slowness = 2;
	float durationSlowness;
	bool isSlowness;

public:
	
	PlayerObject();
	~PlayerObject();
	void SetTexture(std::string path);
	void SetSheetInfo(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void Render(glm::mat4 globalModelTransform);
	void setVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void setIsShooting(bool isShoot);
	void setIsAiming(bool isAim);
	void setNumber(int num);
	void setCooldown(int skill, int time);
	void reduceCooldown();
	void setDurationSlowness(int time);
	void reduceDurationSlowness();
	void setIsSlowness(bool isSlow);
	glm::vec3 getVelocity();
	bool getIsShooting();
	bool getIsAiming();
	Collider* GetCollider();
	int getNumber();
	float getCooldown(int skill);
	float getDurationSlowness();
	bool getIsSlowness();
};
