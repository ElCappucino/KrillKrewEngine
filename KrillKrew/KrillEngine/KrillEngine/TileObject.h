#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>

#include "SpriteRenderer.h"
#include "Collider.h"
#include "InfoStruct.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "EntityObject.h"
#include "PlayerHitboxObject.h"

#define MAP_WIDTH  21
#define MAP_HEIGHT 16

/// @brief The class for creating object that render using texture
class TileObject : public EntityObject
{
private:

	bool isBreakable;
	bool isBroke;

	int maxDurability;
	int currentDurability;

	/*int tilePositionX;
	int tilePositionY;*/

	ImageObject* crackOverlay;
	

protected:


	Collider* collider;

public:

	TileObject();
	~TileObject();

	// int(*groundTileInfo)[MAP_HEIGHT][MAP_WIDTH];

	virtual void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);

	virtual void SetSize(float sizeX, float sizeY);
	virtual void SetPosition(glm::vec3 newPosition);
	bool GetIsBreakable() const;
	bool GetIsBroke() const;
	void SetIsBroke(bool isBroke);
	void SetIsBreakable(bool isBreakable);
	/*void SetTilePosition(int x, int y);
	glm::vec2 GetTilePosition() const;*/
	void CheckIfBreak();
	void GotHit();

	virtual Collider* GetCollider();
	ImageObject* GetOverlaySprite();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);
};