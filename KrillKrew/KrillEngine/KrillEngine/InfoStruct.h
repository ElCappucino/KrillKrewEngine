#pragma once
#include <string>

struct OrthographicValue 
{
	float left;
	float right;
	float bottom;
	float top;
};

struct CameraZoomInfo 
{
	float minZoom_horizontal; // minimum of the length between left and right
	float minZoom_vertical; // minimum of the length between bottom and top
	float maxZoom_horizontal; // maximum of the length between left and right
	float maxZoom_vertical; // maximum of the length between bottom and top
	float t; // use to calculate the zoom amount based on current projection and target projection. the value is between 0-1 
			 // (ex. t = 0.1 when using with a + (t * (b - a)) means that the zoom is increase 10% towards target projection every update time)
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