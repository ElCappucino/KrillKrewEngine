#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "EntityObject.h"
#include "Collider.h"
#include "Ability.h"

/// @brief The class for creating object that render using texture
class TrapObject :public EntityObject
{
	int lifeTime;
	int playerNumOwner;

public:
	TrapObject();
	~TrapObject();
	void Render(glm::mat4 globalModelTransform);
	void SetTexture(std::string path);
	void setLifeTime(int lifeTime);
	void setNumOwner(int Num);
	void reduceLifeTime();
	int getLifetime();
	int getNumOwner();

};