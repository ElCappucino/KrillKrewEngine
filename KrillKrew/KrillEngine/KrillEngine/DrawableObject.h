#pragma once
#include "glm.hpp"
#include <vector>
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

/// @brief The class for creating drawable object
class DrawableObject
{
protected:
	glm::vec3 pos;
	glm::vec3 size;
	int orderingLayer;
	bool isActive = true;
public:
	glm::mat4 getTransform();
	bool GetIsActive();
	void SetIsActive(bool isActive);
	DrawableObject();
	virtual ~DrawableObject();
	virtual void Render(glm::mat4 globalModelTransform) = 0;
	virtual void SetSize(float sizeX, float sizeY);
	virtual void SetPosition(glm::vec3 newPosition);
	void SetOrderingLayer(int layer);
	void Translate(glm::vec3 moveDistance);
	glm::vec3 getPos();
	glm::vec3 getSize();
	int getOrderingLayer() const;

	//Rotate, Scale ???

};

