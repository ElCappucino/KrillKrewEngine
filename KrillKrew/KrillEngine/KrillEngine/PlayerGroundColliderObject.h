#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>

#include "ImageObject.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "InfoStruct.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
// #include "PlayerObject.h"
#include "EntityObject.h"
#include "TileObject.h"

class PlayerObject;

/// @brief The class for creating object that render using texture
class PlayerGroundColliderObject : public EntityObject
{
private:

	PlayerObject* parent;
	glm::vec2 colliderOffset;

protected:

	Collider* collider;

public:

	PlayerGroundColliderObject(PlayerObject* parent);
	~PlayerGroundColliderObject();

	virtual void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);

	virtual void SetSize(float sizeX, float sizeY);
	virtual void SetPosition(glm::vec3 newPosition);
	void SetCollisionOffset(glm::vec2 newOffset);

	virtual Collider* GetCollider();
	glm::vec2 GetColliderOffset() const;

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);
};