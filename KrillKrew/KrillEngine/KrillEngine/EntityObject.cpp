
#include "EntityObject.h"



EntityObject::EntityObject()
{
	isAnimated = false;
	collider = new Collider(Collider::Trigger, this);
	collider->setColliderSize(this->size);
	
	spriteRenderer = new SpriteRenderer("");
	this->pos = glm::vec3(0, 0, 0);

	this->orderingLayer = 2;
}


EntityObject::~EntityObject()
{
	delete collider;
	collider = nullptr;
	animList.clear();
}

void EntityObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void EntityObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->SetTexture(info.texture);
	spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	
}

void EntityObject::Render(glm::mat4 globalModelTransform)
{
	RenderTexturedObject(globalModelTransform);
}

void EntityObject::SetSize(float sizeX, float sizeY)
{
	size = glm::vec3(sizeX, sizeY, 1);
	this->collider->setColliderSize(size);
}
Collider* EntityObject::GetCollider()
{
	return collider;
}

void EntityObject::setColliderSize(glm::vec3 size) {
	collider->setColliderSize(size);
}

void EntityObject::OnColliderEnter(Collider* other)
{
	// std::cout << "On Collider Enter" << std::endl;
}
void EntityObject::OnColliderStay(Collider* other)
{
	// std::cout << "On Collider Stay" << std::endl;
}
void EntityObject::OnColliderExit(Collider* other)
{
	// std::cout << "On Collider Exit" << std::endl;
}
void EntityObject::OnTriggerEnter(Collider* other)
{
	// std::cout << "On Trigger Enter" << std::endl;
}
void EntityObject::OnTriggerStay(Collider* other)
{
	// std::cout << "On Trigger Enter" << std::endl;
}
void EntityObject::OnTriggerExit(Collider* other)
{
	// std::cout << "On Trigger Enter" << std::endl;
}

void EntityObject::SetAnimationSprite(AnimationState state, SpritesheetInfo spriteInfo)
{
	animList.insert({ state, spriteInfo });
}
void EntityObject::ChangeAnimationState(AnimationState anim)
{
	auto animation = animList.find(anim);

	if (animation == animList.end() || this->spriteRenderer == nullptr)
	{
		return;
	}

	if (currAnimState != anim)
	{
		currAnimState = anim;
		this->SetTextureWithID(animation->second, animation->second.textureid);
		this->spriteRenderer->SetTexture(animation->second.texture);
	}
}
void EntityObject::UpdateCurrentAnimation()
{
	//std::cout << "Update Animation Entity" << std::endl;
}

void EntityObject::UpdateCollider()
{
	if (this->GetCollider() == nullptr)
	{
		return;
	}

	this->GetCollider()->Update(this->GetCollider()->GetSize(), this->getPos());
}

void EntityObject::UpdateSpriteSheetPosition()
{
	this->GetSpriteRenderer()->ShiftColumn();
	//this->UpdateCurrentAnimation();
}

void EntityObject::LocateCurrentLevel(Level* currLevel)
{
	KK_CORE_INFO("EntityObject: LocateCurrentLevel");
	currentLevel = currLevel;

	if (currentLevel == nullptr)
	{
		KK_CORE_ERROR("EntityObject: currentLevel == nullptr");
	}
}
