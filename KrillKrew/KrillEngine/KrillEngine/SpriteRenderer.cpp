#include "SpriteRenderer.h"

void SpriteRenderer::SetSpriteInfo(float spritewidth, float spriteheight, float sheetwidth, float sheetheight)
{
	this->spritewidth = spritewidth;
	this->spriteheight = spriteheight;
	this->sheetwidth = sheetwidth;
	this->sheetheight = sheetheight;
}
void SpriteRenderer::SetTexture(std::string texture)
{
	this->texture = texture;
}
void SpriteRenderer::SetFrame(int frame)
{
	this->frame = frame;
}
void SpriteRenderer::ShiftColumn()
{
	if (column == (sheetwidth / spritewidth) - 1)
	{
		if (isLoop)
		{
			column = 0;
		}
	}
	else 
	{
		column++;
	}
}
void SpriteRenderer::ShiftRow()
{
	if (row == (sheetheight / spriteheight) - 1)
	{
		row = 0;
	}
	else
	{
		row++;
	}
}
void SpriteRenderer::ShiftTo(float row, float column)
{
	if (row <= - 1)
	{
		row = (sheetheight / spriteheight) - 1;
	}
	if (column <= -1)
	{
		if (isLoop)
		{
			column = (sheetwidth / spritewidth) - 1;
		}
	}

	this->row = row;
	this->column = column;
}
SpriteRenderer::SpriteRenderer(std::string texture)
{
	this->texture = texture;

	this->row = 0;
	this->column = 0;
	this->spritewidth = 0;
	this->spriteheight = 0;
	this->sheetwidth = 0;
	this->sheetheight = 0;

	this->isLoop = true;
}

float SpriteRenderer::GetRow()
{
	return row;
}
float SpriteRenderer::GetColumn()
{
	return column;
}
float SpriteRenderer::GetSpriteWidth()
{
	return spritewidth;
}
float SpriteRenderer::GetSpriteHeight()
{
	return spriteheight;
}
float SpriteRenderer::GetSheetWidth()
{
	return sheetwidth;
}
float SpriteRenderer::GetSheetHeight()
{
	return sheetheight;
}
int SpriteRenderer::GetFrame()
{
	return frame;
}