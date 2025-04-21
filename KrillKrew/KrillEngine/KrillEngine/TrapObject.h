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
class TrapObject :public EntityObject
{

public:
	 enum TypeTrap
	{
		Trap,
		Tnt
	};

private:
	int lifeTime;
	int playerNumOwner;
	bool CanKnockback;
	int type;
	
	std::vector<TileObject*> TileInRange;
public:
	bool isActivate = false;
	TrapObject();
	virtual ~TrapObject();
	void Render(glm::mat4 globalModelTransform);
	void SetTexture(std::string path);
	void SetLifeTime(int lifeTime);
	void SetPlayerNumber(int Num);
	void ReduceLifeTime();
	int GetLifetime();
	int GetPlayerNumber();
	void SetCanKnockback(bool isCanKnockback);
	bool GetCanKnockback();
	void SetType(int type);
	bool GetType();

	void AddTileInRange(TileObject* tile);
	void DeleteTileInRange(TileObject* tile);
	void ExplodeTileInRange();

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

};
