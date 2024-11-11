#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GizmosObject.h"

class EntityObject;

class Collider {

public:

	enum CollisionType
	{
		Static,
		Kinematic,
		Trigger
	};

private:

	// use pos and scale from Object class
	EntityObject* parent;
	glm::vec3 previousPos;
	CollisionType collisionType;
	GizmosObject* gizmos;

	glm::vec3 size;
	glm::vec3 halfSize;

	bool isEnter = false;
	bool isExit = false;

public:


	Collider(CollisionType type);
	void Update(glm::vec3 size, glm::vec3 position);
	GizmosObject* GetGizmos();
	glm::vec3 GetSize();
	glm::vec3 GetPreviousPos();
	void SetPreviousPos(glm::vec3 pos);
	glm::vec3 GetHalfSize();
	void SetGismosColor(glm::vec3 color);
	CollisionType GetCollisionType();
	void SetCollisionType(CollisionType type);
	//void OnColliderEnter();
	//void OnColliderStay();
	//void OnColliderExit();
	//void OnTriggerEnter();
	//void OnColliderStay();
	//void OnColliderExit();
	bool IsOverlap(Collider anotherCollider);
	bool IsInside(glm::vec3 pointPos);

};