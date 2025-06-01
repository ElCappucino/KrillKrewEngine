#include "Collider.h"
#include "ImageObject.h"

Collider::Collider(CollisionType type, ImageObject* parent)
{
	collisionType = type;
	this->parent = parent;

	gizmos = new GizmosObject();
	switch (type)
	{
		case CollisionType::Trigger:
			gizmos->SetColor(1.f, 0, 0);
			break;
		case CollisionType::Kinematic:
			gizmos->SetColor(0, 1.f, 0);
			break;
		case CollisionType::Static:
			gizmos->SetColor(0, 0, 1.f);
			break;
	}

	this->offset = glm::vec3(0, 0, 0);
	
}
void Collider::Update(glm::vec3 size, glm::vec3 position)
{
	this->size = size;
	//this->previousPos = position;
	this->halfSize = glm::vec3(size.x / 2, size.y / 2, 1);
	gizmos->SetSize(size.x, size.y);
	gizmos->SetPosition(position);
}

GizmosObject* Collider::GetGizmos()
{
	return gizmos;
}

glm::vec3 Collider::GetSize()
{
	return size;
}

glm::vec3 Collider::GetHalfSize()
{
	return halfSize;
}

glm::vec3 Collider::GetPreviousPos()
{
	return previousPos;
}
ImageObject* Collider::GetParent()
{
	return parent;
}
void Collider::SetPreviousPos(glm::vec3 pos)
{
	previousPos = pos;
}

Collider::CollisionType Collider::GetCollisionType()
{
	return collisionType;
}

void Collider::SetCollisionType(Collider::CollisionType type)
{
	collisionType = type;
	switch (type)
	{
	case CollisionType::Trigger:
		gizmos->SetColor(1.f, 0, 0);
		break;
	case CollisionType::Kinematic:
		gizmos->SetColor(0, 1.f, 0);
		break;
	case CollisionType::Static:
		gizmos->SetColor(0, 0, 1.f);
		break;
	}
}

void Collider::setColliderSize(glm::vec3 size) {
	this->size = size;
}

glm::vec3 Collider::GetOffset() const
{
	return this->offset;
}
void Collider::SetOffset(float x, float y, float z)
{
	this->offset = glm::vec3(x, y, z);
}