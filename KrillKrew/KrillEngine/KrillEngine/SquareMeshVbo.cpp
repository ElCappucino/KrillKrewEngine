
#include "SquareMeshVbo.h"

std::string const SquareMeshVbo::MESH_NAME = "square";

void SquareMeshVbo::LoadData()
{
	//VBO data
	GLfloat vertexData[] =
	{
	  -0.5f, -0.5f,
	  0.5f, -0.5f,
	  0.5f,  0.5f,
	  -0.5f,  0.5f
	};

	GLfloat texData[] =
	{
	  0.5f, 0.0f,
	  1.0f, 0.0f,
	  1.0f, 1.0f,
	  0.5f, 1.0f
	};

	//Create VBO
	glGenBuffers(1, &(this->posVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->texVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), texData, GL_STATIC_DRAW);


}

void SquareMeshVbo::ChangeTextureData(float row, float column, float spritewidth, float spriteheight, float sheetwidth, float sheetheight) {
	
	GLfloat texData[] =
	{
	  column * spritewidth / sheetwidth,			row * spriteheight / sheetheight,
	  (column + 1) * spritewidth / sheetwidth,		row * spriteheight / sheetheight,
	  (column + 1) * spritewidth / sheetwidth,		(row + 1) * spriteheight / sheetheight,
	  column * spritewidth / sheetwidth,			(row + 1) * spriteheight / sheetheight
	};

	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), texData, GL_STATIC_DRAW);
}

SquareMeshVbo::SquareMeshVbo()
{
}

std::string SquareMeshVbo::GetMeshName()
{
	return MESH_NAME;
}

void SquareMeshVbo::Render()
{
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	if (this->texAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
		glVertexAttribPointer(this->texAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}