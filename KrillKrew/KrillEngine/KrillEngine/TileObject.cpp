#include "TileObject.h"
#include "PlayerObject.h"
#include "Level.h"

int BFSTile
(
	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT>& currentTile,
	int startX,
	int startY,
	int newFlag)
{
	int tileAmount = 0;
	std::queue<glm::vec2> checkQueue;
	checkQueue.emplace(glm::vec2(startX, startY));
	while (!checkQueue.empty())
	{
		glm::vec2 current = checkQueue.front();
		checkQueue.pop();
		if (current.x < 1 || current.x >= MAP_HEIGHT || current.y < 1 || current.y >= MAP_WIDTH)
			continue;
		if (currentTile[current.x][current.y] == 1)
		{
			tileAmount++;
			currentTile[current.x][current.y] = newFlag;
			checkQueue.push(glm::vec2(current.x - 1, current.y));
			checkQueue.push(glm::vec2(current.x + 1, current.y));
			checkQueue.push(glm::vec2(current.x, current.y - 1));
			checkQueue.push(glm::vec2(current.x, current.y + 1));
		}
	}

	return tileAmount;
}

void TileCollapseCheck(std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT>& currentTile)
{
	// create buffer copy from currentTile
	std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT> bufferTile = currentTile;

	// give replace value = 2
	int replaceVal = 2;

	// map int int store the amount of eachreplace tile
	std::map<int, int> adjacentSize;

	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		for (int j = 1; j < MAP_WIDTH - 1; j++)
		{
			// check tile
			if (bufferTile[i][j] != 1)// if not 1 skip
			{
				continue;
			}
			else
			{
				// if 1 bfs and replace it with replace value. updaate map[replace value] then replace value++
				int size = BFSTile(bufferTile, i, j, replaceVal);
				adjacentSize.emplace(replaceVal, size);
				replaceVal++;
				
			}

		}
	}
	// if (repalce value = 2, break the function
	if (replaceVal <= 3)
	{
		return;
	}

	int min = INT_MAX;
	int minFlag = -1;
	// loop through the map and check if which part has most adjacent tile
	for (auto it : adjacentSize)
	{
		if (min > it.second)
		{
			min = it.second;
			minFlag = it.first;
		}
	}

	// set the reference tile info to zero. change it to fall animation later.
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		for (int j = 1; j < MAP_WIDTH - 1; j++)
		{
			// check tile
			if (bufferTile[i][j] == minFlag)// if not 1 skip
			{
				currentTile[i][j] = 2;
			}

		}
	}
	
}

TileObject::TileObject()
{
	this->updateTile = nullptr;
	this->isBreakable = false;
	this->isBroke = false;
	this->collider = new Collider(Collider::Trigger, this);

	this->maxDurability = 3;
	this->currentDurability = 0;

	SpritesheetInfo crackEffectSprite = SpritesheetInfo("CrackEffect", "../Resource/Texture/tileCrack.png", 128, 128, 512, 128);

	this->crackOverlay = new ImageObject();
	this->crackOverlay->SetSpriteInfo(crackEffectSprite);
	this->crackOverlay->SetSize(128.f, -128.f);

	this->orderingLayer = 0;

	this->currAnimState = AnimationState::Idle;

}
TileObject::~TileObject()
{
	//delete collider;
	crackOverlay = nullptr;
	currentLevel = nullptr;
	updateTile = nullptr;
}

void TileObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}
void TileObject::SetTexture(std::string path)
{
	this->texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
	// KK_INFO(this->texture);
}

void TileObject::SetIsBreakable(bool isBreakable)
{
	this->isBreakable = isBreakable;
	if (!isBreakable)
	{
		this->crackOverlay->SetIsActive(false);
	}
}
void TileObject::SetIsBroke(bool isBroke)
{
	this->isBroke = isBroke;
}
bool TileObject::GetIsBreakable() const
{
	return isBreakable;
}
bool TileObject::GetIsBroke() const
{
	return isBroke;
}
void TileObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		std::cout << "Error: Can't perform transformation " << std::endl;
		return;
	}
	if (renderModeId == -1) {
		std::cout << "Error: Can't set renderMode in ImageObject " << std::endl;
		return;
	}

	squareMesh->ChangeTextureData(spriteRenderer->GetRow(),
		spriteRenderer->GetColumn(),
		spriteRenderer->GetSpriteWidth(),
		spriteRenderer->GetSpriteHeight(),
		spriteRenderer->GetSheetWidth(),
		spriteRenderer->GetSheetHeight());

	std::vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->Render();

	}
}

void TileObject::SetSize(float sizeX, float sizeY)
{
	size = glm::vec3(sizeX, sizeY, 1);
	this->collider->setColliderSize(size);
	crackOverlay->SetSize(sizeX, sizeY);

}
void TileObject::SetPosition(glm::vec3 newPosition)
{
	pos = newPosition;
	crackOverlay->SetPosition(newPosition);
}

Collider* TileObject::GetCollider()
{
	return this->collider;
}

ImageObject* TileObject::GetOverlaySprite()
{
	return this->crackOverlay;
}
void TileObject::SetTilePosition(int x, int y)
{
	this->tilePos.x = x;
	this->tilePos.y = y;
}

void TileObject::UpdateTileArray(int flag)
{
	(*updateTile)[tilePos.x][tilePos.y] = flag;
}
void TileObject::SetUpdateTileset(std::array<std::array<int, MAP_WIDTH>, MAP_HEIGHT>* tiles)
{
	this->updateTile = tiles;
}

void TileObject::DisableOverlaySprite()
{
	this->isBroke = true;
	this->isBreakable = false;
	this->crackOverlay->SetIsActive(false);
	this->GetCollider()->GetGizmos()->SetIsActive(false);
}
void TileObject::CheckIfBreak()
{
	if (currentDurability >= maxDurability)
	{
		// create tile falling animation object
		DisableOverlaySprite();

		UpdateTileArray(0);
		AddCollapseTileToScene();
		// this->SetIsActive(false);

		/*std::cout << "Check Before Collapse -----------------------------" << std::endl;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				std::cout << (*updateTile)[i][j] << ", ";
			}
			std::cout << std::endl;
		}*/

		TileCollapseCheck(*updateTile);

		/*std::cout << "Check After Collapse -----------------------------" << std::endl;

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				std::cout << (*updateTile)[i][j] << ", ";
			}
			std::cout << std::endl;
		}*/
	}
}
void TileObject::GotHit()
{
	currentDurability++;
	this->crackOverlay->GetSpriteRenderer()->ShiftColumn();
	CheckIfBreak();
}

void TileObject::OnColliderEnter(Collider* other)
{

}
void TileObject::OnColliderStay(Collider* other)
{

}
void TileObject::OnColliderExit(Collider* other)
{

}
void TileObject::OnTriggerEnter(Collider* other)
{
	
}
void TileObject::OnTriggerStay(Collider* other)
{

}
void TileObject::OnTriggerExit(Collider* other)
{

}

void TileObject::UpdateSpriteSheetPosition()
{
	if (currAnimState == AnimationState::Breaking)
	{
		this->GetSpriteRenderer()->ShiftColumn();
		currentDurability++;
	}
	if (currentDurability >= maxDurability)
	{
		this->currAnimState = TileObject::AnimationState::FinishBreaking;
		this->SetIsActive(false);
	}
}
void TileObject::AddCollapseTileToScene()
{
	if (currentLevel == nullptr)
	{
		KK_CORE_ERROR("TileObject: current level == nullptr");
		return;
	}
	SpritesheetInfo collapseTileSprite = SpritesheetInfo("CollapseTile", "../Resource/Texture/Props/prop_spr_vfx_smoke.png", 200, 200, 800, 200);
	TileObject* collapseTile = new TileObject();
	collapseTile->SetIsAnimated(true);
	collapseTile->currAnimState = AnimationState::Breaking;
	collapseTile->SetSize(256.f, -256.f);
	collapseTile->SetPosition(this->pos);
	collapseTile->GetSpriteRenderer()->SetFrame(10);
	collapseTile->SetSpriteInfo(collapseTileSprite);
	collapseTile->GetSpriteRenderer()->ShiftTo(this->GetSpriteRenderer()->GetRow(), this->GetSpriteRenderer()->GetColumn());

	currentLevel->AddEntityToScene(collapseTile);
}

