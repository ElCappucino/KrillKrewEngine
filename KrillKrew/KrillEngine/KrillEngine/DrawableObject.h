#pragma once
#include "glm.hpp"
#include <vector>


/// @brief The class for creating drawable object
class DrawableObject
{
protected:
	glm::vec3 pos;
	glm::vec3 size;
	bool isActive = true;
public:
	glm::mat4 getTransform();
	bool GetIsActive();
	DrawableObject();
	~DrawableObject();
	virtual void Render(glm::mat4 globalModelTransform) = 0;
	void SetSize(float sizeX, float sizeY);
	void SetPosition(glm::vec3 newPosition);
	void Translate(glm::vec3 moveDistance);
	glm::vec3 getPos();
	glm::vec3 getSize();
	//Rotate, Scale ???

};

