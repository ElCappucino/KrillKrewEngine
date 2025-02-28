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
		Fireball = 1,
		Teleport,
		Bola,
		Cleave
	};

	glm::vec3 velocity;
	float lifeTime;
	PlayerObject* playerOwner;
	bool isCanKnockback;
	int type;
	bool isShooting;
	bool isCanStun;

public:
	ProjectileObject();
	~ProjectileObject();
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);

	void SetVelocity(float axisX, float axisY, bool isPositiveX, bool isPositiveY);
	void SetLifeTime(float lifeTime);
	//void setNumOwner(int Num);
	void SetOwner(PlayerObject* player);

	glm::vec3 GetVelocity();
	void ReduceLifeTime();
	int GetLifetime();
	void SetIsCanKnockback(bool isCanKnockback);
	bool GetIsCanKnockback();
	PlayerObject* GetOwner();
	void SetType(int Type);
	int GetType();
	void SetIsShooting(bool isShooting);
	bool GetIsShooting();
	void SetIsCanStun(bool isCanStun);
	bool GetIsCanStun();

	virtual Collider* GetCollider();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

};
