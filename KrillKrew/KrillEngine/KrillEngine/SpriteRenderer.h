#pragma once
#include <iostream>
#include <string>

class SpriteRenderer
{
private:
	std::string texture;

	float row;
	float column;
	float spritewidth;
	float spriteheight;
	float sheetwidth;
	float sheetheight;
public:
	void SetSpriteInfo(float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void ShiftColumn();
	void ShiftRow();
	void ShiftTo(float row, float column);
	float GetRow();
	float GetColumn();
	float GetSpriteWidth();
	float GetSpriteHeight();
	float GetSheetWidth();
	float GetSheetHeight();
	SpriteRenderer(std::string texture);
};