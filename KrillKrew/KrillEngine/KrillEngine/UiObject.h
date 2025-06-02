#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <string>
#include <array>
#include "ImageObject.h"
#include "Collider.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

/// @brief The class for creating object that render using texture
class UiObject : public ImageObject
{

public:

	enum UIType
	{
		Default,
		Kraken,
		SkillIcon,
		SkillCover,
		PauseMenu,
		PauseText
	};

	UIType uiType = UIType::Default;

private:

	int playerNumOwner;
	bool isRender = true;

public:
	UiObject();
	virtual ~UiObject();
	void SetTexture(std::string path);
	void Render(glm::mat4 globalModelTransform);
	void setNumOwner(int Num);
	int getNumOwner();

	void SetIsRender(bool isRender);
	bool GetIsRender() const;

	virtual void OnColliderEnter(Collider* other);
	virtual void OnColliderStay(Collider* other);
	virtual void OnColliderExit(Collider* other);
	virtual void OnTriggerEnter(Collider* other);
	virtual void OnTriggerStay(Collider* other);
	virtual void OnTriggerExit(Collider* other);

	virtual float getOrderingLayer() const;
};
