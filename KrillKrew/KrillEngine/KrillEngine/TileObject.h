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


#define MAP_WIDTH  20
#define MAP_HEIGHT 16


/// @brief The class for creating object that render using texture
class TileObject : public EntityObject
{

public:
	virtual enum AnimationState
	{
		Idle = 1,
		Breaking,
		FinishBreaking
	};

	AnimationState currAnimState;
private:

	bool isBreakable;
	bool isBroke;

	int maxDurability;
	int currentDurability;

	glm::ivec2 tilePos;
	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> *updateTile;
	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> *updateTile_lookup;

	ImageObject* crackOverlay;

	//Level* currentLevel;

protected:


	//Collider* collider;

public:

	TileObject();
	virtual ~TileObject();

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
	void SetTilePosition(int x, int y);
	void SetUpdateTileset(std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT>* tiles);
	
	void UpdateTileArray(int flag);
	void CheckIfBreak();
	void GotHit();
	void DisableOverlaySprite();
	void AddCollapseTileToScene();

	virtual Collider* GetCollider();
	ImageObject* GetOverlaySprite();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	virtual void UpdateSpriteSheetPosition();
};