#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "EntityObject.h"
#include "Collider.h"
#include "PlayerObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

/// @brief The class for creating object that render using texture
class ProjectileObject : public EntityObject
{
public:
	enum TypeProjectile
	{
		Fireball,
		Teleport
	};

	unsigned int texture;
	glm::vec3 velocity;
	int lifeTime;
	int playerNumOwner;
	bool isCanKnockback;
	int type;

public:
	ProjectileObject();
	~ProjectileObject();
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
	void setVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void setLifeTime(int lifeTime);
	void setNumOwner(int Num);
	void setOwner(PlayerObject* player);
	glm::vec3 getVelocity();
	void reduceLifeTime();
	int getLifetime();
	void setIsCanKnockback(bool isCanKnockback);
	bool getIsCanKnockback();
	void setType(int Type);
	bool getType();

	virtual Collider* GetCollider();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);
	
	int getNumOwner();
};
