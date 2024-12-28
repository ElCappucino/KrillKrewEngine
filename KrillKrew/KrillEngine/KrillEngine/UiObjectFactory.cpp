#include "UIObjectFactory.h"

void UiObjectFactory::SetSpriteInfo(SpritesheetInfo info)
{
	this->sheetInfo = info;
}
void UiObjectFactory::SetIsAnimated(bool isAnimated)
{
	this->isAnimated = isAnimated;
}
void UiObjectFactory::SetPosition(glm::vec3 pos)
{
	this->pos = pos;
}
void UiObjectFactory::SetSize(glm::vec3 size)
{
	this->size = size;
}
void UiObjectFactory::SetOwner(int owner)
{
	this->playerNumOwner = owner;
}
void UiObjectFactory::Reset()
{
	SpritesheetInfo placeholder("Xoey_UI", "../Resource/Texture/xoey.png", 430, 220, 430, 220);
	this->sheetInfo = placeholder;
	this->isAnimated = false;
	this->pos = glm::vec3(0, 0, 0);
	this->size = glm::vec3(215.f, -100.f, 0);
	this->playerNumOwner = 0;
}
UiObject* UiObjectFactory::CreateObject()
{
	UiObject* obj = new UiObject();
	obj->SetSpriteInfo(sheetInfo);
	obj->SetTexture(sheetInfo.texture);
	obj->SetIsAnimated(this->isAnimated);
	obj->SetPosition(this->pos);
	obj->SetSize(this->size.x, this->size.y);
	obj->setNumOwner(this->playerNumOwner);

	return obj;
}