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

	SpritesheetInfo()
	{
		this->name = "name";
		this->texture = "texture";
		this->spritewidth = 0;
		this->spriteheight = 0;
		this->sheetwidth = 0;
		this->sheetheight = 0;
	}
	SpritesheetInfo(std::string name,
					std::string texture,
					float spritewidth, 
					float spriteheight, 
					float sheetwidth, 
					float sheetheight)
	{
		this->name = name;
		this->texture = texture;
		this->spritewidth = spritewidth;
		this->spriteheight = spriteheight;
		this->sheetwidth = sheetwidth;
		this->sheetheight = sheetheight;
	}
};