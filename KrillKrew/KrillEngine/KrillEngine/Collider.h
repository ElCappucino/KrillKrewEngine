#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GizmosObject.h"

class ImageObject;

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
	ImageObject* parent;
	glm::vec3 previousPos;
	glm::vec3 offset;
	CollisionType collisionType;
	GizmosObject* gizmos;

	glm::vec3 size;
	glm::vec3 halfSize;

	bool isEnter = false;
	bool isExit = false;

public:


	Collider(CollisionType type, ImageObject* parent);
	void Update(glm::vec3 size, glm::vec3 position);
	GizmosObject* GetGizmos();
	glm::vec3 GetSize();
	glm::vec3 GetPreviousPos();
	ImageObject* GetParent();
	void SetPreviousPos(glm::vec3 pos);
	glm::vec3 GetHalfSize();
	void SetGismosColor(glm::vec3 color);
	CollisionType GetCollisionType();
	void SetCollisionType(CollisionType type);
	void setColliderSize(glm::vec3 size);

	glm::vec3 GetOffset() const;
	void SetOffset(float x, float y, float z);

};