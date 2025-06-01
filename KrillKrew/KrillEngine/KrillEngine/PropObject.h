#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include <queue>

#include "SpriteRenderer.h"
#include "Collider.h"
#include "InfoStruct.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "EntityObject.h"
#include "PlayerHitboxObject.h"
#include "ParticleObject.h"


#define MAP_WIDTH  20
#define MAP_HEIGHT 16

class TileObject;

/// @brief The class for creating object that render using texture
class PropObject : public EntityObject
{

public:
	virtual enum AnimationState
	{
		Idle = 1,
		Breaking,
		FinishBreaking
	};

	enum PropType
	{
		Tiny,
		Small,
		Tree
	};

	AnimationState currAnimState;
	PropType propType;
	SpritesheetInfo propBreakSprite;
	std::vector<TileObject*> surroundTile;

private:

	int maxDurability;
	int currentDurability;

	bool isBreakable;

public:

	PropObject();
	virtual ~PropObject();

	// int(*groundTileInfo)[MAP_HEIGHT][MAP_WIDTH];

	virtual void SetSpriteInfo(SpritesheetInfo info);
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);

	/*virtual void SetSize(float sizeX, float sizeY);
	virtual void SetPosition(glm::vec3 newPosition);*/

	void CheckIfBreak();
	void GotHit();
	void CheckIfNoTileSurround();

	void SetIsBreakable(bool isBreakable);
	bool GetIsBreakable() const;

	virtual Collider* GetCollider();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	virtual void UpdateCollider();

	virtual void UpdateSpriteSheetPosition();

	virtual float getOrderingLayer() const;
};