#include "Collider.h"

Collider::Collider()
{
	

	gizmos = new GizmosObject();
	gizmos->SetColor(1.f, 0, 0);
	


}
void Collider::Update(glm::vec3 size, glm::vec3 position)
{
	// std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	this->size = size;
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
//void Collider::OnColliderEnter()
//{
//
//}
//void Collider::OnColliderStay()
//{
//
//}
//void Collider::OnColliderExit()
//{
//
//}
//bool Collider::IsOverlap(Collider anotherCollider)
//{
//
//}
//bool Collider::IsInside(glm::vec3 pointPos)
//{
//
//}