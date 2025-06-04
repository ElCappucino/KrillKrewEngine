#include "PropObject.h"
#include "Level.h"
#include "TileObject.h"
#include "SoundManager.h"

PropObject::PropObject()
{

	this->collider = new Collider(Collider::Trigger, this);

	this->maxDurability = 3;
	this->currentDurability = 0;
	//this->isAnimated = false; // change later
	//this->GetSpriteRenderer()->SetFrame(10);

	this->orderingLayer = 3;

	this->currAnimState = AnimationState::Idle;
}
PropObject::~PropObject()
{

}

// int(*groundTileInfo)[MAP_HEIGHT][MAP_WIDTH];

void PropObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}
void PropObject::SetTexture(std::string path)
{
	this->texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}
void PropObject::Render(glm::mat4 globalModelTransform)
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

//virtual void SetSize(float sizeX, float sizeY);
//virtual void SetPosition(glm::vec3 newPosition);

void PropObject::CheckIfBreak()
{
	if (currentDurability >= maxDurability)
	{
		currAnimState = AnimationState::Breaking;

		//SpritesheetInfo collapseTileSprite = SpritesheetInfo("CollapseTile", "../Resource/Texture/Props/prop_spr_vfx_smoke.png", 200, 200, 800, 200);

		if (propType == PropType::Tree)
		{
			std::vector<ParticleObject*> particleList;

			int particleAmount = 7;
			for (int i = 0; i < particleAmount; i++)
			{
				particleList.push_back(new ParticleObject());
			}

			for (int i = 0; i < particleAmount; i++)
			{
				particleList[i]->SetSpriteInfo(propBreakSprite);
				//breakEffect->SetSpriteInfo(propBreakSprite);
				glm::vec3 position = glm::vec3
				(
					this->pos.x,
					(this->pos.y + (this->size.y / 2.f)) + ((i * (-this->size.y) / (float)particleAmount)),
					0.f
				);

				particleList[i]->SetPosition(position);
				particleList[i]->SetSize(particleList[i]->GetSpriteRenderer()->GetSpriteWidth() * 2.f, particleList[i]->GetSpriteRenderer()->GetSpriteHeight() * 2.f);
				this->currentLevel->AddEntityToScene(particleList[i]);
			}
		}
		else
		{
			ParticleObject* particle = new ParticleObject();
			particle->SetSpriteInfo(propBreakSprite);

			particle->SetPosition(this->pos);
			particle->SetSize(particle->GetSpriteRenderer()->GetSpriteWidth(), particle->GetSpriteRenderer()->GetSpriteHeight());
			this->currentLevel->AddEntityToScene(particle);
			KrillSoundManager::SoundManager::GetInstance()->PlaySFX("Rock_Destroyed", false);
			KK_TRACE("PropObject:destroy Prop");
		}

		

		this->isActive = false;
	}
}
void PropObject::GotHit()
{
	if (isBreakable)
	{
		currentDurability++;
		CheckIfBreak();
	}
	
}

void PropObject::CheckIfNoTileSurround()
{
	for (TileObject* tile : surroundTile)
	{
		if (tile->GetIsBroke())
		{
			auto it = std::find(surroundTile.begin(), surroundTile.end(), tile);
			if (it != surroundTile.end())
			{
				surroundTile.erase(it);
			}
		}
	}
	if (surroundTile.empty())
	{
		//KK_TRACE("PropObject: surroundTile.empty()");
		currentDurability = maxDurability;
		CheckIfBreak();
	}
	
}
void PropObject::SetIsBreakable(bool isBreakable)
{
	this->isBreakable = isBreakable;
}
bool PropObject::GetIsBreakable() const
{
	return this->isBreakable;
}
Collider* PropObject::GetCollider()
{
	return this->collider;
}

void PropObject::UpdateCollider()
{
	if (propType == PropType::Tree)
	{
		glm::vec3 size = glm::vec3(this->getSize().x / 4.f, this->getSize().x / 4.f, 0);
		glm::vec3 pos = glm::vec3(this->getPos().x, this->getPos().y , 0);
		this->GetCollider()->Update(size, pos);
	}
	else
	{
		this->GetCollider()->Update(this->getSize(), this->getPos());
	}
}


void PropObject::OnColliderEnter(Collider* other)
{
	TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());

	if (tile != nullptr)
	{
		surroundTile.push_back(tile);

	}
}
void PropObject::OnColliderStay(Collider* other) 
{

}
void PropObject::OnColliderExit(Collider* other) 
{
	/*TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());

	if (tile != nullptr)
	{
		auto it = std::find(surroundTile.begin(), surroundTile.end(), tile);
		if (it != surroundTile.end())
		{
			surroundTile.erase(it);
		}
	}*/
}
void PropObject::OnTriggerEnter(Collider* other) 
{

}
void PropObject::OnTriggerStay(Collider* other) 
{

}
void PropObject::OnTriggerExit(Collider* other) 
{

}

void PropObject::UpdateSpriteSheetPosition() 
{

}

float PropObject::getOrderingLayer() const {
	return this->pos.y + (this->size.y / 2.f);
	//if (propType == PropType::Small)
	//{
	//	return this->pos.y;
	//}
	//else if (propType == PropType::Tree)
	//{
	//	//KK_CORE_INFO("pos.y = {0} Size y = {1} order = {2}", this->pos.y, this->size.y, this->pos.y + this->size.y);
	//	return this->pos.y + (this->size.y / 2.f);
	//}
	
}