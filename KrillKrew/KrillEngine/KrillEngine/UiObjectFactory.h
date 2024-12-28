#pragma once
#include "UiObject.h"
#include "ObjectFactory.h"

class UiObjectFactory : public ObjectFactory
{
	SpriteRenderer* spriteRenderer;
	SpritesheetInfo sheetInfo;
	bool isAnimated;
	glm::vec3 pos;
	glm::vec3 size;
	int playerNumOwner;
public:
	void SetSpriteInfo(SpritesheetInfo info);
	void SetIsAnimated(bool isAnimated);
	void SetPosition(glm::vec3 pos);
	void SetSize(glm::vec3 size);
	void SetOwner(int owner);
	void Reset();
	UiObject* CreateObject();
};