#include "UiObject.h"

UiObject::UiObject()
{
    SpritesheetInfo placeholder("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
    this->sheetInfo = placeholder;
    this->isAnimated = false;
    this->pos = glm::vec3(0, 0, 0);
    this->size = glm::vec3(215.f, -100.f, 0);
    this->playerNumOwner = 0;

    this->orderingLayer = 4;
}

UiObject::~UiObject()
{
}

void UiObject::SetTexture(std::string path)
{
    texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void UiObject::SetIsRender(bool isRender)
{
    this->isRender = isRender;
}
bool UiObject::GetIsRender() const
{
    return this->isRender;
}
void UiObject::ShiftSpriteTo(int row, int col)
{
    this->GetSpriteRenderer()->ShiftTo(row, col);
}
void UiObject::Render(glm::mat4 globalModelTransform)
{
    if (! isRender)
    {
        return;
    }

    RenderTexturedObject(globalModelTransform);
}

void UiObject::setNumOwner(int num)
{
    playerNumOwner = num;
}

int UiObject::getNumOwner()
{
    return playerNumOwner;
}

void UiObject::OnColliderEnter(Collider* other)
{
}
void UiObject::OnColliderStay(Collider* other)
{
}
void UiObject::OnColliderExit(Collider* other)
{
}
void UiObject::OnTriggerEnter(Collider* other)
{
}
void UiObject::OnTriggerStay(Collider* other)
{
}
void UiObject::OnTriggerExit(Collider* other)
{
}

float UiObject::getOrderingLayer() const
{
    switch (uiType)
    {
        case SkillIcon:
            return -2100.0f;
            break;
        case SkillCover:
            return -2200.0f;
            break;
        case PauseMenu:
            return -2500.0f;
            break;
        case PauseText:
            return -2600.0f;
            break;
        case AreYouSureBG:
            return -2900.0f;
            break;
        case YesNoButton:
            return -3000.0f;
            break;
        case Knob:
            return -3100.0f;
            break;
        default:
            return -2000;
            break;
    }
}
