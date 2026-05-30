#include "PlayerGroundColliderObject.h"
#include "PlayerObject.h"

PlayerGroundColliderObject::PlayerGroundColliderObject(PlayerObject* parent)
{
    this->parent = parent;
    this->collider = new Collider(Collider::Trigger, parent);
    this->isAnimated = false;

    glm::vec3 attackSize = glm::vec3(parent->getSize().x / 2, parent->getSize().y / 4, 0);
    glm::vec3 attackPos = glm::vec3(parent->getPos().x, parent->getPos().y - 128.f, 0);
    this->size = attackSize;
    this->pos = attackPos;

    this->collider->Update(attackSize, attackPos);

    this->colliderOffset = glm::vec2(0, -96.f);

    SpritesheetInfo hitboxSprite = SpritesheetInfo("hitbox", "../Resource/Texture/marker01.png", 500, 500, 500, 500);

    this->SetSpriteInfo(hitboxSprite);

    this->orderingLayer = 2;
}
PlayerGroundColliderObject::~PlayerGroundColliderObject()
{
    parent = nullptr;
}

void PlayerGroundColliderObject::SetSpriteInfo(SpritesheetInfo info)
{
    this->spriteRenderer->SetSpriteInfo(info.spritewidth, info.spriteheight, info.sheetwidth, info.sheetheight);
    this->SetTexture(info.texture);
}
void PlayerGroundColliderObject::SetTexture(std::string path)
{
    this->texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}
void PlayerGroundColliderObject::Render(glm::mat4 globalModelTransform)
{
    RenderTexturedObject(globalModelTransform);
}

void PlayerGroundColliderObject::SetSize(float sizeX, float sizeY)
{
    this->size = glm::vec3(sizeX, sizeY, 0);
}
void PlayerGroundColliderObject::SetPosition(glm::vec3 newPosition)
{
    this->pos = newPosition;
}
void PlayerGroundColliderObject::SetCollisionOffset(glm::vec2 newOffset)
{
    this->colliderOffset = newOffset;
}
Collider* PlayerGroundColliderObject::GetCollider()
{
    return this->collider;
}
glm::vec2 PlayerGroundColliderObject::GetColliderOffset() const
{
    return this->colliderOffset;
}
void PlayerGroundColliderObject::OnColliderEnter(Collider* other)
{
    TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());
    if (tile != nullptr && tile->GetIsBroke() == false)
    {
        // KK_TRACE("Player {0} is On Ground", this->parent->GetPlayerNumber());
        this->parent->SetIsOnGround(true);
    }
}
void PlayerGroundColliderObject::OnColliderStay(Collider* other)
{
    TileObject* tile = dynamic_cast<TileObject*>(other->GetParent());
    if (tile != nullptr && tile->GetIsBroke() == false)
    {
        // KK_TRACE("Player {0} is On Ground", this->parent->GetPlayerNumber());
        this->parent->SetIsOnGround(true);
    }
}
void PlayerGroundColliderObject::OnColliderExit(Collider* other)
{
}
void PlayerGroundColliderObject::OnTriggerEnter(Collider* other)
{
}
void PlayerGroundColliderObject::OnTriggerStay(Collider* other)
{
}
void PlayerGroundColliderObject::OnTriggerExit(Collider* other)
{
}