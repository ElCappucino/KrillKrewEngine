#include "ParticleObject.h"

ParticleObject::ParticleObject() 
{
	isAnimated = true;
	collider = new Collider(Collider::Trigger, this);
	collider->setColliderSize(this->size);
	spriteRenderer = new SpriteRenderer("");
	this->pos = glm::vec3(0, 0, 0);

	this->orderingLayer = -2000;
		
	currAnimState = AnimationState::idle;
	type = ParticleType::BigProp;

	this->spriteRenderer->ShiftTo(0, 0);
	this->spriteRenderer->SetFrame(10);
	this->SetSize(this->spriteRenderer->GetSpriteWidth(), this->spriteRenderer->GetSpriteHeight());

	//this->SetTexture("../Resource/Texture/Props/prop_spr_vfx_leaf.png");
}
ParticleObject::~ParticleObject() 
{

}

void ParticleObject::SetTexture(std::string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}


void ParticleObject::Render(glm::mat4 globalModelTransform)
{
	RenderTexturedObject(globalModelTransform);
}

void ParticleObject::SetSpriteInfo(SpritesheetInfo info)
{
	this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
	this->SetTexture(info.texture);
}

void ParticleObject::SetColliderSize(glm::vec3 size) 
{

}
void ParticleObject::OnColliderEnter(Collider* other) 
{

}
void ParticleObject::OnColliderStay(Collider* other) 
{

}
void ParticleObject::OnColliderExit(Collider* other) 
{

}
void ParticleObject::OnTriggerEnter(Collider* other) 
{

}
void ParticleObject::OnTriggerStay(Collider* other) 
{

}
void ParticleObject::OnTriggerExit(Collider* other) 
{

}
void ParticleObject::UpdateSpriteSheetPosition()
{
	//KK_TRACE("ParticleObject: UpdateSpriteSheetPosition");
	this->GetSpriteRenderer()->ShiftColumn();
}
void ParticleObject::SetAnimationSprite(ParticleObject::AnimationState state, SpritesheetInfo spriteInfo)
{
	animList.insert({ state, spriteInfo });
}
void ParticleObject::UpdateCurrentAnimation() 
{
	//KK_CORE_WARN("ParticleObject: UpdateCurrentAnimation");
	//KK_CORE_WARN("ParticleObject: Position = {0} {1} {2}", this->pos.x, this->pos.y, this->pos.z);
	int currentColumn = this->GetSpriteRenderer()->GetColumn();
	float lastFrame = (GetSpriteRenderer()->GetSheetWidth() / GetSpriteRenderer()->GetSpriteWidth()) - 1;

	if (currentColumn == lastFrame)
	{
		if (type == ParticleType::Tentacle)
		{
			ChangeAnimationState(AnimationState::idle);
		}
		else
		{
			this->SetIsActive(false);
		}
		
	}
}

void ParticleObject::ChangeAnimationState(AnimationState anim)
{
	if (currAnimState != anim)
	{
		currAnimState = anim;
		this->SetTextureWithID(animList.find(anim)->second, animList.find(anim)->second.textureid);
		this->spriteRenderer->SetTexture(animList.find(anim)->second.texture);
		//this->SetTexture(animList.find(anim)->second.texture);
		this->spriteRenderer->ShiftTo(0, 0);
		this->spriteRenderer->isLoop = animList.find(anim)->second.isLoop;
	}
}

void ParticleObject::UpdateCollider() 
{

}

float ParticleObject::getOrderingLayer() const
{
	return 1000;
}
