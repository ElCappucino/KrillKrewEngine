#pragma once
#include <string>

struct OrthographicValue 
{
	float left;
	float right;
	float bottom;
	float top;
};

struct SpritesheetInfo 
{
	std::string name;
	std::string texture;
	float spritewidth; 
	float spriteheight; 
	float sheetwidth; 
	float sheetheight;
	bool isLoop;

	SpritesheetInfo()
	{
		this->name = "name";
		this->texture = "texture";
		this->spritewidth = 0;
		this->spriteheight = 0;
		this->sheetwidth = 0;
		this->sheetheight = 0;
		this->isLoop = false;
	}
	SpritesheetInfo(std::string name,
					std::string texture,
					float spritewidth, 
					float spriteheight, 
					float sheetwidth, 
					float sheetheight,
					bool isLoop = true)
	{
		this->name = name;
		this->texture = texture;
		this->spritewidth = spritewidth;
		this->spriteheight = spriteheight;
		this->sheetwidth = sheetwidth;
		this->sheetheight = sheetheight;
		this->isLoop = isLoop;
	}
};