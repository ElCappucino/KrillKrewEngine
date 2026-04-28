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

	float frame;

	

public:

	bool isLoop;
	void SetSpriteInfo(float spritewidth, float spriteheight, float sheetwidth, float sheetheight);
	void SetTexture(std::string texture);
	void SetFrame(int frame);

	void ShiftColumn();
	void ShiftRow();
	void ShiftTo(float row, float column);

	float GetRow();
	float GetColumn();
	float GetSpriteWidth();
	float GetSpriteHeight();
	float GetSheetWidth();
	float GetSheetHeight();
	int GetFrame();

	SpriteRenderer(std::string texture);
};