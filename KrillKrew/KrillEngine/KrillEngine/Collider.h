#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GizmosObject.h"

class Collider {

private:

	// use pos and scale from Object class
	glm::vec3 previousPos;

	GizmosObject* gizmos;

	glm::vec3 size;
	glm::vec3 halfSize;

	bool isEnter = false;
	bool isExit = false;

public:

	Collider();
	void Update(glm::vec3 size, glm::vec3 position);
	GizmosObject* GetGizmos();
	glm::vec3 GetSize();
	glm::vec3 GetPreviousPos();
	glm::vec3 GetHalfSize();
	void SetGismosColor(glm::vec3 color);
	/*void OnColliderEnter();
	void OnColliderStay();
	void OnColliderExit();
	bool IsOverlap(Collider anotherCollider);
	bool IsInside(glm::vec3 pointPos);*/

};